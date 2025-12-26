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
		guiRenderer.fileManager.persistShelves();
	}
	ImGui::SameLine();
	ImGui::InputText("##shelfName", &guiRenderer.selectedShelf->name);
	ImGui::SameLine();
	if (ImGui::Button(u8"Nowa książka"))
	{
		guiRenderer.currentMode = BOOK;
		guiRenderer.fileManager.persistShelves();
		guiRenderer.selectedShelf->addBook(BookData());
		Book& newBook = guiRenderer.selectedShelf->getBooks().back();
		guiRenderer.selectedBook = &newBook;
		guiRenderer.fileManager.persistBook(newBook);
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
		for (auto& book : guiRenderer.selectedShelf->getBooks())
		{
			guiRenderer.fileManager.deleteBook(book);
		}
		guiRenderer.library.removeShelf(*guiRenderer.selectedShelf);
		guiRenderer.selectedShelf = nullptr;
		guiRenderer.fileManager.persistShelves();
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
