// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice
#include "jeju/msg/detail/erp_read__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
jeju__msg__ERPRead__init(jeju__msg__ERPRead * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    jeju__msg__ERPRead__fini(msg);
    return false;
  }
  // s
  // t
  // x
  // aorm
  // estop
  // gear
  // speed
  // steer
  // brake
  // enc
  // alive
  // etx0
  // etx1
  return true;
}

void
jeju__msg__ERPRead__fini(jeju__msg__ERPRead * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // s
  // t
  // x
  // aorm
  // estop
  // gear
  // speed
  // steer
  // brake
  // enc
  // alive
  // etx0
  // etx1
}

bool
jeju__msg__ERPRead__are_equal(const jeju__msg__ERPRead * lhs, const jeju__msg__ERPRead * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // s
  if (lhs->s != rhs->s) {
    return false;
  }
  // t
  if (lhs->t != rhs->t) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // aorm
  if (lhs->aorm != rhs->aorm) {
    return false;
  }
  // estop
  if (lhs->estop != rhs->estop) {
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
  // enc
  if (lhs->enc != rhs->enc) {
    return false;
  }
  // alive
  if (lhs->alive != rhs->alive) {
    return false;
  }
  // etx0
  if (lhs->etx0 != rhs->etx0) {
    return false;
  }
  // etx1
  if (lhs->etx1 != rhs->etx1) {
    return false;
  }
  return true;
}

bool
jeju__msg__ERPRead__copy(
  const jeju__msg__ERPRead * input,
  jeju__msg__ERPRead * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // s
  output->s = input->s;
  // t
  output->t = input->t;
  // x
  output->x = input->x;
  // aorm
  output->aorm = input->aorm;
  // estop
  output->estop = input->estop;
  // gear
  output->gear = input->gear;
  // speed
  output->speed = input->speed;
  // steer
  output->steer = input->steer;
  // brake
  output->brake = input->brake;
  // enc
  output->enc = input->enc;
  // alive
  output->alive = input->alive;
  // etx0
  output->etx0 = input->etx0;
  // etx1
  output->etx1 = input->etx1;
  return true;
}

jeju__msg__ERPRead *
jeju__msg__ERPRead__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__ERPRead * msg = (jeju__msg__ERPRead *)allocator.allocate(sizeof(jeju__msg__ERPRead), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__msg__ERPRead));
  bool success = jeju__msg__ERPRead__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__msg__ERPRead__destroy(jeju__msg__ERPRead * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__msg__ERPRead__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__msg__ERPRead__Sequence__init(jeju__msg__ERPRead__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__ERPRead * data = NULL;

  if (size) {
    data = (jeju__msg__ERPRead *)allocator.zero_allocate(size, sizeof(jeju__msg__ERPRead), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__msg__ERPRead__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__msg__ERPRead__fini(&data[i - 1]);
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
jeju__msg__ERPRead__Sequence__fini(jeju__msg__ERPRead__Sequence * array)
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
      jeju__msg__ERPRead__fini(&array->data[i]);
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

jeju__msg__ERPRead__Sequence *
jeju__msg__ERPRead__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__msg__ERPRead__Sequence * array = (jeju__msg__ERPRead__Sequence *)allocator.allocate(sizeof(jeju__msg__ERPRead__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__msg__ERPRead__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__msg__ERPRead__Sequence__destroy(jeju__msg__ERPRead__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__msg__ERPRead__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__msg__ERPRead__Sequence__are_equal(const jeju__msg__ERPRead__Sequence * lhs, const jeju__msg__ERPRead__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__msg__ERPRead__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__msg__ERPRead__Sequence__copy(
  const jeju__msg__ERPRead__Sequence * input,
  jeju__msg__ERPRead__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__msg__ERPRead);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__msg__ERPRead * data =
      (jeju__msg__ERPRead *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__msg__ERPRead__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__msg__ERPRead__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__msg__ERPRead__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
