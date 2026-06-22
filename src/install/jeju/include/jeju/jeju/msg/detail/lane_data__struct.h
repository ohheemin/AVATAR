// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jeju:msg/LaneData.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_DATA__STRUCT_H_
#define JEJU__MSG__DETAIL__LANE_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'center_points'
// Member 'left_points'
// Member 'right_points'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/LaneData in the package jeju.
typedef struct jeju__msg__LaneData
{
  bool detected;
  float steer;
  geometry_msgs__msg__Vector3__Sequence center_points;
  geometry_msgs__msg__Vector3__Sequence left_points;
  geometry_msgs__msg__Vector3__Sequence right_points;
} jeju__msg__LaneData;

// Struct for a sequence of jeju__msg__LaneData.
typedef struct jeju__msg__LaneData__Sequence
{
  jeju__msg__LaneData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jeju__msg__LaneData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__LANE_DATA__STRUCT_H_
