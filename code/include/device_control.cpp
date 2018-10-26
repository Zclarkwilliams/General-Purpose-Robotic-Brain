/**
*	DeviceControl.cpp
*	This is the device functions and math functions to run the neuromorphic model.
*
*/

// Standard libraries
#include <algorithm>
#include <iostream>

// Non-Standard Libraries
#include "config_data.hpp"

//#include <cuda.h>
//#include <cuda_runtime_api.h>

/*
 *	Membrane Capacitance Equation
 *		C_m = (R*tau)^-1
 *				R	: Neuron Input Resistance
 *				tau	: Time constant for voltage decay from capacitance
 */
//__global__
double Membrane_Capacitance(double R, double Tau) {
	return(1 / (R * Tau));
};

/*
 *	Leak Current Equation 
 *		I_leak = G_m * (E_r - V)
 *				G_m	: Conductance of the neuron cell membrane
 *					G_m = 1/(size * 10^6)
 *						size : Input resistance portional to membrane size
 *				E_r : Neuron membrane resting potential lacking any synaptic input
 */
 //__global__
double Leak_Current(double V,  double E_r, double R) {
	return((E_r - V) / (R * pow(10, 6)));
};

/*
 *	Synaptic Input Current Stimulation
 *		I_sym = SUMMATION ( g_s[i] * (E_s[i] - V)) from i = 0 to number of synaptic connexions
 *			g_s	: Maximum synaptic channel conductance 
 *			E_s	: Synaptic channel charge potential equilibrium
 */
 //__global__
double Synaptic_Current(SimulationModel::Neurons * neur_ptr, SimulationModel::Organisms * org_ptr, double R, double * I_app) {
	double V	 = 0.0;
	double I_sym = 0.0;

	// Get the number of synaptic connections
	int num_synapses = neur_ptr->connexionVector.size();
	// vecotize the synaptic connexion data, creating a matrix of data
	std::vector<double>	g_s, E_s, E_lo, E_hi;
	// copy the synapseID to match for correct calculation data
	std::vector<std::string> synapseid;
	// get the size of a string to copy the data from string -> int
	std::string::size_type sz; //alias of size_t

	// Step through all the synaptic connexions, ascertaining characteristic data vector matrices
	int l = 0;
	for (auto j = neur_ptr->connexionVector.begin(); j != neur_ptr->connexionVector.end(); ++j) {
		synapseid.emplace_back(j->synapsetypeid);
		for (auto k = org_ptr->nonspikingVector.begin(); k != org_ptr->nonspikingVector.end(); ++k) {
			if (synapseid[l].compare(k->id) == 0) {
				E_s.emplace_back(std::stod(k->equil, &sz));
				g_s.emplace_back(std::stod(k->synamp, &sz));
				E_lo.emplace_back(std::stod(k->threshv, &sz));
				E_hi.emplace_back(std::stod(k->saturatev, &sz));
			}
			l++;
		}
	}

	// copy the applied current to aclulate with
	double I_in = (*I_app);
	double V_noise = std::stod(neur_ptr->noise, &sz);

	// perform summation across all synaptic connextion inputs
	for (int i = 0; i < num_synapses; i++) {
		V = V_noise + (I_in * R) + neur_ptr->V;
		I_sym = I_sym + (g_s[i] * (E_s[i] - V));
	}
	return I_sym;
};

/*
 *	Synaptic Conductance Input
 *					{ 0,					   				 if V_pre < E_lo
 * 		G_s[i]	=	{ g_s[i] * (V_pre - E_lo)/(E_hi - E_lo), if E_lo < V_pre < E_hi
 *					{ g_s[i]				   				 if V_pre > E_hi
 *			V_pre : Pre-Synaptic votlage, voltage from sending neuron
 *			g_s	  : Maximum synaptic channel conductance 
 *			E_lo  : Resting potential of the receiving neuron 
 *			E_hi  : Saturation potential of the receiving neuron
 */
 //__global__
double Synaptic_Conductance(SimulationModel::Neurons * neur_ptr, SimulationModel::Organisms * org_ptr, double V_pre) {
	// Get the synapse we are calculating output charge for
	std::vector<std::string> synapseid;
	std::vector<std::string> targetid;
	std::vector<double> E_s;
	std::vector<double> g_s;
	std::vector<double> E_lo;
	std::vector<double> E_hi;
	std::string::size_type sz; //alias of size_t

	// Step through all the synaptic connexions, ascertaining characteristic data vector matrices
	int l = 0;
	for (auto j = neur_ptr->connexionVector.begin(); j != neur_ptr->connexionVector.end(); ++j) {
		synapseid.emplace_back(j->synapsetypeid);
		targetid.emplace_back(j->targetid);
		for (auto k = org_ptr->nonspikingVector.begin(); k != org_ptr->nonspikingVector.end(); ++k) {
			if (synapseid[l].compare(k->id) == 0) {
				E_s.emplace_back(std::stod(k->equil, &sz));
				g_s.emplace_back(std::stod(k->synamp, &sz));
				E_lo.emplace_back(std::stod(k->threshv, &sz));
				E_hi.emplace_back(std::stod(k->saturatev, &sz));
			}
			l++;
		}
	}

	// Calculate the piecewise funtion for each synaptic connexion output for the neuron 
	//	issuing to the synaptic conductance vector specific to that neuron
	for (int k = 0; k < E_s.size(); k++) {
		for (auto i = org_ptr->neuronVector.begin(); i != org_ptr->neuronVector.end(); ++i) {
			if (targetid[k].compare(i->id) != 0) {
				if (V_pre < E_lo[k]) {
					i->G_s[k] = 0.0;
				}
				else if (V_pre > E_hi[k]) {
					i->G_s[k] = g_s[k];
				}
				else {
					i->G_s[k] = g_s[k] * ((V_pre - E_lo[k]) / (E_hi[k] - E_lo[k]));
				}
			}
			else {
				std::cout << "ERROR: Target ID was not found while calculating the synaptic_conductance" << targetid[k] << std::endl;
				return 1;
			}
		}
	}
		return 0;
};

/*
 *	Sodium Channel Deactivation(h)/Activation(m) Equation
 * 		z_infinity 	= 1 / (1 + A_z * exp(S_z * (V - E_z)))
 * 		9. G_s,i 		= g_i * min(max((V_pre-E_lo,i)/(E_hi,i - E_lo,i),0),1)
 *			g_s	: Maximum synaptic channel conductance
 *			E_s	: Synaptic channel charge potential equilibrium
 */
 //__global__
double Z_Infinity(double V, double z, double A_z, double S_z, double E_z) {
	return (1 / (1 + A_z * exp(S_z * (V - E_z))));
};

/*
 *	Sodium Channel Current
 *		I_NaP = G_Na * m_infinity(V) * h * (E_Na - V)
 *			G_Na		: Sodium channel conductance
 *			E_Na		: Sodium channel equilibrium/resting potential
 *			h			: Deactivation scaler
 *			m_infinity	: Sodium channel activation voltage
 */
 //__global__
double Sodium_Current(double V, double G_Na, double E_r, double h, double m, double A_m, double S_m, double E_m) {
	double m_infinity = Z_Infinity(V, m, A_m, S_m, E_m);
	return (G_Na * m_infinity * h * (E_r - V));
};

/*
 *	Deactivation Time Constant at Charge Potential V(t)
 *		tau_h(V) = tau_h * h_infinity(V) * sqrt(A_h * exp(S_h * (V - E_h))
 *			tau_h			: Deactivation time constant of sodium channel
 *			A_h, S_h, E_h	: Specific parameters to deactivation of neuron
 */
 //__global__
double H_Time_Const(double V, double h, double tau_h, double A_h, double S_h, double E_h) {
	double h_inf = Z_Infinity(V, h, A_h, S_h, E_h);
	return (tau_h * h_inf * sqrt(A_h * exp(S_h * (V - E_h))));
};

/*
 *	Synaptic Input Current Stimulation
 *		h_dot = (h_inifinity - h) / tau_h(V)
 *			h			: Deactivation scaler
 *			tau_h		: Deactivation time constant of sodium channel
 *			h_infinity	: Sodium channel deactivation voltage
 */
 //__global__
double H_Dot(double V, double h, double tau_h, double A_h, double S_h, double E_h) {
	double h_infinity = Z_Infinity(V, h, A_h, S_h, E_h);
	double tau_h = H_Time_Const(V, h, tau_h, A_h, S_h, E_h);
	return ((h_infinity - h) / tau_h);
};

/*
 *	Synaptic Input Conductance of the i'th Synapse
 *		G_s[i] = g[i] * min( max( (V_pre - E_lo[i]) / (E_hi[i] - E_lo[i]) ,0) ,1)
 *			g[i]	: Synaptic conductance of the i'th channel (SynAmp)
 *			V_pre[i]: Pres-Synaptic charge of the sending neuron
 *			E_lo[i]	: Resting potential of the receiving neuron 
 *			E_hi[i]	: Saturation potential of the receiving neuron
 */
 //__global__
double Synaptic_Conductance(double g, double V_pre, double E_lo, double E_hi) {
	double g_max = std::max(((V_pre - E_lo) / (E_hi - E_lo)), 0.0);
	double g_min = std::min(g_max, 1.0);
	return (g * g_min);
};


//__global__ 
//void getOrganismData(NeuralModel::Organisms* org_ptr) {
int getOrgData(SimulationModel::Organisms * org_ptr, std::string input_node_id, double * I_app, bool quit = false) {
	
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
	 * 	**These are the sodium synaptic channel equations (~20%) of neurons will use these
	 * 		5. I_NaP		= G_Na * m_infinity(V) * h * (E_Na - V)
	 * 		6. h_dot 		= (h_inifinity - h) / tau_h(V)
	 * 		7. z_infinity 	= 1 / (1 + A_z * exp(S_z * (V - E_z)))
	 * 		8. tau_h(V) 	= tau_h_,_max * h_infinity(V) * sqrt(A_h * exp(S_z * (V - E_z))
	 * 		9. G_s,i 		= g_i * min(max((V_pre-E_lo,i)/(E_hi,i - E_lo,i),0),1)
	 */

	double G_Na;
	double h	= 1.0;
	double A_h	= 0.5;
	double m	= 0.0;
	double A_m	= 1.0;
	
	const double E_Na = 0.5; // Adjust to be found from org.neuron.CaEqilPot variable from config_parser
	
	double 	I_leak, I_sym, I_app;

	double 	m_inf, S_m, E_m; 
	double 	h_dot, h_inf, S_h, E_h, tau_h;
	double 	G_s, g, E_r;
	double	V_noise, V_pre, V_post; 
	double	C_m, G_m, I_NaP, Tau, R;
	double	Voltage;
	
	std::vector<std::string> next_neuron;
	std::string current_neuron;
	int l = 0;

	std::string::size_type sz; //alias of size_t
	
	//copy the input neuron id to utilize in function
	current_neuron = input_node_id;

	while (!quit) {// unless user wants to quit or timer triggered quit, loop this process
		for (auto i = org_ptr->neuronVector.begin(); i != org_ptr->neuronVector.end(); ++i) {
			if (i->id.compare(current_neuron) == 0) {
				// Assign the neuron characteristics to the equation counter-parts
				R = std::stod(i->size, &sz);
				Tau = std::stod(i->timeconst, &sz);
				E_r = std::stod(i->restingpot, &sz);
				V_noise = std::stod(i->noise, &sz);
				Voltage = V_noise + i->V;

				// 1. 
				C_m = Membrane_Capacitance(R, Tau);

				// 2. 
				I_leak = Leak_Current(Voltage, E_r, R);

				// 3.
				I_sym = Synaptic_Current((SimulationModel::Neurons *) &i, org_ptr, R, I_app);

				// 4.
				G_s = Synaptic_Conductance((SimulationModel::Neurons *) &i, org_ptr, Voltage);

				// 5.
				I_NaP = Sodium_Current(Voltage, G_Na, E_r, h, m, A_m, S_m, E_m);

				// 6.
				h_dot = H_Dot(Voltage, h, tau_h, A_h, S_h, E_h);

				// 7.
				G_s = Synaptic_Conductance((SimulationModel::Neurons *) &i, org_ptr, Voltage);

				// Set the next neurons to attend to
				int k = 0;
				if (next_neuron.empty() == true) {
					next_neuron.clear();//empty the vector to reload
					for (auto j = i->connexionVector.begin(); j != i->connexionVector.end(); ++j) {
						next_neuron.emplace_back(j->targetid);
					}
				}
				else if (current_neuron.compare(next_neuron[]) != 0) {
					l = 0; // reset vector index
					next_neuron.clear();//empty the vector to reload
					for (auto j = i->connexionVector.begin(); j != i->connexionVector.end(); ++j) {
						next_neuron.emplace_back(j->targetid); // not sure this is right but need to reload the next set of neurons to proceed to
					}
				}
				// set the next current neuronal id to address
				current_neuron = next_neuron[l];
				// incrememnt to look at next neuron id in vector
				l++;
				// break for loop of current id to re-loop to find next neuron to calculate with
				break;
			}
		}
	}
	return 0; // we will return all the organism data so we can update plots and other monitoring windows
};