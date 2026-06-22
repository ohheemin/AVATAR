// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jeju:msg/CtrlMode.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__CTRL_MODE__TRAITS_HPP_
#define JEJU__MSG__DETAIL__CTRL_MODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jeju/msg/detail/ctrl_mode__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jeju
{

namespace msg
{

inline void to_flow_style_yaml(
  const CtrlMode & msg,
  std::ostream & out)
{
  out << "{";
  // member: ctrl_algo
  {
    out << "ctrl_algo: ";
    rosidl_generator_traits::value_to_yaml(msg.ctrl_algo, out);
    out << ", ";
  }

  // member: ctrl_speed
  {
    out << "ctrl_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.ctrl_speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CtrlMode & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ctrl_algo
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ctrl_algo: ";
    rosidl_generator_traits::value_to_yaml(msg.ctrl_algo, out);
    out << "\n";
  }

  // member: ctrl_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ctrl_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.ctrl_speed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CtrlMode & msg, bool use_flow_style = false)
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
  const jeju::msg::CtrlMode & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::msg::to_yaml() instead")]]
inline std::string to_yaml(const jeju::msg::CtrlMode & msg)
{
  return jeju::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::msg::CtrlMode>()
{
  return "jeju::msg::CtrlMode";
}

template<>
inline const char * name<jeju::msg::CtrlMode>()
{
  return "jeju/msg/CtrlMode";
}

template<>
struct has_fixed_size<jeju::msg::CtrlMode>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<jeju::msg::CtrlMode>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<jeju::msg::CtrlMode>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JEJU__MSG__DETAIL__CTRL_MODE__TRAITS_HPP_
