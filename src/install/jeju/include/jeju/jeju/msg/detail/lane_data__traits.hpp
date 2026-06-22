// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jeju:msg/LaneData.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_DATA__TRAITS_HPP_
#define JEJU__MSG__DETAIL__LANE_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jeju/msg/detail/lane_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'center_points'
// Member 'left_points'
// Member 'right_points'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace jeju
{

namespace msg
{

inline void to_flow_style_yaml(
  const LaneData & msg,
  std::ostream & out)
{
  out << "{";
  // member: detected
  {
    out << "detected: ";
    rosidl_generator_traits::value_to_yaml(msg.detected, out);
    out << ", ";
  }

  // member: steer
  {
    out << "steer: ";
    rosidl_generator_traits::value_to_yaml(msg.steer, out);
    out << ", ";
  }

  // member: center_points
  {
    if (msg.center_points.size() == 0) {
      out << "center_points: []";
    } else {
      out << "center_points: [";
      size_t pending_items = msg.center_points.size();
      for (auto item : msg.center_points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: left_points
  {
    if (msg.left_points.size() == 0) {
      out << "left_points: []";
    } else {
      out << "left_points: [";
      size_t pending_items = msg.left_points.size();
      for (auto item : msg.left_points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: right_points
  {
    if (msg.right_points.size() == 0) {
      out << "right_points: []";
    } else {
      out << "right_points: [";
      size_t pending_items = msg.right_points.size();
      for (auto item : msg.right_points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LaneData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detected: ";
    rosidl_generator_traits::value_to_yaml(msg.detected, out);
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

  // member: center_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.center_points.size() == 0) {
      out << "center_points: []\n";
    } else {
      out << "center_points:\n";
      for (auto item : msg.center_points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: left_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.left_points.size() == 0) {
      out << "left_points: []\n";
    } else {
      out << "left_points:\n";
      for (auto item : msg.left_points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: right_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.right_points.size() == 0) {
      out << "right_points: []\n";
    } else {
      out << "right_points:\n";
      for (auto item : msg.right_points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LaneData & msg, bool use_flow_style = false)
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
  const jeju::msg::LaneData & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::msg::to_yaml() instead")]]
inline std::string to_yaml(const jeju::msg::LaneData & msg)
{
  return jeju::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::msg::LaneData>()
{
  return "jeju::msg::LaneData";
}

template<>
inline const char * name<jeju::msg::LaneData>()
{
  return "jeju/msg/LaneData";
}

template<>
struct has_fixed_size<jeju::msg::LaneData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jeju::msg::LaneData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jeju::msg::LaneData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JEJU__MSG__DETAIL__LANE_DATA__TRAITS_HPP_
