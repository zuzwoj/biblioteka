#include "guiRenderer.h"

GuiRenderer::GuiRenderer(Library& library) : library(library) {}

void GuiRenderer::render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(position, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	switch (currentMode)
	{
	case GuiMode::LIBRARY:
		renderShelves();
		break;
	case GuiMode::SHELF:
		renderBooks(selectedShelf);
		break;
	case GuiMode::BOOK:
		renderBook(selectedBook);
		break;
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiRenderer::renderSeparator()
{
	ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
}

void GuiRenderer::renderHeaderSeparator()
{
	ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
	ImGui::Separator();
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
}

void GuiRenderer::renderShelves()
{
	ImGui::Begin(
		u8"Półki", 
		NULL, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	if (ImGui::Button(u8"Nowa półka"))
	{
		library.addShelf(u8"Nowa półka");
	}
	renderHeaderSeparator();
	int i = 0;
	for (Shelf& s : library.getShelves())
	{
		ImGui::PushID(i);
		if (ImGui::Button(u8"Otwórz"))
		{
			selectedShelf = &s;
			currentMode = SHELF;
		}
		ImGui::SameLine();
		ImGui::Text(s.name.c_str());
		ImGui::PopID();
		++i;
		renderSeparator();
	}
	ImGui::End();
}

void GuiRenderer::renderBooks(Shelf* shelf)
{
	ImGui::Begin(
		u8"Zawartość półki", 
		NULL, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	char* shelfName = (char*)shelf->name.c_str();
	if (ImGui::Button(u8"Powrót"))
	{
		currentMode = LIBRARY;
	}
	ImGui::SameLine();
	if (ImGui::InputText("##shelfName", shelfName, 100))
	{
		shelf->name = shelfName;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Nowa książka"))
	{
		shelf->addBook(BookData());
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Usuń półkę"))
	{

	}
	renderHeaderSeparator();
	int i = 0;
	for (Book& b : selectedShelf->getBooks())
	{
		ImGui::PushID(i);
		if (ImGui::Button(u8"Otwórz"))
		{
			selectedBook = &b;
			currentMode = BOOK;
		}
		ImGui::SameLine();
		ImGui::Text(b.bookData.title.c_str());
		ImGui::SameLine();
		ImGui::Text("|");
		ImGui::SameLine();
		ImGui::Text(b.bookData.author.c_str());
		ImGui::PopID();
		++i;
		renderSeparator();
	}
	ImGui::End();
}

void GuiRenderer::renderBook(Book* book)
{
	ImGui::Begin(
		u8"Szczegóły książki", 
		NULL, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	if (ImGui::Button(u8"Powrót"))
	{
		currentMode = SHELF;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Usuń książkę"))
	{

	}
	renderHeaderSeparator();
	if (ImGui::BeginTable("##bookDetails", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text(u8"Tytuł");
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(selectedBook->bookData.title.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Autor");
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(selectedBook->bookData.author.c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Rok wydania");
		ImGui::TableSetColumnIndex(1);
		ImGui::Text(std::to_string(selectedBook->bookData.year).c_str());

		ImGui::EndTable();
	}
	ImGui::TextWrapped(selectedBook->bookData.note.c_str());
	ImGui::End();
}
