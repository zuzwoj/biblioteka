#include "popup.h"

Popup::Popup(std::string name) : name(name) { } 

void Popup::render()
{
    if (ImGui::BeginPopupModal(name.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        renderContent();
        ImGui::EndPopup();
    }
}
