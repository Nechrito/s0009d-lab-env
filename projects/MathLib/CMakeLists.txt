PROJECT(MathLib)
FILE(GLOB headers code/*.h)
FILE(GLOB sources code/*.cpp)

SET(files_all ${headers} ${sources})
SOURCE_GROUP("MathLib" FILES ${files_all})

ADD_LIBRARY(MathLib STATIC ${files_all})
TARGET_LINK_LIBRARIES(MathLib core render)
ADD_DEPENDENCIES(MathLib core render)

TARGET_INCLUDE_DIRECTORIES(MathLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/code/)