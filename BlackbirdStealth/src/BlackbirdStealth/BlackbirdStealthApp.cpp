
#include "Blackbird.h"

#include "BlackbirdStealthLayer.h"
#include "BlackbirdTest/BlackbirdTest.h"

class BlackbirdStealth : public Blackbird::Application
{
public:
	BlackbirdStealth()
		: Blackbird::Application("Sandbox")
	{
		// PushLayer(new BlackbirdStealthLayer());
		PushLayer(new BlackbirdTest::Sandbox2D());
	}
};

int main(int argc, char** argv)
{
	auto app = new BlackbirdStealth();
	app->Run();
	delete app;
}
