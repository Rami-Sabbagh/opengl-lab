#include <optional>

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include "lab-utils/orbit-application.hpp"

// How many pixels should the mouse travel to amount for 180 degrees turn.
constexpr glm::vec2 MOUSE_SPEED{ 400.0f, 400.0f };

namespace LabUtils
{
	void LabOrbitApplication::updateCamera()
	{
		float _long = orbitCoords.x; // Logitude.
		float _lat = orbitCoords.y; // Latitude.
		float _dist = orbitCoords.z; // Distance.

		glm::vec3 position = { _dist, 0.0f, 0.0f };

		glm::mat4 position_transform{ 1.0f };
		position_transform = glm::rotate(position_transform, _long, { 0.0f, 0.0f, 1.0f });
		position_transform = glm::rotate(position_transform, _lat, { 0.0f, 1.0f, 0.0f });

		position = position_transform * glm::vec4{ position, 1.0f };

		glm::mat4 lookAtTransform = glm::lookAt(
			position,
			glm::vec3(0.0f, 0.0f, 0.0f),  // target
			glm::vec3(0.0f, 0.0f, 1.0f)   // up
		);

		auto windowSize = window.getSize();
		float width = windowSize.x, height = windowSize.y;

		glm::mat4 projectionTransform = glm::perspective(
			glm::radians(45.0f),	// Field of view in radians
			width / height,		    // Aspect ratio (width / height)
			0.1f,					// Near clipping plane
			100.0f					// Far clipping plane
		);

		camera = projectionTransform * lookAtTransform;
	}

	void LabOrbitApplication::updateOrbitControls()
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);
		sf::Vector2i deltaPosition = position - lastMousePosition;
		lastMousePosition = position;

		if (window.hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			glm::vec2 dPosition{ deltaPosition.x, deltaPosition.y };
			glm::vec2 dAngle = -dPosition / MOUSE_SPEED * glm::pi<float>();

			constexpr float lat_lim = 1.0f;

			orbitCoords += glm::vec3{ dAngle, 0.f };
			orbitCoords.y = glm::clamp(orbitCoords.y,
				glm::radians(-90.0f + lat_lim),
				glm::radians(90.0f - lat_lim));
		}
	}

	void LabOrbitApplication::handleOrbitEvents(std::optional<sf::Event> event)
	{
		if (const auto* keyEv = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyEv->code == sf::Keyboard::Key::Backspace)
				orbitCoords.x = 0, orbitCoords.y = 0;
		}
	}

	void LabOrbitApplication::runEventLoop()
	{
		onInit();

		bool running = true;
		while (running)
		{
			while (const std::optional event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					running = false;
				else if (const auto* resized = event->getIf<sf::Event::Resized>())
					glViewport(0, 0, resized->size.x, resized->size.y);

				handleOrbitEvents(event);

				if (const auto* keyEv = event->getIf<sf::Event::KeyPressed>())
					onKeyPressed(*keyEv);
				else if (const auto* keyEv = event->getIf<sf::Event::KeyReleased>())
					onKeyReleased(*keyEv);
			}

			float t = t_clock.getElapsedTime().asSeconds();
			float dt = dt_clock.getElapsedTime().asSeconds();
			dt_clock.restart();

			updateOrbitControls();
			updateCamera();

			onUpdate(t, dt);
			onDraw(t, dt);

			window.display();
		}

		onExit();
	}
}