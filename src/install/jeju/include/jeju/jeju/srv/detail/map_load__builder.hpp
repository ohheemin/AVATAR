// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jeju:srv/MapLoad.idl
// generated code does not contain a copyright notice

#ifndef JEJU__SRV__DETAIL__MAP_LOAD__BUILDER_HPP_
#define JEJU__SRV__DETAIL__MAP_LOAD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jeju/srv/detail/map_load__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jeju
{

namespace srv
{

namespace builder
{

class Init_MapLoad_Request_request
{
public:
  Init_MapLoad_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::jeju::srv::MapLoad_Request request(::jeju::srv::MapLoad_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::srv::MapLoad_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::srv::MapLoad_Request>()
{
  return jeju::srv::builder::Init_MapLoad_Request_request();
}

}  // namespace jeju


namespace jeju
{

namespace srv
{

namespace builder
{

class Init_MapLoad_Response_response
{
public:
  Init_MapLoad_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::jeju::srv::MapLoad_Response response(::jeju::srv::MapLoad_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::srv::MapLoad_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::srv::MapLoad_Response>()
{
  return jeju::srv::builder::Init_MapLoad_Response_response();
}

}  // namespace jeju

#endif  // JEJU__SRV__DETAIL__MAP_LOAD__BUILDER_HPP_
