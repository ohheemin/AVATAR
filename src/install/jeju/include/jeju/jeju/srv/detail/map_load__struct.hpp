// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jeju:srv/MapLoad.idl
// generated code does not contain a copyright notice

#ifndef JEJU__SRV__DETAIL__MAP_LOAD__STRUCT_HPP_
#define JEJU__SRV__DETAIL__MAP_LOAD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jeju__srv__MapLoad_Request __attribute__((deprecated))
#else
# define DEPRECATED__jeju__srv__MapLoad_Request __declspec(deprecated)
#endif

namespace jeju
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MapLoad_Request_
{
  using Type = MapLoad_Request_<ContainerAllocator>;

  explicit MapLoad_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->request = "";
    }
  }

  explicit MapLoad_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->request = "";
    }
  }

  // field types and members
  using _request_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _request_type request;

  // setters for named parameter idiom
  Type & set__request(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->request = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::srv::MapLoad_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::srv::MapLoad_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::srv::MapLoad_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::srv::MapLoad_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__srv__MapLoad_Request
    std::shared_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__srv__MapLoad_Request
    std::shared_ptr<jeju::srv::MapLoad_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MapLoad_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    return true;
  }
  bool operator!=(const MapLoad_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MapLoad_Request_

// alias to use template instance with default allocator
using MapLoad_Request =
  jeju::srv::MapLoad_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jeju


#ifndef _WIN32
# define DEPRECATED__jeju__srv__MapLoad_Response __attribute__((deprecated))
#else
# define DEPRECATED__jeju__srv__MapLoad_Response __declspec(deprecated)
#endif

namespace jeju
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MapLoad_Response_
{
  using Type = MapLoad_Response_<ContainerAllocator>;

  explicit MapLoad_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response = "";
    }
  }

  explicit MapLoad_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response = "";
    }
  }

  // field types and members
  using _response_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__response(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::srv::MapLoad_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::srv::MapLoad_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::srv::MapLoad_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::srv::MapLoad_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__srv__MapLoad_Response
    std::shared_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__srv__MapLoad_Response
    std::shared_ptr<jeju::srv::MapLoad_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MapLoad_Response_ & other) const
  {
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const MapLoad_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MapLoad_Response_

// alias to use template instance with default allocator
using MapLoad_Response =
  jeju::srv::MapLoad_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jeju

namespace jeju
{

namespace srv
{

struct MapLoad
{
  using Request = jeju::srv::MapLoad_Request;
  using Response = jeju::srv::MapLoad_Response;
};

}  // namespace srv

}  // namespace jeju

#endif  // JEJU__SRV__DETAIL__MAP_LOAD__STRUCT_HPP_
