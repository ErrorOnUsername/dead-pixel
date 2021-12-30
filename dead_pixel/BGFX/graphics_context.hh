#pragma once

namespace DP {

struct GraphicsContext {
	void* window_handle;

	GraphicsContext(void* window);

	void swap_buffers();
};

}
