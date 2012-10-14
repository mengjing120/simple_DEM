#include <stdio.h>
#include <math.h>

/* Structure declarations and function prototypes */
#include "header.h"

/* Global and constant simulation properties */
#include "global_properties.h"


int main(int argc, char* argv[])
{

  printf("\n## simple_DEM ##\n");
  printf("Particles: %d\n", np);
  printf("maxStep: %d\n", maxStep);


  double time = 0.0;	/* Time at simulation start */

  /* Allocate memory */
  grain g[np];		/* Grain structure */


  /* Compute simulation domain dimensions */
  double wleft  = 0.0;			/* Left wall */
  double wright = (npw+1)*2*rmax; 	/* Right wall */
  double wdown  = 0.0;			/* Lower wall */
  double wup	= (np/npw+1)*2*rmax;	/* Upper wall */

  /* Variables for pressures on walls */
  double wp_up, wp_down, wp_left, wp_right;

  /* Initiailze grains inside the simulation domain */
  triangular_grid(g);



  /* Main time loop */
  int step;
  for (step = 0; step < maxStep; ++step) {

    time += dt;	/* Update current time */

    /* Predict new kinematics */
    prediction(g);

    /* Calculate contact forces between grains */
    interact_grains(g);

    /* Calculate contact forces between grains and walls */
    interact_walls(g, wleft, wright, wup, wdown, &wp_up, &wp_down, &wp_left, &wp_right);

    /* Update acceleration from forces */
    update_acc(g);

    /* Correct velocities */
    correction(g);

    /* Write output files if the fileInterval is reached */
    if (step % fileInterval == 0) {
      (void)vtk_export_grains(g, step);
      (void)vtk_export_forces(g, step);
    }

  } /* End of main time loop */


  /* Free dynamically allocated memory */
  /*free(g);*/
  

  printf("\nSimulation ended without errors.\n");
  return 0;	/* Terminate successfully */
}

