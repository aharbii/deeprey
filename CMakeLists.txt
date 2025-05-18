cmake_minimum_required(VERSION 3.16)
project(wxOpenGLApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define paths
set(RELEASE_DIR ${CMAKE_BINARY_DIR}/release)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

# Create release directory
file(MAKE_DIRECTORY ${RELEASE_DIR})
file(MAKE_DIRECTORY ${RELEASE_DIR}/assets)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base gl)

# Include wxWidgets
include(${wxWidgets_USE_FILE})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find SOIL
find_library(SOIL_LIB SOIL)
include_directories(/usr/include/SOIL)

# Source files
set(SOURCES 
    src/main.cpp
    src/GLCanvas.cpp
)

# Add executable
add_executable(wxOpenGLApp ${SOURCES})

# Define output directory for the executable
set_target_properties(wxOpenGLApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RELEASE_DIR})

# Link libraries
target_link_libraries(wxOpenGLApp ${wxWidgets_LIBRARIES} OpenGL::GL ${SOIL_LIB})

# Copy assets to release directory AFTER defining the target
file(GLOB ASSET_FILES "${ASSETS_DIR}/*")
foreach(asset ${ASSET_FILES})
    get_filename_component(asset_name ${asset} NAME)
    add_custom_command(
        TARGET wxOpenGLApp
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${asset} ${RELEASE_DIR}/assets/${asset_name}
    )
endforeach()

# Copy the binary to the release directory
add_custom_command(TARGET wxOpenGLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:wxOpenGLApp> ${RELEASE_DIR}/wxOpenGLApp
)
