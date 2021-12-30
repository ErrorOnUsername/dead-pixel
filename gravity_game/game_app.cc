#include <DeadPixel.h>
#include <DeadPixelEntry.h>

#include <GameLayer.h>

class GameEntry : public DP::Application {
public:
	GameEntry () { push_layer(new GameLayer()); }
	~GameEntry() { }
};

DP::Application* create_application()
{
	return new GameEntry;
}
