cmake_minimum_required(VERSION 3.11)
project(imgui_sfml_starter)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(CMAKE_CXX_FLAGS -DSFML_STATIC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSFML_STATIC")
set(BUILD_SHARED_LIBS OFF) #build SFML with static libs

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

include_directories(
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/
    ${PROJECT_SOURCE_DIR}/external_libs/fmt/include/
    ${PROJECT_SOURCE_DIR}/external_libs/sources/sfml/include/
    ${PROJECT_SOURCE_DIR}/external_libs/)


set(FMT_SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/external_libs/fmt/src/format.cc 
    ${PROJECT_SOURCE_DIR}/external_libs/fmt/src/posix.cc)  

set(IMGUI_SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/imconfig.h
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/imgui_demo.cpp
    #${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/misc/cpp/imgui_stdlib.cpp
    ${PROJECT_SOURCE_DIR}/external_libs/sources/imgui/imgui-SFML.cpp)

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/main.cpp )

add_subdirectory(external_libs/sources/SFML)

set(SFML_LIBS sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

add_executable(imgui_sfml_starter_tests tests/tests.cpp)

if(LINUX)
    add_executable(imgui_sfml_starter ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} )
    target_link_libraries(imgui_sfml_starter ${SFML_LIBS})
    target_link_libraries(imgui_sfml_starter_tests ${SFML_LIBS})
elseif(WIN32)
    add_executable(imgui_sfml_starter ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} )
    target_link_libraries(imgui_sfml_starter ${SFML_LIBS})
    target_link_libraries(imgui_sfml_starter_tests ${SFML_LIBS})
elseif(APPLE)
    set(FRAMEWORK_LIBS_BASE "-framework Carbon" "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" "-framework CoreFoundation")

    set(MACOSX_BUNDLE_BUNDLE_NAME imgui_sfml_starter)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "alexanderbrevig.imgui_sfml_starter.boilerplate")
    set(MACOSX_BUNDLE_INFO_STRING "Boilerplate for ImGui and SFML")
    set(MACOSX_BUNDLE_ICON_FILE "icon.icns")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

    add_executable(imgui_sfml_starter MACOSX_BUNDLE ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${FMT_SOURCE_FILES} )

    target_link_libraries(imgui_sfml_starter stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${SFML_LIBS} ${FRAMEWORK_LIBS_BASE} )
    target_link_libraries(imgui_sfml_starter_tests stdc++ -ObjC /usr/local/opt/llvm/lib/libc++experimental.a /usr/local/opt/llvm/lib/libc++fs.a ${SFML_LIBS} ${FRAMEWORK_LIBS_BASE} )
    set_target_properties(imgui_sfml_starter PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
            FRAMEWORK ${SFML_LIBS})
endif()

add_test(do_imgui_sfml_starter_tests imgui_sfml_starter_tests)
