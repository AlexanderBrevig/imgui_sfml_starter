#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/OpenGL.hpp>

#include "MainMenuBar.hpp"

int main()
{
    auto mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "imgui_sfml_starter");
    window.setView(sf::View(sf::FloatRect(0.f, 0.f, mode.width, mode.height)));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.resetGLStates(); // call it if you only process ImGui. Otherwise not needed.

    ImGui::SFML::Init(window);

    MainMenuBar menu;
    //set boolean bindings
    menu.setBinding("canUndo", false);
    menu.setBinding("canRedo", false);
    //populate list bindings
    menu.setListBinding("recentFiles", {"file1.txt", "file2.txt"});

    menu.observeState("recentFiles", [](std::string name, bool state) {
        std::cout << "Open recent file: " << name << std::endl;
    });
    menu.observeState("New", [](std::string name, bool state) {
        std::cout << "New file!" << std::endl;
    });

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

        menu.draw();
        auto windowPos = ImVec2(.0f, 20.0f);
        ImGui::SetNextWindowPos(windowPos);
        auto contentRegion = ImGui::GetWindowContentRegionMax();
        contentRegion.y -= windowPos.y + 10;
        ImGui::SetWindowSize(size);
        ImGui::SetNextWindowContentSize(contentRegion);
        ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());

        ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

        ImGui::SetWindowFontScale(3);
        ImGui::Text("Welcome to this Dear ImGui & SFML boilerplate.");
        ImGui::SetWindowFontScale(1);
        if (ImGui::CollapsingHeader("Getting Started")) {
            
            menu.setBinding("canRedo", true); //simulate a change - now the File->Redo is enabled
            ImGui::Text("PROGRAMMER GUIDE:");
            ImGui::BulletText("Please see src/main.cpp");
            ImGui::BulletText("Edit menu.json to suit your needs.");
            ImGui::BulletText("Then add menu.observeState to get notified when item is selected");
            ImGui::Text("FEATURE GUIDE:");
            ImGui::BulletText("Please click File->README and witness the new README section below");
        }

        if (menu.has("README")) {
            ImGui::Separator();
            if (ImGui::CollapsingHeader("menu.has(\"README\")")) {
                ImGui::Text("You can check for any state using menu.has(\"some string\")");
                
                if (ImGui::Button("menu.consume(\"README\")")){
                    menu.consume("README");
                }
            }
        }

        ImGui::End();

        window.clear(ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
    return 0;
}