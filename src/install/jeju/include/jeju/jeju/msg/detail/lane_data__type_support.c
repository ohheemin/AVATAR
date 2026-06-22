// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jeju:msg/LaneData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jeju/msg/detail/lane_data__rosidl_typesupport_introspection_c.h"
#include "jeju/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jeju/msg/detail/lane_data__functions.h"
#include "jeju/msg/detail/lane_data__struct.h"


// Include directives for member types
// Member `center_points`
// Member `left_points`
// Member `right_points`
#include "geometry_msgs/msg/vector3.h"
// Member `center_points`
// Member `left_points`
// Member `right_points`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jeju__msg__LaneData__init(message_memory);
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_fini_function(void * message_memory)
{
  jeju__msg__LaneData__fini(message_memory);
}

size_t jeju__msg__LaneData__rosidl_typesupport_introspection_c__size_function__LaneData__center_points(
  const void * untyped_member)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return member->size;
}

const void * jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__center_points(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__center_points(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__fetch_function__LaneData__center_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Vector3 * item =
    ((const geometry_msgs__msg__Vector3 *)
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__center_points(untyped_member, index));
  geometry_msgs__msg__Vector3 * value =
    (geometry_msgs__msg__Vector3 *)(untyped_value);
  *value = *item;
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__assign_function__LaneData__center_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Vector3 * item =
    ((geometry_msgs__msg__Vector3 *)
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__center_points(untyped_member, index));
  const geometry_msgs__msg__Vector3 * value =
    (const geometry_msgs__msg__Vector3 *)(untyped_value);
  *item = *value;
}

bool jeju__msg__LaneData__rosidl_typesupport_introspection_c__resize_function__LaneData__center_points(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  geometry_msgs__msg__Vector3__Sequence__fini(member);
  return geometry_msgs__msg__Vector3__Sequence__init(member, size);
}

size_t jeju__msg__LaneData__rosidl_typesupport_introspection_c__size_function__LaneData__left_points(
  const void * untyped_member)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return member->size;
}

const void * jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__left_points(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__left_points(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__fetch_function__LaneData__left_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Vector3 * item =
    ((const geometry_msgs__msg__Vector3 *)
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__left_points(untyped_member, index));
  geometry_msgs__msg__Vector3 * value =
    (geometry_msgs__msg__Vector3 *)(untyped_value);
  *value = *item;
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__assign_function__LaneData__left_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Vector3 * item =
    ((geometry_msgs__msg__Vector3 *)
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__left_points(untyped_member, index));
  const geometry_msgs__msg__Vector3 * value =
    (const geometry_msgs__msg__Vector3 *)(untyped_value);
  *item = *value;
}

bool jeju__msg__LaneData__rosidl_typesupport_introspection_c__resize_function__LaneData__left_points(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  geometry_msgs__msg__Vector3__Sequence__fini(member);
  return geometry_msgs__msg__Vector3__Sequence__init(member, size);
}

size_t jeju__msg__LaneData__rosidl_typesupport_introspection_c__size_function__LaneData__right_points(
  const void * untyped_member)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return member->size;
}

const void * jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__right_points(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__right_points(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__fetch_function__LaneData__right_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Vector3 * item =
    ((const geometry_msgs__msg__Vector3 *)
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__right_points(untyped_member, index));
  geometry_msgs__msg__Vector3 * value =
    (geometry_msgs__msg__Vector3 *)(untyped_value);
  *value = *item;
}

void jeju__msg__LaneData__rosidl_typesupport_introspection_c__assign_function__LaneData__right_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Vector3 * item =
    ((geometry_msgs__msg__Vector3 *)
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__right_points(untyped_member, index));
  const geometry_msgs__msg__Vector3 * value =
    (const geometry_msgs__msg__Vector3 *)(untyped_value);
  *item = *value;
}

bool jeju__msg__LaneData__rosidl_typesupport_introspection_c__resize_function__LaneData__right_points(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  geometry_msgs__msg__Vector3__Sequence__fini(member);
  return geometry_msgs__msg__Vector3__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_member_array[5] = {
  {
    "detected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneData, detected),  // bytes offset in struct
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
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneData, steer),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "center_points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneData, center_points),  // bytes offset in struct
    NULL,  // default value
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__size_function__LaneData__center_points,  // size() function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__center_points,  // get_const(index) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__center_points,  // get(index) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__fetch_function__LaneData__center_points,  // fetch(index, &value) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__assign_function__LaneData__center_points,  // assign(index, value) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__resize_function__LaneData__center_points  // resize(index) function pointer
  },
  {
    "left_points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneData, left_points),  // bytes offset in struct
    NULL,  // default value
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__size_function__LaneData__left_points,  // size() function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__left_points,  // get_const(index) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__left_points,  // get(index) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__fetch_function__LaneData__left_points,  // fetch(index, &value) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__assign_function__LaneData__left_points,  // assign(index, value) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__resize_function__LaneData__left_points  // resize(index) function pointer
  },
  {
    "right_points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju__msg__LaneData, right_points),  // bytes offset in struct
    NULL,  // default value
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__size_function__LaneData__right_points,  // size() function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_const_function__LaneData__right_points,  // get_const(index) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__get_function__LaneData__right_points,  // get(index) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__fetch_function__LaneData__right_points,  // fetch(index, &value) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__assign_function__LaneData__right_points,  // assign(index, value) function pointer
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__resize_function__LaneData__right_points  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_members = {
  "jeju__msg",  // message namespace
  "LaneData",  // message name
  5,  // number of fields
  sizeof(jeju__msg__LaneData),
  jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_member_array,  // message members
  jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_init_function,  // function to initialize message memory (memory has to be allocated)
  jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_type_support_handle = {
  0,
  &jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jeju
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jeju, msg, LaneData)() {
  jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  if (!jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_type_support_handle.typesupport_identifier) {
    jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jeju__msg__LaneData__rosidl_typesupport_introspection_c__LaneData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
