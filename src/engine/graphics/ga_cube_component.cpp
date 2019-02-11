/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_cube_component.h"
#include "ga_material.h"

#include "entity/ga_entity.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <cassert>

static const GLfloat k_cube_vertices[] = {
	// Front
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// Top
	-1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0,
	// Back
	1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	// Bottom
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0,  1.0,
	-1.0, -1.0,  1.0,
	// Left
	-1.0, -1.0, -1.0,
	-1.0, -1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0,
	// Right
	1.0, -1.0,  1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	1.0,  1.0,  1.0,
};

static const GLfloat k_cube_texcoords[] = {
	// Front
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	// Top
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	// Back
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	// Bottom
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	// Left
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	// Right
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
};

static const GLfloat k_cube_normals[] = {
	// Front
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	// Top
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	// Back
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	// Bottom
	0.0, -1.0, 0.0,
	0.0, -1.0, 0.0,
	0.0, -1.0, 0.0,
	0.0, -1.0, 0.0,
	// Left
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	// Right
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
};

static const GLushort k_cube_indices[] = {
	// Front
	0,  1,  2,
	2,  3,  0,
	// Top
	4,  5,  6,
	6,  7,  4,
	// Back
	8,  9, 10,
	10, 11,  8,
	// Bottom
	12, 13, 14,
	14, 15, 12,
	// Left
	16, 17, 18,
	18, 19, 16,
	// Right
	20, 21, 22,
	22, 23, 20,
};

GLuint vbo[4];

void ga_cube_component::create_vertex_array()
{
	// TODO: Homework 3 - Create the vertex array object _vao and any 
	// buffers needed to hold the vertex data provided above.

}

void ga_cube_component::destroy_vertex_array()
{
	// TODO: Homework 3 - Do any necessary cleanup here.
}

ga_cube_component::ga_cube_component(ga_entity* ent, const char* texture_file) : ga_component(ent)
{
	_material = new ga_unlit_texture_material(texture_file);
	_material->init();

	_index_count = uint32_t(sizeof(k_cube_indices) / sizeof(*k_cube_indices));

	create_vertex_array();
}

ga_cube_component::~ga_cube_component()
{
	destroy_vertex_array();

	delete _material;
}

void ga_cube_component::update(ga_frame_params* params)
{
	const float dt = std::chrono::duration_cast<std::chrono::duration<float>>(params->_delta_time).count();

	// Rotate the cube 60 degrees per second around the y-axis

	get_entity()->rotate({ 0,60.0f*dt,0 });

	// Prepare the draw calls and add it to the list
	ga_static_drawcall draw;
	draw._name = "ga_cube_component";
	draw._vao = _vao;
	draw._index_count = _index_count;
	draw._transform = get_entity()->get_transform();
	draw._draw_mode = GL_TRIANGLES;
	draw._material = _material;

	while (params->_static_drawcall_lock.test_and_set(std::memory_order_acquire)) {}
	params->_static_drawcalls.push_back(draw);
	params->_static_drawcall_lock.clear(std::memory_order_release);
}
