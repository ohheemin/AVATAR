// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jeju:msg/LaneData.idl
// generated code does not contain a copyright notice
#include "jeju/msg/detail/lane_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `center_points`
// Member `left_points`
// Member `right_points`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
jeju__msg__LaneData__init(jeju__msg__LaneData * msg)
{
  if (!msg) {
    return false;
  }
  // detected
  // steer
  // center_points
  if (!geometry_msgs__msg__Vector3__Sequence__init(&msg->center_points, 0)) {
    jeju__msg__LaneData__fini(msg);
    return false;
  }
  // left_points
  if (!geometry_msgs__msg__Vector3__Sequence__init(&msg->left_points, 0)) {
    jeju__msg__LaneData__fini(msg);
    return false;
  }
  // right_points
  if (!geometry_msgs__msg__Vector3__Sequence__init(&msg->right_points, 0)) {
    jeju__msg__LaneData__fini(msg);
    return false;
  }
  return true;
}

void
jeju__msg__LaneData__fini(jeju__msg__LaneData * msg)
{
  if (!msg) {
    return;
  }
  // detected
  // steer
  // center_points
  geometry_msgs__msg__Vector3__Sequence__fini(&msg->center_points);
  // left_points
  geometry_msgs__msg__Vector3__Sequence__fini(&msg->left_points);
  // right_points
  geometry_msgs__msg__Vector3__Sequence__fini(&msg->right_points);
}

bool
jeju__msg__LaneData__are_equal(const jeju__msg__LaneData * lhs, const jeju__msg__LaneData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // detected
  if (lhs->detected != rhs->detected) {
    return false;
  }
  // steer
  if (lhs->steer != rhs->steer) {
    return false;
  }
  // center_points
  if (!geometry_msgs__msg__Vector3__Sequence__are_equal(
      &(lhs->center_points), &(rhs->center_points)))
  {
    return false;
  }
  // left_points
  if (!geometry_msgs__msg__Vector3__Sequence__are_equal(
      &(lhs->left_points), &(rhs->left_points)))
  {
    return false;
  }
  // right_points
  if (!geometry_msgs__msg__Vector3__Sequence__are_equal(
      &(lhs->right_points), &(rhs->right_points)))
  {
    return false;
  }
  return true;
}

bool
jeju__msg__LaneData__copy(
  const jeju__msg__LaneData * input,
  jeju__msg__LaneData * output)
{
  if (!input || !output) {
    return false;
  }
  // detected
  output->detected = input->detected;
  // steer
  output->steer = input->steer;
  // center_points
  if (!geometry_msgs__msg__Vector3__Sequence__copy(
      &(input->center_points), &(output->center_points)))
  {
    return false;
  }
  // left_points
  if (!geometry_msgs__msg__Vector3__Sequence__copy(
      &(input->left_points), &(output->left_points)))
  {
    return false;
  }
  // right_points
  if (!geometry_msgs__msg__Vector3__Sequence__copy(
      &(input->right_points), &(output->right_points)))
  {
    return false;
  }
  return true;
}

jeju__msg__LaneData *
jeju__msg__LaneData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__LaneData * msg = (jeju__msg__LaneData *)allocator.allocate(sizeof(jeju__msg__LaneData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__msg__LaneData));
  bool success = jeju__msg__LaneData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__msg__LaneData__destroy(jeju__msg__LaneData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__msg__LaneData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__msg__LaneData__Sequence__init(jeju__msg__LaneData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__LaneData * data = NULL;

  if (size) {
    data = (jeju__msg__LaneData *)allocator.zero_allocate(size, sizeof(jeju__msg__LaneData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__msg__LaneData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__msg__LaneData__fini(&data[i - 1]);
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
jeju__msg__LaneData__Sequence__fini(jeju__msg__LaneData__Sequence * array)
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
      jeju__msg__LaneData__fini(&array->data[i]);
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

jeju__msg__LaneData__Sequence *
jeju__msg__LaneData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__LaneData__Sequence * array = (jeju__msg__LaneData__Sequence *)allocator.allocate(sizeof(jeju__msg__LaneData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__msg__LaneData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__msg__LaneData__Sequence__destroy(jeju__msg__LaneData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__msg__LaneData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__msg__LaneData__Sequence__are_equal(const jeju__msg__LaneData__Sequence * lhs, const jeju__msg__LaneData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__msg__LaneData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__msg__LaneData__Sequence__copy(
  const jeju__msg__LaneData__Sequence * input,
  jeju__msg__LaneData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__msg__LaneData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__msg__LaneData * data =
      (jeju__msg__LaneData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__msg__LaneData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__msg__LaneData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__msg__LaneData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
