#pragma once
#include <glad/glad.h> 
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Application
{
private:
	const int WINDOW_WIDTH = 1425;
	const int WINDOW_HEIGHT = 900;
	const char* FONT_PATH = "C:/Windows/Fonts/courbd.ttf";
	const float FONT_SIZE = 14.0f;

	GLFWwindow* window;
	ImGuiIO* io = nullptr;

public:
	bool initialize();
	void run();
	void cleanup();
};
