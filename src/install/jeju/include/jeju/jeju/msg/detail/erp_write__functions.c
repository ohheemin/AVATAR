// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jeju:msg/ERPWrite.idl
// generated code does not contain a copyright notice
#include "jeju/msg/detail/erp_write__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
jeju__msg__ERPWrite__init(jeju__msg__ERPWrite * msg)
{
  if (!msg) {
    return false;
  }
  // is_auto
  // is_estop
  // gear
  // speed
  // steer
  // brake
  return true;
}

void
jeju__msg__ERPWrite__fini(jeju__msg__ERPWrite * msg)
{
  if (!msg) {
    return;
  }
  // is_auto
  // is_estop
  // gear
  // speed
  // steer
  // brake
}

bool
jeju__msg__ERPWrite__are_equal(const jeju__msg__ERPWrite * lhs, const jeju__msg__ERPWrite * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_auto
  if (lhs->is_auto != rhs->is_auto) {
    return false;
  }
  // is_estop
  if (lhs->is_estop != rhs->is_estop) {
    return false;
  }
  // gear
  if (lhs->gear != rhs->gear) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  // steer
  if (lhs->steer != rhs->steer) {
    return false;
  }
  // brake
  if (lhs->brake != rhs->brake) {
    return false;
  }
  return true;
}

bool
jeju__msg__ERPWrite__copy(
  const jeju__msg__ERPWrite * input,
  jeju__msg__ERPWrite * output)
{
  if (!input || !output) {
    return false;
  }
  // is_auto
  output->is_auto = input->is_auto;
  // is_estop
  output->is_estop = input->is_estop;
  // gear
  output->gear = input->gear;
  // speed
  output->speed = input->speed;
  // steer
  output->steer = input->steer;
  // brake
  output->brake = input->brake;
  return true;
}

jeju__msg__ERPWrite *
jeju__msg__ERPWrite__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__ERPWrite * msg = (jeju__msg__ERPWrite *)allocator.allocate(sizeof(jeju__msg__ERPWrite), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__msg__ERPWrite));
  bool success = jeju__msg__ERPWrite__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__msg__ERPWrite__destroy(jeju__msg__ERPWrite * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__msg__ERPWrite__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__msg__ERPWrite__Sequence__init(jeju__msg__ERPWrite__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__ERPWrite * data = NULL;

  if (size) {
    data = (jeju__msg__ERPWrite *)allocator.zero_allocate(size, sizeof(jeju__msg__ERPWrite), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__msg__ERPWrite__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__msg__ERPWrite__fini(&data[i - 1]);
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
jeju__msg__ERPWrite__Sequence__fini(jeju__msg__ERPWrite__Sequence * array)
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
      jeju__msg__ERPWrite__fini(&array->data[i]);
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

jeju__msg__ERPWrite__Sequence *
jeju__msg__ERPWrite__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__ERPWrite__Sequence * array = (jeju__msg__ERPWrite__Sequence *)allocator.allocate(sizeof(jeju__msg__ERPWrite__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__msg__ERPWrite__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__msg__ERPWrite__Sequence__destroy(jeju__msg__ERPWrite__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__msg__ERPWrite__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__msg__ERPWrite__Sequence__are_equal(const jeju__msg__ERPWrite__Sequence * lhs, const jeju__msg__ERPWrite__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__msg__ERPWrite__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__msg__ERPWrite__Sequence__copy(
  const jeju__msg__ERPWrite__Sequence * input,
  jeju__msg__ERPWrite__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__msg__ERPWrite);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__msg__ERPWrite * data =
      (jeju__msg__ERPWrite *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__msg__ERPWrite__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__msg__ERPWrite__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__msg__ERPWrite__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
