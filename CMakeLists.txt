#
#     _  _ _ |_ . _ _  _ _  _ |
#    (_)_\(_|| ||| | || | |(/_|
#          _|  
#
# Copyright (c) 2011-2012, Daniel Müller <dm@g4t3.de>
# Computer Graphics Systems Group at the Hasso-Plattner-Institute, Germany
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:
#   * Redistributions of source code must retain the above copyright notice, 
#     this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright 
#     notice, this list of conditions and the following disclaimer in the 
#     documentation and/or other materials provided with the distribution.
#   * Neither the name of the Computer Graphics Systems Group at the 
#     Hasso-Plattner-Institute (HPI), Germany nor the names of its 
#     contributors may be used to endorse or promote products derived from 
#     this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
# POSSIBILITY OF SUCH DAMAGE.
  
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

# macros

macro(SOURCE_GROUP_BY_PATH parent_path)

    foreach(filename ${ARGV})
	
        get_filename_component(path "${filename}" REALPATH)
        file(RELATIVE_PATH path ${parent_path} ${path})
        get_filename_component(path "${path}" PATH)
        string(REPLACE "/" "\\" path "${path}")

        if(${filename} MATCHES "h$|hpp$|cpp$|c$|ui$|qrc$")
            source_group("${path}" FILES ${filename})
        endif()

    endforeach()

endmacro()


# config

project(osgHimmel C CXX)

# only msvc have multiple configurations in same build dir
if(MSVC)
 set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)
endif()

set(VERSION_MAJOR "0" CACHE STRING "${PROJECT_NAME} Major Version")
set(VERSION_MINOR "0" CACHE STRING "${PROJECT_NAME} Minor Version")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

option(OSGHIMMEL_MAKE_DEMOS "Make Demos" ON)
option(OSGHIMMEL_MAKE_SKYBOX "Make SkyBox - Sandbox for osgHimmel (requires Qt)" ON)
option(OSGHIMMEL_MAKE_TESTS "Make Tests" ON)


# 3rdp and resources

find_package(OpenGL REQUIRED)
find_package(OpenSceneGraph 3.0.0 REQUIRED osgDB osgGA osgText osgViewer osgUtil)

# lib/bin copy

set(OSG_PLUGINS osgPlugins-${OPENSCENEGRAPH_VERSION})

# sources
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

# osgHimmel public includes
include_directories(include)

# add the osgHimmel library source
add_subdirectory(src)

if(OSGHIMMEL_MAKE_TESTS)
  add_subdirectory(tests)
endif()
if(OSGHIMMEL_MAKE_DEMOS OR OSGHIMMEL_MAKE_SKYBOX)
  add_subdirectory(examples)
endif()


# cpack deploy

set(CPACK_PACKAGE_CONTACT "helsing72@users.noreply.github.com")

set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH 0)

# provide license text with package
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
if(WIN32)
  set(CPACK_GENERATOR ZIP NSIS)
  set(CPACK_SOURCE_GENERATOR ZIP)
else()
  set(CPACK_GENERATOR DEB TGZ)
  set(CPACK_SOURCE_GENERATOR TGZ)
endif()

include(CPack)
