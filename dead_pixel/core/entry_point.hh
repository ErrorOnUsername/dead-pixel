#pragma once

extern DP::Application* create_application();

int main(int argc, char** argv)
{
	DP::Logger::init();

	DP::Application* application = create_application();
	application->run();
	delete application;
}
