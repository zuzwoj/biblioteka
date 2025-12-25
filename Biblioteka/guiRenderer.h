#pragma once
#include "library.h"
#include "shelf.h"
#include "book.h"
#include "screen.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum GuiMode
{
	LIBRARY = 0, SHELF = 1, BOOK = 2
};

class GuiRenderer
{
private:
	Screen* screens[3] = { new LibraryScreen(*this), new ShelfScreen(*this), new BookScreen(*this) };
	ImVec2 position = ImVec2(0, 0);


public:
	GuiRenderer(Library& library);
	~GuiRenderer();

	GuiMode currentMode = GuiMode::LIBRARY;

	Library& library;
	Shelf* selectedShelf = nullptr;
	Book* selectedBook = nullptr;

	void render();
};
