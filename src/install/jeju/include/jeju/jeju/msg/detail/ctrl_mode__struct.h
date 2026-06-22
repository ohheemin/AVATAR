// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jeju:msg/CtrlMode.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__CTRL_MODE__STRUCT_H_
#define JEJU__MSG__DETAIL__CTRL_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CtrlMode in the package jeju.
typedef struct jeju__msg__CtrlMode
{
  int8_t ctrl_algo;
  int8_t ctrl_speed;
} jeju__msg__CtrlMode;

// Struct for a sequence of jeju__msg__CtrlMode.
typedef struct jeju__msg__CtrlMode__Sequence
{
  jeju__msg__CtrlMode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jeju__msg__CtrlMode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__CTRL_MODE__STRUCT_H_
