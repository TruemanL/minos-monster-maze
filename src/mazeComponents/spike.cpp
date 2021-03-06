#include "../include/mazeComponents/spike.hpp"

#include <string>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

bool Spike::init(vec2 position)
{
    // Reads the spikes mesh from a file, which contains a list of vertices and indices
    FILE* mesh_file = fopen(mesh_path("spike.mesh"), "r");
    if (mesh_file == nullptr)
        return false;

    // Reading vertices and colors
    size_t num_vertices;
    fscanf(mesh_file, "%zu\n", &num_vertices);
    for (size_t i = 0; i < num_vertices; ++i)
    {
        float x, y, z;
        float _u[3]; // unused
        int r, g, b;
        fscanf(mesh_file, "%f %f %f %f %f %f %d %d %d\n", &x, &y, &z, _u, _u+1, _u+2, &r, &g, &b);
        Vertex vertex;
        vertex.position = { x, y, -z };
        vertex.color = { (float)r / 255, (float)g / 255, (float)b / 255 };
        vertices.push_back(vertex);
		local_vertex_coords.push_back(vertex.position);
    }

    // Reading associated indices
    size_t num_indices;
    fscanf(mesh_file, "%zu\n", &num_indices);
    for (size_t i = 0; i < num_indices; ++i)
    {
        int idx[3];
        fscanf(mesh_file, "%d %d %d\n", idx, idx + 1, idx + 2);
        indices.push_back((uint16_t)idx[0]);
        indices.push_back((uint16_t)idx[1]);
        indices.push_back((uint16_t)idx[2]);
    }

    // Done reading
    fclose(mesh_file);

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors())
        return false;

    // Loading shaders
    if (!effect.load_from_file(shader_path("colored.vs.glsl"), shader_path("colored.fs.glsl")))
        return false;

    // Setting initial values
    m_scale.x = 10.f;
	m_scale.y = 25.f;
    m_num_indices = indices.size();
    m_position = position;
    can_kill = true;
    set_dimensions();

    return true;
}


void Spike::draw(const mat3& projection)
{
    float color[] = { 0.8, 0.15, 0.15 };
    RenderManager::init_drawing_data(m_position, m_rotation, m_scale, this);
    RenderManager::draw_mesh(projection, this, color, m_num_indices);

}

bool Spikes::spawn_spike(vec2 position, SpikeDir dir)
{
	Spike spike;

	if (spike.init(position))
	{
		switch (dir)
		{
		case DOWN:
			spike.set_rotation(M_PI);
			break;
		case LEFT:
			spike.set_rotation(-M_PI / 2);
			break;
		case RIGHT:
			spike.set_rotation(M_PI / 2);
			break;
		default:
			spike.set_rotation(0);
			break;
		}
		spike.set_collision_properties();
		m_spikes.emplace_back(spike);
		return true;
	}
	fprintf(stderr, "Failed to spawn spikes");
	return false;
}

std::vector<Spike> Spikes::get_spike_vector()
{
	return m_spikes;
}

void Spikes::draw(const mat3 & projection)
{
	for (auto& spike : m_spikes)
		spike.draw(projection);
}

void Spikes::destroy()
{
	for (auto& spike : m_spikes)
		spike.destroy();
	m_spikes.clear();
}

bool Spikes::renderSetup()
{
	return false;
}
