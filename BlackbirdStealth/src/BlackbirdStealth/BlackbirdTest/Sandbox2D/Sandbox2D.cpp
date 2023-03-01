
#include "Sandbox2D.h"

#include "Platform/GraphicsPlatform/OpenGL/Engine/OpenGLShader/OpenGLShader.h"

namespace BlackbirdTest
{

	Sandbox2D::Sandbox2D()
		: Blackbird::Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
	{
		m_Texture = Blackbird::S_TextureFactory::CreateTexture2D("assets/texture/RGBA_comp.png");
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

		Blackbird::S_RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Blackbird::S_RendererCommand::Clear();

		Blackbird::S_Renderer2D::BeginScene(m_CameraController.GetCamera());

		Blackbird::S_Renderer2D::CreateQuadDesigner()
			.SetPosition(glm::vec2{ 0.0f, 0.0f })
			.SetColor(m_SquareColor)
			.DefaultDraw();

		Blackbird::S_Renderer2D::CreateQuadDesigner()
			.SetPosition(glm::vec2{ 2.0f, 2.0f })
			.SetSize(glm::vec2{ 0.5f, 0.5f })
			.SetRotation(glm::radians(45.0f))
			.SetColor(m_SquareColor)
			.DefaultDraw();

		Blackbird::S_Renderer2D::CreateQuadDesigner()
			.SetPosition(glm::vec3{ 0.0f, 0.0f, -0.1f })
			.SetSize(glm::vec2{ 10.f, 10.f })
			.SetRotation(glm::radians(20.0f))
			.SetTexture(m_Texture)
			.DefaultDraw();

		Blackbird::S_Renderer2D::EndScene();
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
