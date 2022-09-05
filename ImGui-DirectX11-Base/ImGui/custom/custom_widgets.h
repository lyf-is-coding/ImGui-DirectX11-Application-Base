#pragma once

#include "../../pch.h"
#include "../imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui_internal.h"

#include "../utils/imgui_utils.h"

#include "../../Utils/Utils.h"

#ifndef _CUSTOM_WIDGETS_H_
#define _CUSTOM_WIDGETS_H_

namespace ImGui
{
	IMGUI_API bool ImageButton(ImTextureID texture_id, ImVec2 texture_size, const char* text, const char* text_end, const int text_line, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1));
}

#endif