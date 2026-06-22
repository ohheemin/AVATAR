// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from msg_test:msg/Sum.idl
// generated code does not contain a copyright notice

#ifndef MSG_TEST__MSG__DETAIL__SUM__TRAITS_HPP_
#define MSG_TEST__MSG__DETAIL__SUM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "msg_test/msg/detail/sum__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace msg_test
{

namespace msg
{

inline void to_flow_style_yaml(
  const Sum & msg,
  std::ostream & out)
{
  out << "{";
  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << ", ";
  }

  // member: sum
  {
    out << "sum: ";
    rosidl_generator_traits::value_to_yaml(msg.sum, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Sum & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }

  // member: sum
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sum: ";
    rosidl_generator_traits::value_to_yaml(msg.sum, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Sum & msg, bool use_flow_style = false)
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

}  // namespace msg_test

namespace rosidl_generator_traits
{

[[deprecated("use msg_test::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const msg_test::msg::Sum & msg,
  std::ostream & out, size_t indentation = 0)
{
  msg_test::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use msg_test::msg::to_yaml() instead")]]
inline std::string to_yaml(const msg_test::msg::Sum & msg)
{
  return msg_test::msg::to_yaml(msg);
}

template<>
inline const char * data_type<msg_test::msg::Sum>()
{
  return "msg_test::msg::Sum";
}

template<>
inline const char * name<msg_test::msg::Sum>()
{
  return "msg_test/msg/Sum";
}

template<>
struct has_fixed_size<msg_test::msg::Sum>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<msg_test::msg::Sum>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<msg_test::msg::Sum>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MSG_TEST__MSG__DETAIL__SUM__TRAITS_HPP_
