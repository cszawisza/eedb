#.rst:
# ECMOptionalAddSubdirectory
# --------------------------
#
# Make subdiretories optional.
#
# ::
#
#   optional_add_subdirectory(<dir>)
#
# This behaves like add_subdirectory(), except that it does not complain if the
# directory does not exist.  Additionally, if the directory does exist, it
# creates an option to allow the user to skip it.
#
# This is useful for "meta-projects" that combine several mostly-independent
# sub-projects.
#
# If the CMake variable DISABLE_ALL_OPTIONAL_SUBDIRECTORIES is set to TRUE for
# the first CMake run on the project, all optional subdirectories will be
# disabled by default (but can of course be enabled via the respective options).
# For example, the following will disable all optional subdirectories except the
# one named "foo":
#
# .. code-block:: sh
#
#   cmake -DDISABLE_ALL_OPTIONAL_SUBDIRECTORIES=TRUE -DBUILD_foo=TRUE myproject
#
# Since pre-1.0.0.

#=============================================================================
# Copyright 2007 Alexander Neundorf <neundorf@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file COPYING-CMAKE-SCRIPTS for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of extra-cmake-modules, substitute the full
#  License text for the above reference.)


function(optional_add_subdirectory _dir)
  get_filename_component(_fullPath ${_dir} ABSOLUTE)
  if(EXISTS ${_fullPath}/CMakeLists.txt)
    if(DISABLE_ALL_OPTIONAL_SUBDIRECTORIES)
      set(_DEFAULT_OPTION_VALUE FALSE)
    else()
      set(_DEFAULT_OPTION_VALUE TRUE)
    endif()
    if(DISABLE_ALL_OPTIONAL_SUBDIRS  AND NOT DEFINED  BUILD_${_dir})
      set(_DEFAULT_OPTION_VALUE FALSE)
    endif()
    option(BUILD_${_dir} "Build directory ${_dir}" ${_DEFAULT_OPTION_VALUE})
    if(BUILD_${_dir})
      add_subdirectory(${_dir})
    endif()
  endif()
endfunction()

