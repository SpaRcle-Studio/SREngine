//
// Created by Monika on 07.07.2026.
//

#ifndef SR_ENGINE_IMMEDIATE_GUI_WINDOWS_IMPL_H
#define SR_ENGINE_IMMEDIATE_GUI_WINDOWS_IMPL_H

#ifdef SR_USE_IMGUI
#ifdef SR_WIN32
    extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

namespace SR_GRAPH_GUI_NS::Immediate {
#ifdef SR_WIN32
    static LRESULT ImGui_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (ImGui::GetCurrentContext() == NULL)
            return 0;

        ImGuiIO& io = ImGui::GetIO();

        switch (msg) {
            case WM_CHAR: {
                wchar_t wch;
                MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char*)&wParam, 1, &wch, 1);
                io.AddInputCharacter(wch);
                return 1;
            }
            default:
                break;
        }

        return 0;
    }

    static LRESULT ImmediateGUI_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (ImGui::GetCurrentContext() && !ImGui_WndProcHandler(hwnd, msg, wParam, lParam)) {
            if (ImGui::GetIO().BackendPlatformUserData && ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam)) {
                return true;
            }
        }
        return 0;
    }
#endif
}
#endif // SR_USE_IMGUI

#endif //SR_ENGINE_IMMEDIATE_GUI_WINDOWS_IMPL_H
