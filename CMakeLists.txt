# Copyright © 2020 Andy Maloney <asmaloney@gmail.com>
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required( VERSION 3.13 )

project( easyexif_demo
    LANGUAGES
        CXX
)

# Require out-of-source builds
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )

if ( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in the source directory. Please use a build subdirectory." )
endif()

add_executable( ${PROJECT_NAME} )

target_compile_features( ${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_sources( ${PROJECT_NAME}
    PRIVATE
        demo.cpp
        exif.cpp
        exif.h
)
