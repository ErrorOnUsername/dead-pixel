#pragma once

#include <dead_pixel.hh>

class GameLayer : public DP::Layer {
public:
	GameLayer();

	void on_update(float delta_time) override;
	void on_event(DP::Event&) override;

	bool on_mouse_scrolled(DP::MouseScrolledEvent&);

	DP::RefPtr<DP::VertexArray> m_vertex_array;
	DP::RefPtr<DP::Shader> m_shader;

	DP::PersectiveCamera   m_camera;
	DP::OrthographicCamera m_ui_camera;
	glm::mat4              m_cube_transform;
	float                  m_cube_rotation;
	float                  m_zoom;
};
