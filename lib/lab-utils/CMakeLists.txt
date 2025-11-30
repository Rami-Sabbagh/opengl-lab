add_library(lab-utils STATIC)

target_sources(lab-utils
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			# Application
			include/lab-utils/life-cycle.hpp
			include/lab-utils/application.hpp
			include/lab-utils/orbit-application.hpp
			# Utils
			include/lab-utils/shader-utils.hpp
			# Shapes
			include/lab-utils/basic-shape.hpp
			include/lab-utils/textured-shape.hpp

	PRIVATE
		# Application
		src/application.cpp
		src/orbit-application.cpp
		# Utils
		src/shader-utils.cpp
		# Shapes
		src/basic-shape.cpp
		src/textured-shape.cpp
 )

target_compile_features(lab-utils PRIVATE cxx_std_17)
target_link_libraries(lab-utils PUBLIC GLAD SFML::Window glm::glm)
