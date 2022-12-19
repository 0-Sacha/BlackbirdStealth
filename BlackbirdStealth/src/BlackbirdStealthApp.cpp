
#include "Blackbird.h"

#include "BlackbirdStealthLayer.h"

class Sandbox : public Blackbird::Application
{
public:
	Sandbox()
		: Blackbird::Application("Sandbox")
	{
		PushLayer(new BlackbirdStealthLayer());
	}
};

Blackbird::Application* Blackbird::CreateApplication()
{
	return new Sandbox();
}
