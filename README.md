# Maps
Console application for finding minimum distances in different types of graphs. With this application you can create multiple street systems between cities in the cartesian plane. Different street networks are called "regions".
These graphs (regions) are classified by the application in a number of different types of graphs for which it chooses an optimum approach for finding the minimum distance between two cities.
The supported types of graphs are:
- complete graph (undirected streets)
- line graph (undirected streets)
- tree (undirected streets)
- directed acyclic graph (directed streets)
- directed graph (the generic region with directed streets)
- undirected graph (the generic region with undirected streets)

# Installation
Make sure you have installed `git`, `make` and `cmake`.
If not, you can install any of them using these commands (works for **Ubuntu 16.04** and later):
```sh
sudo apt install git
sudo apt install build-essential
sudo apt install cmake
```

To install the application follow these commands:
```sh
git clone 'https://github.com/iordachebogdan/Maps/'

#make new directory for binary
mkdir build
cd build

#pass the path to the CMakeLists.txt to cmake, in this case the parent directory of build
cmake ..

#run make
make

#the binary Maps should now be present in the build folder and you can run it like this
./Maps
```

After running the binary follow the instructions displayed in the helper menu. It will be displayed automatically when starting the application.
