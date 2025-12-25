#include "guiUtils.h"

namespace GuiUtils
{
	float DUMMY_HEIGHT = 3.0f;

	void renderSeparator()
	{
		ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
	}

	void renderHeaderSeparator()
	{
		ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, DUMMY_HEIGHT));
	}
}
