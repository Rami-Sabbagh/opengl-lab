add_library(lab-utils STATIC)

target_sources(lab-utils
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS include
		FILES
			include/lab-utils/shader-utils.hpp
			include/lab-utils/basic-shader.hpp
			include/lab-utils/basic-shape.hpp
			include/lab-utils/life-cycle.hpp
			include/lab-utils/application.hpp
			include/lab-utils/orbit-application.hpp

	PRIVATE
		src/shader-utils.cpp
		src/basic-shape.cpp
		src/application.cpp
		src/orbit-application.cpp
 )

target_compile_features(lab-utils PRIVATE cxx_std_17)
target_link_libraries(lab-utils PUBLIC GLAD SFML::Window glm::glm)
