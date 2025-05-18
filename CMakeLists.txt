cmake_minimum_required(VERSION 3.16)
project(wxOpenGLApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base gl)

# Include wxWidgets
include(${wxWidgets_USE_FILE})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Source files
set(SOURCES 
    src/main.cpp
    src/GLCanvas.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} OpenGL::GL)
