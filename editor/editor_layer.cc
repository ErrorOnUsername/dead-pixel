#include "editor_layer.hh"
#include <cstdio>

void EditorLayer::on_update(float delta_time)
{
	printf("dt: %f\n", delta_time);
}

void EditorLayer::on_event(DP::Event& e)
{ }
