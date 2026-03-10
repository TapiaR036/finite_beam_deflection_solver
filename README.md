# Finite Beam Deflection Solver

A C++ finite-difference solver for the deflection of a simply supported beam under a uniform distributed load.

## Overview

This project approximates beam deflection by discretizing the beam into evenly spaced grid points, forming the corresponding linear system, and solving for the nodal deflections numerically. The code also compares the numerical solution against the exact analytical solution and reports the relative L2 error.

## Features

- Finite-difference beam deflection model
- Simply supported beam under distributed load
- Gauss-Seidel linear solver
- Relative L2 error calculation
- Optional turbo mode for faster runs with reduced terminal output
- Solve timing and iteration count reporting

## How to Run

- Compile the solver from the solver using the provided cript: bash build.bat
- Run the solver from the command line using:
-   ./beam [n] [L] [EI] [q] <turbo>
- Where:
-   [n] - Number of discretized beam points
-   [L] - Beam Length
-   [EI] - Flexural Rigidity (Young's Modulus x Second Moment of Inertia)
-   [q] - Distributed load per unit length
-   <turbo> - Optional flag (1 enables turbo mode)
- Example Input:
-   ./beam 5 3 600 1500 1
- Example Output:
-    Iterations: 27
-    Solve Time: 4e-05
-    l2 Error: 0.0513426
-    Mesh Interval: 0.75

## Turbo Mode

Turbo mode disables verbose solver output to improve runtime performance when solving larger systems. The numerical solution remains unchanged; only the amount of printed output differs.

## Mathematical Model

The beam deflection is modeled using the Euler–Bernoulli beam equation. The continuous differential equation is discretized using a finite difference approximation, resulting in a linear system of equations that is solved iteratively using the Gauss-Seidel method.
