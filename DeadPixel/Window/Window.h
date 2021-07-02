#pragma once

#include <cstdint>
namespace DP {

class Window {
public:
    Window(uint32_t width = 1024, uint32_t height = 576, bool fullscreen = false);
    ~Window();

    bool is_fullscreen();
    void set_fullscreen(bool);

    bool should_close();
    void set_should_close(bool);

private:
	uint32_t m_width;
	uint32_t m_height;

	bool m_fullscreen;
};

}