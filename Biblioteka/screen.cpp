#include "screen.h"
#include "guiUtils.h"

Screen::Screen(GuiRenderer& guiRenderer, std::string name) : guiRenderer(guiRenderer), name(name) { }

void Screen::render()
{
	ImGui::Begin(
		name.c_str(),
		NULL,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	renderHeader();
	GuiUtils::renderHeaderSeparator();
	renderContents();
	ImGui::End();
}
