// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jeju:srv/MapLoad.idl
// generated code does not contain a copyright notice

#ifndef JEJU__SRV__DETAIL__MAP_LOAD__TRAITS_HPP_
#define JEJU__SRV__DETAIL__MAP_LOAD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jeju/srv/detail/map_load__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jeju
{

namespace srv
{

inline void to_flow_style_yaml(
  const MapLoad_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request
  {
    out << "request: ";
    rosidl_generator_traits::value_to_yaml(msg.request, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MapLoad_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "request: ";
    rosidl_generator_traits::value_to_yaml(msg.request, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MapLoad_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace jeju

namespace rosidl_generator_traits
{

[[deprecated("use jeju::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jeju::srv::MapLoad_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::srv::to_yaml() instead")]]
inline std::string to_yaml(const jeju::srv::MapLoad_Request & msg)
{
  return jeju::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::srv::MapLoad_Request>()
{
  return "jeju::srv::MapLoad_Request";
}

template<>
inline const char * name<jeju::srv::MapLoad_Request>()
{
  return "jeju/srv/MapLoad_Request";
}

template<>
struct has_fixed_size<jeju::srv::MapLoad_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jeju::srv::MapLoad_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jeju::srv::MapLoad_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace jeju
{

namespace srv
{

inline void to_flow_style_yaml(
  const MapLoad_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: response
  {
    out << "response: ";
    rosidl_generator_traits::value_to_yaml(msg.response, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MapLoad_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "response: ";
    rosidl_generator_traits::value_to_yaml(msg.response, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MapLoad_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace jeju

namespace rosidl_generator_traits
{

[[deprecated("use jeju::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jeju::srv::MapLoad_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  jeju::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jeju::srv::to_yaml() instead")]]
inline std::string to_yaml(const jeju::srv::MapLoad_Response & msg)
{
  return jeju::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jeju::srv::MapLoad_Response>()
{
  return "jeju::srv::MapLoad_Response";
}

template<>
inline const char * name<jeju::srv::MapLoad_Response>()
{
  return "jeju/srv/MapLoad_Response";
}

template<>
struct has_fixed_size<jeju::srv::MapLoad_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jeju::srv::MapLoad_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jeju::srv::MapLoad_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<jeju::srv::MapLoad>()
{
  return "jeju::srv::MapLoad";
}

template<>
inline const char * name<jeju::srv::MapLoad>()
{
  return "jeju/srv/MapLoad";
}

template<>
struct has_fixed_size<jeju::srv::MapLoad>
  : std::integral_constant<
    bool,
    has_fixed_size<jeju::srv::MapLoad_Request>::value &&
    has_fixed_size<jeju::srv::MapLoad_Response>::value
  >
{
};

template<>
struct has_bounded_size<jeju::srv::MapLoad>
  : std::integral_constant<
    bool,
    has_bounded_size<jeju::srv::MapLoad_Request>::value &&
    has_bounded_size<jeju::srv::MapLoad_Response>::value
  >
{
};

template<>
struct is_service<jeju::srv::MapLoad>
  : std::true_type
{
};

template<>
struct is_service_request<jeju::srv::MapLoad_Request>
  : std::true_type
{
};

template<>
struct is_service_response<jeju::srv::MapLoad_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // JEJU__SRV__DETAIL__MAP_LOAD__TRAITS_HPP_
