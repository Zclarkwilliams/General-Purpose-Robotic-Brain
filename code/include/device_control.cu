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

	//float I_leak, G_m, E_r, V;

	//int m, m_inf, I_NaP, A_m, S_m, E_m;

	//int h, h_dot, h_inf, A_h, S_h, E_h;


/*	I_leak = G_m * (E_r - V);
	
	for(int i=0;i<numinputs;i++){
		I_syn = I_syn + (G_s[i] * (E_s[i] - V));
	};

	m_inf = 1/(1 + A_m * exp(A_m * (V - E_m)));
	
	
	h_inf = 1/(1 + A_h * exp(A_h * (V - E_h)));

	I_NaP = G_Na * m_inf * h * (E_Na - V);
*/

};