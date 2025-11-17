# Horizon engine
## installation
Horizon Engine uses CMake as its build system,
to obtain a copy for your project or to contribute, 
clone the repo, but first make shore your in the right directory with:
```bash 
cd path/to/directory
```
then you can call:
```bash
   git clone https://github.com/Engineer112/Horizon_Engine.git
```
to clone the repo
## layout
all sets of .h and .cpp files are grouped into their own folder with the title of the data type as its name
### Directories
* src
  * datastructs: data structs used throughout program
    * Bits: structs used for bit management
  * ECS: src for the entity component system
  * Graphics: src for graphics abstraction layer
  * Windowing: src for windowing abstraction
  * System: src for OS abstraction layer
## documentation
