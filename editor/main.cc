#include <core/application.hh>
#include <core/log.hh>

#include <editor_layer.hh>

int main()
{
	DP::Logger::init();
	DP::Application::init(1280, 720, "DeadPixel Editor");

	EditorLayer editor_layer;

	DP::Application::push_layer(&editor_layer);

	DP::Application::run();
}
