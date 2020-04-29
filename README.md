# Graphics Tests
This repository contains raytracing algorithm test for learning purposes. This will eventually include more projects as a start testing more algorithms. This projects are not ready for distribution, as I will not be focusing on optimization, you should aproach this projects for learning purposes.

## Raycasting test
In this test you can find a basic raycasting algorithm. The objective of this test is to learn the camera model used in this types of algorithms and basic intersections with infinite planes and spheres. As raycasting is the most basic raytracing algorithm this is a good start to learn the basics. This test will support sphere, infinite plane, quad and cube intersection and some basic phong shading.

### Roadmap
* [X] Calculation of cameras pixels in world space.
* [X] Intersection with spheres.
* [ ] Intersection with infinite planes.
* [ ] Intersection with quads.
* [ ] Intersection with cubes.
* [X] Depth testing
* [ ] Phong shading
* [ ] Shadows
* [ ] Reflections

## OpenGL 
This is used to learn the basics of OpenGL and aims to create an API with clases that abstract the basic functionality and boilerplate code.

### Roadmap
* [X] Getting a triangle rendered
* [X] Drawing a textured quad
* [X] Abstraction for buffers
* [X] Abstraction for textures
* [X] Abstraction for shaders
* [X] Basic camera and transformation

## Post processing stack (OPENGL)
This project is used to learn about how to create a little post processing stack for future projects.

### Roadmap
* [ ] Getting a triangle
* [ ] Small helper functions for dealing with OpenGL 
* [ ] Rendering into an offscreen framebuffer
* [ ] Postprocessing framework