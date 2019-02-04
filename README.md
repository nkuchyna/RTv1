# RTv1
Simple Ray Tracer on C | UNIT Factory | The first step to create a Raytracing program

The goal of this project was to create program to generate images according to Raytracing protocol (selfmade file format to describe scenes). Those computer generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

- Implemented the Ray-Tracing method to create a computer generated image.
- 4 simple geometric objects as a base (not composed): plane, sphere, cylinder and cone.
- Program is able to apply translation and rotation transformation to objects before displaying them.
- Position and direction of any point of vision and of simple objects.
- Smallest light management (applying [Phong model](https://en.wikipedia.org/wiki/Phong_reflection_model)): different brightness, shadows.
- Graphic library miniLibX was used. This library was developed internally and includes the minimum necessary to open a window, light a pixel and deal with events linked to this window: keyboard and mouse.

Usage: ./RTv1 [file]

BONUS PART:

- multi-spots;
- shine effect.

![Screenshot](https://github.com/nkuchyna/RTv1/blob/master/screenshots/sphere.png | width=200)
![Screenshot](https://github.com/nkuchyna/RTv1/blob/master/screenshots/cone.png)
![Screenshot](https://github.com/nkuchyna/RTv1/blob/master/screenshots/all_objects.png)
![Screenshot](https://github.com/nkuchyna/RTv1/blob/master/screenshots/hall.png)
