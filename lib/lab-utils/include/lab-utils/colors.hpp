#pragma once

#include "glm/glm.hpp"

namespace LabUtils
{
	namespace Colors
	{
		constexpr glm::vec3 red{ 1.f, 0.f, 0.f };
		constexpr glm::vec3 green{ 0.f, 1.f, 0.f };
		constexpr glm::vec3 blue{ 0.f, 0.f, 1.f };

		constexpr glm::vec3 white{ 1.f, 1.f, 1.f };
		constexpr glm::vec3 black{ 0.f, 0.f, 0.f };

		constexpr glm::vec3 yellow{ 1.f, 1.f, 0.f };
		constexpr glm::vec3 magenta{ 1.f, 0.f, 1.f };
		constexpr glm::vec3 cyan{ 0.f, 1.f, 1.f };
	}
}