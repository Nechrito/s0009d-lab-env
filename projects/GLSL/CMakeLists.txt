PROJECT(GLSL)
FILE(GLOB headers code/*.h)
FILE(GLOB sources code/*.cpp)
FILE(GLOB shaders shaders/*.glsl)

SET(files_all ${headers} ${sources})
SET(files_shaders ${shaders})

SOURCE_GROUP("GLSL" FILES ${files_all})
SOURCE_GROUP("Shaders" FILES ${files_shaders})

ADD_LIBRARY(GLSL STATIC ${files_all} ${files_shaders})
TARGET_LINK_LIBRARIES(GLSL core render)
ADD_DEPENDENCIES(GLSL core render)

ADD_CUSTOM_COMMAND(
	TARGET GLSL POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/shaders/
	${CMAKE_SOURCE_DIR}/bin/shaders/
)

TARGET_INCLUDE_DIRECTORIES(GLSL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/code/)
TARGET_INCLUDE_DIRECTORIES(GLSL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/shaders/)