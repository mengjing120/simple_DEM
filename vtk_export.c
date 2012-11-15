#include <stdio.h>
#include "header.h"
#include "global_properties.h"

int vtk_export_grains(grain* g, int numfile)
{
  FILE* fout;
  int i;

  char filename[25]; /* File name */
  sprintf(filename, "output/grains%04d.vtk", numfile);

  if ((fout = fopen(filename, "wt")) == NULL) {
    fprintf(stderr, "vtk_export error, cannot open ");
    fprintf(stderr, filename);
    fprintf(stderr, "!\n");
    return 1;
  }

  /* Write header */
  fprintf(fout, "# vtk DataFile Version 3.0\n");

  /* Write title */
  fprintf(fout, "'Time: %f s'\n", numfile*dt);

  /* Write data type */
  fprintf(fout, "ASCII\nDATASET UNSTRUCTURED_GRID\n");

  /* Grain coordinates */
  fprintf(fout, "POINTS %d FLOAT\n", np);
  for (i = 0; i < np; i++)
    fprintf(fout, "%f %f 0.0\n", g[i].x, g[i].y);
  fprintf(fout, "POINT_DATA %d\n", np);

  /* Grain radii */
  fprintf(fout, "VECTORS Radius float\n");
  for (i = 0; i < np; i++) 
    fprintf(fout, "%f 0.0 0.0\n", g[i].R);

  /* Grain velocities */
  fprintf(fout, "VECTORS Velocity float\n");
  for (i = 0; i < np; i++) 
    fprintf(fout, "%f %f 0.0\n", g[i].vx, g[i].vy);

  /* Pressure */
  fprintf(fout, "SCALARS Pressure float 1\n");
  fprintf(fout, "LOOKUP_TABLE default\n");
  for (i = 0; i < np; i++) 
    fprintf(fout, "%e\n", g[i].p);

  /* Anpular velocity */
  fprintf(fout, "SCALARS Anpvel float 1\n");
  fprintf(fout, "LOOKUP_TABLE default\n");
  for (i = 0; i < np; i++)
    fprintf(fout, "%e\n", g[i].angv);
  
  fclose(fout);
  return 0;
}

int vtk_export_forces(grain* g, int numfile)
{
  FILE* fout;

  char filename[25]; /* File name */
  sprintf(filename, "output/forces%04d.vtk", numfile);

  if ((fout = fopen(filename, "wt")) == NULL) {
    fprintf(stderr,"vtk_export error, cannot open ");
    fprintf(stderr, filename);
    fprintf(stderr, "!\n");
    return 1;
  }

  /* Write header */
  fprintf(fout, "# vtk DataFile Version 3.0\n");

  /* Write title */
  fprintf(fout, "'Time: %f s'\n", numfile*dt);

  /* Write data type */
  fprintf(fout, "ASCII\nDATASET POLYDATA\n");


  fclose(fout);
  return 0;
}
