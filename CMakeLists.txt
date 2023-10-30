CMAKE_MINIMUM_REQUIRED(VERSION 3.16.0)

PROJECT(FTGL)
SET(CMAKE_MODULE_PATH ${FTGL_SOURCE_DIR})

SET(VERSION_SERIES 2)
SET(VERSION_MAJOR 4)
SET(VERSION_MINOR 0)
SET(FTGL_SOVERSION 1)

FIND_PACKAGE(Freetype REQUIRED) # if it fails, check this: https://bugs.launchpad.net/ubuntu/+source/cmake/+bug/826988
set(OpenGL_GL_PREFERENCE GLVND)
FIND_PACKAGE(OpenGL REQUIRED)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Allow the developer to select if Dynamic or Static libraries are built
OPTION(BUILD_SHARED_LIBS "Build Shared Libraries" ON)
IF(BUILD_SHARED_LIBS)
 	SET(LIB_TYPE SHARED)
	ADD_DEFINITIONS(-DFTGL_LIBRARY)
ELSE(BUILD_SHARED_LIBS)
	SET(LIB_TYPE STATIC)
	ADD_DEFINITIONS(-D FTGL_LIBRARY_STATIC)
ENDIF(BUILD_SHARED_LIBS)

ADD_CUSTOM_TARGET(doc)

FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
  ADD_CUSTOM_TARGET(doxygen
    ${DOXYGEN_EXECUTABLE}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Doxygen ...")
  ADD_DEPENDENCIES(doc doxygen)

ENDIF(DOXYGEN_FOUND)

add_subdirectory(src)

FIND_PACKAGE(GLUT     REQUIRED)

OPTION(BUILD_DEMO "Build demo" ON)
if(BUILD_DEMO AND GLUT_FOUND)
    add_subdirectory(demo)
endif()

FIND_PACKAGE(PkgConfig)
pkg_check_modules(CPPUNIT cppunit)
IF(CPPUNIT_FOUND AND GLUT_FOUND)
	OPTION(BUILD_TESTS "Build Unit Tests" ON)
	IF(BUILD_TESTS)
	  add_subdirectory(test)
	ENDIF(BUILD_TESTS)
ENDIF(CPPUNIT_FOUND)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/FTGLConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/FTGLConfig.cmake"
  @ONLY)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/FTGLConfig-install.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/FTGLConfig.cmake"
  @ONLY)

if (WIN32)
  set(cmakedir cmake)
else ()
  set(cmakedir lib/cmake/FTGL)
endif ()

install(EXPORT FTGL-targets DESTINATION "${cmakedir}")
install(
  FILES       "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/FTGLConfig.cmake"
  DESTINATION "${cmakedir}")

SET(PKGCONFIG_INSTALL_PREFIX "lib${LIB_SUFFIX}/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")
CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/ftgl.pc.cmake 
  ${CMAKE_CURRENT_BINARY_DIR}/ftgl.pc 
  @ONLY)
INSTALL(
  FILES       ${CMAKE_CURRENT_BINARY_DIR}/ftgl.pc
  DESTINATION ${PKGCONFIG_INSTALL_PREFIX})
