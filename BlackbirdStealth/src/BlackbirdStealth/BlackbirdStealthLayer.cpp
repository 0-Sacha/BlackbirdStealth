
#include "BlackbirdStealthLayer.h"

#include "Platform/OpenGL/Renderer/OpenGLShader/OpenGLShader.h"

BlackbirdStealthLayer::BlackbirdStealthLayer()
	: m_CameraController(16.0f / 9.0f, true)
{

}

BlackbirdStealthLayer::~BlackbirdStealthLayer()
{

}

void BlackbirdStealthLayer::OnAttach()
{
	Blackbird::OpenGL::EnableOpenGlDebugging();

	m_TriangleVertexArray = Blackbird::VertexArray::Create();

	float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	std::shared_ptr<Blackbird::VertexBuffer> triangleVertexBuffer = Blackbird::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
	Blackbird::BufferLayout triangleLayout = {
		{ Blackbird::ShaderData::Type::Float3, "a_Position" },
		{ Blackbird::ShaderData::Type::Float4, "a_Color" }
	};
	triangleVertexBuffer->SetLayout(triangleLayout);
	m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

	uint32_t triangleIndices[] = { 0, 1, 2 };
	std::shared_ptr<Blackbird::IndexBuffer> triangleIndexBuffer = Blackbird::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
	m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);
	
	m_ShaderLibrary.LoadFromPath("assets/shaders/TriangleShader.glsl");
	
	m_SquareVertexArray = Blackbird::VertexArray::Create();

	float squareVertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	std::shared_ptr<Blackbird::VertexBuffer> squareVertexBuffer = Blackbird::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	Blackbird::BufferLayout squareLayout = {
		{ Blackbird::ShaderData::Type::Float3, "a_Position" },
		{ Blackbird::ShaderData::Type::Float2, "a_TexCoord" }
	};
	squareVertexBuffer->SetLayout(squareLayout);
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Blackbird::IndexBuffer> squareIndexBuffer = Blackbird::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	m_ShaderLibrary.LoadFromPath("assets/shaders/SquareShader.glsl");
	m_ShaderLibrary.LoadFromPath("assets/shaders/TexSquareShader.glsl");

	m_Texture = Blackbird::Texture2D::Create("assets/texture/TestTexture.png");
	m_BlendTexture = Blackbird::Texture2D::Create("assets/texture/RGBA_comp.png");

	m_ShaderLibrary.Get("TexSquareShader")->Bind();
	std::dynamic_pointer_cast<Blackbird::Platform::OpenGL::OpenGLShader>(m_ShaderLibrary.Get("TexSquareShader"))->UploadUniformInt("u_Texture", 0);
}

void BlackbirdStealthLayer::OnDetach()
{
}

void BlackbirdStealthLayer::OnUpdate(Blackbird::TimeStep ts)
{
	Blackbird::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Blackbird::RendererCommand::Clear();

	m_CameraController.OnUpdate(ts);

	if (Blackbird::Input::IsKeyPressed(Blackbird::KeyboardKey::J))
		m_SquarePosition.x -= m_SquareMoveSpeed * ts;
	else if (Blackbird::Input::IsKeyPressed(Blackbird::KeyboardKey::L))
		m_SquarePosition.x += m_SquareMoveSpeed * ts;
	
	if (Blackbird::Input::IsKeyPressed(Blackbird::KeyboardKey::I))
		m_SquarePosition.y += m_SquareMoveSpeed * ts;
	else if (Blackbird::Input::IsKeyPressed(Blackbird::KeyboardKey::K))
		m_SquarePosition.y -= m_SquareMoveSpeed * ts;

	Blackbird::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	
	m_ShaderLibrary.Get("SquareShader")->Bind();
	std::dynamic_pointer_cast<Blackbird::Platform::OpenGL::OpenGLShader>(m_ShaderLibrary.Get("SquareShader"))->UploadUniformFloat4("u_Color", m_SquareColor);

	for (auto i = 0; i < 5; i++)
	{
		for (auto j = 0; j < 5; j++)
		{
			glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
			glm::mat4 subTransform = glm::translate(transform, pos) * scale;
			Blackbird::Renderer::Submit(m_ShaderLibrary.Get("SquareShader"), m_SquareVertexArray, subTransform);
		}
	}

	glm::mat4 bigSquareTransform = glm::scale(glm::mat4(1.0f), glm::vec3{ 0.3f, 0.3f, 0.3f });
	m_Texture->Bind();
	Blackbird::Renderer::Submit(m_ShaderLibrary.Get("TexSquareShader"), m_SquareVertexArray, bigSquareTransform);

	m_BlendTexture->Bind();
	Blackbird::Renderer::Submit(m_ShaderLibrary.Get("TexSquareShader"), m_SquareVertexArray, bigSquareTransform);

	// Blackbird::Renderer::Submit(m_TriangleShader, m_TriangleVertexArray);

	Blackbird::Renderer::EndScene();
}

void BlackbirdStealthLayer::OnImGuiRender()
{
	ImGui::Begin("Controls");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void BlackbirdStealthLayer::OnEvent(Blackbird::Event& event)
{
	m_CameraController.OnEvent(event);
	Blackbird::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<Blackbird::MouseButtonPressedEvent>(
		[&](Blackbird::MouseButtonPressedEvent& e)
		{
			return false;
		});

	dispatcher.Dispatch<Blackbird::MouseButtonReleasedEvent>(
		[&](Blackbird::MouseButtonReleasedEvent& e)
		{
			return false;
		});
}