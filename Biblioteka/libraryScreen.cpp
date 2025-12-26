#include "screen.h"
#include "guiRenderer.h"
#include "library.h"
#include "guiUtils.h"
#include "imgui_stdlib.h"

LibraryScreen::LibraryScreen(GuiRenderer& guiRenderer) : Screen(guiRenderer, u8"Półki") {}

void LibraryScreen::renderHeader()
{
	ImGui::Columns(2, "##columns", false);
	ImGui::SetColumnWidth(0, ImGui::GetIO().DisplaySize.x - 120.f);
	ImGui::SetNextItemWidth(100.0f);
	ImGui::Combo("##searchBy", &guiRenderer.searchParams.searchBy, guiRenderer.searchParams.searchTypes, 2);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(800.0f);
	ImGui::InputTextWithHint("##searchBar", u8"Wpisz szukaną frazę...", &guiRenderer.searchParams.query);
	ImGui::SameLine();
	if (ImGui::Button("Szukaj"))
	{
		guiRenderer.currentMode = SEARCH;
	}
	ImGui::NextColumn();
	ImGui::SetColumnWidth(1, 120.f);
	if (ImGui::Button(u8"Nowa półka"))
	{
		int assignedIndex = guiRenderer.library.addShelf(u8"Nowa półka");
		guiRenderer.selectedShelf = &guiRenderer.library.getShelves().at(assignedIndex);
		guiRenderer.currentMode = SHELF;
		guiRenderer.fileManager.persistShelves();
	}
	ImGui::Columns();
}

void LibraryScreen::renderContents()
{
	int i = 0;
	for (auto& s : guiRenderer.library.getShelves())
	{
		ImGui::PushID(i);
		if (ImGui::Button(u8"Otwórz"))
		{
			guiRenderer.selectedShelf = &s.second;
			guiRenderer.currentMode = SHELF;
		}
		ImGui::SameLine();
		ImGui::Text(s.second.name.c_str());
		ImGui::PopID();
		++i;
		GuiUtils::renderSeparator();
	}
}
