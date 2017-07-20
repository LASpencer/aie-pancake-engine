#pragma once
#include "SpriteBase.h"
#include "ResourceManager.h"

/*	Component for drawing a sprite from a single texture
*/
class Sprite :
	public SpriteBase
{
public:
	Sprite();
	Sprite(TexturePtr texture,float width = 0.0f, float height = 0.0f, 
		float uvx = 0.0f, float uvy = 0.0f, float uvw = 1.0f, float uvh = 1.0f, 
		float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual ~Sprite();

	/** Set texture to draw sprite from
	*	@param TexturePtr reference to texture in resource manager*/
	void setTexture(TexturePtr texture);

	// Draw sprite at position given by entity
	virtual void draw(aie::Renderer2D* renderer);

protected:
	TexturePtr m_texture;	// Texture to draw sprite from
};
