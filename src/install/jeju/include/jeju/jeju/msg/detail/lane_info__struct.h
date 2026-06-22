// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jeju:msg/LaneInfo.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_INFO__STRUCT_H_
#define JEJU__MSG__DETAIL__LANE_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'center_line_x'
// Member 'center_line_y'
// Member 'center_line_yaw'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/LaneInfo in the package jeju.
typedef struct jeju__msg__LaneInfo
{
  rosidl_runtime_c__float__Sequence center_line_x;
  rosidl_runtime_c__float__Sequence center_line_y;
  rosidl_runtime_c__float__Sequence center_line_yaw;
  bool lane_mode;
  int8_t speed_mode;
} jeju__msg__LaneInfo;

// Struct for a sequence of jeju__msg__LaneInfo.
typedef struct jeju__msg__LaneInfo__Sequence
{
  jeju__msg__LaneInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jeju__msg__LaneInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__LANE_INFO__STRUCT_H_
