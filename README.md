# Project Animation simulation and rendering

## Installation

```bash
  git clone git@github.com:jmaleo/OpenGLBezierProject.git
  cd OpenGLBezierProject
  mkdir build && cd build
  cmake .. && make -j20
```

## Move arround the scene

* To move arround the scene, you can use the mouse and the ZQSD keys.

## Description of the interface

The interface is mainly composed of many tools, widgets. 

* The first one allows the user to see or not the scene. 
If the user wants to see the scene, he can click on the button "Show scene".
If it's true, the scene is displayed and also others widgets are displayed.
* The second one allows the user to show or not objects, or lights.
Also, this widget provides a list of tools to use the rendering status (bloom / hdr / only bright points after bluring).

If the user wants to see objects, he can click on the button "Show objects".
If it's true, the objects are displayed.
* The third one allows the user to select the objects.
There is a list of objects to choose, following the visible objects.

If you click on one of them, the object is blinking and a little widget is displayed.
* This little widget allows the user to move the object, to change the color and the variables of the materials for the microfacet rendering.

If the user wants to see lights he can click on the button "Show lights" of the second widget.
If it's true, the lights are displayed.
* The fourth one allows the user to select lights and also add lights.
There is a list of lights to choose, following the visible lights.

If you click on one of them, the light is blinking and a little widget is displayed.
* This little widget allows the user to move the light, to change the color.


* The last widget allows the user to play with particles. 
You can stop the simulation, change the time between each frame, change the number of particles, change the distribution of the particles inside the box.

## Description of the scene

Here is the initial scene.

![Initial scene](img/initial_scene.png)

## Indications

When you want to add lights, make sure to press ESC to quit the application, as the GLSL shaders are overwritte when adding lights.
To make sure the tool works, when restarting the application, you can just re cmake .. the project, only to make sure the shaders are correct.


## Images 

Little video of the scene.
![Little video](img/animation_demo.gif)

Initial Scene.
![Initial scene](img/initial_scene.png)

Initial scene without HDR.
![Initial scene wo hdr](img/initial_scene_wo_hdr.png)

Initial scene without HDR and BLOOM.
![Initial scene](img/initial_scene_wo_hdr_bloom.png)

Initial scene with only bright blurred points.
![Initial scene](img/initial_scene_only_bright.png)
