PROJECT(Resource)
FILE(GLOB headers code/*.h)
FILE(GLOB sources code/*.cpp)

SET(files_all ${headers} ${sources})
SOURCE_GROUP("Resource" FILES ${files_Resource})

ADD_LIBRARY(Resource STATIC ${files_all})
TARGET_LINK_LIBRARIES(Resource core render MathLib LinuxAssignment)
ADD_DEPENDENCIES(Resource core render MathLib LinuxAssignment)

TARGET_INCLUDE_DIRECTORIES(Resource INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/code/)