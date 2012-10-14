#ifndef GLOBAL_CONSTANTS_H_
#define GLOBAL_CONSTANTS_H_

// Properties of sample
const int ng = 5000; 		// Number of grains

// Size distribution
const double rmin = 1e-3;	// Min. radius
const double rmax = 2e-3; 	// Max. radius

// Properties of grains
const double kn = 1e5;		// Normal stiffness
const double nu = 30;		// Normal damping
const double rho = 1000;	// Density of the grains
const double mu = 0.5;		// Sliding friction
const double kt = kn;		// Tangential stiffness

// Temporal variables
const double dt = 1e-4;		// Time step length
const int maxStep = 3000;	// Number of steps
const int fileInterval = 20;	// No. of steps between output

// Physical constants
const double grav = 9.80;	// Gravity

// Number of grains along the width in the initial configuration
const int ngw = 100;

#endif

