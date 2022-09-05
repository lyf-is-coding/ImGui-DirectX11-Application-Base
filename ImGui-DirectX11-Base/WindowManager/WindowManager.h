#pragma once

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "../ImGui/imgui.h"
#include "../ImGui/backends/imgui_impl_win32.h"
#include "../ImGui/backends/imgui_impl_dx11.h"
#include "../ImGui/stb/stb_image.h"

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WindowManager
{
private:
	ImFont* SEGOEUI_20;

public:
	WindowManager();
	~WindowManager();

	bool BeginFrame() const;
	void EndFrame() const;

	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

	bool IsDone = false;
	HWND hwnd;
	WNDCLASSEX wc;
};

#endif // !WINDOWMANAGER_H
