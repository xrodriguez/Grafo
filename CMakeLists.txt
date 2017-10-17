cmake_minimum_required(VERSION 3.5.0)
project( sfml-app C CXX )

set(CMAKE_BUILD_TYPE Debug)

#find_package( OpenGL REQUIRED )

#find_package( PkgConfig REQUIRED )

#find_package(SFML REQUIRED audio graphics window system)
#if(SFML_FOUND)
#  include_directories(${SFML_INCLUDE_DIR})
#endif()

set( CMAKE_CXX_STANDARD 11 )
#SET( CMAKE_STATIC_LINKER_FLAGS  "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio" )
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH} )
find_package(SFML 2 REQUIRED system window graphics audio)

link_directories( /usr/lib/ /usr/lib64/ /usr/local/lib/ )

#file( GLOB  CUDA_FILES "/cuda/robotics/" *.cu)

set( SOURCES 
    Graph.cpp
    Edge.cpp 
    Heuristics.cpp 
    Node.cpp
      )

#cuda_compile( HELPER_CUDA_ROBOTICS cuda/robotics/LRoboticsCudaHelpers.cu )

#cuda_add_executable( robot2D
#					 main.cpp
#					 gl/LApp.cpp
#					 gl/core/primitives/LPrimitivesRenderer2D.cpp
#					 gl/core/shaders/LShaderManager.cpp
#					 app/graphics/LAppGraphics2D.cpp
#					 app/robotics/LAppRobotics2D.cpp
#					 app/particles2D/LAppParticles2D.cpp
#					 app/robotics/LCommonRobotics2D.cpp
#					 app/robotics/robot/LRobot2D.cpp
#					 app/robotics/robot/LRobotLaserSensor.cpp
#					 opencl/robotics/LopenclHelpers.cpp
#					 app/robotics/robot/localization/LRobotLocalizer.cpp
#					 ${HELPER_CUDA_ROBOTICS} )

add_executable( sfml-app
				main.cpp
			    Graph.cpp
			    Edge.cpp 
			    Heuristics.cpp 
			    Node.cpp)

target_link_libraries( sfml-app ${SFML_LIBRARIES} )