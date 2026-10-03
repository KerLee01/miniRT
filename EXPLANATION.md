# How miniRT Works — Conceptual Guide & Architecture Walkthrough

This guide explains how **miniRT** functions from the ground up. It is written to give anyone unfamiliar with ray tracing an intuitive, step-by-step understanding of the optical principles, mathematics, and code structure of this project.

---

## 1. The Core Concept: What is Ray Tracing?

In the physical world, light travels from a light source (like the sun or a lamp), bounces off objects in the environment, and a small fraction of those scattered photons eventually enters our eyes.

Simulating billions of random light photons scattering through space would be computationally unfeasible on a CPU, because 99.99% of those rays would never hit the camera.

### The Ray Tracing Inversion
**Ray Tracing solves this by reversing the physical path of light:**
Instead of tracking rays from the light source to the camera, the ray tracer shoots virtual **primary rays** from the **camera eye through each discrete pixel on the screen into the 3D scene** to determine what object is visible at that exact pixel.

```
       [Light Source]
             \
              \ (Shadow Ray tests visibility)
               v
 [Camera Eye] ----(Primary Ray)----> [Pixel on Screen] ----> [Object Collision (Hit Point)]
```

---

## 2. The 5-Step Pipeline (Life of a Frame)

When running `./miniRT valid_scene.rt`, the application follows a 5-step pipeline:

```
+-------------------------------------------------------------------------------+
| 1. Scene Parsing (.rt)  -> Validate and load Camera, Light, and Shapes        |
| 2. Viewport Setup       -> Calculate 3D camera orientation and pixel grid     |
| 3. Ray Generation       -> Cast a ray from camera origin through each pixel   |
| 4. Ray Intersection     -> Find closest shape collision (Sphere, Plane, Tube) |
| 5. Shading & Lighting   -> Compute Normals, Hard Shadows, and Lambertian light|
+-------------------------------------------------------------------------------+
                                      |
                                      v
                       [MiniLibX Window Display]
```

---

### Step 1: Parsing the Scene File (`.rt`)
Before anything can be rendered, the engine reads and validates the `.rt` scene file.

- **Reader**: `parse_scene` reads lines sequentially using `get_next_line`.
- **Sanitization**: Tabs and newlines are sanitized into uniform whitespace to ensure resilient token splitting.
- **Components Loaded**:
  - `A` (**Ambient Light**): Global base illumination ratio `[0.0, 1.0]` and color.
  - `C` (**Camera**): 3D coordinates, orientation vector `[-1.0, 1.0]`, and Field of View (FOV `[0, 180]`).
  - `L` (**Point Light**): 3D coordinates, brightness `[0.0, 1.0]`, and color.
  - `sp`, `pl`, `cy` (**Shapes**): Dynamically allocated and appended to a polymorphic linked list (`t_shape`).
- **Validation**: Strict checks ensure no duplicate cameras or lights, coordinates and colors are bounded, dimensions are positive, and invalid scenes fail immediately with `"Error\n"`.

*Relevant Files*:
- `srcs/parser/parser.c`
- `srcs/parser/fill_elements.c`
- `srcs/parser/fill_sphere.c`, `fill_plane.c`, `fill_cylinder.c`
- `srcs/parser/utils/parse_helpers.c`

---

### Step 2: Constructing the Virtual Camera & Viewport
The camera exists as a point in 3D space (`cam.origin`), but the output image is a 2D grid ($800 \times 600$ pixels). We must construct a virtual 2D rectangular window floating in 3D space in front of the camera:

1. **Camera Basis Vectors (Right & Up)**:
   - To know which way the camera tilts, we compute the camera's local **Right** vector:
     $$\vec{\text{Right}} = \text{normalize}(\vec{\text{WorldUp}} \times \vec{\text{Forward}})$$
   - The local **True Up** vector is then:
     $$\vec{\text{TrueUp}} = \text{normalize}(\vec{\text{Right}} \times \vec{\text{Forward}})$$
   - **Gimbal Lock Protection**: If looking straight up or down along $\pm Y$, `world_up` dynamically changes to $(0, 0, 1)$ to prevent vector collapse.
2. **Virtual Screen Dimensions**:
   - At focal distance $1.0$, the horizontal width is:
     $$W = 2 \cdot \tan\left(\frac{\text{FOV} \cdot \pi}{360}\right)$$
   - The height is derived from the aspect ratio ($800 / 600$):
     $$H = \frac{W}{\text{Aspect Ratio}}$$
3. **Pixel Step Deltas**:
   - $\Delta u = \vec{U}_{\text{viewport}} / 800$ (horizontal step between pixel columns).
   - $\Delta v = \vec{V}_{\text{viewport}} / 600$ (vertical step between pixel rows).
   - $\text{Pixel}_{00}$ calculates the 3D center of the top-left pixel $(0, 0)$.

*Relevant Files*:
- `srcs/camera/camera.c`
- `srcs/camera/viewport.c`

---

### Step 3: Ray Generation (Looping Over Pixels)
In `render_scene`, two nested loops iterate over all pixels from row $y = 0 \to 599$ and column $x = 0 \to 799$:

1. For every pixel coordinate $(x, y)$, the exact 3D position in space is:
   $$\vec{P}_{\text{pixel}} = \text{Pixel}_{00} + (x \cdot \Delta u) + (y \cdot \Delta v)$$
2. A ray is constructed:
   - **Origin**: Camera position (`cam.origin`).
   - **Direction**: Normalized unit vector pointing from camera eye to $\vec{P}_{\text{pixel}}$.

*Relevant Files*:
- `srcs/camera/ray.c`
- `srcs/render.c`

---

### Step 4: Geometric Ray Intersections (What Did We Hit?)
The ray propagates into the 3D scene according to the line equation:
$$P(t) = \text{Origin} + t \cdot \text{Direction} \quad (t > 0)$$

`get_closest_shape` tests the ray against all shapes in the linked list and records the closest positive distance $t$:

1. **Sphere (`hit_sphere`)**:
   - Substituted into $(P - C) \cdot (P - C) = r^2$, yielding a quadratic equation $At^2 + Bt + C = 0$.
   - If $\Delta = B^2 - 4AC \ge 0$, solves for $t$ using the quadratic formula.
2. **Plane (`hit_plane`)**:
   - Solves the planar equation $(P - P_0) \cdot \vec{N} = 0$, giving $t = \frac{(P_0 - \text{Origin}) \cdot \vec{N}}{\text{Direction} \cdot \vec{N}}$.
3. **Cylinder (`hit_cylinder`)**:
   - **Curved Body**: Solves a 2D quadratic projection perpendicular to the cylinder axis, then bounds $t$ within height $[0, h]$.
   - **End Caps**: Tests circular disc caps on both the bottom and top of the cylinder.

If no shape is hit, the pixel is colored black (`0x000000`).

*Relevant Files*:
- `srcs/sphere.c`
- `srcs/plane.c`
- `srcs/cylinder.c`

---

### Step 5: Lighting, Shadows & Pixel Coloring
When a shape is hit at collision point $P_{\text{hit}}$, `calculate_lighting` computes its appearance:

1. **Surface Normal ($\vec{N}$)**:
   - The perpendicular unit vector at the hit point.
   - **Inside Handling**: If the ray strikes from the inside (e.g. camera is inside a sphere or cylinder), the normal is automatically inverted so the interior is correctly illuminated.
2. **Hard Shadows (`in_shadow`)**:
   - A **secondary shadow ray** is cast from $P_{\text{hit}} + 0.001 \cdot \vec{L}$ toward the light position.
   - The $0.001$ offset prevents "shadow acne" (floating-point precision self-collision).
   - If any object blocks the shadow ray before reaching the light, the point is occluded in shadow ($I_{\text{diffuse}} = 0$).
3. **Lambertian Reflection**:
   - If illuminated, brightness depends on the angle of incoming light:
     $$I_{\text{diffuse}} = \max(0, \vec{N} \cdot \vec{L}) \times \text{Light Brightness}$$
4. **Total Illumination**:
   $$\text{Intensity} = \text{Ambient Ratio} + I_{\text{diffuse}} \quad (\text{clamped to } 1.0)$$
   The object's base RGB color is multiplied by this intensity.
5. **Direct Pixel Put**:
   - The resulting color (`0x00RRGGBB`) is written directly into the offscreen MiniLibX image buffer.

*Relevant Files*:
- `srcs/lighting.c`
- `srcs/shadow.c`
- `srcs/mlx.c`

---

## 3. Window Display & Event Loop

Once all pixels are computed:
1. `mlx_put_image_to_window` pushes the completed frame buffer to the macOS/X11 window.
2. **Interactive Hooks**:
   - Pressing **ESC** (`keycode 53`) cleanly frees shapes, destroys the image, closes the window, and exits.
   - Clicking the **Window Close Button (Red X)** performs the same clean exit.
   - Expose events redraw the cached image buffer if minimized or uncovered.
3. `mlx_loop` keeps the application active and responsive.

*Relevant Files*:
- `srcs/main.c`
- `srcs/mlx.c`

---

## 4. Source Code File Map

| Subsystem | Source Files | Purpose |
|---|---|---|
| **Entry & Window** | `srcs/main.c`, `srcs/mlx.c` | CLI validation, MLX setup, event hooks, pixel buffer writing |
| **Render Engine** | `srcs/render.c` | Pixel traversal, shape dispatcher, color packing |
| **Camera** | `srcs/camera/camera.c`, `viewport.c`, `ray.c` | Orthonormal basis vectors, viewport metrics, ray construction |
| **Geometry** | `srcs/sphere.c`, `plane.c`, `cylinder.c` | Analytical ray-surface intersections and normal vectors |
| **Illumination** | `srcs/lighting.c`, `srcs/shadow.c` | Lambertian diffuse model, shadow ray occlusion testing |
| **Math Library** | `srcs/math/basic_arith.c`, `adv_arith.c`, `helper_funcs.c` | 3D vector arithmetic (dot product, cross product, normalize) |
| **Parser** | `srcs/parser/parser.c`, `fill_elements.c`, `fill_*.c`, `utils/*.c` | `.rt` line reading, tokenization, error enforcement, memory cleanup |
