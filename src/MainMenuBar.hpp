#ifndef MAIN_MENU_BAR_HPP
#define MAIN_MENU_BAR_HPP

#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "imgui.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class MainMenuBar
{
  public:
    using StateChangeCallback = std::function<void(std::string, bool)>;
    MainMenuBar()
    {
        std::ifstream i("menu.json");
        i >> j;
    }
    void consume(std::string bind) {
        hadState[bind] = false;
    }
    bool has(std::string bind) {
        return hadState[bind];
    }
    void setBinding(std::string bind, bool val) {
        state[bind] = val;
    }
    void setListBinding(std::string bind, std::vector<std::string> list) {
        listBindings[bind] = list;
    }
    void observeState(std::string state, StateChangeCallback cb)
    {
        observers[state].push_back(cb);
    }
    void notify(std::string state, std::string data,  bool isActive)
    {
        for (auto &cb : observers[state])
        {
            cb(data, isActive);
        }
    }
    bool draw()
    {
        if (ImGui::BeginMainMenuBar())
        {
            for (auto &element : j["mainMenu"])
            {
                if (element["type"].is_string() && element["type"].get<std::string>() == "Menu" && element["name"].is_string())
                {
                    std::string name = element["name"].get<std::string>();
                    bool clicked = ImGui::BeginMenu(name.c_str());
                    setState(name, name, clicked);
                    if (clicked && element["items"].is_array())
                    {
                        renderItems(element["items"]);
                    }
                }
            }

            ImGui::EndMainMenuBar();
            return true;
        }
        return false;
    }

  private:
    std::map<std::string, std::vector<StateChangeCallback>> observers;
    void setState(std::string name, std::string data, bool newState)
    {
        bool prevState = state[name.c_str()];
        state[name.c_str()] = newState;
        if (prevState != newState && newState)
        {
            hadState[name] = true;
            notify(name, data, newState);
        }
        
    }
    void renderItems(json &items)
    {
        for (auto &element : items)
        {
            if (element["type"].is_string())
            {
                if (element["type"].get<std::string>() == "MenuItem")
                {
                    std::string name = element["name"].get<std::string>();
                    const char *nameCZ = name.c_str();
                    const char *shortcut = element["shortcut"].is_string() ? element["shortcut"].get<std::string>().c_str() : 0;
                    bool selected = element["shortcut"].is_boolean() ? element["shortcut"].get<bool>() : false;
                    bool enabled = element["enabled"].is_string()
                                       ? state[element["enabled"].get<std::string>()]
                                       : element["enabled"].is_boolean() ? element["enabled"].get<bool>() : true;
                    if (element["binding"].is_string())
                    {
                        bool clicked = ImGui::BeginMenu(nameCZ);
                        setState(name, name, clicked);
                        if (clicked)
                        {
                            for (auto &bind : listBindings[element["binding"].get<std::string>()])
                            {
                                std::string bindingName = name + ":" + bind;
                                bool clicked = ImGui::MenuItem(bind.c_str());
                                setState(element["binding"].get<std::string>(), bind, clicked);
                            }
                            ImGui::EndMenu();
                        }
                    }
                    else
                    {
                        bool clicked = ImGui::MenuItem(nameCZ, shortcut, selected, enabled);
                        setState(name, name, clicked);
                    }
                }
                else if (element["type"].get<std::string>() == "Separator")
                {
                    ImGui::Separator();
                }
            }
        }
        ImGui::EndMenu();
    }
    json j;
    std::map<std::string, bool> state;
    std::map<std::string, bool> hadState;
    std::map<std::string, std::vector<std::string>> listBindings;
};

#endif