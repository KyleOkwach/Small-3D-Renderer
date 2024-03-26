@echo off
mkdir build
pushd build
g++ ../main.cpp -o Rebel3D ../includes/Window.cpp ../includes/Utils.cpp ../includes/gl/RebelGL.cpp ../includes/math/RVector.cpp ../includes/gl/3D/Tri.cpp ../includes/gl/3D/Mesh.cpp -lcomdlg32 -lgdi32 
.\Rebel3D
popd