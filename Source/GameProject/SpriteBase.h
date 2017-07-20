#pragma once
#include "Component.h"

/*	Abstract base class for sprite component
	Provides methods for setting the dimensions and origin
	of sprites, as well as setting the uvRect to draw from
*/
class SpriteBase :
	public Component {
public:
	SpriteBase();
	SpriteBase(float width, float height, float uvx, float uvy, float uvw, float uvh,
				float xOrigin, float yOrigin);
	virtual ~SpriteBase();

	// Set UVRect coordinates and size for drawing this sprite
	void setUVRect(float uvx, float uvy, float uvw, float uvh);

	// Set dimensions of sprite
	void setDimensions(float width, float height);

	// Set sprite origin for transforming sprite, with 0.5 being center
	void setOrigin(float x, float y);

	virtual void update(float deltaTime) {};
	virtual void draw(aie::Renderer2D* renderer) = 0;

	virtual Identifier getID();

protected:
	float m_uvx, m_uvy, m_uvw, m_uvh;	//UV Rect location and size
	float m_width, m_height;			//Dimensions of sprite
	float m_xOrigin, m_yOrigin;			//Origin for transforming sprite
};