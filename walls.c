#include <cmath>
#include "header.h"
#include "global_properties.h"

// Compute force between i and upper wall
double compute_force_upper_wall(int i, grain* g, double wup)
{
  double dn = wup - (g[i].y + g[i].R); // Overlap
  
  if(dn<0.0) {
    double vn,fn;
    // velocity (wall velocity = 0)
    vn = g[i].vy;
    // force
    fn = -kn * dn - nu * vn;
    // Update sum of forces on grains
    g[i].fy -= fn;
    // Add fn to pressure on grains i
    g[i].p += fn;
    // Update stress to the wall
    return fn;
  }
  return 0.0;
}

double compute_force_lower_wall(int i, grain* g, double wdown)
{

  double dn = g[i].y - g[i].R - wdown; // Overlap
  
  if(dn<0.0) {
    double vn,fn;
    // velocity (wall velocity = 0)
    vn = g[i].vy;
    // force
    fn = - kn * dn - nu * vn;
    // Update sum of forces on grains
    g[i].fy += fn;
    // Add fn to pressure on grains i
    g[i].p += fn;
    // Update stress to the wall
    return fn;
  }
  return 0.0;
}

double compute_force_left_wall(int i, grain* g, double wleft)
{
  double dn = wleft + g[i].x - g[i].R; // Overlap
  
  if(dn<0.0) {
    double vn,fn;
    // velocity (wall velocity = 0)
    vn = g[i].vx;
    // force
    fn = -kn * dn - nu * vn;
    // Update sum of forces on grains
    g[i].fx += fn;
    // Add fn to pressure on grains i
    g[i].p += fn;
    // Update stress to the wall
    return fn;
  }
  return 0.0;
}


double compute_force_right_wall(int i, grain* g, double wright)
{
  double dn = wright - (g[i].x + g[i].R); // Overlap
  
  if(dn<0.0) {
    double vn,fn;
    // velocity (wall velocity = 0)
    vn = -g[i].vx;
    // force
    fn = -kn * dn - nu * vn;
    // Update sum of forces on grains
    g[i].fx -= fn;
    // Add fn to pressure on grains i
    g[i].p += fn;
    // Update stress to the wall
    return fn;
  }
  return 0.0;
}

void interact_walls(grain* g, double wleft, double wright, double wup, double wdown, 
    		    double* wp_up, double* wp_down, double* wp_left, double* wp_right)
{
  double u = 0.0;
  double d = 0.0;
  double r = 0.0;
  double l = 0.0;

  int i;

  #pragma omp parallel for shared(g, u, d, r, l) private (i)
  for (i = 0; i < ng; i++) {
    u += compute_force_upper_wall(i, g, wup);
    d += compute_force_lower_wall(i, g, wdown);
    r += compute_force_right_wall(i, g, wright);
    l += compute_force_left_wall(i, g, wleft);
  }
  *wp_up 	= u;
  *wp_down 	= d;
  *wp_left	= l;
  *wp_right	= r;
}
