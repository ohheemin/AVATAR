// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from msg_test:msg/Sum.idl
// generated code does not contain a copyright notice
#include "msg_test/msg/detail/sum__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
msg_test__msg__Sum__init(msg_test__msg__Sum * msg)
{
  if (!msg) {
    return false;
  }
  // a
  // b
  // sum
  return true;
}

void
msg_test__msg__Sum__fini(msg_test__msg__Sum * msg)
{
  if (!msg) {
    return;
  }
  // a
  // b
  // sum
}

bool
msg_test__msg__Sum__are_equal(const msg_test__msg__Sum * lhs, const msg_test__msg__Sum * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  // sum
  if (lhs->sum != rhs->sum) {
    return false;
  }
  return true;
}

bool
msg_test__msg__Sum__copy(
  const msg_test__msg__Sum * input,
  msg_test__msg__Sum * output)
{
  if (!input || !output) {
    return false;
  }
  // a
  output->a = input->a;
  // b
  output->b = input->b;
  // sum
  output->sum = input->sum;
  return true;
}

msg_test__msg__Sum *
msg_test__msg__Sum__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msg_test__msg__Sum * msg = (msg_test__msg__Sum *)allocator.allocate(sizeof(msg_test__msg__Sum), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(msg_test__msg__Sum));
  bool success = msg_test__msg__Sum__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
msg_test__msg__Sum__destroy(msg_test__msg__Sum * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    msg_test__msg__Sum__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
msg_test__msg__Sum__Sequence__init(msg_test__msg__Sum__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msg_test__msg__Sum * data = NULL;

  if (size) {
    data = (msg_test__msg__Sum *)allocator.zero_allocate(size, sizeof(msg_test__msg__Sum), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = msg_test__msg__Sum__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        msg_test__msg__Sum__fini(&data[i - 1]);
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
msg_test__msg__Sum__Sequence__fini(msg_test__msg__Sum__Sequence * array)
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
      msg_test__msg__Sum__fini(&array->data[i]);
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

msg_test__msg__Sum__Sequence *
msg_test__msg__Sum__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msg_test__msg__Sum__Sequence * array = (msg_test__msg__Sum__Sequence *)allocator.allocate(sizeof(msg_test__msg__Sum__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = msg_test__msg__Sum__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
msg_test__msg__Sum__Sequence__destroy(msg_test__msg__Sum__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    msg_test__msg__Sum__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
msg_test__msg__Sum__Sequence__are_equal(const msg_test__msg__Sum__Sequence * lhs, const msg_test__msg__Sum__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!msg_test__msg__Sum__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
msg_test__msg__Sum__Sequence__copy(
  const msg_test__msg__Sum__Sequence * input,
  msg_test__msg__Sum__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(msg_test__msg__Sum);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    msg_test__msg__Sum * data =
      (msg_test__msg__Sum *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!msg_test__msg__Sum__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          msg_test__msg__Sum__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!msg_test__msg__Sum__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
