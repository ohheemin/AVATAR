// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from jeju:msg/CtrlMode.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "jeju/msg/detail/ctrl_mode__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace jeju
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void CtrlMode_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) jeju::msg::CtrlMode(_init);
}

void CtrlMode_fini_function(void * message_memory)
{
  auto typed_message = static_cast<jeju::msg::CtrlMode *>(message_memory);
  typed_message->~CtrlMode();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember CtrlMode_message_member_array[2] = {
  {
    "ctrl_algo",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju::msg::CtrlMode, ctrl_algo),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "ctrl_speed",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jeju::msg::CtrlMode, ctrl_speed),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers CtrlMode_message_members = {
  "jeju::msg",  // message namespace
  "CtrlMode",  // message name
  2,  // number of fields
  sizeof(jeju::msg::CtrlMode),
  CtrlMode_message_member_array,  // message members
  CtrlMode_init_function,  // function to initialize message memory (memory has to be allocated)
  CtrlMode_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t CtrlMode_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &CtrlMode_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace jeju


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<jeju::msg::CtrlMode>()
{
  return &::jeju::msg::rosidl_typesupport_introspection_cpp::CtrlMode_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, jeju, msg, CtrlMode)() {
  return &::jeju::msg::rosidl_typesupport_introspection_cpp::CtrlMode_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
