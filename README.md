*This project has been created as part of the 42 curriculum by kerlee and yichen.*

# miniRT

## Description
**miniRT** is a software ray tracing engine developed in C using 42 School's **MiniLibX** graphical library. The goal of this project is to simulate the physics of light propagation in a 3D environment without reliance on modern GPU graphics APIs (such as OpenGL shaders or Vulkan).

The engine renders 3D geometric objects (spheres, infinite planes, and finite capped cylinders) illuminated by point lights and ambient illumination. It models realistic optical phenomena including:
- Primary camera ray generation through an orthonormal viewport basis.
- Analytical quadratic ray–surface intersection algorithms.
- Surface normal computation (handling both outside surfaces and inner views when inside objects).
- Lambertian diffuse reflection combined with global ambient lighting.
- Hard shadow occlusion testing using secondary shadow rays with surface acne bias.
- Window management and event handling (keyboard ESC and window close hooks).

---

## Instructions

### Compilation
The project includes a Makefile with standard rules (`all`, `clean`, `fclean`, `re`, `bonus`):

```bash
make        # Compiles the libft library and links the miniRT executable
make clean  # Removes intermediate object files (.o)
make fclean # Removes object files, libft.a, and the miniRT executable
make re     # Performs a clean rebuild
make bonus  # Mandatory/bonus compilation rule
```

### Execution
Run the executable by passing a valid `.rt` scene description file as the sole argument:

```bash
./miniRT valid_scene.rt
```

### Controls
- **ESC Key** (`Keycode 53` on macOS): Closes the window and terminates the application cleanly without memory leaks.
- **Window Close Button (Red X)**: Closes the window and terminates the program cleanly.

---

## Scene File Grammar (`.rt`)
Each element in the `.rt` file is separated by newlines, with fields separated by whitespace:

| Identifier | Format | Description |
|---|---|---|
| `A` | `A <ratio> <R,G,B>` | Ambient lighting (ratio `[0.0, 1.0]`, RGB `[0, 255]`) |
| `C` | `C <x,y,z> <nx,ny,nz> <FOV>` | Camera viewpoint, orientation vector `[-1.0, 1.0]`, FOV `[0, 180]` |
| `L` | `L <x,y,z> <brightness> <R,G,B>` | Light point location, brightness ratio `[0.0, 1.0]` |
| `sp` | `sp <x,y,z> <diameter> <R,G,B>` | Sphere center, diameter, color |
| `pl` | `pl <x,y,z> <nx,ny,nz> <R,G,B>` | Plane point, normal vector `[-1.0, 1.0]`, color |
| `cy` | `cy <x,y,z> <nx,ny,nz> <diam> <h> <R,G,B>` | Cylinder base center, axis vector, diameter, height, color |

Example scene (`valid_scene.rt`):
```text
A 0.2 255,255,255
C 7.0,5.0,-10.0 0.0,0.0,1.0 70
L -40.0,0.0,-10.0 0.6 255,255,255
sp 0.0,0.0,20.6 12.6 10,0,255
pl 0.0,0.0,30.0 0.0,0.0,-1.0 33,33,33
cy 15.0,0.0,20.6 0.0,1.0,0.0 6.0 21.42 150,150,150
```

---

## Bonus Part
The bonus executable `miniRT_bonus` is compiled with `make bonus` and includes the following three features:
1. **Specular Reflection (Phong Reflection Model)**: Surface highlights simulated via reflection vectors and view direction with specular shininess exponent ($s = 32$).
2. **Colored & Multi-Spot Lights**: Support for multiple point lights in the `.rt` scene file, each with independent RGB colors, positions, and brightness ratios.
3. **Color Disruption (Checkerboard Pattern)**: Procedural alternating checkerboard pattern applied across planes in any orientation in 3D space.

Execute bonus scene:
```bash
./miniRT_bonus final_bonus.rt
```

Example scene (`final_bonus.rt`):
```text
A 0.1 255,255,255
C 0,4,-12 0,-0.2,1 70
L -5,8,-5 0.7 255,50,50
L 5,8,-5 0.7 50,50,255
L 0,2,4 0.5 50,255,50
pl 0,0,0 0,1,0 255,255,255
sp 0,3,0 6 255,255,255
cy 4,2,2 0.2,1,0 2 4 200,200,200
```

---

## Resources

### References & Documentation
- *Ray Tracing in One Weekend* (Peter Shirley) — foundational principles of camera rays, sphere intersection, and surface normals.
- *Scratchapixel 2.0* (Geometry and Ray Tracing algorithms) — planar and cylindrical intersection equations, coordinate system transformations.
- 42 School MiniLibX Documentation & man pages (`man 3 math`, `open`, `close`, `read`, `write`, `malloc`, `free`).

### AI Usage Description
In accordance with 42 curriculum guidelines, AI assistance was utilized for:
1. **Automated Stress Testing & Edge-Case Identification**: Generating comprehensive test suites for parsing boundary conditions (invalid tokens, negative dimensions, duplicate identifiers, whitespace variations) and geometric edge cases (camera inside objects, gimbal lock singularities).
2. **Documentation Synthesis**: Drafting in-depth architectural breakdown and mathematical derivations for documentation and evaluation preparation.

---

## Other tests

### Mandatory
- Centered sphere
```text
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L -10,10,10 0.8 255,255,255
sp 0,0,0 5.0 255,0,0
```
- Centered plane
```text
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L 0,10,10 0.8 255,255,255
pl 0,0,0 0,0,1 0,255,0
```
- Centered cylinder
```text
A 0.2 255,255,255
C 0,5,25 0,-0.1,-1 70
L -10,10,15 0.8 255,255,255
cy 0,0,0 0,1,0 4.0 10.0 0,0,255
```
- Sphere translation
```text
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L -10,10,10 0.8 255,255,255
sp 0,0,0 4.0 255,50,50
sp -10,0,0 4.0 50,50,255
```

- 90-degree cylinder rotation
```text
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L 0,10,10 0.8 255,255,255
cy 0,0,0 1,0,0 4.0 10.0 50,255,50
```

- camera x-axis
```text
A 0.2 255,255,255
C 25,0,0 -1,0,0 70
L 10,10,10 0.8 255,255,255
sp 0,0,0 5.0 255,50,50
cy 0,-4,0 0,1,0 6.0 8.0 50,50,255
```

- camera y-axis
```text
A 0.2 255,255,255
C 0,25,0 0,-1,0 70
L 10,10,10 0.8 255,255,255
sp 0,0,0 5.0 255,50,50
cy 0,-4,0 0,1,0 6.0 8.0 50,50,255
```

- camera z-axis
```text
A 0.2 255,255,255
C 0,0,25 0,0,-1 70
L 10,10,10 0.8 255,255,255
sp 0,0,0 5.0 255,50,50
cy 0,-4,0 0,1,0 6.0 8.0 50,50,255
```

- camera random diagonal
```text
A 0.2 255,255,255
C -15,15,20 0.5,-0.5,-0.7 70
L 0,15,10 0.8 255,255,255
sp 0,0,0 5.0 255,50,50
cy 0,-4,0 0,1,0 6.0 8.0 50,50,255
```
- Object lit sideways
```text
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L -20,0,5 0.8 255,255,255
sp 0,0,0 5.0 255,0,0
```

- Vertical spot and plane shadow
```text
A 0.2 255,255,255
C 0,10,25 0,-0.3,-1 70
L 0,20,0 0.9 255,255,255
pl 0,0,0 0,1,0 255,255,255
sp 0,4,0 6.0 255,50,50
```

- Objects casting shadows onto other objects
```text
A 0.1 255,255,255
C 0,8,30 0,-0.2,-1 70
L -15,15,15 0.9 255,255,255
pl 0,0,0 0,1,0 200,200,200
sp 0,4,0 8.0 255,50,50
cy -6,6,8 0.5,0.5,0 2.0 8.0 50,50,255
sp 6,2,8 4.0 50,255,50
```

- Translated sphere lit sideways (halo after translation)
```text
A 0.1 255,255,255
C 5,3,20 0,0,-1 70
L -15,3,10 0.8 255,255,255
sp 5,3,0 6.0 255,50,50
```

- Intersecting sphere and cylinder
```text
A 0.2 255,255,255
C 0,2,20 0,0,-1 70
L -10,10,10 0.8 255,255,255
sp 0,0,0 6.0 255,50,50
cy 0,-2,0 0,1,0 3.0 8.0 50,50,255
```

- Multiple objects of each shape
```text
A 0.2 255,255,255
C 0,5,25 0,-0.2,-1 70
L -10,15,15 0.8 255,255,255
pl 0,0,0 0,1,0 200,200,200
sp -5,3,0 5.0 255,50,50
sp 5,3,0 5.0 50,50,255
cy -3,2,8 0,1,0 2.5 6.0 50,255,50
cy 3,2,8 0,1,0 2.5 6.0 255,255,50
```

### Bonus

- Bonus 1: Specular Reflection (Shininess power 32)
```text
A 0.1 255,255,255
C 0,0,20 0,0,-1 70
L -10,10,15 0.9 255,255,255
sp 0,0,0 6.0 255,50,50
```

- Bonus 2: Color Disruption (Checkerboard floor plane)
```text
A 0.2 255,255,255
C 0,6,20 0,-0.2,-1 70
L -10,15,15 0.8 255,255,255
pl 0,0,0 0,1,0 255,255,255
sp 0,3,0 5.0 255,50,50
```

- Bonus 3: Multi-Spot Colored Lights
```text
A 0.1 255,255,255
C 0,5,25 0,-0.1,-1 80
L 10,15,10 0.7 255,50,50
L -15,10,5 0.7 50,150,255
pl 0,0,0 0,1,0 255,255,255
sp -4,3,0 6.0 200,200,200
cy 5,4,-5 0,1,0 4.0 8.0 200,200,200
```

- Bonus 4: Combined Feature Showcase
```text
A 0.1 255,255,255
C 0,6,-16 0,-0.2,1 70
L -7,10,-5 0.7 255,50,50
L 7,10,-5 0.7 50,150,255
L 0,4,-8 0.6 255,255,255
pl 0,0,0 0,1,0 255,255,255
sp -2,3,0 6 200,200,200
cy 4,3,2 0.2,1,0.2 2.5 6 200,200,200
```

---

## Testing Script (`test.sh`)

An interactive evaluation testing script is included to quickly run all test cases with automated memory leak detection (`leaks -atExit --`). All scene files are organized in the `scenes/` directory.

### Quick Start
```bash
./test.sh             # Interactive menu (select category or run all)
./test.sh mandatory   # Step through all 15 mandatory visual scenes
./test.sh bonus       # Step through all 4 bonus visual scenes
./test.sh error       # Fast automated check of 23 parsing/syntax edge cases + leaks
./test.sh all         # Run complete evaluation suite
./test.sh <scene.rt>  # Run any custom scene file with automated leak checking
```

### Features
- **Zero Copy-Pasting**: All scenes are saved under `scenes/mandatory/`, `scenes/bonus/`, and `scenes/invalid/`.
- **Step-by-Step Interactive Mode**: Inspect each visual rendering window, press `ESC` or close window, and press `[ENTER]` in terminal to load the next test.
- **Automated Memory Leak Checking**: Runs via Apple's native `/usr/bin/leaks` tool to ensure zero leaks on both window exit and error handling.
- **Built-in Norminette Checker**: Quickly verify Norminette compliance across all source code.
