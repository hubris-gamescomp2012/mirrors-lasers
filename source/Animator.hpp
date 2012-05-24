#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "ResourceManager.hpp"

namespace sf {
	class Sprite;
}

// Handles sprite animation at a fixed frame-rate.
class Animator {
public:
	Animator(SpriteID& a_sprite, int a_width, int a_height, int a_rows, int a_columns, int a_framerate, int a_frames);
	void Update(float a_dt);
private:
	int m_width;
	int m_height;
	int m_rows;
	int m_columns;
	int m_frames;
	int m_currentFrame;
	float m_framerate;
	float m_timer;
	SpriteID& m_sprite;
};

#endif // ANIMATOR_H