#pragma once

#include <glm/glm.hpp>

#include <core/events.hh>
#include <core/layer.hh>
#include <core/scene.hh>
#include <gfx/framebuffer.hh>
#include <gfx/camera.hh>

struct EditorLayer : DP::Layer {
	DP::Framebuffer* framebuffer;
	DP::Camera*      editor_camera;
	DP::Scene*       test_scene;

	glm::vec2 current_viewport_size;
	glm::vec2 viewport_minimum_bounds;
	glm::vec2 viewport_maximum_bounds;

	void on_attach() override;

	void on_update(float delta_time) override;
	void on_imgui_render() override;

	void on_event(DP::Event&) override;
};
