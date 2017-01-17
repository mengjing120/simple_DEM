==========
simple_DEM
==========

A basic CPU-based discrete element method algorithm, created for comparison against more sophisticated codes.

Written by Anders Damsgaard Christensen, `<adc@geo.au.dk>`_, and is maintained at `<https://github.com/anders-dc/simple_DEM>`_.

Requirements
------------
- GNU Make
- GCC
- Optional: Paraview

Obtaining
---------
``git clone https://github.com/anders-dc/simple_DEM.git``

Building
--------
``make``

Running
-------
Simply execute ``./simple_DEM`` in the root folder. Output is written to the ``output/`` folder. 
All simulation parameters must be specified in ``global_properties.h`` before compiling. If any parameters are changed, run ``make`` in the root folder.

Visualization
-------------
See `<https://youtu.be/HOKfgUy5e58>`_ for an example on how to visualize the 
grains in Paraview.

License
-------
The code is licenced under the GNU Public License V.3, see ``license.txt`` for details.
