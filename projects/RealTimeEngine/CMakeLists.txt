PROJECT(RealTimeEngine)

FILE(GLOB headers code/*.h)
FILE(GLOB sources code/*.cpp)

SET(files_headers ${headers})
SET(files_sources ${sources})

SOURCE_GROUP("Header Files" FILES ${files_headers})
SOURCE_GROUP("Source Files" FILES ${files_sources})

ADD_EXECUTABLE(RealTimeEngine ${files_headers} ${files_sources})
TARGET_LINK_LIBRARIES(RealTimeEngine core render MathLib Resource GLSL)
ADD_DEPENDENCIES(RealTimeEngine core render MathLib Resource GLSL)



ADD_CUSTOM_COMMAND(
	TARGET RealTimeEngine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/models/
	${CMAKE_SOURCE_DIR}/bin/models/
)

SET_PROPERTY (DIRECTORY PROPERTY VS_STARTUP_PROJECT "RealTimeEngine")

SET_TARGET_PROPERTIES(RealTimeEngine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)