#include "SceneHierarchyPanel.h"

#include "Blackbird/ImGui/ImGuiLayer.h"
#include "Blackbird/Scene/Components.h"

namespace Blackbird
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene2D>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene2D>& scene)
	{
		m_Context = scene;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->Registry().ForEachEntities([this](LECS::EntityId entityId) {
			Entity entity(this->m_Context.get(), entityId);

			this->DrawEntityNode(entity);
			});
		
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		TagComponent& tag = entity.Get<TagComponent>();

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		if (m_SelectionContext == entity)
			flags |= ImGuiTreeNodeFlags_Selected;
		bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity.GetEntityId().Id), flags, tag.Tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (open)
		{
			ImGui::TreePop();
		}

	}

}
