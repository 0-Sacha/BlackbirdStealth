#pragma once

#include "SceneHierarchyPanel.h"

#include "glm/gtc/type_ptr.hpp"
#include "ImGui/misc/cpp/imgui_stdlib.h"

namespace Blackbird
{
	template <typename T, typename Function>
	void SceneHierarchyPanel::DrawComponent(Entity entity, const char* label, Function function)
	{
		if (entity.Has<T>())
		{
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(T).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, label))
			{
				function();
				ImGui::TreePop();
			}
		}
	}
}
