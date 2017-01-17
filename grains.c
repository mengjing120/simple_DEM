#include <math.h>
#include "header.h"
#include "global_properties.h"


void prediction(grain* g)
{
  int i;

  #pragma omp parallel for shared(g) private (i)
  for (i = 0; i < np; i++) {
    /* Predict positions and velocities */
    g[i].x   += dt * g[i].vx + 0.5 * dt * dt * g[i].ax;
    g[i].y   += dt * g[i].vy + 0.5 * dt * dt * g[i].ay;
    g[i].vx  += 0.5 * dt * g[i].ax;
    g[i].vy  += 0.5 * dt * g[i].ay;

    g[i].ang  += dt * g[i].angv + 0.5 * dt * dt * g[i].anga;
    g[i].angv += 0.5 * dt * g[i].anga;

    /* Zero forces */
    g[i].fx  = 0.0;
    g[i].fy  = 0.0;
    g[i].t   = 0.0;
    g[i].p   = 0.0;
  }
}

void interparticle_force(grain* g, int a, int b)
{
  if (a > b) { /* Use Newtons 3rd law to find both forces at once */

    /* Particle center coordinate component differences */
    double x_ab = g[a].x - g[b].x;
    double y_ab = g[a].y - g[b].y;

    /* Particle center distance */
    double dist = sqrt(x_ab*x_ab + y_ab*y_ab);

    /* Size of overlap */
    double dn = dist - (g[a].R + g[b].R);

    if (dn < 0.0) { /* Contact */
      double xn, yn, vn, fn; /* Normal components */
      double xt, yt, vt, ft; /* Tangential components */
      /* Local axes */
      xn = x_ab / dist;
      yn = y_ab / dist;
      xt = -yn;
      yt = xn;

      /* Compute the velocity of the contact */
      double vx_ab = g[a].vx - g[b].vx;
      double vy_ab = g[a].vy - g[b].vy;
      vn = vx_ab*xn + vy_ab*yn;
      vt = vx_ab*xt + vy_ab*yt - (g[a].R*g[a].angv + g[b].R*g[b].angv);

      /* Compute force in local axes */
      fn = -kn * dn - nu * vn;

      /* Rotation */
      if (fn < 0) 
          fn = 0.0;
      ft = fabs(kt * vt);
      if (ft > mu*fn) /* Coefficient of friction */
          ft = mu*fn;
      if (vt > 0)
          ft = -ft;

      /* Calculate sum of forces on a and b in global coordinates */
      g[a].fx  += fn * xn;
      g[a].fy  += fn * yn;
      g[a].t   += -ft*g[a].R;
      g[a].p   += fn;
      g[b].fx  -= fn * xn;
      g[b].fy  -= fn * yn;
      g[b].p   += fn;
      g[b].t   += -ft*g[b].R;

    }

  } else {
    return;
  }
}

void interact_grains(grain* g)
{
  int a, b;
  #pragma omp parallel for shared(g) private (a,b)
  /* Loop through particle a */
  for (a = 0; a < np; a++) {
   
    /* Loop through particle b */
    for (b = 0; b < np; b++) {
      interparticle_force(g, a, b);  
    }
  }
}

void update_acc(grain* g)
{
  int i;
  #pragma omp parallel for shared(g) private (i)
  for (i = 0; i < np; i++) {
    g[i].ax   = g[i].fx / g[i].m;
    g[i].ay   = g[i].fy / g[i].m - grav;
    g[i].anga = g[i].t / g[i].I;
  }
}

void correction(grain* g)
{
  int i;
  #pragma omp parallel for shared(g) private (i)
  for (i = 0; i < np; i++) {
    g[i].vx   += 0.5 * dt * g[i].ax;
    g[i].vy   += 0.5 * dt * g[i].ay;
    g[i].angv += 0.5 * dt * g[i].anga;
  }
}

