#include "popup.h"

ConfirmationPopup::ConfirmationPopup(std::string message) : message(message), Popup(u8"Potwierdź akcję") {}

void ConfirmationPopup::renderContent()
{
    result = false;
    ImGui::Text(message.c_str());
    if (ImGui::Button("Tak"))
    {
        result = true;
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Anuluj"))
    {
        ImGui::CloseCurrentPopup();
    }
}

bool ConfirmationPopup::confirmed() 
{ 
    bool oldValue = result;
    result = false;
    return oldValue; 
}