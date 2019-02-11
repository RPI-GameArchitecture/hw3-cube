/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	// TODO (HW1):
	// Initialize the queue.
}

ga_queue::~ga_queue()
{
	// TODO (HW1):
	// Free any resources held by the queue.
}

void ga_queue::push(void* data)
{
	// TODO (HW1):
	// Push 'data' onto the queue in a thread-safe manner.
	// If you preallocated 'node_count' elements, and if the queue is full when
	// this function is called, you must block until another thread pops an
	// element off the queue.
}

bool ga_queue::pop(void** data)
{
	// TODO (HW1):
	// Pop one element off the queue in a thread-safe manner and place it in
	// the memory pointed to by 'data'.
	// If the queue is empty when this function is called, return false.
	// Otherwise return true.

	return false;
}

int ga_queue::get_count() const
{
	// TODO (HW1):
	// Get the number of elements currently in the queue.
	return 0;
}


