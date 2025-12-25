#pragma once
#include <glad/glad.h> 
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "guiRenderer.h"

class Application
{
private:
	const char* FONT_PATH = "C:/Windows/Fonts/arial.ttf";
	const float FONT_SIZE = 18.0f;

	GLFWwindow* window;
	ImGuiIO* io = nullptr;
	GuiRenderer* guiRenderer;
	Library* library;

	void initializeDummyLibrary();

public:
	bool initialize();
	void run();
	void cleanup();
};
