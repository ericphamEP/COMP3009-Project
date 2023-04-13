Eric Pham
101104095
Sean Martin
101115739
COMP 3009A
Doron Nussbaum
April 12, 2023
------------------------------
COMP 3009 Project Instructions
------------------------------

Compiling instructions
--------------

The project was created in Microsoft Visual Studio 2022 and should be opened and executed in the same environment. The shared_gl folder from class must also be set up such that the relevant libraries can be used.


Execution instructions
--------------

After unzipping the project zip folder, the project can be opened at “project_code.sln”. All source files are located in the “project_code” directory.

Setting the input 3D model: The program will read one .obj file and one texture file (an image such as .png or .jpg) to use as the primary model that animations are performed on. To set these files for the program to read them, follow these instructions:
  - Open the file "modelpath.txt" in the folder ./project_code/models
  - Insert the path to your desired .obj file after "obj "
  - Insert the path to the associated texture after "mat "
	- Note: do not include quotation marks in the path, (ideally path is relative to ./project_code)
  - Once this is complete it should load the correct model according to your input

Note: The project comes with three default models to test with, but will work with any 3D model as long as it is defined by a single .obj file and single texture image file, and the object does not exceed a million vertices or faces.

See the below section for mouse and keyboard controls.


Viewing or accessing features
--------------

Mouse controls:

Left click and drag:
Left movement: Right rotation around object
Right movement: Left rotation around object
Up movement: Move camera down
Down movement: Move camera up
	Mouse scroll:
Scroll up: move camera closer to model
Scroll down: move camera away from model
Left click (when Auto Mode is turned off):
Initiate a head pat
Right click to open a menu to change different options to:
Toggle Auto Mode
Toggle skybox
Adjust animation speed
Adjust squish intensity
etc.

Keyboard controls:

Camera movement:
‘w’ - Move camera closer to model
‘s’ - Move camera away from model
‘a’ - Left rotation around object
‘d’ - Left rotation around object
‘x’ - Move camera up
‘z’ - Move camera down
Left key - Increase camera roll angle
Right key - Decrease camera roll angle
Up key - Increase camera pitch angle
Down key - Decrease camera pitch angle

Adjustment Controls:
‘h’ - Adjust base position of hand up
‘H’ - Adjust base position of hand down
‘j’ - Decrease scale magnitude in x-axis
‘J’ - Increase scale magnitude in x-axis
‘k’ - Decrease scale magnitude in y-axis
‘K’ - Increase scale magnitude in y-axis
‘l’ - Decrease scale magnitude in z-axis
‘L’ - Increase scale magnitude in z-axis
‘i’ - Decrease animation speed
‘I’ - Increase animation speed (Capital ‘i’)
