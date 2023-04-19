#include "SceneHierarchyPanel.h"

#include "Blackbird/ImGui/ImGuiLayer.h"
#include "Blackbird/Scene/Components.h"

#include "SceneHierarchyPanel.inl"

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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext.Invalidate();
		
		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext.IsValid())
			DrawComponents(m_SelectionContext);
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

	static void DrawVec3Control(const char* label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label);
		ImGui::NextColumn();
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.Has<TagComponent>())
		{
			std::string& tag = entity.Get<TagComponent>().Tag;
			ImGui::InputText("Tag", &tag);
		}

		DrawComponent<TransformComponent>(entity, "Transform", []() {
			});

		DrawComponent<SceneCameraComponent>(entity, "Camera", [&]() {
				SceneCameraComponent& component = entity.Get<SceneCameraComponent>();

				BLACKBIRD_ASSERT(entity.GetScene() != nullptr);

				bool isPrimary = entity.GetScene()->GetPrimatryCameraEntity() == entity;
				if (ImGui::Checkbox("Primary", &isPrimary))
				{
					if (isPrimary)
						entity.GetScene()->SetPrimatryCameraEntity(entity);
					else
						entity.GetScene()->SetPrimatryCameraEntity(Entity{});

					if (entity.Has<NativeScriptComponent>())
					{
						entity.Get<NativeScriptComponent>().Enable = isPrimary;
					}
				}

				static constexpr const char* projectionTypeString[] = { "Perspective", "Orthographic" };
				const char* currentProjectionType = projectionTypeString[static_cast<int>(component.Camera.GetProjectionType())];

				if (ImGui::BeginCombo("Projection", currentProjectionType))
				{
					for (int i = 0; i < 2; ++i)
					{
						bool isSelected = currentProjectionType == projectionTypeString[i];
						if (ImGui::Selectable(projectionTypeString[i], isSelected))
						{
							component.Camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (component.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = component.Camera.GetOrthographicSize();
					float nearClip = component.Camera.GetOrthographicNearClip();
					float farClip = component.Camera.GetOrthographicFarClip();

					bool changed = ImGui::DragFloat("Size", &orthoSize, 0.025f);
					changed = ImGui::DragFloat("NearClip", &nearClip, 0.025f) || changed;
					changed = ImGui::DragFloat("FarClip", &farClip, 0.025f) || changed;

					if (changed)
						component.Camera.SetOrthographic(orthoSize, nearClip, farClip);

				}
				else if (component.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float fov = glm::degrees(component.Camera.GetPerspectiveFOV());
					float nearClip = component.Camera.GetPerspectiveNearClip();
					float farClip = component.Camera.GetPerspectiveFarClip();

					bool changed = ImGui::DragFloat("FOV", &fov, 0.025f);
					changed = ImGui::DragFloat("NearClip", &nearClip, 0.025f) || changed;
					changed = ImGui::DragFloat("FarClip", &farClip, 0.025f) || changed;

					if (changed)
						component.Camera.SetPerspective(glm::radians(fov), nearClip, farClip);
				}

				ImGui::Checkbox("Aspect-ratio relative to viewport", &component.ResizeAspectRatioOnViewport);
			});


		DrawComponent<SpritRendererComponent>(entity, "Sprite", [&]() {
				SpritRendererComponent& component = entity.Get<SpritRendererComponent>();
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
			});
	}

}
