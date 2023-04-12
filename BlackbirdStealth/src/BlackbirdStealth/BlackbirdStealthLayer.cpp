#include "BlackbirdStealthLayer.h"

#include "Blackbird/EngineUtils/UtilsScripts/CameraControllerScript.h"

namespace Blackbird
{
	BlackbirdStealthLayer::BlackbirdStealthLayer()
		: Layer("BlackbirdStealthLayer")
	{}
	
	
	void BlackbirdStealthLayer::OnAttach()
	{
		S_Application::GetImGuiLayer().EnableDockspace();

		m_Texture = S_TextureFactory::CreateTexture2DFromPath("Assets/texture/RGBA_comp.png");
		m_SpritesFactoryLibrary = S_TextureFactory::CreateSpritesFactoryLibraryFromPath("Assets/texture/RPGpack_sheet_2X.png", { 128, 128 });
		m_SpritesFactoryLibrary->AddSprite("Stairs", { 7, 6 });
		m_SpritesFactoryLibrary->AddSprite("Barrel", { 8, 2 });
		m_SpritesFactoryLibrary->AddSprite("BigGreenTree", { 0, 1 }, { 1, 2 });

		FramebufferSpecification framebufferSpecification;
		framebufferSpecification.Height = 180;
		framebufferSpecification.Width = 320;
		m_Framebuffer = S_FramebufferFactory::Create(framebufferSpecification);

		m_Scene = std::make_shared<Scene2D>(S_Renderer2D::GetRef());
		m_Square = m_Scene->CreateEntity("Square");
		m_Square.Add<SpritRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		m_CameraOne = m_Scene->CreateEntity("CameraOne");
		m_CameraOne.Add<SceneCameraComponent>().ResizeAspectRatioOnViewport = true;
		m_CameraOne.Add<NativeScriptComponent>().Bind<CameraControllerScript>(m_CameraOne, m_ApplicationLinked->GetEngineContext().Input());

		m_CameraTwo = m_Scene->CreateEntity("CameraTwo");
		m_CameraTwo.Add<SceneCameraComponent>().ResizeAspectRatioOnViewport = true;
		m_CameraTwo.Add<NativeScriptComponent>().Bind<CameraControllerScript>(m_CameraTwo, m_ApplicationLinked->GetEngineContext().Input());
		m_Scene->SetPrimatryCameraEntity(m_CameraOne);
	}

	void BlackbirdStealthLayer::OnDetach()
	{

	}

	static int lastFPSCount = 0;

	void BlackbirdStealthLayer::OnUpdate(TimeStep ts)
	{
		S_Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		
		S_RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		S_RendererCommand::Clear();

		m_Scene->OnUpdate(ts);

		m_Framebuffer->Release();
	}

	/*
		lastFPSCount = ts.GetFPS();

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
		*/

	void BlackbirdStealthLayer::OnImGuiRender()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) { S_Application::Close(); }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Viewport");
		if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
			S_Application::GetImGuiLayer().BlockEvent();
		else
			S_Application::GetImGuiLayer().UnblockEvent();

		std::uint32_t framebufferID = m_Framebuffer->GetColorAttachementID();
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		ImGui::Image((void*)framebufferID, viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		if (viewportSize.x > 0 && viewportSize.y > 0)
		{
			m_Scene->OnViewportResize(viewportSize.x, viewportSize.y);
			m_Framebuffer->Resize(viewportSize.x, viewportSize.y);
		}
		ImGui::End();

		ImGui::Begin("Setting");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_Square.Get<SpritRendererComponent>().Color));
		ImGui::End();
		ImGui::PopStyleVar();

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

		ImGui::Begin("Camera");
		if (ImGui::Button("Switch camera"))
		{
			if (m_Scene->GetPrimatryCameraEntity() == m_CameraOne)
			{
				m_CameraTwo.Get<NativeScriptComponent>().Enable = true;
				m_CameraOne.Get<NativeScriptComponent>().Enable = false;
				m_Scene->SetPrimatryCameraEntity(m_CameraTwo);
			}
			else
			{
				m_CameraOne.Get<NativeScriptComponent>().Enable = true;
				m_CameraTwo.Get<NativeScriptComponent>().Enable = false;
				m_Scene->SetPrimatryCameraEntity(m_CameraOne);
			}
		}

		ImGui::DragFloat3("Tranform Camera One", glm::value_ptr(m_CameraOne.Get<TransformComponent>().Transform[3]), 0.1f);
		float orthoSizeCameraOne = m_CameraOne.Get<SceneCameraComponent>().Camera.GetOrthographicSize();
		if (ImGui::DragFloat("Orthographic Size Camera One", &orthoSizeCameraOne, 0.1f))
			m_CameraOne.Get<SceneCameraComponent>().Camera.SetOrthographicSize(orthoSizeCameraOne);

		ImGui::DragFloat3("Tranform Camera Two", glm::value_ptr(m_CameraTwo.Get<TransformComponent>().Transform[3]), 0.1f);
		float orthoSizeCameraTwo = m_CameraTwo.Get<SceneCameraComponent>().Camera.GetOrthographicSize();
		if (ImGui::DragFloat("Orthographic Size Camera Two", &orthoSizeCameraTwo, 0.1f))
			m_CameraTwo.Get<SceneCameraComponent>().Camera.SetOrthographicSize(orthoSizeCameraTwo);

		ImGui::End();
	}

	void BlackbirdStealthLayer::OnEvent(Event& event)
	{
	}

}
