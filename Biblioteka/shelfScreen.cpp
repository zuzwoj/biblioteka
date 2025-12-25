#include "screen.h"
#include "guiRenderer.h"
#include "guiUtils.h"
#include "imgui_stdlib.h"

ShelfScreen::ShelfScreen(GuiRenderer& guiRenderer) 
	: popup(ConfirmationPopup(u8"Czy na pewno chcesz usunąć tę półkę?")),
	Screen(guiRenderer, u8"Zawartość półki") {}

void ShelfScreen::renderHeader()
{
	if (ImGui::Button(u8"Powrót"))
	{
		guiRenderer.currentMode = LIBRARY;
	}
	ImGui::SameLine();
	ImGui::InputText("##shelfName", &guiRenderer.selectedShelf->name);
	ImGui::SameLine();
	if (ImGui::Button(u8"Nowa książka"))
	{
		guiRenderer.selectedShelf->addBook(BookData());
		guiRenderer.selectedBook = &guiRenderer.selectedShelf->getBooks().back();
		guiRenderer.currentMode = BOOK;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Usuń półkę"))
	{
		ImGui::OpenPopup(popup.getName());
	}
	popup.render();
	if (popup.confirmed())
	{
		guiRenderer.currentMode = LIBRARY;
		guiRenderer.library.removeShelf(*guiRenderer.selectedShelf);
		guiRenderer.selectedShelf = nullptr;
	}
}

void ShelfScreen::renderContents()
{
	if (guiRenderer.selectedShelf == nullptr)
	{
		return;
	}
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
