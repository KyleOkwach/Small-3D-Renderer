@echo off
mkdir build
pushd build
g++ main.cpp -o ./build/Main -lcomdlg32 -lgdi32
popd