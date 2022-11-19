project(gfx_shapes)
FIND_PACKAGE(FLTK REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
cmake_minimum_required(VERSION 3.0)


add_executable(shapes shapes.cpp)
TARGET_LINK_LIBRARIES(shapes ${FLTK_LIBRARIES})
TARGET_LINK_LIBRARIES(shapes ${OPENGL_LIBRARIES})
