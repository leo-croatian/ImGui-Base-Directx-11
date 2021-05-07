#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <tchar.h>
#include <corecrt_wstdio.h>
#include "D2D1Helper.h"
#include <D2D1.h>
#include <d3d9.h>
#include <d3d9types.h>

static float size = 450;
bool fovcircle = false;

#define _CRT_SECURE_NO_WARNINGS

void SaveConfig()
{
    MessageBoxA(NULL, _T("Config Stored In C:\\Documents\\ZombieCheats\\"), _T("[+] Success"), MB_OK | MB_SYSTEMMODAL);
}
void Load()
{
    MessageBoxA(NULL, _T("Config Loaded"), _T("[+] Success"), MB_OK | MB_SYSTEMMODAL);
}

void DC()
{
	MessageBoxA(NULL, _T("This was made by kernel.sys#1111 on discord"), _T("[~] Info"), MB_OK | MB_SYSTEMMODAL);
}

void watermark()
{

	//watermark code here

}

void circlefovvv()
{
	static int cases = 0;
	static float r = 1.00f, g = 0.00f, b = 1.00f;
	switch (cases)
	{
	case 0: { r -= 0.010f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.010f; b -= 0.010f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.010f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.010f; g -= 0.010f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}

	ImGui::Begin("##fovcircle", nullptr, ImGuiWindowFlags_NoDecoration);

	auto draw = ImGui::GetBackgroundDrawList();

	draw->AddCircle(ImVec2(1920 / 2, 1080 / 2), size, IM_COL32(r, g, b, 255), 100, 1.0f);
	ImGui::End();
}

void RenderStyle()
{
	//==================================================
	//Below here is just to render our mouse cursor so it doesn't go behind the menu etc.

	ImGui::GetMouseCursor();
	ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);

	auto& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(650, 500); // This sets the minimum window size

	style.FrameBorderSize = 0;
	style.WindowRounding = 0;
	style.TabRounding = 0;
	style.ScrollbarRounding = 0;
	style.FramePadding = ImVec2(8, 6);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_TitleBg] = ImColor(227, 0, 40, 255);			// The top bar color
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(227, 0, 40, 255);			// When you press in the imgui menu
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(15, 15, 15, 50);		        // When the title is collapsed

	style.Colors[ImGuiCol_WindowBg] = ImColor(12, 12, 12, 255);				// Window Background

	style.Colors[ImGuiCol_Button] = ImColor(24, 25, 24, 255);			// button color
	style.Colors[ImGuiCol_ButtonActive] = ImColor(54, 53, 55);	        // button color when pressed
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(54, 53, 55);		    // button when hovered

	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 0, 255);			//check mark color

	style.Colors[ImGuiCol_FrameBg] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(36, 37, 36, 255);

	style.Colors[ImGuiCol_Header] = ImColor(24, 24, 24, 255);			// for collapsing headers , etc
	style.Colors[ImGuiCol_HeaderActive] = ImColor(54, 53, 55);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(24, 24, 24, 100);

	style.Colors[ImGuiCol_ResizeGrip] = ImColor(51, 49, 50, 255);		    // the resize grip thing bottom right
	style.Colors[ImGuiCol_ResizeGripActive] = ImColor(54, 53, 55);			// when you hold it / active
	style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(51, 49, 50, 255);			// when you hover over it

	style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 0, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 0, 0, 255);

	style.Colors[ImGuiCol_Border] = ImColor(54, 54, 54);

	style.Colors[ImGuiCol_Separator] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorActive] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorHovered] = ImColor(54, 54, 54);
}
