@echo off
mkdir build
pushd build
g++ ../main.cpp -o Rebel3D ../includes/Window.cpp ../includes/Utils.cpp ../includes/gl/RebelGL.cpp -lcomdlg32 -lgdi32 
popd