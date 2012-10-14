#ifndef HEADER_H_
#define HEADER_H_

/* Structure declarations */

struct grain
{
  double m; 		/* Mass */
  double R;		/* Radius */
  double I; 		/* Inertia */
  double x, y, th;	/* Position */
  double vx, vy, vth;	/* Velocities */
  double ax, ay, ath;	/* Acceleration */
  double fx, fy, fth;	/* Sum of forces, decomposed */
  double p;		/* Pressure */
};



/* Prototype functions */

/* initialize.cpp */
void triangular_grid(grain* g);

/* grains.cpp */
void prediction(grain* g);
void interparticle_force(grain* g, int a, int b);
void interact_grains(grain* g);
void update_acc(grain* g);
void correction(grain* g);

/* walls.cpp */
void compute_force_upper_wall(int i, grain* g, double wfy, double wupy);
void compute_force_lower_wall(int i, grain* g, double wfy, double wloy);
void compute_force_left_wall(int i, grain* g, double wfy, double wlex);
void compute_force_right_wall(int i, grain* g, double wfy, double wrix);


/* vtk_export.cpp */
int vtk_export_grains(grain* g, int numfile);
/*int vtk_export_walls(int numfile, double wlex, double wrix, double wloy, double wupy);*/
int vtk_export_forces(grain* g, int numfile);


#endif
