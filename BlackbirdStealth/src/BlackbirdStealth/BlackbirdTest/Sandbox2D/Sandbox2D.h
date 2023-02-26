#pragma once

#include "Blackbird.h"

namespace BlackbirdTest
{

class Sandbox2D : public Blackbird::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Blackbird::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Blackbird::Event& event) override;

public:
	Blackbird::OrthographicCameraController m_CameraController;
	Blackbird::Ref<Blackbird::VertexArray> m_SquareVA;
	Blackbird::Ref<Blackbird::Shader> m_FlatColorShader;
	Blackbird::Ref<Blackbird::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
};

}
