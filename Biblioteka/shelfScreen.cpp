#include "screen.h"
#include "guiRenderer.h"
#include "guiUtils.h"

ShelfScreen::ShelfScreen(GuiRenderer& guiRenderer) : Screen(guiRenderer, u8"Zawartość półki") {}

void ShelfScreen::renderHeader()
{
	char* shelfName = (char*)guiRenderer.selectedShelf->name.c_str();
	if (ImGui::Button(u8"Powrót"))
	{
		guiRenderer.currentMode = LIBRARY;
	}
	ImGui::SameLine();
	if (ImGui::InputText("##shelfName", shelfName, 100))
	{
		guiRenderer.selectedShelf->name = shelfName;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Nowa książka"))
	{
		guiRenderer.selectedShelf->addBook(BookData());
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Usuń półkę"))
	{

	}
}

void ShelfScreen::renderContents()
{
	int i = 0;
	for (Book& b : guiRenderer.selectedShelf->getBooks())
	{
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
