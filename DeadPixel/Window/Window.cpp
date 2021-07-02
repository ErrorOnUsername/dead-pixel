#include "Window.h"

Window::Window(uint32_t width, uint32_t height, bool fullscreen)
    : m_width      (width)
    , m_height     (height)
    , m_fullscreen (fullscreen)
{

}

Window::~Window()
{}