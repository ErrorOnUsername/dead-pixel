#include "imgui_layer.hh"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <core/application.hh>

namespace DP {

static void init_dead_pixel_style_settings();

void ImGuiLayer::on_attach() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

#ifdef __APPLE__
	io.FontDefault = io.Fonts->AddFontFromFileTTF("/System/Library/Fonts/SFNS.ttf", 18.0f);
#elif defined(_WIN32)
	// FIXME: Verify that this is the right path
	io.FontDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 18.0f);
#endif

	init_dead_pixel_style_settings();

	ImGuiStyle& style = ImGui::GetStyle();
	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	GLFWwindow* window = (GLFWwindow*)Application::current_window()->window_handle;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 400 core");
}

void ImGuiLayer::on_detach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::end()
{
	Window* window = Application::current_window();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(window->data.width,window->data.height);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_context);
	}
}

static void init_dead_pixel_style_settings()
{
	ImVec4 dp_purple_dark   = ImVec4(0.35f, 0.00f, 0.50f, 1.0f);
	ImVec4 dp_purple        = ImVec4(0.45f, 0.09f, 0.60f, 1.0f);
	ImVec4 dp_purple_bright = ImVec4(0.55f, 0.19f, 0.70f, 1.0f);

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text]                  = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg]               = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border]                = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive]         = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	colors[ImGuiCol_TitleBg]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive]         = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered]  = dp_purple;
	colors[ImGuiCol_ScrollbarGrabActive]   = dp_purple_bright;
	colors[ImGuiCol_CheckMark]             = dp_purple;
	colors[ImGuiCol_SliderGrab]            = dp_purple;
	colors[ImGuiCol_SliderGrabActive]      = dp_purple_bright;
	colors[ImGuiCol_Button]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered]         = dp_purple;
	colors[ImGuiCol_ButtonActive]          = dp_purple_bright;
	colors[ImGuiCol_Header]                = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered]         = dp_purple;
	colors[ImGuiCol_HeaderActive]          = dp_purple_bright;
	colors[ImGuiCol_Separator]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered]      = dp_purple;
	colors[ImGuiCol_SeparatorActive]       = dp_purple_bright;
	colors[ImGuiCol_ResizeGrip]            = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered]     = dp_purple;
	colors[ImGuiCol_ResizeGripActive]      = dp_purple_bright;
	colors[ImGuiCol_Tab]                   = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered]            = dp_purple;
	colors[ImGuiCol_TabActive]             = dp_purple_dark;
	colors[ImGuiCol_TabUnfocused]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_DockingPreview]        = dp_purple_dark;
	colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines]             = dp_purple;
	colors[ImGuiCol_PlotLinesHovered]      = dp_purple;
	colors[ImGuiCol_PlotHistogram]         = dp_purple;
	colors[ImGuiCol_PlotHistogramHovered]  = dp_purple_bright;
	colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg]        = dp_purple_dark;
	colors[ImGuiCol_DragDropTarget]        = dp_purple;
	colors[ImGuiCol_NavHighlight]          = dp_purple_bright;
	colors[ImGuiCol_NavWindowingHighlight] = dp_purple_bright;
	colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding     = ImVec2(8.00f, 8.00f);
	style.FramePadding      = ImVec2(5.00f, 2.00f);
	style.CellPadding       = ImVec2(6.00f, 6.00f);
	style.ItemSpacing       = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing  = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing     = 25;
	style.ScrollbarSize     = 15;
	style.GrabMinSize       = 10;
	style.WindowBorderSize  = 1;
	style.ChildBorderSize   = 1;
	style.PopupBorderSize   = 1;
	style.FrameBorderSize   = 1;
	style.TabBorderSize     = 1;
	style.WindowRounding    = 0;
	style.ChildRounding     = 0;
	style.FrameRounding     = 0;
	style.PopupRounding     = 0;
	style.ScrollbarRounding = 0;
	style.GrabRounding      = 0;
	style.TabRounding       = 0;
	style.LogSliderDeadzone = 4;
}

}
