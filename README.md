# Rendering-Shading
This program provides user with an interactive interface for 3D real-time rendering and shading based on openGL. The shaders are written by GLSL. The GUI is created with QT.
![Figure 1: User Interface example.](https://github.com/TopModLab/Rendering-Shading/blob/master/GUI.PNG)

The control panel on the right-hand side allows adjustments of the relection-refraction effect with four sliders on the top. From left to right, the first three sliders control three parameters a, b and c for Fresnel curves description and the last slider controls the refractive index.

Ambient color, diffuse color and specular color are mixed in a linear way. The relative powers of diffuse and specular color can be adjusted through "material Kd" and "material Ks". Clicking the "export" button generates a log file "export.txt" with current set of parameters.