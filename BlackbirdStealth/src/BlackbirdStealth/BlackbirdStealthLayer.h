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

	Blackbird::ShaderLibrary m_ShaderLibrary;

	Blackbird::Ref<Blackbird::VertexArray> m_TriangleVertexArray;
	Blackbird::Ref<Blackbird::VertexArray> m_SquareVertexArray;
	
	Blackbird::Ref<Blackbird::Texture> m_Texture;
	Blackbird::Ref<Blackbird::Texture> m_BlendTexture;


	glm::vec3 m_SquarePosition = glm::vec3(0.0f);
	float m_SquareMoveSpeed = 1.5f;

	glm::vec4 m_SquareColor = glm::vec4(0.9f, 0.1f, 0.8f, 1.0f);
};
