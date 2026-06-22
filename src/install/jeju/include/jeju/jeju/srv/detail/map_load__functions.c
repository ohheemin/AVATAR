// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jeju:srv/MapLoad.idl
// generated code does not contain a copyright notice
#include "jeju/srv/detail/map_load__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `request`
#include "rosidl_runtime_c/string_functions.h"

bool
jeju__srv__MapLoad_Request__init(jeju__srv__MapLoad_Request * msg)
{
  if (!msg) {
    return false;
  }
  // request
  if (!rosidl_runtime_c__String__init(&msg->request)) {
    jeju__srv__MapLoad_Request__fini(msg);
    return false;
  }
  return true;
}

void
jeju__srv__MapLoad_Request__fini(jeju__srv__MapLoad_Request * msg)
{
  if (!msg) {
    return;
  }
  // request
  rosidl_runtime_c__String__fini(&msg->request);
}

bool
jeju__srv__MapLoad_Request__are_equal(const jeju__srv__MapLoad_Request * lhs, const jeju__srv__MapLoad_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // request
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  return true;
}

bool
jeju__srv__MapLoad_Request__copy(
  const jeju__srv__MapLoad_Request * input,
  jeju__srv__MapLoad_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // request
  if (!rosidl_runtime_c__String__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  return true;
}

jeju__srv__MapLoad_Request *
jeju__srv__MapLoad_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__srv__MapLoad_Request * msg = (jeju__srv__MapLoad_Request *)allocator.allocate(sizeof(jeju__srv__MapLoad_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__srv__MapLoad_Request));
  bool success = jeju__srv__MapLoad_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__srv__MapLoad_Request__destroy(jeju__srv__MapLoad_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__srv__MapLoad_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__srv__MapLoad_Request__Sequence__init(jeju__srv__MapLoad_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__srv__MapLoad_Request * data = NULL;

  if (size) {
    data = (jeju__srv__MapLoad_Request *)allocator.zero_allocate(size, sizeof(jeju__srv__MapLoad_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__srv__MapLoad_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__srv__MapLoad_Request__fini(&data[i - 1]);
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
jeju__srv__MapLoad_Request__Sequence__fini(jeju__srv__MapLoad_Request__Sequence * array)
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
      jeju__srv__MapLoad_Request__fini(&array->data[i]);
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

jeju__srv__MapLoad_Request__Sequence *
jeju__srv__MapLoad_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__srv__MapLoad_Request__Sequence * array = (jeju__srv__MapLoad_Request__Sequence *)allocator.allocate(sizeof(jeju__srv__MapLoad_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__srv__MapLoad_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__srv__MapLoad_Request__Sequence__destroy(jeju__srv__MapLoad_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__srv__MapLoad_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__srv__MapLoad_Request__Sequence__are_equal(const jeju__srv__MapLoad_Request__Sequence * lhs, const jeju__srv__MapLoad_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__srv__MapLoad_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__srv__MapLoad_Request__Sequence__copy(
  const jeju__srv__MapLoad_Request__Sequence * input,
  jeju__srv__MapLoad_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__srv__MapLoad_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__srv__MapLoad_Request * data =
      (jeju__srv__MapLoad_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__srv__MapLoad_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__srv__MapLoad_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__srv__MapLoad_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `response`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
jeju__srv__MapLoad_Response__init(jeju__srv__MapLoad_Response * msg)
{
  if (!msg) {
    return false;
  }
  // response
  if (!rosidl_runtime_c__String__init(&msg->response)) {
    jeju__srv__MapLoad_Response__fini(msg);
    return false;
  }
  return true;
}

void
jeju__srv__MapLoad_Response__fini(jeju__srv__MapLoad_Response * msg)
{
  if (!msg) {
    return;
  }
  // response
  rosidl_runtime_c__String__fini(&msg->response);
}

bool
jeju__srv__MapLoad_Response__are_equal(const jeju__srv__MapLoad_Response * lhs, const jeju__srv__MapLoad_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // response
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
jeju__srv__MapLoad_Response__copy(
  const jeju__srv__MapLoad_Response * input,
  jeju__srv__MapLoad_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // response
  if (!rosidl_runtime_c__String__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

jeju__srv__MapLoad_Response *
jeju__srv__MapLoad_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__srv__MapLoad_Response * msg = (jeju__srv__MapLoad_Response *)allocator.allocate(sizeof(jeju__srv__MapLoad_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jeju__srv__MapLoad_Response));
  bool success = jeju__srv__MapLoad_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jeju__srv__MapLoad_Response__destroy(jeju__srv__MapLoad_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jeju__srv__MapLoad_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jeju__srv__MapLoad_Response__Sequence__init(jeju__srv__MapLoad_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__srv__MapLoad_Response * data = NULL;

  if (size) {
    data = (jeju__srv__MapLoad_Response *)allocator.zero_allocate(size, sizeof(jeju__srv__MapLoad_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jeju__srv__MapLoad_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jeju__srv__MapLoad_Response__fini(&data[i - 1]);
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
jeju__srv__MapLoad_Response__Sequence__fini(jeju__srv__MapLoad_Response__Sequence * array)
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
      jeju__srv__MapLoad_Response__fini(&array->data[i]);
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

jeju__srv__MapLoad_Response__Sequence *
jeju__srv__MapLoad_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jeju__srv__MapLoad_Response__Sequence * array = (jeju__srv__MapLoad_Response__Sequence *)allocator.allocate(sizeof(jeju__srv__MapLoad_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jeju__srv__MapLoad_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jeju__srv__MapLoad_Response__Sequence__destroy(jeju__srv__MapLoad_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jeju__srv__MapLoad_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jeju__srv__MapLoad_Response__Sequence__are_equal(const jeju__srv__MapLoad_Response__Sequence * lhs, const jeju__srv__MapLoad_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jeju__srv__MapLoad_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jeju__srv__MapLoad_Response__Sequence__copy(
  const jeju__srv__MapLoad_Response__Sequence * input,
  jeju__srv__MapLoad_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jeju__srv__MapLoad_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jeju__srv__MapLoad_Response * data =
      (jeju__srv__MapLoad_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jeju__srv__MapLoad_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jeju__srv__MapLoad_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jeju__srv__MapLoad_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
