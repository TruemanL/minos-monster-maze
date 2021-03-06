#pragma once

#include "../common.hpp"
#include "../renderManager.hpp"
#include "../spriteSheet.hpp"
#include "../stateTree.hpp"

class Physics;

class Character : public Renderable
{
public:
	// Creates all the associated render resources and default transform
	virtual bool init(vec2 initialPosition, Physics* physicsHandler);

	void set_properties(vec2 initialPosition, float scaleFactor, float xVel);

	void set_dimensions(Texture* texture, float spriteSheetWidth, float spriteSheetHeight, int xTrim, int yTrim);

	// Releases all associated resources
	void destroy();

	// Update character position
	// ms represents the number of milliseconds elapsed from the previous update() call
	virtual void update(float ms) = 0;

	// Renders the character
	void draw(const mat3& projection) = 0;

	// Set the character's acceleration vector
	void set_acceleration(vec2 acc);

	// Get the character's acceleration vector
	vec2 get_acceleration();

	// Set the character's velocity vector
	void set_velocity(vec2 vel);

	// Get the character's velocity vector
	vec2 get_velocity();

	// Returns the current character position
	vec2 get_position()const;

	void set_position(vec2 pos);

	// Returns the current scale of the character
	vec2 get_scale()const;

	void set_scale(vec2 scale);

	// Freeze and unfreeze the character
	void freeze();

	void unfreeze();

	// Moves the character based on current velocity
	void move();

	// Change character movement direction
	void set_direction(Direction d);

	bool is_invincible()const;

	void set_invincibility(bool setting);

	// Get character's horizontal direction
	Direction get_h_direction();
	
	// Set character rotation in radians
	void set_rotation(float radians);

		// True if the character is alive
	bool is_alive()const;

	// Kills the character, changing its alive state and triggering on death events
	void kill();

	// Initializes character state tree
	void initStateTree();

	// Sets the correct sprite sheet tile for appropriate animation
	virtual void set_animation() = 0;

	// Sets the vertex coordinates in the world (should be called once per update)
	void set_world_vertex_coord();

	StateTree* characterState;
	float width;
	float height;
	float boundingCircleRadius;
	bool isOnPlatform;
	// collision related fields
	bool isBelowPlatform;
	std::vector<MTV> collisionMTVs;

	// constants
	float jumpVel = -12.5f;
	float maxHorzSpeed = 8;
	float accStep = 0.8f;
	float m_animTime = 0.f;
	float m_platform_drag;

protected:
	Physics* physicsHandler;
	vec2 m_velocity;
	vec2 m_acceleration;

	// states
	bool m_frozen;
	State preFreezeState;
	bool isInvincible = false;

	Direction direction; // direction of intended movement
    // 1.f in each dimension. 1.f is as big as the associated texture
	size_t m_num_indices; // passed to glDrawElements
	Texture m_texture;
	SpriteSheet spriteSheet;
	bool is_anim_once = false;

	// sets texture to sprite or coloured box for debugging collisions
	bool use_sprite;
	Texture box_texture;

	bool is_hidden = false;

};
