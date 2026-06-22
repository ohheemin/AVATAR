// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jeju:msg/ERPWrite.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_WRITE__STRUCT_H_
#define JEJU__MSG__DETAIL__ERP_WRITE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ERPWrite in the package jeju.
typedef struct jeju__msg__ERPWrite
{
  bool is_auto;
  bool is_estop;
  uint8_t gear;
  uint16_t speed;
  int16_t steer;
  uint8_t brake;
} jeju__msg__ERPWrite;

// Struct for a sequence of jeju__msg__ERPWrite.
typedef struct jeju__msg__ERPWrite__Sequence
{
  jeju__msg__ERPWrite * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jeju__msg__ERPWrite__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__ERP_WRITE__STRUCT_H_
