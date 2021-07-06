# kafei
OpenGL Game Programming


### Dependencies

- DearImgui: `https://github.com/ocornut/imgui.git`
- GLFW: `https://github.com/glfw/glfw.git`
- GLAD: `https://glad.dav1d.de/` **NOTE:** Must download and unzip into the `deps` folder

Clone each of the above into the root of this project in a folder called `deps`

**OR**

1. `scripts/getdeps.sh`


### Building

1. `mkdir build && cd build`
2. `cmake ..`
3. Build using the CMake generated files...

**OR**

Use VSCode's build & launch tasks that are defined in the `.vscode` folder.
