#pragma once
#include "library.h"
#include "shelf.h"
#include "book.h"
#include "screen.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum GuiMode
{
	LIBRARY = 0, SHELF = 1, BOOK = 2, SEARCH = 3
};

enum SearchMode
{
	TITLE = 0, AUTHOR = 1
};

struct SearchParams
{
	int searchBy = TITLE;
	const char* searchTypes[2] = { u8"Tytuł", "Autor" };
	std::string query = "";
};

class GuiRenderer
{
private:
	Screen* screens[4] = { 
		new LibraryScreen(*this), 
		new ShelfScreen(*this), 
		new BookScreen(*this), 
		new SearchScreen(*this) };
	ImVec2 position = ImVec2(0, 0);


public:
	GuiRenderer(Library& library);
	~GuiRenderer();

	GuiMode currentMode = GuiMode::LIBRARY;
	SearchParams searchParams;

	Library& library;
	Shelf* selectedShelf = nullptr;
	Book* selectedBook = nullptr;

	void render();
};
