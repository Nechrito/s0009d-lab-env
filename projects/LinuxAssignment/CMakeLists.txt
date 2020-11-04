PROJECT(LinuxAssignment)
FILE(GLOB headers code/*.h)
FILE(GLOB sources code/*.cpp)

SET(files_all ${headers} ${sources})
SOURCE_GROUP("LinuxAssignment" FILES ${files_all})

ADD_LIBRARY(LinuxAssignment STATIC ${files_all})
TARGET_LINK_LIBRARIES(LinuxAssignment MathLib core render)
ADD_DEPENDENCIES(LinuxAssignment MathLib core render)

TARGET_INCLUDE_DIRECTORIES(LinuxAssignment INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/code/)
