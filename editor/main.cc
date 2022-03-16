#include <core/application.hh>

#include <editor_layer.hh>
#include <imgui_layer.hh>

int main()
{
	DP::Application::init(1280, 1024, "DeadPixel Editor");

	EditorLayer editor_layer;
	ImGUILayer  imgui_layer;

	DP::Application::push_layer(&editor_layer);
	DP::Application::push_layer(&imgui_layer);

	DP::Application::run();
}
