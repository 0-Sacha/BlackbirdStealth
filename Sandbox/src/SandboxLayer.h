#pragma once

#include "Blackbird.h"

class SandboxLayer : public Blackbird::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

public:
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Blackbird::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Blackbird::Event& event) override;

private:
	Blackbird::Shader* m_Shader;
	Blackbird::Utils::OrthographicCameraController m_CameraController;

	GLuint m_QuadVA, m_QuadVB, m_QuadIB;

	glm::vec4 m_SquareBaseColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_SquareAlternateColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_SquareColor = m_SquareBaseColor;
};

