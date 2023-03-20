
-- Oxylus Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["Oxylus"] = "%{wks.location}/Oxylus-Engine/Oxylus/src/"
IncludeDir["vendor"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/"
IncludeDir["rapidyaml"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/rapidyaml/include"
IncludeDir["GLFW"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/entt"
IncludeDir["ktx"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/ktx/include"
IncludeDir["miniaudio"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/miniaudio"
IncludeDir["PhysX"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/PhysX/PhysX/include"
IncludeDir["tinygltf"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/tinygltf"
IncludeDir["tracy"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/tracy/public"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

Library["GLFW"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/lib/glfw3.lib"
Library["ktx"] = "%{wks.location}/Oxylus-Engine/Oxylus/vendor/lib/ktx.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolbsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"