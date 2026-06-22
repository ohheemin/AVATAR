// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jeju:msg/LaneInfo.idl
// generated code does not contain a copyright notice
#include "jeju/msg/detail/lane_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `center_line_x`
// Member `center_line_y`
// Member `center_line_yaw`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
jeju__msg__LaneInfo__init(jeju__msg__LaneInfo * msg)
{
  if (!msg) {
    return false;
  }
  // center_line_x
  if (!rosidl_runtime_c__float__Sequence__init(&msg->center_line_x, 0)) {
    jeju__msg__LaneInfo__fini(msg);
    return false;
  }
  // center_line_y
  if (!rosidl_runtime_c__float__Sequence__init(&msg->center_line_y, 0)) {
    jeju__msg__LaneInfo__fini(msg);
    return false;
  }
  // center_line_yaw
  if (!rosidl_runtime_c__float__Sequence__init(&msg->center_line_yaw, 0)) {
    jeju__msg__LaneInfo__fini(msg);
    return false;
  }
  // lane_mode
  // speed_mode
  return true;
}

void
jeju__msg__LaneInfo__fini(jeju__msg__LaneInfo * msg)
{
  if (!msg) {
    return;
  }
  // center_line_x
  rosidl_runtime_c__float__Sequence__fini(&msg->center_line_x);
  // center_line_y
  rosidl_runtime_c__float__Sequence__fini(&msg->center_line_y);
  // center_line_yaw
  rosidl_runtime_c__float__Sequence__fini(&msg->center_line_yaw);
  // lane_mode
  // speed_mode
}

bool
jeju__msg__LaneInfo__are_equal(const jeju__msg__LaneInfo * lhs, const jeju__msg__LaneInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // center_line_x
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->center_line_x), &(rhs->center_line_x)))
  {
    return false;
  }
  // center_line_y
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->center_line_y), &(rhs->center_line_y)))
  {
    return false;
  }
  // center_line_yaw
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->center_line_yaw), &(rhs->center_line_yaw)))
  {
    return false;
  }
  // lane_mode
  if (lhs->lane_mode != rhs->lane_mode) {
    return false;
  }
  // speed_mode
  if (lhs->speed_mode != rhs->speed_mode) {
    return false;
  }
  return true;
}

bool
jeju__msg__LaneInfo__copy(
  const jeju__msg__LaneInfo * input,
  jeju__msg__LaneInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // center_line_x
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->center_line_x), &(output->center_line_x)))
  {
    return false;
  }
  // center_line_y
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->center_line_y), &(output->center_line_y)))
  {
    return false;
  }
  // center_line_yaw
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->center_line_yaw), &(output->center_line_yaw)))
  {
    return false;
  }
  // lane_mode
  output->lane_mode = input->lane_mode;
  // speed_mode
  output->speed_mode = input->speed_mode;
  return true;
}

jeju__msg__LaneInfo *
jeju__msg__LaneInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__LaneInfo * msg = (jeju__msg__LaneInfo *)allocator.allocate(sizeof(jeju__msg__LaneInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__msg__LaneInfo));
  bool success = jeju__msg__LaneInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__msg__LaneInfo__destroy(jeju__msg__LaneInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__msg__LaneInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__msg__LaneInfo__Sequence__init(jeju__msg__LaneInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__LaneInfo * data = NULL;

  if (size) {
    data = (jeju__msg__LaneInfo *)allocator.zero_allocate(size, sizeof(jeju__msg__LaneInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__msg__LaneInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__msg__LaneInfo__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
jeju__msg__LaneInfo__Sequence__fini(jeju__msg__LaneInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      jeju__msg__LaneInfo__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

jeju__msg__LaneInfo__Sequence *
jeju__msg__LaneInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__LaneInfo__Sequence * array = (jeju__msg__LaneInfo__Sequence *)allocator.allocate(sizeof(jeju__msg__LaneInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__msg__LaneInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__msg__LaneInfo__Sequence__destroy(jeju__msg__LaneInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__msg__LaneInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__msg__LaneInfo__Sequence__are_equal(const jeju__msg__LaneInfo__Sequence * lhs, const jeju__msg__LaneInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__msg__LaneInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__msg__LaneInfo__Sequence__copy(
  const jeju__msg__LaneInfo__Sequence * input,
  jeju__msg__LaneInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__msg__LaneInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__msg__LaneInfo * data =
      (jeju__msg__LaneInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__msg__LaneInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__msg__LaneInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__msg__LaneInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
