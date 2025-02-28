# LSGFW

## Handling Dependencies

I already provide both [glad](https://github.com/Dav1dde/glad) and [stb_ds](https://github.com/nothings/stb/blob/master/stb_ds.h), which can both be found in the dependencies directory.
However you do need to add a copy of [GLFW](https://www.glfw.org/) yourself.

To do so, build GLFW as a library file and drag it into the root of the dependencies directory, renaming it to `libglfw.a` (or `libglfw.lib`). Also create a folder titled `glfw` (case sensitive) inside the dependencies directory and add GLFW's include files into that new folder.

## Compiling LSGFW

For a quick and easy build, simply run the commands below.

```
cmake -S /path/to/lsgfw -B /path/to/build
cd /path/to/build
cmake --build .
```

You'll then find a shared library file inside your build directory.

## Usage
