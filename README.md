# imgui_sfml_starter

Boilerplate for starting with ImGui and SFML for making applications

## Get The Source

### Either Fork It
    git clone --recurse-submodules https://github.com/YOUR_USER_NAME/imgui_sfml_starter

### Or Simple Clone It
    git clone --recurse-submodules https://github.com/AlexanderBrevig/imgui_sfml_starter

## Build it
### Linux

    cd imgui_sfml_starter
    cmake .
    make

### Windows

    cd imgui_sfml_starter
    code .
    # use the CMake Tools extension, and configure for x86 debug
    # build using Ctrl+Shift+P CMake: Build
    ./build/imgui_sfml_starter.exe
    
Alternatively use Visual Studio by going

    cd imgui_sfml_starter
    cmake .
    start imgui_sfml_starter.sln
    # now select imgui_sfml_starter as start up project
    # press F5 !    
    

## Libraries
- [SFML](https://github.com/SFML/SFML) - For sound streaming, window, clipboard and displaying graphics.
- [Dear ImGui](https://github.com/ocornut/imgui) - For anything GUI related.
- [Catch2](https://github.com/catchorg/Catch2/) - For testing
- [json](https://github.com/nlohmann/json) - For JSON read/write
- [fmt](https://github.com/fmtlib/fmt) - For formatting
- [cpplinq](https://github.com/mrange/cpplinq) - Higher order functions for range manipulations

## Contributions
Heavily based on the work of [SSBMTonberry](https://github.com/ssbmtonberry) and his [emu-jukebox](https://github.com/SSBMTonberry/emu-jukebox) project.

Thank you!
