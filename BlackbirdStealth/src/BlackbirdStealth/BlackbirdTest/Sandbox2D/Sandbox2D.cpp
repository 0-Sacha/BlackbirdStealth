
#include "Sandbox2D.h"

#include "Platform/OpenGL/Engine/OpenGLShader/OpenGLShader.h"

namespace BlackbirdTest
{

	Sandbox2D::Sandbox2D()
		: Blackbird::Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
	{
		m_Texture = Blackbird::TextureFactory::CreateTexture2D("assets/texture/RGBA_comp.png");
	}

	void Sandbox2D::OnAttach()
	{
	}

	void Sandbox2D::OnDetach()
	{

	}

	void Sandbox2D::OnUpdate(Blackbird::TimeStep ts)
	{
		m_CameraController.OnUpdate(ts);

		Blackbird::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Blackbird::RendererCommand::Clear();

		Blackbird::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Blackbird::Renderer2D::DrawQuad(glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f }, 0.0f, m_SquareColor);
		Blackbird::Renderer2D::DrawQuad(glm::vec2{ 2.0f, 2.0f }, glm::vec2{ 0.5f, 0.5f }, 45.0f * glm::pi<float>() / 180.0f, m_SquareColor);

		Blackbird::Renderer2D::DrawQuad(glm::vec3{ 0.0f, 0.0f, -0.1f }, glm::vec2{ 10.f, 10.f }, 20.0f * glm::pi<float>() / 180.0f, m_Texture);

		Blackbird::Renderer2D::EndScene();
	}

	void Sandbox2D::OnImGuiRender()
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void Sandbox2D::OnEvent(Blackbird::Event& event)
	{
		m_CameraController.OnEvent(event);
	}

}
