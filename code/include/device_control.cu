/**
*	DeviceControl.cpp
*	This is the device functions and math functions to run the neuromorphic model.
*
*/

#include <cuda.h>
#include <cuda_runtime_api.h>

__global__ 
//void getOrganismData(NeuralModel::Organisms* org_ptr) {
void getOrgData(NeuralModel::Organisms* org_ptr) {
	
	/*
	 *	Neural Equations 
	 * 		1. C_m(dV/dt)	= I_leak + I_sym + I_app
	 * 		2. I_leak 		= G_m * (E_r - V)
	 *		3. I_sym 		= SUM_i=1->n(G_s,i * (E_s,i - V))
	 *						  { 0,					   				  if V_pre < E_lo
	 * 		4. G_s,i		= { g_s,i * (V_pre - E_lo)/(E_hi - E_lo), if E_lo < V_pre < E_hi
	 *				  		  { g_s,i,				   				  if V_pre > E_hi
	 *
	 *				  G_s,i	^
	 *						|	  	  |-R-|    
	 *				 g_s,i -|            /------>
	 *						|	    	/ 
	 *						|          /
	 *	    			 0 -| --------/
	 *	 					----------|---|-------> V_pre
	 *								E_lo E_hi
	 *
	 * 	**~20% of neurons will use these equations
	 * 		5. I_NaP		= G_Na * m_infinity(V) * h * (E_Na - V)
	 * 		6. h_dot 		= (h_inifinity - h) / tao_h(V)
	 * 		7. z_infinity 	= 1 / (1 + A_z * exp(S_z * (V - E_z)))
	 * 		8. tao_h(V) 	= tao_h_,_max * h_infinity(V) * sqrt(A_h * exp(S_z * (V - E_z))
	 * 		9. G_s,i 		= g_i * min(max((V_pre-E_lo,i)/(E_hi,i - E_lo,i),0),1)
	 */

	const float A_h = 0.5;
	const float A_m = 1.0;
	const float m = 0.0;
	const float h = 1.0;
	
	const float E_Na = 0.5; // Adjust to be found from org.neuron.CaEqilPot variable from config_parser
	
	float 	I_leak, I_sym, I_app;

	float 	m_inf, S_m, E_m; 
	float 	h_dot, h_inf, S_h, E_h;
	float 	E_r, E_lo, E_hi;
	float	V_noise, V_pre, V_post; 
	float	C_m, G_m, I_NaP, Tau, R;
	float 	G_s, g_s, g, E_s;

	int		num_neurons, num_synaptic_connexions;

	// 1. 
	C_m 	= Membrane_Capacitance(R[i], Tau[i]);
	
	// 2. 
	I_leak	= Leak_Current(V, E_r[i], R[i]);

	// 3.
	I_sym	= Synaptic_Current(V, V_noise[i], R[i], g_s[i], E_s[i], I_app);
	
	// 4.
	G_s 	= Synaptic_Conductance(V, g_s[i], E_lo[i], E_hi[i]);
	
	// 5.
	I_NaP	= Sodium_Current(V, G_Na, h, E_h[i]);
	
	// 6.
	h_dot	= H_Dot(h, tau_h, A_h, S_h, E_h);
	
	// 7.
	G_s		= G_s(g, V_pre, E_lo[i], E_hi[i]);
};

float Leak_Current(float V, E_r, R){
	return(I_leak	=  (E_r - V) / (R * 10^6));
};

float Synaptic_Current(float V, V_noise, R, g_s, E_s, I_app){
	float I_sym = 0.0;
	for(int i=0; i<num_synaptic_connexions; i++){
		V 		= V_noise + (I_app * R);
		I_sym	= I_sym + (g_s * (E_s - V));
	}
	return I_sym;
};

float Membrane_Capacitance(float R, Tau){
	return(1 / (R * Tau));
};

float Synaptic_Conductance(float V_pre, g_s, E_lo, E_hi){
	if(V_pre < E_lo){
		return(0);
	}
	else if (V_pre > E_hi){
		return(g_s);
	}
	else{
		return(g_s * ((V_pre - E_lo) / (E_hi - E_lo)));
	}
};

float Z_Infinity(float z, A_z, S_z, E_z){
	return a / (1 + A_z * exp(S_z * (V - E_z)))
};

float Sodium_Current(float V, G_Na, h, E_m){
	float m_infinity = Z_Infinity(m, A_m, S_m, E_m);
	return (G_Na * m_infinity * h * (E_r - V));
};

float H_Dot(float h, tau_h, A_h, S_h, E_h){
	float h_infinity = Z_Infinity(h, A_h, S_h, E_h);
	return ((h_infinity - h) / tau_h);
};

float G_s(float g, V_pre, E_lo, E_hi){
	float g_max = max(((V_pre - E_lo) / (E_hi - E_lo)),0);
	float g_min = min(g_max, 1);
	return (g * g_min);
};