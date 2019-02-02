#pragma once

// internal
#include "../common.hpp"
#include "../characters/player.hpp"
#include "../characters/enemy.hpp"
#include "../mazeComponents/mazeComponent.hpp"
#include "../mazeComponents/fixedComponent.hpp"
#include "../mazeComponents/floor.hpp"
#include "../mazeComponents/exit.hpp"
#include "../mazeComponents/ice.hpp"
#include "../water.hpp"
#include "../physics.hpp"

// stlib
#include <vector>
#include <random>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

// One of our many worlds

class Level0
{
public:
	Level0();
	~Level0();

    // Creates a window, sets up events and begins the game
	bool init(vec2 screen, Physics* physicsHandler);

	// Releases all associated resource
    void destroy();

	// Steps the game ahead by ms milliseconds
    bool update(float elapsed_ms);

    // Renders our scene
	void draw();

	// Should the game be over ?
	bool is_over()const;

private:
	// !!! INPUT CALLBACK FUNCTIONS
	void on_key(GLFWwindow*, int key, int, int action, int mod);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos);

	// Add enemies with hardcoded positions
	void spawn_enemies();

	// Helper to generates a new enemy
	bool spawn_enemy(vec2 position, float bound);

	// Generates a new floor
	bool spawn_floor(vec2 position);

	// Generates hard-coded maze in each level
	void generate_maze();
private:
	// Window handle
	GLFWwindow* m_window;

    // Screen texture
	// The draw loop first renders to this texture, then it is used for the water shader
	GLuint m_frame_buffer;
	Texture m_screen_tex;

	// Water effect
	Water m_water;

    Player m_player;
	Exit m_exit;
	std::vector<Enemy> m_enemies;
    std::vector<Floor> m_floor;

    float m_current_speed;

    float m_next_floor_spawn;

    Mix_Music* m_background_music;

    // C++ rng
	std::default_random_engine m_rng;
	std::uniform_real_distribution<float> m_dist; // default 0..1

    // initial position of player
	vec2 initialPosition = { 700.f, 600.f };

	Physics* physicsHandler;
};