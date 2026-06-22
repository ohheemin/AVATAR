// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jeju:msg/LaneInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jeju/msg/detail/lane_info__rosidl_typesupport_introspection_c.h"
#include "jeju/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jeju/msg/detail/lane_info__functions.h"
#include "jeju/msg/detail/lane_info__struct.h"


// Include directives for member types
// Member `center_line_x`
// Member `center_line_y`
// Member `center_line_yaw`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jeju__msg__LaneInfo__init(message_memory);
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_fini_function(void * message_memory)
{
  jeju__msg__LaneInfo__fini(message_memory);
}

size_t jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__size_function__LaneInfo__center_line_x(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_x(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_x(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__fetch_function__LaneInfo__center_line_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_x(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__assign_function__LaneInfo__center_line_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_x(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__resize_function__LaneInfo__center_line_x(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__size_function__LaneInfo__center_line_y(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_y(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_y(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__fetch_function__LaneInfo__center_line_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_y(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__assign_function__LaneInfo__center_line_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_y(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__resize_function__LaneInfo__center_line_y(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__size_function__LaneInfo__center_line_yaw(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_yaw(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_yaw(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__fetch_function__LaneInfo__center_line_yaw(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_yaw(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__assign_function__LaneInfo__center_line_yaw(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_yaw(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__resize_function__LaneInfo__center_line_yaw(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_member_array[5] = {
  {
    "center_line_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneInfo, center_line_x),  // bytes offset in struct
    NULL,  // default value
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__size_function__LaneInfo__center_line_x,  // size() function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_x,  // get_const(index) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_x,  // get(index) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__fetch_function__LaneInfo__center_line_x,  // fetch(index, &value) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__assign_function__LaneInfo__center_line_x,  // assign(index, value) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__resize_function__LaneInfo__center_line_x  // resize(index) function pointer
  },
  {
    "center_line_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneInfo, center_line_y),  // bytes offset in struct
    NULL,  // default value
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__size_function__LaneInfo__center_line_y,  // size() function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_y,  // get_const(index) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_y,  // get(index) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__fetch_function__LaneInfo__center_line_y,  // fetch(index, &value) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__assign_function__LaneInfo__center_line_y,  // assign(index, value) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__resize_function__LaneInfo__center_line_y  // resize(index) function pointer
  },
  {
    "center_line_yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneInfo, center_line_yaw),  // bytes offset in struct
    NULL,  // default value
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__size_function__LaneInfo__center_line_yaw,  // size() function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_const_function__LaneInfo__center_line_yaw,  // get_const(index) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__get_function__LaneInfo__center_line_yaw,  // get(index) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__fetch_function__LaneInfo__center_line_yaw,  // fetch(index, &value) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__assign_function__LaneInfo__center_line_yaw,  // assign(index, value) function pointer
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__resize_function__LaneInfo__center_line_yaw  // resize(index) function pointer
  },
  {
    "lane_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneInfo, lane_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneInfo, speed_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_members = {
  "jeju__msg",  // message namespace
  "LaneInfo",  // message name
  5,  // number of fields
  sizeof(jeju__msg__LaneInfo),
  jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_member_array,  // message members
  jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_type_support_handle = {
  0,
  &jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jeju
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jeju, msg, LaneInfo)() {
  if (!jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_type_support_handle.typesupport_identifier) {
    jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jeju__msg__LaneInfo__rosidl_typesupport_introspection_c__LaneInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
