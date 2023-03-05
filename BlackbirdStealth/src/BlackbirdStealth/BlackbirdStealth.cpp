
#include "Blackbird.h"

#include "BlackbirdStealthLayer.h"

namespace Blackbird
{

	class BlackbirdStealth : public Application
	{
	public:
		BlackbirdStealth()
			: Blackbird::Application("BlackbirdStealth")
		{
			PushLayer(std::make_shared<BlackbirdStealthLayer>());
		}
	};

}

int main(int argc, char** argv)
{
	auto app = new Blackbird::BlackbirdStealth{};
	app->Run();
	delete app;
}
