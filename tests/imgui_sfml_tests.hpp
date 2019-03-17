#ifndef IMGUI_SFML_TESTS_H
#define IMGUI_SFML_TESTS_H

#include <imgui.h>
#include <SFML/System/Vector2.hpp>

unsigned int ImGui_Vec2_To_SFML_Vector2(const ImVec2 vec) {
    const sf::Vector2<float> sfvec = vec;
    return sfvec.x == vec.x && sfvec.y == vec.y;
}

unsigned int SFML_Vector2_To_ImGui_Vec2(const sf::Vector2<float> vec) {
    const ImVec2 imvec = vec;
    return imvec.x == vec.x && imvec.y == vec.y;
}

unsigned int SFML_Color_To_ImGui_Vec4(const sf::Color col) {
    const ImVec4 imvec = col;
    return imvec.x == col.r/255.f 
        && imvec.y == col.g/255.f  
        && imvec.z == col.b/255.f  
        && imvec.w == col.a/255.f;
}

unsigned int ImGui_Vec4_To_SFML_Color(const ImVec4 vec) {
    const sf::Color sfcol = vec;
    return sfcol.r == vec.x*255.f 
        && sfcol.g == vec.y*255.f  
        && sfcol.b == vec.z*255.f  
        && sfcol.a == vec.w*255.f;
}



TEST_CASE("ImGui and sf::Vector2 can play nice", "[imgui_sfml]") {
    REQUIRE(ImGui_Vec2_To_SFML_Vector2(ImVec2 { 0,0 }));
    REQUIRE(ImGui_Vec2_To_SFML_Vector2(ImVec2 { -10.5f, 10.5f }));
    REQUIRE(ImGui_Vec2_To_SFML_Vector2(ImVec2 { 3.1415f, 1.618f }));
    REQUIRE(ImGui_Vec2_To_SFML_Vector2(ImVec2 { 10, 20 }));
}

TEST_CASE("sf::Vector2 and ImGui can play nice", "[imgui_sfml]") {
    REQUIRE(SFML_Vector2_To_ImGui_Vec2(sf::Vector2<float> { 0,0 }));
    REQUIRE(SFML_Vector2_To_ImGui_Vec2(sf::Vector2<float> { -10.5f, 10.5f }));
    REQUIRE(SFML_Vector2_To_ImGui_Vec2(sf::Vector2<float> { 3.1415f, 1.618f }));
    REQUIRE(SFML_Vector2_To_ImGui_Vec2(sf::Vector2<float> { 10, 20 }));
}

TEST_CASE("sf::Color and ImGui can play nice", "[imgui_sfml]") {
    REQUIRE(SFML_Color_To_ImGui_Vec4(sf::Color::Red));
    REQUIRE(SFML_Color_To_ImGui_Vec4(sf::Color::Green));
    REQUIRE(SFML_Color_To_ImGui_Vec4(sf::Color::Blue));
    REQUIRE(SFML_Color_To_ImGui_Vec4(sf::Color::Transparent));
}

TEST_CASE("ImGui and sf::Color can play nice", "[imgui_sfml]") {
    REQUIRE(ImGui_Vec4_To_SFML_Color(ImVec4 {0,0,0,1}));
    REQUIRE(ImGui_Vec4_To_SFML_Color(ImVec4 {1,0,0,1}));
    REQUIRE(ImGui_Vec4_To_SFML_Color(ImVec4 {0,1,0,1}));
    REQUIRE(ImGui_Vec4_To_SFML_Color(ImVec4 {0,0,1,1}));
    REQUIRE(ImGui_Vec4_To_SFML_Color(ImVec4 {0,0,0,0}));
}

#endif