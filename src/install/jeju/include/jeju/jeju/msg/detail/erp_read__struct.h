// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_READ__STRUCT_H_
#define JEJU__MSG__DETAIL__ERP_READ__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/ERPRead in the package jeju.
typedef struct jeju__msg__ERPRead
{
  std_msgs__msg__Header header;
  uint8_t s;
  uint8_t t;
  uint8_t x;
  uint8_t aorm;
  uint8_t estop;
  uint8_t gear;
  uint16_t speed;
  int16_t steer;
  uint8_t brake;
  int32_t enc;
  uint8_t alive;
  uint8_t etx0;
  uint8_t etx1;
} jeju__msg__ERPRead;

// Struct for a sequence of jeju__msg__ERPRead.
typedef struct jeju__msg__ERPRead__Sequence
{
  jeju__msg__ERPRead * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jeju__msg__ERPRead__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__ERP_READ__STRUCT_H_
