#include "guiRenderer.h"

GuiRenderer::GuiRenderer(Library& library) : library(library) {}

void GuiRenderer::render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(position, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	screens[currentMode]->render();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GuiRenderer::~GuiRenderer()
{
	delete screens[0];
	delete screens[1];
	delete screens[2];
}
