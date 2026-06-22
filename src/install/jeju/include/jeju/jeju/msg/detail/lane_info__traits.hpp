// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jeju:msg/LaneInfo.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_INFO__TRAITS_HPP_
#define JEJU__MSG__DETAIL__LANE_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jeju/msg/detail/lane_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jeju
{

namespace msg
{

inline void to_flow_style_yaml(
  const LaneInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: center_line_x
  {
    if (msg.center_line_x.size() == 0) {
      out << "center_line_x: []";
    } else {
      out << "center_line_x: [";
      size_t pending_items = msg.center_line_x.size();
      for (auto item : msg.center_line_x) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: center_line_y
  {
    if (msg.center_line_y.size() == 0) {
      out << "center_line_y: []";
    } else {
      out << "center_line_y: [";
      size_t pending_items = msg.center_line_y.size();
      for (auto item : msg.center_line_y) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: center_line_yaw
  {
    if (msg.center_line_yaw.size() == 0) {
      out << "center_line_yaw: []";
    } else {
      out << "center_line_yaw: [";
      size_t pending_items = msg.center_line_yaw.size();
      for (auto item : msg.center_line_yaw) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: lane_mode
  {
    out << "lane_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.lane_mode, out);
    out << ", ";
  }

  // member: speed_mode
  {
    out << "speed_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LaneInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: center_line_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.center_line_x.size() == 0) {
      out << "center_line_x: []\n";
    } else {
      out << "center_line_x:\n";
      for (auto item : msg.center_line_x) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: center_line_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.center_line_y.size() == 0) {
      out << "center_line_y: []\n";
    } else {
      out << "center_line_y:\n";
      for (auto item : msg.center_line_y) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: center_line_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.center_line_yaw.size() == 0) {
      out << "center_line_yaw: []\n";
    } else {
      out << "center_line_yaw:\n";
      for (auto item : msg.center_line_yaw) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: lane_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lane_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.lane_mode, out);
    out << "\n";
  }

  // member: speed_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LaneInfo & msg, bool use_flow_style = false)
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
  const jeju::msg::LaneInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::msg::to_yaml() instead")]]
inline std::string to_yaml(const jeju::msg::LaneInfo & msg)
{
  return jeju::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::msg::LaneInfo>()
{
  return "jeju::msg::LaneInfo";
}

template<>
inline const char * name<jeju::msg::LaneInfo>()
{
  return "jeju/msg/LaneInfo";
}

template<>
struct has_fixed_size<jeju::msg::LaneInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jeju::msg::LaneInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jeju::msg::LaneInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JEJU__MSG__DETAIL__LANE_INFO__TRAITS_HPP_
