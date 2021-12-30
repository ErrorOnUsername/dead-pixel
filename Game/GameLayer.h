#pragma once

#include <DeadPixel.h>

class GameLayer : public DP::Layer {
public:
	GameLayer();

	virtual void on_update(float delta_time) override;
	virtual void on_event(DP::Event&) override;

	DP::RefPtr<DP::VertexArray> m_vertex_array;
	DP::RefPtr<DP::Shader> m_shader;

	DP::Camera m_camera;
	glm::mat4  m_cube_transform;
	float      m_cube_rotation;
};
