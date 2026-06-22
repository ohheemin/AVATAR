# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_jeju_07_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED jeju_07_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(jeju_07_FOUND FALSE)
  elseif(NOT jeju_07_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(jeju_07_FOUND FALSE)
  endif()
  return()
endif()
set(_jeju_07_CONFIG_INCLUDED TRUE)

# output package information
if(NOT jeju_07_FIND_QUIETLY)
  message(STATUS "Found jeju_07: 0.0.0 (${jeju_07_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'jeju_07' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${jeju_07_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(jeju_07_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${jeju_07_DIR}/${_extra}")
endforeach()
