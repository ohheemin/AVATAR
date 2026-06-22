// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jeju:msg/ERPWrite.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jeju/msg/detail/erp_write__rosidl_typesupport_introspection_c.h"
#include "jeju/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jeju/msg/detail/erp_write__functions.h"
#include "jeju/msg/detail/erp_write__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jeju__msg__ERPWrite__init(message_memory);
}

void jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_fini_function(void * message_memory)
{
  jeju__msg__ERPWrite__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_member_array[6] = {
  {
    "is_auto",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__ERPWrite, is_auto),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_estop",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__ERPWrite, is_estop),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gear",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__ERPWrite, gear),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__ERPWrite, speed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "steer",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__ERPWrite, steer),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "brake",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__ERPWrite, brake),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_members = {
  "jeju__msg",  // message namespace
  "ERPWrite",  // message name
  6,  // number of fields
  sizeof(jeju__msg__ERPWrite),
  jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_member_array,  // message members
  jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_init_function,  // function to initialize message memory (memory has to be allocated)
  jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_type_support_handle = {
  0,
  &jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jeju
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jeju, msg, ERPWrite)() {
  if (!jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_type_support_handle.typesupport_identifier) {
    jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jeju__msg__ERPWrite__rosidl_typesupport_introspection_c__ERPWrite_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
