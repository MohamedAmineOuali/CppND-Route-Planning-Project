# Route Planning Project


This repo is based on the project
[udacity/CppND-Route-Planning-Project](https://github.com/udacity/CppND-Route-Planning-Project).
It contains my work:
* Implementing the A* algorithm on OpenStreetMap data (This
  implementation is based on the c++ nano-degree from Udacity)
* Optimisation for the A* algorithm and the function related to it
* Fix the bugs that exist in the initial source code: Like the window
  scaling: The fixes are done on the code of the
  [IO2D library](https://github.com/MohamedAmineOuali/P0267_RefImpl/tree/Fix_bugs_SDL2)
* Use SDL2 backend to dynamically select the start and end points for A* algorithm from the map

<img src="demo.gif" width="600" height="450" />



## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/MohamedAmineOuali/CppND-Route-Planning-Project.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:MohamedAmineOuali/CppND-Route-Planning-Project.git --recurse-submodules
```

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D dependencies 
  * Install Cairo: sudo apt install libcairo2-dev 
  * Install graphicsmagick: sudo apt install libgraphicsmagick1-dev
  * Install libpng: sudo apt install libpng-dev
  * Install SDL2: sudo apt-get install libsdl2-dev

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

## Description of the work and implementation

### A* algorithm implementation 
Helper functions were implemented to keep the code as simple and as
readable as possible. 

Efficient data structures were used to implement A* like priority_queue.
Optimizations were made to remove repeated calculations and reduce the
memory needed by the program like using reference and pointer for large
data structure instead of copying them.

### fix bugs that exist in the base code
There were some bugs that I fixed in the implementation of the io2d library that involves the scaling of the windows. In the initial source code, the callback for the window_size_change was not called when the window size change. This provokes a low-resolution rendering of the map.

These problems were fixed in the code of the
[io2d library](https://github.com/MohamedAmineOuali/P0267_RefImpl/tree/Fix_bugs_SDL2)
My changes are located in the Fix_bugs_SDL2 branch.

### Select the start and end points of the A* algorithm dynamically from the map

The initial implementation requires the coordinates of the start and end
points of the A* to be giving statistically to the program. The
algorithm of A* run only for one time before the display of the map and
the start and end point coordinates are feed through the standard i/o or
hardcoded in the source code.

By introducing the dynamic selection of the points. We can choose a point directly on the map.
* left clique to select the start point on the map
* right clique to select the end point on the map 

=> After each selection the A* algorithm run again to update the path
between the start and the end point.
