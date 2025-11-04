#ifndef LAB_UTILS__LIFE_CYCLE_HPP
#define LAB_UTILS__LIFE_CYCLE_HPP

namespace LabUtils
{
	// The set of callabacks available for lab applications to override.
	class LifeCycleCallbacks
	{
	public:
		// Called at the start of the application. Useful to initialize resources such as vertex buffers.
		virtual void onInit() {}

		// Called when the application closes gracefully. Use to release allocated resources.
		virtual void onExit() {}

		// Called every frame before onDraw. Given a time counter in seconds since application start,
		// and a measurement of elapsed time between frames. Suitable for updating your geometry/transforms.
		virtual void onUpdate(float t, float dt) {}

		// Called every frame after onUpdate. Given a time counter in seconds since application start,
		// and a measurement of elapsed time between frames. Suitable for drawing operations.
		virtual void onDraw(float t, float dt) {}
	};
}

#endif // LAB_UTILS__LIFE_CYCLE_HPP