include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "ProjectCyclone"
	architecture "x86_64"
	startproject "ProjectKart"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "ProjectCyclone"
include "Oxylus-Engine/Oxylus"
