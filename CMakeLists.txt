cmake_minimum_required(VERSION 3.11)
project(imgui_sfml_starter)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSFML_STATIC")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(RELEASE 1)
    message("Building Release to: ${CMAKE_BINARY_DIR}")
else()
    set(DEBUG 1)
    message("Building Debug to: ${CMAKE_BINARY_DIR}")
endif()

if(UNIX AND NOT APPLE)
    set(LINUX 1)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
elseif(APPLE)
    link_directories(/usr/local/opt/llvm/lib/)
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 1)
    set(MSVC 0)
    set(MINGW 0)
elseif(WIN32)
    set(LINUX 0)
    set(WINDOWS 1)
    set(APPLE 0)
    if(MSVC)
        set(MSVC 1)
        set(MINGW 0)
    elseif(MINGW)
        set(MINGW 1)
        set(MSVC 0)
    endif()
else()
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
endif()

configure_file (
    "${PROJECT_SOURCE_DIR}/imgui_sfml_starter.h.in" 
    "${PROJECT_SOURCE_DIR}/imgui_sfml_starter.h")
    
configure_file(
    "${PROJECT_SOURCE_DIR}/src/menu.json"
    "${CMAKE_BINARY_DIR}/menu.json"
    COPYONLY)

include_directories(
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/
    ${PROJECT_SOURCE_DIR}/external_libs/fmt/include/
    ${PROJECT_SOURCE_DIR}/external_libs/sfml/include/
    ${PROJECT_SOURCE_DIR}/external_libs/)


set(FMT_SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/external_libs/fmt/src/format.cc 
    ${PROJECT_SOURCE_DIR}/external_libs/fmt/src/posix.cc)  

set(IMGUI_SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/imgui.cpp 
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/imconfig.h
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/imgui_draw.cpp 
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/imgui_demo.cpp 
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/misc/cpp/imgui_stdlib.cpp
    ${PROJECT_SOURCE_DIR}/external_libs/imgui/imgui-SFML.cpp)

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/main.cpp )

if(LINUX)
    set(SFML_DEPENDENCIES jpeg X11 Xrandr freetype xcb X11-xcb xcb-randr xcb-image GL FLAC ogg vorbis vorbisenc vorbisfile openal pthread)
    set(SFML_REST udev) #libudev
elseif(WIN32)
    if(MSVC)
        message("USING MSVC")
        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/SFML/lib/Debug/)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/SFML/lib/Release/)
        endif()

        set(SFML_DEPENDENCIES opengl32.lib winmm.lib gdi32.lib ws2_32.lib )
    else()
        message("USING MINGW - untested, consider using Visual Studio")
        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/SFML/lib/Debug/)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/SFML/lib/Release/)
        endif()
        set(SFML_DEPENDENCIES)
        set(SFML_DEPEND_2 opengl32 winmm gdi32 freetype jpeg)
    endif()
elseif(APPLE)
    message("USING CLANG!")
    set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/frameworks)

    set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/FLAC.framework ${PATH_SFML_DEPEND}/freetype.framework ${PATH_SFML_DEPEND}/ogg.framework ${PATH_SFML_DEPEND}/OpenAL.framework ${PATH_SFML_DEPEND}/vorbis.framework ${PATH_SFML_DEPEND}/vorbisenc.framework ${PATH_SFML_DEPEND}/vorbisfile.framework)
endif()

add_executable(imgui_sfml_starter_tests tests/tests.cpp)

if(LINUX)
    set(SFML_DEPENDENCIES jpeg X11 Xrandr freetype xcb X11-xcb xcb-randr xcb-image GL FLAC ogg vorbis vorbisenc vorbisfile openal pthread)
    set(SFML_REST udev) #libudev
    if(DEBUG)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/linux/debug)
        set(PATH_SFML_LIB ${PATH_LIBS}/sfml)
        set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
    elseif(RELEASE)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/linux/release)
        set(PATH_SFML_LIB ${PATH_LIBS}/sfml)
        set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
    endif()

    add_executable(imgui_sfml_starter ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES}  )
    target_link_libraries(imgui_sfml_starter stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
    target_link_libraries(imgui_sfml_starter_tests stdc++fs png ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES} ${SFML_REST})
elseif(WIN32)
    if(MSVC)
        set(PATH_LIBS ${PROJECT_SOURCE_DIR}/external_libs/libs/win)
        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/msvc/sfml)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/msvc/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/sfml-network-s-d.lib ${PATH_SFML_LIB}/sfml-audio-s-d.lib ${PATH_SFML_LIB}/sfml-main-d.lib ${PATH_SFML_LIB}/sfml-graphics-s-d.lib ${PATH_SFML_LIB}/sfml-window-s-d.lib ${PATH_SFML_LIB}/sfml-system-s-d.lib)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/msvc/sfml)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/msvc/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/sfml-network-s.lib ${PATH_SFML_LIB}/sfml-audio-s.lib ${PATH_SFML_LIB}/sfml-main.lib ${PATH_SFML_LIB}/sfml-graphics-s.lib ${PATH_SFML_LIB}/sfml-window-s.lib ${PATH_SFML_LIB}/sfml-system-s.lib)
        endif()
        
        set(SFML_DEPENDENCIES opengl32.lib winmm.lib gdi32.lib ${PATH_SFML_DEPEND}/freetype.lib ${PATH_SFML_DEPEND}/openal32.lib ${PATH_SFML_DEPEND}/flac.lib ${PATH_SFML_DEPEND}/vorbisenc.lib ${PATH_SFML_DEPEND}/vorbisfile.lib ${PATH_SFML_DEPEND}/vorbis.lib ${PATH_SFML_DEPEND}/ogg.lib ws2_32.lib )
        add_executable(imgui_sfml_starter ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} )
        target_link_libraries(imgui_sfml_starter ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
        target_link_libraries(imgui_sfml_starter_tests ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    else()
        if(DEBUG)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/mingw/sfml)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/debug/mingw/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
        elseif(RELEASE)
            set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/mingw/sfml)
            set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/win/release/mingw/sfml)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
        endif()
        set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/libfreetype.a ${PATH_SFML_DEPEND}/libFLAC.a ${PATH_SFML_DEPEND}/libogg.a ${PATH_SFML_DEPEND}/libopenal32.a ${PATH_SFML_DEPEND}/libvorbis.a ${PATH_SFML_DEPEND}/libvorbisenc.a ${PATH_SFML_DEPEND}/libvorbisfile.a)
        set(SFML_DEPEND_2 opengl32 winmm gdi32 freetype jpeg)
        add_executable(imgui_sfml_starter ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} )
        target_link_libraries(imgui_sfml_starter stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
        target_link_libraries(imgui_sfml_starter_tests stdc++fs ${MY_STATIC_LIBS} ${SFML_DEPENDENCIES})
    endif()
elseif(APPLE)
    set(PATH_SFML_DEPEND ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/frameworks)
    set(SFML_DEPENDENCIES ${PATH_SFML_DEPEND}/FLAC.framework ${PATH_SFML_DEPEND}/freetype.framework ${PATH_SFML_DEPEND}/ogg.framework ${PATH_SFML_DEPEND}/OpenAL.framework ${PATH_SFML_DEPEND}/vorbis.framework ${PATH_SFML_DEPEND}/vorbisenc.framework ${PATH_SFML_DEPEND}/vorbisfile.framework)
    set(SFML_BUILD_STATIC 1)
    if(DEBUG)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/debug/sfml)
        if(SFML_BUILD_STATIC)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s-d.a ${PATH_SFML_LIB}/libsfml-audio-s-d.a ${PATH_SFML_LIB}/libsfml-graphics-s-d.a ${PATH_SFML_LIB}/libsfml-window-s-d.a ${PATH_SFML_LIB}/libsfml-system-s-d.a)
        else()
            set(MY_DYNAMIC_LIBS ${PATH_SFML_LIB}/libsfml-network-d.dylib ${PATH_SFML_LIB}/libsfml-audio-d.dylib ${PATH_SFML_LIB}/libsfml-graphics-d.dylib ${PATH_SFML_LIB}/libsfml-window-d.dylib ${PATH_SFML_LIB}/libsfml-system-d.dylib)
        endif()
    elseif(RELEASE)
        set(PATH_SFML_LIB ${PROJECT_SOURCE_DIR}/external_libs/libs/osx/release/sfml)
        if(SFML_BUILD_STATIC)
            set(MY_STATIC_LIBS ${PATH_SFML_LIB}/libsfml-network-s.a ${PATH_SFML_LIB}/libsfml-audio-s.a ${PATH_SFML_LIB}/libsfml-graphics-s.a ${PATH_SFML_LIB}/libsfml-window-s.a ${PATH_SFML_LIB}/libsfml-system-s.a)
        else()
            set(MY_DYNAMIC_LIBS ${PATH_SFML_LIB}/libsfml-network.dylib ${PATH_SFML_LIB}/libsfml-audio.dylib ${PATH_SFML_LIB}/libsfml-graphics.dylib ${PATH_SFML_LIB}/libsfml-window.dylib ${PATH_SFML_LIB}/libsfml-system.dylib)
        endif()
    endif()

    set(FRAMEWORK_LIBS_BASE "-framework Carbon" "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation")

    set(MACOSX_BUNDLE_BUNDLE_NAME imgui_sfml_starter)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "alexanderbrevig.imgui_sfml_starter.boilerplate")
    set(MACOSX_BUNDLE_INFO_STRING "Boilerplate for ImGui and SFML")
    set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    add_executable(imgui_sfml_starter MACOSX_BUNDLE ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} )

    if(SFML_BUILD_STATIC)
        target_link_libraries(imgui_sfml_starter stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
        target_link_libraries(imgui_sfml_starter_tests stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_STATIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
    else()
        target_link_libraries(imgui_sfml_starter stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_DYNAMIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
        target_link_libraries(imgui_sfml_starter_tests stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${MY_DYNAMIC_LIBS} ${FRAMEWORK_LIBS_BASE} ${SFML_DEPENDENCIES})
        set_target_properties(imgui_sfml_starter PROPERTIES
                MACOSX_BUNDLE TRUE
                MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
                FRAMEWORK ${MY_DYNAMIC_LIBS})
    endif()
endif()

add_test(do_imgui_sfml_starter_tests imgui_sfml_starter_tests)
