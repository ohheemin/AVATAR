// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msg_test:msg/Sum.idl
// generated code does not contain a copyright notice

#ifndef MSG_TEST__MSG__DETAIL__SUM__STRUCT_H_
#define MSG_TEST__MSG__DETAIL__SUM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Sum in the package msg_test.
typedef struct msg_test__msg__Sum
{
  int32_t a;
  int32_t b;
  int32_t sum;
} msg_test__msg__Sum;

// Struct for a sequence of msg_test__msg__Sum.
typedef struct msg_test__msg__Sum__Sequence
{
  msg_test__msg__Sum * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msg_test__msg__Sum__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSG_TEST__MSG__DETAIL__SUM__STRUCT_H_
