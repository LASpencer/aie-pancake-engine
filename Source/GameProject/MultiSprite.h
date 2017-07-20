#pragma once
#include "SpriteBase.h"
#include "ResourceManager.h"

/*	Component for drawing a sprite by overlaying multiple textures
	This is used to allow textures for different equipment to be 
	drawn onto the base texture for the hero entity
	
	All textures will be drawn at the same position, with the same
	size and uvRect*/
class MultiSprite : public SpriteBase {
public:
	MultiSprite();
	MultiSprite(std::vector<TexturePtr>& textures, float width = 0.0f, float height = 0.0f,
		float uvx = 0.0f, float uvy = 0.0f, float uvw = 1.0f, float uvh = 1.0f,
		float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual ~MultiSprite();

	/** Set textures
	*	@param textures Array containing textures in draw order*/
	void setTextures(std::vector<TexturePtr>& textures);

	// Draw all textures in order given
	virtual void draw(aie::Renderer2D* renderer);
protected:
	std::vector<TexturePtr>	m_textures;	//Textures in order they will be drawn
};