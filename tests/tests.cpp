#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

#include <imgui.h>
#include <SFML/System/Vector2.hpp>

unsigned int ImGui_Vec2_ToSFML(const ImVec2 vec) {
    const sf::Vector2<float> sfvec = vec;
    return sfvec.x == vec.x && sfvec.y == vec.y;
}

TEST_CASE("ImGui and sf::Vector2 can play nice", "[imgui_sfml]") {
    REQUIRE(ImGui_Vec2_ToSFML({ 0,0 }));
    REQUIRE(ImGui_Vec2_ToSFML({ -10.5f, 10.5f }));
    REQUIRE(ImGui_Vec2_ToSFML({ 3.1415f, 1.618f }));
    REQUIRE(ImGui_Vec2_ToSFML({ 10, 20 }));
}