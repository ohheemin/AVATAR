// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_READ__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define JEJU__MSG__DETAIL__ERP_READ__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "jeju/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "jeju/msg/detail/erp_read__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace jeju
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jeju
cdr_serialize(
  const jeju::msg::ERPRead & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jeju
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  jeju::msg::ERPRead & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jeju
get_serialized_size(
  const jeju::msg::ERPRead & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jeju
max_serialized_size_ERPRead(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace jeju

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jeju
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jeju, msg, ERPRead)();

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__ERP_READ__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
