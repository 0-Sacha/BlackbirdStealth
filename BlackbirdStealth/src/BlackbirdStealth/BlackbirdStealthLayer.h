#pragma once

#include "Blackbird.h"

namespace Blackbird
{

	class BlackbirdStealthLayer : public Layer
	{
	public:
		BlackbirdStealthLayer();

	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(TimeStep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_CameraController;
		Ref<SpritesFactoryLibrary> m_SpritesFactoryLibrary;
		Ref<Texture2D> m_Texture;
		Ref<Framebuffer> m_Framebuffer;

		glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	};

}
