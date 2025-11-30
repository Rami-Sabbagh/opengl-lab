#pragma once

#include <optional>

#include <glm/mat4x4.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "lab-utils/application.hpp"

namespace LabUtils
{
	class LabOrbitApplication : public LabApplication
	{
	protected:
		glm::mat4 camera = glm::mat4(1.0f);

		// Polar coordinates of the orbit-mode camera.
		// Longitude, Latidude, Distance.
		glm::vec3 orbitCoords{0.0f, 0.0f, 2.4f};

		void updateCamera();
		void updateOrbitControls();
		void handleOrbitEvents(std::optional<sf::Event> event);

		void runEventLoop() override;

	private:
		sf::Vector2i lastMousePosition;
	};
}