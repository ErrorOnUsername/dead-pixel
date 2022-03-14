#include <dead_pixel.hh>
#include <dead_pixel_entry.hh>

#include <editor_layer.hh>

class GameEntry : public DP::Application {
public:
	GameEntry () { push_layer(new EditorLayer()); }
	~GameEntry() { }
};

DP::Application* create_application()
{
	return new GameEntry;
}
