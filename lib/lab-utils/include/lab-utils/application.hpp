#ifndef LAB_UTILS__APPLICATION_HPP
#define LAB_UTILS__APPLICATION_HPP

#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "lab-utils/life-cycle.hpp"

namespace LabUtils
{
	class LabApplication : public LifeCycleCallbacks
	{
	protected:
		sf::Window window;
		sf::Clock t_clock; // Used to measure time since application start.
		sf::Clock dt_clock; // Used to measure elapsed time between frames.

		// Override at your own responsibility if you wish to customize window/graphics options.
		void initializeWindowAndGraphics(sf::Vector2u windowSize, const sf::String windowTitle);
		
		// Override at your own responsibility of you wish to customize the event loop.
		virtual void runEventLoop();

	public:
		LabApplication();

		// Configure the application window and start it, running the event loop.
		// The life-cycle callbacks will be triggered as they should. Override them to implement appliaction logic.
		void run(sf::Vector2u windowSize = { 800, 600 }, const sf::String& windowTitle = "Untitled Lab Application");
	};
}

#endif // LAB_UTILS__APPLICATION_HPP