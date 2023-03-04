
#include "Blackbird.h"

#include "BlackbirdSandboxLayer.h"

namespace Blackbird
{

	class BlackbirdSandbox : public Application
	{
	public:
		BlackbirdSandbox()
			: Blackbird::Application("Sandbox")
		{
			PushLayer(std::make_shared<BlackbirdSandboxLayer>());
		}
	};

}

int main(int argc, char** argv)
{
	auto app = new Blackbird::BlackbirdSandbox{};
	app->Run();
	delete app;
}
