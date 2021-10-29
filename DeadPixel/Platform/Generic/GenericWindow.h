#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Core/Window.h>

namespace DP {

class GenericWindow : public Window {
	struct WindowData {
		const char* title;
		uint32_t width;
		uint32_t height;
		bool is_vsync_enabled;

		EventCallback event_callback;
	};
public:
	GenericWindow(WindowProperties const&);
	~GenericWindow();

	virtual void on_update() override;

	virtual inline uint32_t width() const override { return m_data.width; }
	virtual inline uint32_t height() const override { return m_data.height; }

	virtual void set_is_vsync_enabled(bool enabled) override;
	virtual inline bool is_vsync_enabled() const override { return m_data.is_vsync_enabled; }

	virtual void set_event_callback(EventCallback const& callback) override { m_data.event_callback = callback; }
private:
	GLFWwindow* m_window;

	WindowData m_data;
};

};
