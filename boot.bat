@echo off 
mkdir build
pushd build
call D:\programmes\visual\VC\Auxiliary\Build\vcvarsall.bat x64
cl /MDd ../main.c ../utils.c ../camera.c /link ../lib/glew32.lib ../lib/glfw3.lib user32.lib kernel32.lib gdi32.lib comdlg32.lib shell32.lib Opengl32.lib GLU32.lib
popd
pause