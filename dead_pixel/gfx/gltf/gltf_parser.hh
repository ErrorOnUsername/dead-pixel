#pragma once

#include <gfx/gltf/gltf_spec.hh>

namespace DP {

struct GLTFParser {
	static ParsedGLTFFile from_file(char const* filepath);
};

}
