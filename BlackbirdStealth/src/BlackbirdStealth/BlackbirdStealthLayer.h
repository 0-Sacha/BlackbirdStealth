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
		Ref<Scene2D> m_Scene;

		Ref<SpritesFactoryLibrary> m_SpritesFactoryLibrary;
		Ref<Texture2D> m_Texture;
		Ref<Framebuffer> m_Framebuffer;

		Entity m_Square;
		Entity m_CameraOne;
		Entity m_CameraTwo;
	};

}
