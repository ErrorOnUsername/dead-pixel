#include <core/application.hh>

#include <editor_layer.hh>
#include <imgui_layer.hh>

int main()
{
	DP::Application app(1280, 1024, "DeadPixel Editor");

	EditorLayer editor_layer;
	ImGUILayer  imgui_layer;

	app.push_layer(&editor_layer);
	app.push_layer(&imgui_layer);

	app.run();
}
