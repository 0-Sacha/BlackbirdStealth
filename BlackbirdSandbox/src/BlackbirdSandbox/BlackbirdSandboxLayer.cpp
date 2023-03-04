#include "BlackbirdSandboxLayer.h"

namespace Blackbird
{
	BlackbirdSandboxLayer::BlackbirdSandboxLayer()
		: Layer("BlackbirdSandboxLayer")
		, m_CameraController(S_Input::Get(), 16.0f / 9.0f, true)
	{
		m_Texture = S_TextureFactory::CreateTexture2DFromPath("Assets/texture/RGBA_comp.png");
		m_SpritesFactoryLibrary = S_TextureFactory::CreateSpritesFactoryLibraryFromPath("Assets/texture/RPGpack_sheet_2X.png", { 128, 128 });
		m_SpritesFactoryLibrary->AddSprite("Stairs", { 7, 6 });
		m_SpritesFactoryLibrary->AddSprite("Barrel", { 8, 2 });
		m_SpritesFactoryLibrary->AddSprite("BigGreenTree", { 0, 1 }, { 1, 2 });
	}

	void BlackbirdSandboxLayer::OnAttach()
	{
	}

	void BlackbirdSandboxLayer::OnDetach()
	{

	}

	static int lastFPSCount = 0;

	void BlackbirdSandboxLayer::OnUpdate(TimeStep ts)
	{
		S_Renderer2D::ResetStats();
		lastFPSCount = ts.GetFPS();

		m_CameraController.OnUpdate(ts);

		S_RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		S_RendererCommand::Clear();

		S_Renderer2D::BeginScene(m_CameraController.GetCamera());

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec2{ 0.0f, 0.0f })
			.SetColor(m_SquareColor);

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec2{ 2.0f, 2.0f })
			.SetSize(glm::vec2{ 0.5f, 0.5f })
			.SetRotation(glm::radians(45.0f))
			.SetColor(m_SquareColor);

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec3{ -5.0f, -5.0f, -0.1f })
			.SetSize(glm::vec2{ 10.f, 10.f })
			.SetRotation(glm::radians(20.0f))
			.SetTexture(m_Texture)
			.SetTilingFactor(10.0f);

		static float rotation = 0.0f;
		rotation += ts * 0.5f;

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec3{ 12.0f, 12.0f, -0.1f })
			.SetSize(glm::vec2{ 10.f, 10.f })
			.SetRotation(rotation)
			.SetTexture(m_Texture)
			.SetTilingFactor(20.0f);

		S_Renderer2D::EndScene();



		S_Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (float y = -50.0f; y < 50.0f; y += 0.5f)
			for (float x = -50.0f; x < 50.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 50.0f) / 100.0f, 0.3f, (y + 50.0f) / 100.0f, 0.4f };
				S_Renderer2D::DrawQuad()
					->SetPosition({ x, y })
					.SetSize({ 0.45f, 0.45f })
					.SetColor(color);
			}

		S_Renderer2D::EndScene();



		S_Renderer2D::BeginScene(m_CameraController.GetCamera());

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec3{ 1.0f, 0.0f, 0.5f })
			.SetTexture(m_SpritesFactoryLibrary->Get("Stairs"));

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec3{ 4.0f, 0.0f, 0.5f })
			.SetTexture(m_SpritesFactoryLibrary->Get("Barrel"));

		S_Renderer2D::DrawQuad()
			->SetPosition(glm::vec3{ 1.0f, 3.0f, 0.5f })
			.SetSize({ 1.0f, 2.0f })
			.SetTexture(m_SpritesFactoryLibrary->Get("BigGreenTree"));

		S_Renderer2D::EndScene();
	}

	void BlackbirdSandboxLayer::OnImGuiRender()
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	
		auto stats = S_Renderer2D::GetStats();
		ImGui::Begin("Renderer Statistics");
		ImGui::Text("FPS: %d", lastFPSCount);
		ImGui::Text("DrawCall: %d", stats.DrawCall);
		ImGui::BeginChild("QuadDesigner");
		ImGui::Text("QuadCount: %d", stats.QuadStats.QuadCount);
		ImGui::Text("VerticiesCount: %d", stats.QuadStats.GetVerticiesCount());
		ImGui::Text("IndiciesCount: %d", stats.QuadStats.GetIndiciesCount());
		ImGui::EndChild();
		ImGui::End();
	}

	void BlackbirdSandboxLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}

}
