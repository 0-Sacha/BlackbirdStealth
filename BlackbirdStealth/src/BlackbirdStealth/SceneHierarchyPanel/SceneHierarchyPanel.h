#pragma once

#include "Blackbird/Core/Core.h"
#include "Blackbird/Scene/Scene2D.h"

namespace Blackbird
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene2D>& scene);

	public:
		void SetContext(const Ref<Scene2D>& scene);

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		template <typename T, typename Function>
		void DrawComponent(Entity entity, const char* label, Function function);

	private:
		Ref<Scene2D> m_Context{ nullptr };
		Entity m_SelectionContext;
	};
}
