#include <iostream>
#include <cstdio>
#include <fstream>
#include "header.h"
#include "global_properties.h"

int vtk_export_grains(grain* g, int numfile)
{
  FILE* fout;

  char filename[25]; // File name
  sprintf(filename, "output/grains%04d.vtk", numfile);

  if ((fout = fopen(filename, "wt")) == NULL) {
    std::cout << "vtk_export error, cannot open " << filename << "!\n";
    return 1;
  }

  // Write header
  fprintf(fout, "# vtk DataFile Version 3.0\n");

  // Write title
  fprintf(fout, "'Time: %f s'\n", numfile*dt);

  // Write data type
  fprintf(fout, "ASCII\nDATASET UNSTRUCTURED_GRID\n");

  // Grain coordinates
  fprintf(fout, "POINTS %d FLOAT\n", ng);
  for (int i = 0; i < ng; i++)
    fprintf(fout, "%f %f 0.0\n", g[i].x, g[i].y);
  fprintf(fout, "POINT_DATA %d\n", ng);

  // Grain radii
  fprintf(fout, "VECTORS Radius float\n");
  for (int i = 0; i < ng; i++) 
    fprintf(fout, "%f 0.0 0.0\n", g[i].R);

  // Grain velocities
  fprintf(fout, "VECTORS Velocity float\n");
  for (int i = 0; i < ng; i++) 
    fprintf(fout, "%f %f 0.0\n", g[i].vx, g[i].vy);

  // Pressure
  fprintf(fout, "SCALARS Pressure float 1\n");
  fprintf(fout, "LOOKUP_TABLE default\n");
  for (int i = 0; i < ng; i++) 
    fprintf(fout, "%e\n", g[i].p);

  // Angular velocity
  fprintf(fout, "SCALARS Angvel float 1\n");
  fprintf(fout, "LOOKUP_TABLE default\n");
  for (int i = 0; i < ng; i++)
    fprintf(fout, "%e\n", g[i].vth);
  
  fclose(fout);
  return 0;
}

// Save walls vtk file
int vtk_export_walls(int numfile, double wlex, double wrix, double wloy, double wupy,
    		     double wp_up, double wp_down, double wp_left, double wp_right)
{
    char fname[25]; // file name
    sprintf(fname,"output/walls%04d.vtk",numfile);

    using std::endl;

    std::ofstream fow(fname, std::ios::out);
	if (fow)
	{
        fow.precision(3); fow << std::scientific;
        fow << "# vtk DataFile Version 3.0" << endl;
        fow << "My walls" << endl;
        fow << "ASCII" << endl;
        fow << "DATASET POLYDATA" << endl;
        fow << "POINTS 8 float" << endl;
        // lower wall
        fow << wlex << " " << wloy << " 0" << endl;
        fow << wrix << " " << wloy << " 0" << endl;
        // upper wall
        fow << wlex << " " << wupy << " 0" << endl;
        fow << wrix << " " << wupy << " 0" << endl;
        // left wall
        fow << wlex << " " << wloy << " 0" << endl;
        fow << wlex << " " << wupy << " 0" << endl;
        // right wall
        fow << wrix << " " << wloy << " 0" << endl;
        fow << wrix << " " << wupy << " 0" << endl;
        fow << "LINES 4 12" << endl;
        fow << "2 0 1" << endl;
        fow << "2 2 3" << endl;
        fow << "2 4 5" << endl;
        fow << "2 6 7" << endl;
        fow << "POINT_DATA 8" << endl;
        fow << "SCALARS Rayon float" << endl;
        fow << "LOOKUP_TABLE default" << endl;
        fow << wp_up << endl;	// No idea about the following sequence, i only know that there have to be 8 values
        fow << wp_up << endl;
        fow << wp_left << endl;
        fow << wp_left << endl;
        fow << wp_right << endl;
        fow << wp_right << endl;
        fow << wp_down << endl;
        fow << wp_down << endl;   // ??
	}
	return 0;
}

int vtk_export_forces(grain* g, int numfile)
{
  FILE* fout;

  char filename[25]; // File name
  sprintf(filename, "output/forces%04d.vtk", numfile);

  if ((fout = fopen(filename, "wt")) == NULL) {
    std::cout << "vtk_export error, cannot open " << filename << "!\n";
    return 1;
  }

  // Write header
  fprintf(fout, "# vtk DataFile Version 3.0\n");

  // Write title
  fprintf(fout, "'Time: %f s'\n", numfile*dt);

  // Write data type
  fprintf(fout, "ASCII\nDATASET POLYDATA\n");


  fclose(fout);
  return 0;
}
