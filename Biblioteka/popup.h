#pragma once
#include <string>
#include "imgui.h"

class Popup
{
protected:
	std::string name;

	virtual void renderContent() = 0;

public:
	void render();
	const char* getName() { return name.c_str(); }

	Popup(std::string name);
};

class ConfirmationPopup : public Popup
{
private:
	bool result = false;
	std::string message;

	void renderContent() override;

public:
	ConfirmationPopup(std::string message);

	bool confirmed() { return result; }
};
