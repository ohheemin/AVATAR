// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jeju:msg/ERPWrite.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_WRITE__TRAITS_HPP_
#define JEJU__MSG__DETAIL__ERP_WRITE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jeju/msg/detail/erp_write__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jeju
{

namespace msg
{

inline void to_flow_style_yaml(
  const ERPWrite & msg,
  std::ostream & out)
{
  out << "{";
  // member: is_auto
  {
    out << "is_auto: ";
    rosidl_generator_traits::value_to_yaml(msg.is_auto, out);
    out << ", ";
  }

  // member: is_estop
  {
    out << "is_estop: ";
    rosidl_generator_traits::value_to_yaml(msg.is_estop, out);
    out << ", ";
  }

  // member: gear
  {
    out << "gear: ";
    rosidl_generator_traits::value_to_yaml(msg.gear, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << ", ";
  }

  // member: steer
  {
    out << "steer: ";
    rosidl_generator_traits::value_to_yaml(msg.steer, out);
    out << ", ";
  }

  // member: brake
  {
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ERPWrite & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: is_auto
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_auto: ";
    rosidl_generator_traits::value_to_yaml(msg.is_auto, out);
    out << "\n";
  }

  // member: is_estop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_estop: ";
    rosidl_generator_traits::value_to_yaml(msg.is_estop, out);
    out << "\n";
  }

  // member: gear
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gear: ";
    rosidl_generator_traits::value_to_yaml(msg.gear, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }

  // member: steer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steer: ";
    rosidl_generator_traits::value_to_yaml(msg.steer, out);
    out << "\n";
  }

  // member: brake
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ERPWrite & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace jeju

namespace rosidl_generator_traits
{

[[deprecated("use jeju::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jeju::msg::ERPWrite & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::msg::to_yaml() instead")]]
inline std::string to_yaml(const jeju::msg::ERPWrite & msg)
{
  return jeju::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::msg::ERPWrite>()
{
  return "jeju::msg::ERPWrite";
}

template<>
inline const char * name<jeju::msg::ERPWrite>()
{
  return "jeju/msg/ERPWrite";
}

template<>
struct has_fixed_size<jeju::msg::ERPWrite>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<jeju::msg::ERPWrite>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<jeju::msg::ERPWrite>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JEJU__MSG__DETAIL__ERP_WRITE__TRAITS_HPP_
