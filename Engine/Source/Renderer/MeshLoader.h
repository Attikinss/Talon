#pragma once
#include "Mesh.h"

#include <memory>
#include <string>
#include <vector>

namespace Talon
{
	// TODO: This class is not a permanent solution to loading meshes from file
	// and will be replaced with a more viable and extendable implementation
	// that coordinates with some form of asset/resoruce manager.
	class MeshLoader
	{
	public:
		static std::vector<std::shared_ptr<Mesh>> Load(const std::string& filepath);
	};
}