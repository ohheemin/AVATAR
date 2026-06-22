// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jeju:msg/CtrlMode.idl
// generated code does not contain a copyright notice
#include "jeju/msg/detail/ctrl_mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
jeju__msg__CtrlMode__init(jeju__msg__CtrlMode * msg)
{
  if (!msg) {
    return false;
  }
  // ctrl_algo
  // ctrl_speed
  return true;
}

void
jeju__msg__CtrlMode__fini(jeju__msg__CtrlMode * msg)
{
  if (!msg) {
    return;
  }
  // ctrl_algo
  // ctrl_speed
}

bool
jeju__msg__CtrlMode__are_equal(const jeju__msg__CtrlMode * lhs, const jeju__msg__CtrlMode * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ctrl_algo
  if (lhs->ctrl_algo != rhs->ctrl_algo) {
    return false;
  }
  // ctrl_speed
  if (lhs->ctrl_speed != rhs->ctrl_speed) {
    return false;
  }
  return true;
}

bool
jeju__msg__CtrlMode__copy(
  const jeju__msg__CtrlMode * input,
  jeju__msg__CtrlMode * output)
{
  if (!input || !output) {
    return false;
  }
  // ctrl_algo
  output->ctrl_algo = input->ctrl_algo;
  // ctrl_speed
  output->ctrl_speed = input->ctrl_speed;
  return true;
}

jeju__msg__CtrlMode *
jeju__msg__CtrlMode__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__CtrlMode * msg = (jeju__msg__CtrlMode *)allocator.allocate(sizeof(jeju__msg__CtrlMode), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__msg__CtrlMode));
  bool success = jeju__msg__CtrlMode__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__msg__CtrlMode__destroy(jeju__msg__CtrlMode * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__msg__CtrlMode__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__msg__CtrlMode__Sequence__init(jeju__msg__CtrlMode__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__CtrlMode * data = NULL;

  if (size) {
    data = (jeju__msg__CtrlMode *)allocator.zero_allocate(size, sizeof(jeju__msg__CtrlMode), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__msg__CtrlMode__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__msg__CtrlMode__fini(&data[i - 1]);
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
jeju__msg__CtrlMode__Sequence__fini(jeju__msg__CtrlMode__Sequence * array)
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
      jeju__msg__CtrlMode__fini(&array->data[i]);
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

jeju__msg__CtrlMode__Sequence *
jeju__msg__CtrlMode__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__CtrlMode__Sequence * array = (jeju__msg__CtrlMode__Sequence *)allocator.allocate(sizeof(jeju__msg__CtrlMode__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__msg__CtrlMode__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__msg__CtrlMode__Sequence__destroy(jeju__msg__CtrlMode__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__msg__CtrlMode__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__msg__CtrlMode__Sequence__are_equal(const jeju__msg__CtrlMode__Sequence * lhs, const jeju__msg__CtrlMode__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__msg__CtrlMode__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__msg__CtrlMode__Sequence__copy(
  const jeju__msg__CtrlMode__Sequence * input,
  jeju__msg__CtrlMode__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__msg__CtrlMode);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__msg__CtrlMode * data =
      (jeju__msg__CtrlMode *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__msg__CtrlMode__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__msg__CtrlMode__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__msg__CtrlMode__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
