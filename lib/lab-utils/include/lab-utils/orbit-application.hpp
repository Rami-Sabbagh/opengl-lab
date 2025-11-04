#ifndef LAB_UTILS__ORBIT_APPLICATION_HPP
#define LAB_UTILS__ORBIT_APPLICATION_HPP

#include <glm/mat4x4.hpp>

#include "lab-utils/application.hpp"

namespace LabUtils
{
	class LabOrbitApplication : public LabApplication
	{
	protected:
		glm::mat4 camera = glm::mat4(1.0f);

		void updateCamera();
		void runEventLoop() override;
	};
}

#endif // LAB_UTILS__ORBIT_APPLICATION_HPP