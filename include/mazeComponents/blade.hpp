#pragma once

#include "geometricComponent.hpp"
#include <vector>

class Blade : public GeometricComponent
{

public:

    // default spike points upward
    bool init(vec2 position)override;

    // Renders the component
    void draw(const mat3& projection)override;

    void set_pendulum_rot();
    void set_world_vertex_coord();
private:
    float max_rotation = (float) M_PI / 2;
    float min_rotation = (float) (- M_PI / 2);

    float dr = 0.02; //speed of rotation
};

class Blades : public GeometricComponents
{
public:
	bool spawn_blades(vec2 position);
	std::vector<Blade> get_blade_vector();

	// Renders the component
	void draw(const mat3& projection)override;

	void update();

	void destroy();
private:
	std::vector<Blade> m_blades;
};