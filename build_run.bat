@echo off
mkdir build
pushd build
g++ ../main.cpp -o Rebel3D ../includes/Utils.cpp ../gl/RebelGL.cpp ../gl/Window.cpp -lcomdlg32 -lgdi32 
.\Rebel3D
popd