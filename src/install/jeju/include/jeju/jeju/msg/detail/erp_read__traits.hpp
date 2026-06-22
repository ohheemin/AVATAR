// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_READ__TRAITS_HPP_
#define JEJU__MSG__DETAIL__ERP_READ__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jeju/msg/detail/erp_read__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace jeju
{

namespace msg
{

inline void to_flow_style_yaml(
  const ERPRead & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: s
  {
    out << "s: ";
    rosidl_generator_traits::value_to_yaml(msg.s, out);
    out << ", ";
  }

  // member: t
  {
    out << "t: ";
    rosidl_generator_traits::value_to_yaml(msg.t, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: aorm
  {
    out << "aorm: ";
    rosidl_generator_traits::value_to_yaml(msg.aorm, out);
    out << ", ";
  }

  // member: estop
  {
    out << "estop: ";
    rosidl_generator_traits::value_to_yaml(msg.estop, out);
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
    out << ", ";
  }

  // member: enc
  {
    out << "enc: ";
    rosidl_generator_traits::value_to_yaml(msg.enc, out);
    out << ", ";
  }

  // member: alive
  {
    out << "alive: ";
    rosidl_generator_traits::value_to_yaml(msg.alive, out);
    out << ", ";
  }

  // member: etx0
  {
    out << "etx0: ";
    rosidl_generator_traits::value_to_yaml(msg.etx0, out);
    out << ", ";
  }

  // member: etx1
  {
    out << "etx1: ";
    rosidl_generator_traits::value_to_yaml(msg.etx1, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ERPRead & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "s: ";
    rosidl_generator_traits::value_to_yaml(msg.s, out);
    out << "\n";
  }

  // member: t
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "t: ";
    rosidl_generator_traits::value_to_yaml(msg.t, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: aorm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "aorm: ";
    rosidl_generator_traits::value_to_yaml(msg.aorm, out);
    out << "\n";
  }

  // member: estop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estop: ";
    rosidl_generator_traits::value_to_yaml(msg.estop, out);
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

  // member: enc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enc: ";
    rosidl_generator_traits::value_to_yaml(msg.enc, out);
    out << "\n";
  }

  // member: alive
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alive: ";
    rosidl_generator_traits::value_to_yaml(msg.alive, out);
    out << "\n";
  }

  // member: etx0
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "etx0: ";
    rosidl_generator_traits::value_to_yaml(msg.etx0, out);
    out << "\n";
  }

  // member: etx1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "etx1: ";
    rosidl_generator_traits::value_to_yaml(msg.etx1, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ERPRead & msg, bool use_flow_style = false)
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
  const jeju::msg::ERPRead & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::msg::to_yaml() instead")]]
inline std::string to_yaml(const jeju::msg::ERPRead & msg)
{
  return jeju::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::msg::ERPRead>()
{
  return "jeju::msg::ERPRead";
}

template<>
inline const char * name<jeju::msg::ERPRead>()
{
  return "jeju/msg/ERPRead";
}

template<>
struct has_fixed_size<jeju::msg::ERPRead>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<jeju::msg::ERPRead>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<jeju::msg::ERPRead>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JEJU__MSG__DETAIL__ERP_READ__TRAITS_HPP_
