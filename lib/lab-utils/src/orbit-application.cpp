#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lab-utils/orbit-application.hpp"

namespace LabUtils
{
	void LabOrbitApplication::updateCamera()
	{
		glm::mat4 lookAtTransform = glm::lookAt(
			glm::vec3(0.0f, 0.0f, -4.0f), // position
			glm::vec3(0.0f, 0.0f, 0.0f),  // target
			glm::vec3(0.0f, 1.0f, 0.0f)   // up
		);

		auto windowSize = window.getSize();
		float aspectRatio = std::max(windowSize.x, windowSize.y) / std::min(windowSize.x, windowSize.y);

		glm::mat4 projectionTransform = glm::perspective(
			glm::radians(45.0f),	// Field of view in radians
			aspectRatio,		    // Aspect ratio (width / height)
			0.1f,					// Near clipping plane
			100.0f					// Far clipping plane
		);

		camera = projectionTransform * lookAtTransform;
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
			}

			float t = t_clock.getElapsedTime().asSeconds();
			float dt = dt_clock.getElapsedTime().asSeconds();
			dt_clock.restart();

			updateCamera();

			onUpdate(t, dt);
			onDraw(t, dt);

			window.display();
		}

		onExit();
	}
}