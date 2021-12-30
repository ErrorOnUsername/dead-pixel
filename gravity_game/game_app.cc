#include <dead_pixel.hh>
#include <dead_pixel_entry.hh>

#include <game_layer.hh>

class GameEntry : public DP::Application {
public:
	GameEntry () { push_layer(new GameLayer()); }
	~GameEntry() { }
};

DP::Application* create_application()
{
	return new GameEntry;
}
