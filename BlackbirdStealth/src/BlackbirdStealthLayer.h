#pragma once

#include "Blackbird.h"

class BlackbirdStealthLayer : public Blackbird::Layer
{
public:
	BlackbirdStealthLayer();
	virtual ~BlackbirdStealthLayer();

public:
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Blackbird::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Blackbird::Event& event) override;

private:
	Blackbird::OrthographicCameraController m_CameraController;

	std::shared_ptr<Blackbird::VertexArray> m_TriangleVertexArray;
	std::shared_ptr<Blackbird::Shader> m_TriangleShader;
	std::shared_ptr<Blackbird::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Blackbird::Shader> m_SquareShader;
	glm::vec3 m_SquarePosition = glm::vec3(0.0f);
	float m_SquareMoveSpeed = 1.5f;

	glm::vec4 m_SquareBaseColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_SquareAlternateColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_SquareColor = m_SquareBaseColor;
};

