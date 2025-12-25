#pragma once
#include "imgui.h"
#include <string>
#include "popup.h"

class GuiRenderer;

class Screen
{
protected:
	GuiRenderer& guiRenderer;
	std::string name;

	virtual void renderHeader() = 0;
	virtual void renderContents() = 0;

public:
	Screen(GuiRenderer& guiRenderer, std::string name);

	void render();
};

class LibraryScreen : public Screen
{
private:
	void renderHeader() override;
	void renderContents() override;

public:
	LibraryScreen(GuiRenderer& guiRenderer);
};

class ShelfScreen : public Screen
{
private:
	ConfirmationPopup popup;

	void renderHeader() override;
	void renderContents() override;

public:
	ShelfScreen(GuiRenderer& guiRenderer);
};

class BookScreen : public Screen
{
private:
	ConfirmationPopup popup;

	void renderRowHeader(const char* headerName);
	void renderHeader() override;
	void renderContents() override;

public:
	BookScreen(GuiRenderer& guiRenderer);
};

class SearchScreen : public Screen
{
private:
	void renderHeader() override;
	void renderContents() override;

public:
	SearchScreen(GuiRenderer& guiRenderer);
};
