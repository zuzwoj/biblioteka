#include "screen.h"
#include "guiRenderer.h"
#include "imgui_stdlib.h"
#include <vector>

BookScreen::BookScreen(GuiRenderer& guiRenderer) : 
	popup(ConfirmationPopup(u8"Czy na pewno chcesz usunąć tę książkę?")),
	Screen(guiRenderer, u8"Szczegóły książki") { }

void BookScreen::renderRowHeader(const char* headerName)
{
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::Text(headerName);
	ImGui::TableSetColumnIndex(1);
}

void BookScreen::renderHeader()
{
	if (ImGui::Button(u8"Powrót"))
	{
		guiRenderer.currentMode = (guiRenderer.selectedShelf == nullptr) ? SEARCH : SHELF;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Usuń książkę"))
	{
		ImGui::OpenPopup(popup.getName());
	}
	popup.render();
	if (popup.confirmed())
	{
		guiRenderer.currentMode = SHELF;
		guiRenderer.selectedShelf->removeBook(*guiRenderer.selectedBook);
		guiRenderer.selectedBook = nullptr;
	}
}

void BookScreen::renderContents()
{
	if (guiRenderer.selectedBook == nullptr)
	{
		return;
	}
	if (ImGui::BeginTable("##bookDetails", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		renderRowHeader(u8"Tytuł");
		ImGui::InputText("##title", &guiRenderer.selectedBook->bookData.title);

		renderRowHeader("Autor");
		ImGui::InputText("##author", &guiRenderer.selectedBook->bookData.author);

		renderRowHeader("Rok wydania");
		ImGui::InputScalar("##year", ImGuiDataType_U32, &guiRenderer.selectedBook->bookData.year);

		renderRowHeader("Liczba stron");
		ImGui::InputScalar("##pages", ImGuiDataType_U32, &guiRenderer.selectedBook->bookData.pages);

		renderRowHeader(u8"Półka");
		std::vector<const char*> labels;
		std::vector<unsigned int> keys;
		std::map<unsigned int, Shelf>& shelves = guiRenderer.library.getShelves();
		for (auto& s : shelves)
		{
			keys.push_back(s.first);
			labels.push_back(s.second.name.c_str());
		}
		int currentIndex = std::find(
			keys.begin(), 
			keys.end(), 
			guiRenderer.selectedBook->bookData.shelf) - keys.begin();
		int oldIndex = currentIndex;
		if (ImGui::Combo("##shelf", &currentIndex, labels.data(), (int)labels.size()))
		{
			guiRenderer.selectedBook->bookData.shelf = keys[currentIndex];
			shelves.at(keys[currentIndex]).addBook(*guiRenderer.selectedBook);
			shelves.at(keys[oldIndex]).removeBook(*guiRenderer.selectedBook);
			guiRenderer.selectedBook = &shelves.at(keys[currentIndex]).getBooks().back();
			guiRenderer.selectedShelf = &shelves.at(currentIndex);
		}

		renderRowHeader("Przeczytana");
		ImGui::Checkbox("##read", &guiRenderer.selectedBook->bookData.read);

		ImGui::EndTable();
	}

	ImGui::InputTextMultiline(
		"##note", 
		&guiRenderer.selectedBook->bookData.note, 
		ImVec2(ImGui::GetIO().DisplaySize.x, 0), 
		ImGuiInputTextFlags_WordWrap);
}
