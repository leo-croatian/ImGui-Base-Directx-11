#include "includes.h"
#include "vars.h"
#include "main.h"
#include "xor.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("C:\\Users\\delic\\AppData\\Local\\Microsoft\\Windows\\Fonts\\Rubik-Bold.ttf", 20);
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

static int tabs;
bool show_menu = true;

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			Beep(659.26, 200);
			Beep(659.26, 200);
			Sleep(200);
			Beep(659.26, 200);
			Sleep(100);
			Beep(523.26, 200);
			Beep(659.26, 200);
			Sleep(200);
			Beep(783.98, 200);
			Sleep(400);
			Beep(391.99, 200);
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	if (GetAsyncKeyState(VK_END) & 1)
	{
		kiero::shutdown();
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show_menu = !show_menu;
	}
	if (GetAsyncKeyState(VK_HOME) & 1)
	{
		exit(0);
	}

	ImColor BoxColor;
	ImColor HealthColor;
	ImColor SkeletonColor;
	ImColor NameColor;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (show_menu)
	{

		ImGui::Begin("Menu Base", nullptr, ImGuiWindowFlags_NoDecoration);
		RenderStyle();

		ImGui::SetWindowSize(ImVec2(800, 600));
		if (ImGui::Button("Aimbot", ImVec2(150, 75)))
		{
			tabs = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Visuals", ImVec2(150, 75)))
		{
			tabs = 2;
		}
		ImGui::SameLine();
		if (ImGui::Button("World Visuals", ImVec2(150, 75)))
		{
			tabs = 3;
		}
		ImGui::SameLine();
		if (ImGui::Button("Misc", ImVec2(150, 75)))
		{
			tabs = 4;
		}
		ImGui::SameLine();
		if (ImGui::Button("Config", ImVec2(150, 75)))
		{
			tabs = 5;
		}
		ImGui::Separator();
		if (tabs == 1)
		{
			ImGui::Checkbox("Aimbot Enabled", &aimbot::aimbot_enabled);
			if (aimbot::aimbot_enabled)
			{
				ImGui::SliderFloat("Aimbot Distance", &aimbot::aimbot_distance, 0, 400);
			}
		}
		if (tabs == 2)
		{
			ImGui::Checkbox("Enable Player Esp", &visuals::player_esp);

			if (visuals::player_esp)
			{
				ImGui::Checkbox("Box Esp", &visuals::box_esp); // you can use the varaible visuals::box_esp for making a box esp ;) u just need to know how
				ImGui::Spacing();
				ImGui::Checkbox("Health Esp", &visuals::health_esp);
				ImGui::Spacing();
				ImGui::Checkbox("Skeleton Esp", &visuals::skeleton_esp);
				ImGui::Spacing();
				ImGui::Checkbox("Name Esp", &visuals::name_esp);
			}
		}
		if (tabs == 3)
		{
			ImGui::Checkbox("Food Esp", &world_visuals::food_esp);
		}
		if (tabs == 4)
		{
			ImGui::Checkbox("Fov Enabled", &misc::fov_enabled);
			if (misc::fov_enabled)
			{
				ImGui::SliderFloat("Fov Slider", &misc::fovslider, 0, 150);
			}
			ImGui::Checkbox("Fov Circle", &fovcircle);
			if (fovcircle)
			{
				ImGui::SliderFloat("Fov Circle Size", &size, 0, 1920);
			}
			ImGui::Checkbox("Watermark", &misc::watermark);
			if (misc::watermark)
			{
				watermark();
			}
		}
		if (tabs == 5)
		{
			if (ImGui::Button("Save Config"))
			{
				SaveConfig();
			}
			if (ImGui::Button("Load Config"))
			{
				Load();
			}
			if (ImGui::Button("Discord"))
			{
				DC();
			}
		}

		ImGui::End();
	}

	if (fovcircle)
	{

		ImGui::Begin("##fovcircle", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);

		auto draw = ImGui::GetBackgroundDrawList();

		draw->AddCircle(ImVec2(1920 / 2, 1080 / 2), size, IM_COL32(0, 255, 255, 255), 100, 1.0f);
		ImGui::End();
	}

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}