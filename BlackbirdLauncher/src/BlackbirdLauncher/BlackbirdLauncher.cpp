
#include "Blackbird.h"

#include "BlackbirdLauncherLayer.h"

namespace Blackbird
{

	class BlackbirdLauncher : public Application
	{
	public:
		BlackbirdLauncher()
			: Blackbird::Application("BlackbirdLauncher")
		{
			PushLayer(std::make_shared<BlackbirdLauncherLayer>());
		}
	};

}

int main(int argc, char** argv)
{
	auto app = new Blackbird::BlackbirdLauncher{};
	app->Run();
	delete app;
}
