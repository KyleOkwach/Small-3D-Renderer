@echo off
mkdir build
pushd build
g++ ../main.cpp -o Rebel3D -lcomdlg32 -lgdi32
.\Rebel3D
popd