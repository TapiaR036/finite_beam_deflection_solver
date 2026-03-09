// Build script for the Finite Beam Deflection Solver
// This script compiles the source code and creates an executable named "beam"

g++ -std=c++17 -IInclude Apps/beamer.cpp Source/beam.cpp Source/matrix.cpp Source/vector.cpp -o beam