
#include "Blackbird.h"

#include "SandboxLayer.h"

class Sandbox : public Blackbird::Application
{
public:
	Sandbox()
		: Blackbird::Application("Sandbox")
	{
		PushLayer(new SandboxLayer());
	}
};

Blackbird::Application* Blackbird::CreateApplication()
{
	return new Sandbox();
}
