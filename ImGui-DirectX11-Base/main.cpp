#include "pch.h"
#include "WindowManager/WindowManager.h"

static WindowManager g_WndMgr;

int main()
{
    bool is_show = true;
    while (true)
    {
        if (!g_WndMgr.BeginFrame()) break;

        // Draw stuff here

        // Menu is here
        if (is_show)
        {
            ImGui::ShowDemoWindow();
        }

        g_WndMgr.EndFrame();
    }
}