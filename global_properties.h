#ifndef GLOBAL_PROPERTIES_H_
#define GLOBAL_PROPERTIES_H_

/* Properties of sample */
static const int np = 1000; 		/* Number of particles */

/* Size distribution */
static const double rmin = 1.0e-3;	/* Min. radius */
static const double rmax = 2.0e-3; 	/* Max. radius */

/* Properties of grains */
static const double kn = 1.0e5;		/* Normal stiffness */
static const double nu = 30.0;		/* Normal damping */
static const double rho = 1000.0;	/* Density of the grains */
static const double mu = 0.5;		/* Sliding friction */
static const double kt = 1.0e5;		/* Tangential stiffness */

/* Temporal variables */
static const double dt = 5.0e-5;	/* Time step lenpth */
static const int maxStep = 3000;	/* Number of steps */
static const int fileInterval = 20;	/* No. of steps between output */

/* Physical constants */
static const double grav = 9.80;	/* Gravity magnitude */

/* Number of particles along the width in the initial configuration */
static const int npw = 50;

#endif
