// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_READ__FUNCTIONS_H_
#define JEJU__MSG__DETAIL__ERP_READ__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "jeju/msg/rosidl_generator_c__visibility_control.h"

#include "jeju/msg/detail/erp_read__struct.h"

/// Initialize msg/ERPRead message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * jeju__msg__ERPRead
 * )) before or use
 * jeju__msg__ERPRead__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
bool
jeju__msg__ERPRead__init(jeju__msg__ERPRead * msg);

/// Finalize msg/ERPRead message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
void
jeju__msg__ERPRead__fini(jeju__msg__ERPRead * msg);

/// Create msg/ERPRead message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * jeju__msg__ERPRead__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
jeju__msg__ERPRead *
jeju__msg__ERPRead__create();

/// Destroy msg/ERPRead message.
/**
 * It calls
 * jeju__msg__ERPRead__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
void
jeju__msg__ERPRead__destroy(jeju__msg__ERPRead * msg);

/// Check for msg/ERPRead message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
bool
jeju__msg__ERPRead__are_equal(const jeju__msg__ERPRead * lhs, const jeju__msg__ERPRead * rhs);

/// Copy a msg/ERPRead message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
bool
jeju__msg__ERPRead__copy(
  const jeju__msg__ERPRead * input,
  jeju__msg__ERPRead * output);

/// Initialize array of msg/ERPRead messages.
/**
 * It allocates the memory for the number of elements and calls
 * jeju__msg__ERPRead__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
bool
jeju__msg__ERPRead__Sequence__init(jeju__msg__ERPRead__Sequence * array, size_t size);

/// Finalize array of msg/ERPRead messages.
/**
 * It calls
 * jeju__msg__ERPRead__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
void
jeju__msg__ERPRead__Sequence__fini(jeju__msg__ERPRead__Sequence * array);

/// Create array of msg/ERPRead messages.
/**
 * It allocates the memory for the array and calls
 * jeju__msg__ERPRead__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
jeju__msg__ERPRead__Sequence *
jeju__msg__ERPRead__Sequence__create(size_t size);

/// Destroy array of msg/ERPRead messages.
/**
 * It calls
 * jeju__msg__ERPRead__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
void
jeju__msg__ERPRead__Sequence__destroy(jeju__msg__ERPRead__Sequence * array);

/// Check for msg/ERPRead message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
bool
jeju__msg__ERPRead__Sequence__are_equal(const jeju__msg__ERPRead__Sequence * lhs, const jeju__msg__ERPRead__Sequence * rhs);

/// Copy an array of msg/ERPRead messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_jeju
bool
jeju__msg__ERPRead__Sequence__copy(
  const jeju__msg__ERPRead__Sequence * input,
  jeju__msg__ERPRead__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // JEJU__MSG__DETAIL__ERP_READ__FUNCTIONS_H_
