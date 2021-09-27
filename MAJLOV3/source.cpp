#include "v_library.hpp"
#include "v_hook.hpp"
#include "logtut.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <d3d9.h>
#include "imgui/imgui_impl_dx9.h"

/////////////////////////// copyright /////////////////////////////////////////////////////////
/*                                                                                            \\
/*  __  __       _     _                        _               ____                           \\
/* |  \/  |     (_)   | |              ___     | |             |___ \                           \\
/* | \  / | __ _ _  __| | _____   __  ( _ )    | |     _____   ____) |_   _ _ __                 \\
/* | |\/| |/ _` | |/ _` |/ _ \ \ / /  / _ \/\  | |    / _ \ \ / /__ <| | | | '_ \   V2            \\
/* | |  | | (_| | | (_| |  __/\ V /  | (_>  <  | |___| (_) \ V /___) | |_| | |_) |                 \\
/* |_|  |_|\__,_| |\__,_|\___| \_/    \___/\/  |______\___/ \_/|____/ \__, | .__/                   \\
/*			 _/ |                                                    __/ | |                         \\
/*			|__/                                                    |___/|_|                          \\
/*All Rights - MajLov3 Rights Reserved.                                                                \\
/*2021 İnjeckt System - CSGO , LOADLIBRARY**************************************************************\\
/*Lov3yp#2018                                                                                            //
/*Majdev#3031                                                                                            //
/*https://discord.gg/S9r4xjpsAU                                                                          //
***********************************************************************************************************/

namespace MajdevLov3ypriv {
DWORD v_majlovGetGamePID() {
	HWND hwGame = FindWindowA(0, "Counter-Strike: Global Offensive");if (!hwGame) return 0;DWORD ret = 0;GetWindowThreadProcessId(hwGame, &ret);return ret;
}

std::string v_majlovLpcwstr2String(LPCWSTR lps) {
	int len = WideCharToMultiByte(CP_ACP, 0, lps, -1, NULL, 0, NULL, NULL);if (len <= 0) {return "";}else {char* dest = new char[len];WideCharToMultiByte(CP_ACP, 0, lps, -1, dest, len, NULL, NULL);dest[len - 1] = 0;std::string str(dest);delete[] dest;return str;
	}
}

std::string opendiscord()
{
	string opendiscord;
	ShellExecute(0, 0, L"https://discord.gg/S9r4xjpsAU", 0, 0, SW_SHOW);
	ShellExecute(0, 0, L"https://aimlity.com/", 0, 0, SW_SHOW);
	return opendiscord;
}

std::string v_majlovSelectDll() {
	OPENFILENAME ofn;char szFile[300];ZeroMemory(&ofn, sizeof(ofn));ofn.lStructSize = sizeof(ofn);ofn.hwndOwner = NULL;ofn.lpstrFile = (LPWSTR)szFile;ofn.lpstrFile[0] = '\0';LPTSTR        lpstrCustomFilter;DWORD         nMaxCustFilter;ofn.nFilterIndex = 1;LPTSTR        lpstrFile;ofn.nMaxFile = sizeof(szFile);ofn.lpstrFilter = L"DLL File\0*.dll";ofn.lpstrFileTitle = NULL;ofn.nMaxFileTitle = 0;ofn.lpstrInitialDir = NULL;ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	std::string path_image = "";
	if (GetOpenFileName(&ofn)) {
		path_image = v_majlovLpcwstr2String(ofn.lpstrFile);
		return path_image;
	}
	else {
		return "";
	}
}
string v_majlovpathcleoniqq()
{
  char shitter[_MAX_PATH];GetModuleFileNameA(NULL, shitter, _MAX_PATH);return string(shitter);
}

void v_majlovInjectDll(const char* path, DWORD pid) {
	HANDLE hGame = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);char dllpath[MAX_PATH];ZeroMemory(dllpath, sizeof(dllpath));strcpy_s(dllpath, path);LPVOID allocatedMem = VirtualAllocEx(hGame, NULL, sizeof(dllpath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);WriteProcessMemory(hGame, allocatedMem, dllpath, sizeof(dllpath), NULL);HANDLE hThread = CreateRemoteThread(hGame, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocatedMem, 0, 0);WaitForSingleObject(hThread, INFINITE);VirtualFreeEx(hGame, allocatedMem, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

string v_majlovpatchexenameqq(std::size_t length) {
    const string CHARACTERS = "bmRNODZ2ZFJuTTdkcVAxcjlxS1VHRDV0bk5kQUdaQ0Q=ndM86vdRnM7dqP1r9qKUGD5tnNdAGZCD";random_device random_device;std::mt19937 generator(random_device());std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);std::string random_string;for (std::size_t i = 0; i < length; ++i){random_string += CHARACTERS[distribution(generator)];}return random_string;
}


void v_majlovconsoleprint() {
std::cout << R"(
  __  __       _     _                        _               ____               
 |  \/  |     (_)   | |              ___     | |             |___ \              
 | \  / | __ _ _  __| | _____   __  ( _ )    | |     _____   ____) |_   _ _ __   
 | |\/| |/ _` | |/ _` |/ _ \ \ / /  / _ \/\  | |    / _ \ \ / /__ <| | | | '_ \  
 | |  | | (_| | | (_| |  __/\ V /  | (_>  <  | |___| (_) \ V /___) | |_| | |_) | 
 |_|  |_|\__,_| |\__,_|\___| \_/    \___/\/  |______\___/ \_/|____/ \__, | .__/  
             _/ |                                                    __/ | |     
            |__/                                                    |___/|_|     
--------------------------------------------------------------------------------------)" << '\n';
    
}

void v_majlovcheckInternet() {
	if (!InternetCheckConnectionA((LPCSTR)"https://aimlity.com/kontrol", FLAG_ICC_FORCE_CONNECTION, 0) && !InternetCheckConnectionA((LPCSTR)"https://aimlity.com/kontrol1", FLAG_ICC_FORCE_CONNECTION, 0)) {Logger::Write(XorString("no internet connection try again"), Logger::LoggerType.Error);Sleep(2000);exit(-1);}
}


}



int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);HWND kontrolgameproc;if (!(kontrolgameproc = ::FindWindow(NULL, L"Counter-Strike: Global Offensive"))){ MessageBox(0, L"Game Not Found Please open csgo.exe", L"Ops:(", MB_OK | MB_ICONERROR);exit(1);}
	else {
	LPCTSTR lpzClass = NAME;if (!Majlov3clas(hInstance, lpzClass))return 1;RECT screen_rect;GetWindowRect(GetDesktopWindow(), &screen_rect);int x = screen_rect.right / 2 - 150;int y = screen_rect.bottom / 2 - 75;HWND hWnd = CreateWindow(lpzClass, NAME, WS_SYSMENU, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);if (!hWnd) return 2;LPDIRECT3D9 pD3D;if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL){UnregisterClass(lpzClass, hInstance);}ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));g_d3dpp.Windowed = TRUE;g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;g_d3dpp.EnableAutoDepthStencil = TRUE;g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0){pD3D->Release();UnregisterClass(lpzClass, hInstance);return 0;}ImGui_ImplDX9_Init(hWnd, g_pd3dDevice);MSG lov3mesag; ZeroMemory(&lov3mesag, sizeof(lov3mesag)); ShowWindow(hWnd, SW_SHOWDEFAULT); UpdateWindow(hWnd); while (lov3mesag.message != WM_QUIT) {if (PeekMessage(&lov3mesag, NULL, 0U, 0U, PM_REMOVE)) { TranslateMessage(&lov3mesag); DispatchMessage(&lov3mesag); continue; }ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); ImGui_ImplDX9_NewFrame(); DWORD lov3xderms = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse|ImGuiWindowFlags_NoTitleBar; static bool menugostersxd = true; if (!menugostersxd)ExitProcess(0);
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_Button] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	ImGui::Begin("Lov3yp#Majdev - simple base#2", &menugostersxd, ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), 1.0f, lov3xderms);
	{
		   
		    ImGui::SetCursorPosX(50);
			ImGui::SetCursorPosY(50);
			if (ImGui::Button(">Injeckt<", ImVec2(280, 50))) {
				MajdevLov3ypriv::v_majlovcheckInternet();
				DWORD gamePID = MajdevLov3ypriv::v_majlovGetGamePID();
				if (!gamePID) {
					MessageBox(0, L"Game Not Found Please open csgo.exe", L"Ops:(", MB_OK | MB_ICONERROR);
					MajdevLov3ypriv::opendiscord();
					return 0;
				}
				baypshookgames::SetGamepid(gamePID);
				std::string dllpath = MajdevLov3ypriv::v_majlovSelectDll();
				if (dllpath == "") {
					MessageBox(0, L"dll Not Found Please open dll", L"Ops:(", MB_OK | MB_ICONERROR);
					MajdevLov3ypriv::opendiscord();
					return 0;
				}
				if (!baypshookgames::baypssfucka()) {
					MessageBox(0, L"bypass failed try again.", L"Ops:(", MB_OK | MB_ICONERROR);
					MajdevLov3ypriv::opendiscord();
					return 0;
				}
				MajdevLov3ypriv::v_majlovInjectDll(dllpath.c_str(), gamePID);
				baypshookgames::hookfuckcsgo();
				MessageBox(0, L"injeckt complete good games.", L"Succes:)", MB_OK | MB_ICONINFORMATION);
				MajdevLov3ypriv::opendiscord();
				return 0;


			}

		

	}
	ImGui::End();g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false); g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false); g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false); if (g_pd3dDevice->BeginScene() >= 0) { ImGui::Render(); g_pd3dDevice->EndScene(); }g_pd3dDevice->Present(NULL, NULL, NULL, NULL);}ImGui_ImplDX9_Shutdown(); if (g_pd3dDevice) g_pd3dDevice->Release(); if (pD3D) pD3D->Release(); UnregisterClass(NAME, hInstance);return 0;
  }
}







/////////////////////////// copyright /////////////////////////////////////////////////////////
/*                                                                                            \\
/*  __  __       _     _                        _               ____                           \\
/* |  \/  |     (_)   | |              ___     | |             |___ \                           \\
/* | \  / | __ _ _  __| | _____   __  ( _ )    | |     _____   ____) |_   _ _ __                 \\
/* | |\/| |/ _` | |/ _` |/ _ \ \ / /  / _ \/\  | |    / _ \ \ / /__ <| | | | '_ \   V2            \\
/* | |  | | (_| | | (_| |  __/\ V /  | (_>  <  | |___| (_) \ V /___) | |_| | |_) |                 \\
/* |_|  |_|\__,_| |\__,_|\___| \_/    \___/\/  |______\___/ \_/|____/ \__, | .__/                   \\
/*			 _/ |                                                    __/ | |                         \\
/*			|__/                                                    |___/|_|                          \\
/*All Rights - MajLov3 Rights Reserved.                                                                \\
/*2021 İnjeckt System - CSGO , LOADLIBRARY**************************************************************\\
/*Lov3yp#2018                                                                                            //
/*Majdev#3031                                                                                            //
/*https://discord.gg/S9r4xjpsAU                                                                          //
***********************************************************************************************************/