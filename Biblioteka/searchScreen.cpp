#include "screen.h"
#include "guiRenderer.h"
#include "guiUtils.h"

SearchScreen::SearchScreen(GuiRenderer& guiRenderer) : Screen(guiRenderer, "Wyniki wyszukiwania") {}

void SearchScreen::renderHeader()
{
	if (ImGui::Button(u8"Powrót"))
	{
		guiRenderer.currentMode = LIBRARY;
	}
}

void SearchScreen::renderContents()
{
	int i = 0;
	for (auto& s : guiRenderer.library.getShelves())
	{
		for (Book& b : s.second.getBooks())
		{
			switch (guiRenderer.searchParams.searchBy)
			{
			case TITLE:
				if (b.bookData.title.find(guiRenderer.searchParams.query) == std::string::npos)
				{
					continue;
				}
				break;
			case AUTHOR:
				if (b.bookData.author.find(guiRenderer.searchParams.query) == std::string::npos)
				{
					continue;
				}
				break;
			}
			ImGui::PushID(i);
			if (ImGui::Button(u8"Otwórz"))
			{
				guiRenderer.selectedBook = &b;
				guiRenderer.currentMode = BOOK;

			}
			ImGui::SameLine();
			ImGui::Text(b.bookData.title.c_str());
			ImGui::SameLine();
			ImGui::Text("|");
			ImGui::SameLine();
			ImGui::Text(b.bookData.author.c_str());
			ImGui::PopID();
			++i;
			GuiUtils::renderSeparator();
		}
	}
}
