Ray-Tracer
==========

A Whitted ray tracer developed during the course Globla Illumination and Rendering (TNCG15) at Linköping University, written in C++. The computations are done on the CPU.

## Supported Geometries

- Rectangles
- Boxes
- Spheres

## Renderings

If you want to look at some renderings produced by this program. Go ahead and navigate to the ``renderings`` directory, where some .ppm files are located. These can be opened using, for example, photoshop.

## Building

### Compiling and running

The included Makefile only supports Mac OSX. If you for some reason wants to run the program and have alot of spare time.

``make && make run``

then wait...

## Team

- Tim Brodin
- Rasmus Haapaoja

## Huge todo list

Yes, we still try to develop this thing on our spare time

- Fix 16:9 aspect ratio, instead of 1:1 - COMPLETE
- Fix memory leaks
- Improve ray-rectangle intersection
- Reduce surface acne
- Add ray-polygon intersection support, enabling more creative geometries
- Add support for multiple light sources
- Add support for diffrent types of light sources
- Extend to Monte-Carlo framework (this is the main objective)



