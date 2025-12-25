#include "screen.h"
#include "guiRenderer.h"

BookScreen::BookScreen(GuiRenderer& guiRenderer) : Screen(guiRenderer, u8"Szczegóły książki") { }

void BookScreen::renderHeader()
{
	if (ImGui::Button(u8"Powrót"))
	{
		guiRenderer.currentMode = SHELF;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Usuń książkę"))
	{

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
		ImGui::Text(guiRenderer.selectedBook->bookData.title.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Autor");
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(guiRenderer.selectedBook->bookData.author.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Rok wydania");
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(std::to_string(guiRenderer.selectedBook->bookData.year).c_str());

		ImGui::EndTable();
	}
	ImGui::TextWrapped(guiRenderer.selectedBook->bookData.note.c_str());
}
