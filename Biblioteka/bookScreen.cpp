#include "screen.h"
#include "guiRenderer.h"
#include "imgui_stdlib.h"

BookScreen::BookScreen(GuiRenderer& guiRenderer) : 
	popup(ConfirmationPopup(u8"Czy na pewno chcesz usunąć tę książkę?")),
	Screen(guiRenderer, u8"Szczegóły książki") { }

void BookScreen::renderHeader()
{
	if (ImGui::Button(u8"Powrót"))
	{
		guiRenderer.currentMode = SHELF;
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
	}
}

void BookScreen::renderContents()
{
	if (ImGui::BeginTable("##bookDetails", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(u8"Tytuł");
		ImGui::TableSetColumnIndex(1);
		ImGui::InputText("##title", &guiRenderer.selectedBook->bookData.title);

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Autor");
		ImGui::TableSetColumnIndex(1);
		ImGui::InputText("##author", &guiRenderer.selectedBook->bookData.author);

		int year = (int)guiRenderer.selectedBook->bookData.year;
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Rok wydania");
		ImGui::TableSetColumnIndex(1);
		if (ImGui::InputInt("##year", &year))
		{
			if (year < 0)
			{
				year = 0;
			}
			guiRenderer.selectedBook->bookData.year = year;
		}

		ImGui::EndTable();
	}
	ImGui::InputTextMultiline(
		"##note", 
		&guiRenderer.selectedBook->bookData.note, 
		ImVec2(ImGui::GetIO().DisplaySize.x, 0), 
		ImGuiInputTextFlags_WordWrap);
}
