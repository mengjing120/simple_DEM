simple_DEM
==========

A basic CPU-based discrete element method algorithm, created for comparison against more sophisticated codes.

Requirements
------------
- GNU Make
- GCC
- Optional: Paraview

Obtaining
---------
`git clone https://github.com/anders-dc/simple_DEM.git`

Building
--------
`make`

Running
-------
Simply execute `./simple_DEM` in the root folder. Output is written to the `output/` folder. 
All simulation parameters must be specified in `global_properties.h` before compiling. If any parameters are changed, run `make` in the root folder.

