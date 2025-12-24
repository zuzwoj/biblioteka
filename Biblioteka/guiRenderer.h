#pragma once
#include "library.h"
#include "shelf.h"
#include "book.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum GuiMode
{
	LIBRARY, SHELF, BOOK
};

class GuiRenderer
{
private:
	const float DUMMY_HEIGHT = 3.0f;

	ImVec2 position = ImVec2(0, 0);
	GuiMode currentMode = GuiMode::LIBRARY;

	Library& library;
	Shelf* selectedShelf = nullptr;
	Book* selectedBook = nullptr;

	void renderSeparator();
	void renderHeaderSeparator();

	void renderShelves();
	void renderBooks(Shelf* shelf);
	void renderBook(Book* book);

public:
	GuiRenderer(Library& library);

	void render();
};
