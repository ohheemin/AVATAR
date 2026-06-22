// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from msg_test:msg/Sum.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "msg_test/msg/detail/sum__rosidl_typesupport_introspection_c.h"
#include "msg_test/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "msg_test/msg/detail/sum__functions.h"
#include "msg_test/msg/detail/sum__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msg_test__msg__Sum__init(message_memory);
}

void msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_fini_function(void * message_memory)
{
  msg_test__msg__Sum__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_member_array[3] = {
  {
    "a",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msg_test__msg__Sum, a),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "b",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msg_test__msg__Sum, b),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sum",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msg_test__msg__Sum, sum),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_members = {
  "msg_test__msg",  // message namespace
  "Sum",  // message name
  3,  // number of fields
  sizeof(msg_test__msg__Sum),
  msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_member_array,  // message members
  msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_init_function,  // function to initialize message memory (memory has to be allocated)
  msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_type_support_handle = {
  0,
  &msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msg_test
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_test, msg, Sum)() {
  if (!msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_type_support_handle.typesupport_identifier) {
    msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &msg_test__msg__Sum__rosidl_typesupport_introspection_c__Sum_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
