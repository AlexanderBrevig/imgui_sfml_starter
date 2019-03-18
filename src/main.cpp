#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/OpenGL.hpp>

int main() {
    auto mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "imgui_sfml_starter");
    window.setView(sf::View(sf::FloatRect(0.f, 0.f, mode.width, mode.height)));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.resetGLStates(); 

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time deltaTime = deltaClock.restart();
        ImGui::SFML::Update(window, deltaTime);
        auto size = window.getSize();

        auto windowPos = ImVec2(.0f, 20.0f);
        ImGui::SetNextWindowPos(windowPos);
        auto contentRegion = ImGui::GetWindowContentRegionMax();
        contentRegion.y -= windowPos.y + 10;
        ImGui::SetWindowSize(size);
        ImGui::SetNextWindowContentSize(contentRegion);
        ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());

        ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        ImGui::DrawLine(sf::Vector2<float>(0, 0), sf::Vector2<float>(20, 20), sf::Color::Blue);
        
        ImGui::SetWindowFontScale(3);
        ImGui::Text("Welcome to this Dear ImGui & SFML boilerplate.");
        ImGui::SetWindowFontScale(1);
        if (ImGui::CollapsingHeader("Getting Started")) {
            ImGui::Text("PROGRAMMER GUIDE:");
            ImGui::BulletText("Please see src/main.cpp");
        }

        ImGui::End();

        window.clear(ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}