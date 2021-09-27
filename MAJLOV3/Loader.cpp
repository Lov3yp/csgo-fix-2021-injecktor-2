#include "Config.h"
#include "WndProc.h"
#include "Guard.h"
#include <fstream>
#include <string>
#include "LoadLibrary.h"
#include "scam.h"
// DirectX
#include <d3d9.h>

#using <System.dll>
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);
void ToClipboard(const char* text)
{
	if (OpenClipboard(0))
	{
		EmptyClipboard();
		char* clip_data = (char*)(GlobalAlloc(GMEM_FIXED, MAX_PATH));
		lstrcpy(clip_data, text);
		SetClipboardData(CF_TEXT, (HANDLE)(clip_data));
		LCID* lcid = (DWORD*)(GlobalAlloc(GMEM_FIXED, sizeof(DWORD)));
		*lcid = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_NEUTRAL), SORT_DEFAULT);
		SetClipboardData(CF_LOCALE, (HANDLE)(lcid));
		CloseClipboard();
	}
}
static bool meme = CheckLicense();
static bool RevengerLicense = CheckLicense();
static bool SpectroLicense = CheckLicenseSpectro();
static int listbox_item_current = 0;



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// им€ будущего класса
	LPCTSTR lpzClass = NAME;

	// регистраци€ класса
	if (!RegMyWindowClass(hInstance, lpzClass))
		return 1;

	// вычисление координат центра экрана
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect); // разрешение экрана
	int x = screen_rect.right / 2 - 150;
	int y = screen_rect.bottom / 2 - 75;

	// создание диалогового окна
	HWND hWnd = CreateWindow(lpzClass, NAME, WS_POPUP, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	// если окно не создано, описатель будет равен 0
	if (!hWnd) return 2;

	// Initialize Direct3D
	LPDIRECT3D9 pD3D;
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		UnregisterClass(lpzClass, hInstance);
	}

	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // Present without vsync, maximum unthrottled framerate

	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
	{

		pD3D->Release();
		UnregisterClass(lpzClass, hInstance);
		return 0;

	}

	// Setup ImGui binding
	ImGui_ImplDX9_Init(hWnd, g_pd3dDevice);

	ImGuiStyle& style = ImGui::GetStyle();
	
	style.FramePadding = ImVec2(4, 2);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 4.0f;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameRounding = 2.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	
	static int hue = 140;
	static float col_main_sat = 180.f / 255.f;
	static float col_main_val = 161.f / 255.f;
	static float col_area_sat = 124.f / 255.f;
	static float col_area_val = 100.f / 255.f;
	static float col_back_sat = 59.f / 255.f;
	static float col_back_val = 40.f / 255.f;

	ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
	ImVec4 col_main = ImColor::HSV(hue / 255.f, col_main_sat, col_main_val);
	ImVec4 col_back = ImColor::HSV(hue / 255.f, col_back_sat, col_back_val);
	ImVec4 col_area = ImColor::HSV(hue / 255.f, col_area_sat, col_area_val);

	style.Colors[ImGuiCol_Text] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(col_text.x, col_text.y, col_text.z, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_col = ImColor(0, 0, 0, 255);
	


	// Main loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui_ImplDX9_NewFrame();

		DWORD dwFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

		static bool open = true;

		if (!open)
			ExitProcess(0);

		ImGui::Begin(NAME_LOADER, &open, ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), 1.0f, dwFlag );
		{
			//	ImGui::Button("ok? da", ImVec2(100, 0));




				static int iPage = 3;

				if (iPage == 3)
				{
					ImGui::BeginChild(("Tabs"), ImVec2(0, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
					{


						if (ImGui::Button("Cheats", ImVec2(ImGui::GetWindowWidth() / 2 - 10, ImGui::GetWindowHeight() / 2 - 9)))
							iPage = 0;
						ImGui::SameLine();
						if (ImGui::Button("Help", ImVec2(ImGui::GetWindowWidth() / 2 - 10, ImGui::GetWindowHeight() / 2 - 9)))
							iPage = 1;
						if (ImGui::Button("Info", ImVec2(ImGui::GetWindowWidth() / 2 - 10, ImGui::GetWindowHeight() / 2 - 9)))
							iPage = 2;
						ImGui::SameLine();
						if (ImGui::Button("Staff", ImVec2(ImGui::GetWindowWidth() / 2 - 10, ImGui::GetWindowHeight() / 2 - 9)))
							iPage = 4;
					}
					ImGui::EndChild();
				}

				if (iPage != 3)
				{
					ImGui::BeginChild(("Return"), ImVec2(0, 30), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
					{
						if (ImGui::Button("Return ", ImVec2(50, ImGui::GetWindowHeight() - 15)))
							iPage = 3;
					}
					ImGui::EndChild();
					ImGui::BeginChild(("Window"), ImVec2(0, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
					{

						if (iPage == 0)
						{
							{
								ImGui::BeginChild(("Imput Cheat"), ImVec2(ImGui::GetWindowWidth() / 2 - 10, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
								{
									const char* cheats[] = { "Antiscam.cc 37", "Antiscam.cc 48"};


									ImGui::PushItemWidth(ImGui::GetWindowWidth() / 1.1);
									ImGui::ListBox("##list", &listbox_item_current, cheats, ARRAYSIZE(cheats), 9);
								}
								ImGui::EndChild();
							}
							ImGui::SameLine();
							{
								ImGui::BeginChild(("Inject Panel"), ImVec2(ImGui::GetWindowWidth() / 2 - 10, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
								{
									if (listbox_item_current == 0)
									{
											//ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Activated Product");

											if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() / 1.1, 30)))
											{
											
												{
													HRESULT hr;
//													char *appdata = getenv("APPDATA"); //appdata

													LPCTSTR Url = _T("http://`/cheat228.dll"), File = _T("C://Windows//dll1.dll");// nazvanie dll ne trogai!111!!!!!!
													hr = URLDownloadToFile(0, Url, File, 0, 0);
													switch (hr)
													{
													case S_OK:
														cout << "Successful download\n";
														break;
													case E_OUTOFMEMORY:
														cout << "Out of memory error\n";
														break;
													case INET_E_DOWNLOAD_FAILURE:
														cout << "Cannot access server data\n";
														break;
													default:
														cout << "Unknown error\n";
														break;
													}
													Sleep(7000);
													string proccessname;
													string dllname;
													proccessname = "csgo.exe";
													dllname = "dll1.dll";
													scam1->loadlibrarymain(proccessname.c_str(), dllname.c_str());
													//zdes bibi
												}

											}
										
									}
									if (listbox_item_current == 1)
									{
										if (!SpectroLicense)
											ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Dont have License");
										if (SpectroLicense)
										{
											ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Activated Product");

											if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() / 1.1, 30)))
											{
												{
													HRESULT hr;
													//char *appdata = getenv("APPDATA"); //appdata

													LPCTSTR Url = _T("http://`/cheat.dll"), File = _T("C://Windows//dll.dll");// nazvanie dll ne trogai!111!!!!!!
													hr = URLDownloadToFile(0, Url, File, 0, 0);
													switch (hr)
													{
													case S_OK:
														cout << "Successful download\n";
														break;
													case E_OUTOFMEMORY:
														cout << "Out of memory error\n";
														break;
													case INET_E_DOWNLOAD_FAILURE:
														cout << "Cannot access server data\n";
														break;
													default:
														cout << "Unknown error\n";
														break;
													}
													Sleep(7000);
													string proccessname;
													string dllname;
													proccessname = "csgo.exe";
													dllname = "dll.dll";
													load_library->loadlibrarymain(proccessname.c_str(), dllname.c_str());
													//zdes bibi
												}

											}
										}
									}

								}
								ImGui::EndChild();
							}





						}
						if (iPage == 1) {
							ImGui::BeginChild(("Help"), ImVec2(ImGui::GetWindowWidth(), 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
							{
								static int iPageSub = 0;

								{
									ImGui::BeginChild(("SubInject"), ImVec2(115, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
									{
										if (ImGui::Button("Inject", ImVec2(100, 30)))
											iPageSub = 0;

										if (ImGui::Button("NoInject", ImVec2(100, 30)))
											iPageSub = 1;

										if (ImGui::Button("HWID", ImVec2(100, 30)))
											iPageSub = 2;
									}
									ImGui::EndChild();
								}
								ImGui::SameLine();
								{
									ImGui::BeginChild(("SubInject2"), ImVec2(ImGui::GetWindowWidth() / 1.6, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
									{
										if (iPageSub == 0)
										{
											ImGui::Text("");
											ImGui::Text("");
											ImGui::Text(" 1) Open CSGO");
											ImGui::Text(" 2) Chose cheat");
											ImGui::Text(" 3) Click on button Inject");
											ImGui::Text(" 4) Open Cheat on insert");
										}
										if (iPageSub == 1)
										{
											ImGui::Text(" ");
											ImGui::Text(" ");
											ImGui::Text(" ");
											ImGui::Text(" Disable your Anti Virus");
											ImGui::Text(" Open with name Administrator");

										}
										if (iPageSub == 2)
										{
											ImGui::Text(" ");
											ImGui::Text(" ");

											ImGui::Text(" If you want Reset HWID \n Write Support");
											if (ImGui::Button("Open Dialog with Support", ImVec2(180, 20)))
												System::Diagnostics::Process::Start("https://vk.com/");

										}
									}
									ImGui::EndChild();
								}


							}
							ImGui::EndChild();
						}
						if (iPage == 2)
						{
							ImGui::BeginChild(("Information"), ImVec2(ImGui::GetWindowWidth(), 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
							{
								ImGui::BeginChild(("Information3"), ImVec2(ImGui::GetWindowWidth() - 25, 30), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
								{
									if (!meme)
									{
										ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), " Your HWID : ");
										ImGui::SameLine();
										ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", GetSerial());
										ImGui::SameLine();


										if (ImGui::Button("Copy", ImVec2(100, 0)))
											ToClipboard(GetSerial().c_str());
									}
									if (meme)
									{
										ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), " Your HWID : ");
										ImGui::SameLine();
										ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", GetSerial());
										ImGui::SameLine();


										if (ImGui::Button("Copy", ImVec2(100, 0)))
											ToClipboard(GetSerial().c_str());
									}
								}
								ImGui::EndChild();
								ImGui::BeginChild(("Information2"), ImVec2(ImGui::GetWindowWidth() - 25, 0), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
								{
									if (ImGui::Button("VK PAGE", ImVec2(100, 30)))
										System::Diagnostics::Process::Start("https://vk.com/spectrofobia_noofficial");
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}



					}
					ImGui::EndChild();

				}

		}
		ImGui::End();
		
		

		// Rendering
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

			//D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*255.0f), (int)(clear_color.y*255.0f), (int)(clear_color.z*255.0f), (int)(clear_color.w*255.0f));
			//g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
			if (g_pd3dDevice->BeginScene() >= 0)
			{
				ImGui::Render();
				g_pd3dDevice->EndScene();
			}
			g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	ImGui_ImplDX9_Shutdown();
	if (g_pd3dDevice) g_pd3dDevice->Release();
	if (pD3D) pD3D->Release();
	UnregisterClass(NAME, hInstance);

	return 0;
}

////////////////////////////////////////////////////////////////////////// 
// функци€ регистрации класса окон

ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
	WNDCLASS wcWindowClass = { 0 };
	// адрес ф-ции обработки сообщений
	wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
	// стиль окна
	wcWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	// дискриптор экземпл€ра приложени€
	wcWindowClass.hInstance = hInst;
	// название класса
	wcWindowClass.lpszClassName = lpzClassName;
	// загрузка курсора
	wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// загрузка цвета окон
	wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	return RegisterClass(&wcWindowClass); // регистраци€ класса
}

