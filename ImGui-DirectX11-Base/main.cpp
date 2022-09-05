#include "main.h"

int main()
{
    HWND hwnd;
    WNDCLASSEX wc;

    if (!RenderSetup(hwnd, wc))
    {
        return 1;
    }

    bool is_show = true;
    while (true)
    {
        if (GetAsyncKeyState(VK_HOME) & 0x01)
        {
            is_show = !is_show;
            ChangeClickability(is_show, hwnd);
        }

        if (!NewFrame()) break;

        // ESP stuff here

        // Menu is here
        if (is_show)
        {
            ImGui::ShowDemoWindow();
        }

        Rendering();
    }

    Cleanup(hwnd, wc);
}