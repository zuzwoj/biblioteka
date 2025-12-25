#include "screen.h"
#include "guiRenderer.h"
#include "library.h"
#include "guiUtils.h"

LibraryScreen::LibraryScreen(GuiRenderer& guiRenderer) : Screen(guiRenderer, u8"Półki") {}

void LibraryScreen::renderHeader()
{
	if (ImGui::Button(u8"Nowa półka"))
	{
		guiRenderer.library.addShelf(u8"Nowa półka");
	}
}

void LibraryScreen::renderContents()
{
	int i = 0;
	for (Shelf& s : guiRenderer.library.getShelves())
	{
		ImGui::PushID(i);
		if (ImGui::Button(u8"Otwórz"))
		{
			guiRenderer.selectedShelf = &s;
			guiRenderer.currentMode = SHELF;
		}
		ImGui::SameLine();
		ImGui::Text(s.name.c_str());
		ImGui::PopID();
		++i;
		GuiUtils::renderSeparator();
	}
}
