# Define a function to simplify app creation
function(ADD_LAB_EXECUTABLE APP_NAME)
    cmake_parse_arguments(ARG "" "HAS_INCLUDES" "SOURCES" ${ARGN})

    # Add the executable with the provided sources
    add_executable(${APP_NAME} ${ARG_SOURCES})
    target_compile_features(${APP_NAME} PRIVATE cxx_std_17)

    target_link_libraries(${APP_NAME} PRIVATE GLAD SFML::System SFML::Window SFML::Graphics glm::glm lab-utils)

    # Optionally include directories if HAS_INCLUDES is set
    if(ARG_HAS_INCLUDES)
        target_include_directories(${APP_NAME} PRIVATE ${ARG_HAS_INCLUDES})
    endif()
endfunction()
