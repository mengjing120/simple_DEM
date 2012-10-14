#ifndef HEADER_H_
#define HEADER_H_

/* Structure declarations */
typedef struct
{
  double m; 		/* Mass */
  double R;		/* Radius */
  double I; 		/* Inertia */
  double x, y, th;	/* Position */
  double vx, vy, vth;	/* Velocities */
  double ax, ay, ath;	/* Acceleration */
  double fx, fy, fth;	/* Sum of forces, decomposed */
  double p;		/* Pressure */
} grain;



/* Prototype functions */

/* initialize.c */
void triangular_grid(grain* g);

/* grains.c */
void prediction(grain* g);
void interparticle_force(grain* g, int a, int b);
void interact_grains(grain* g);
void update_acc(grain* g);
void correction(grain* g);

/* walls.c */
double compute_force_upper_wall(int i, grain* g, double wup);
double compute_force_lower_wall(int i, grain* g, double wdown);
double compute_force_left_wall(int i, grain* g, double wleft);
double compute_force_right_wall(int i, grain* g, double wright);
void interact_walls(grain* g, double wleft, double wright, double wup, double wdown, 
    		    double* wp_up, double* wp_down, double* wp_left, double* wp_right);

/* vtk_export.c */
int vtk_export_grains(grain* g, int numfile);
/*int vtk_export_walls(int numfile, double wlex, double wrix, double wloy, double wupy);*/
int vtk_export_forces(grain* g, int numfile);

#endif
