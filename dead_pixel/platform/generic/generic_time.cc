#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <core/time.hh>

namespace DP::Time {

float seconds_since_start() { return glfwGetTime(); }

}
