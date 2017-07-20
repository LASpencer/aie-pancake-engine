#include "stdafx.h"
#include "MultiSprite.h"
#include "SceneObject.h"
#include "Entity.h"

MultiSprite::MultiSprite() : SpriteBase(), m_textures()
{
}

MultiSprite::MultiSprite(std::vector<TexturePtr>& textures, float width, float height, float uvx, float uvy, float uvw, float uvh, float xOrigin, float yOrigin)
	: SpriteBase(width, height, uvx, uvy, uvw, uvh, xOrigin, yOrigin), m_textures(textures)
{
}

MultiSprite::~MultiSprite()
{
}

void MultiSprite::setTextures(std::vector<TexturePtr>& textures)
{
	m_textures = textures;
}

void MultiSprite::draw(aie::Renderer2D * renderer)
{
	EntityPtr entity(m_entity);
	SceneObjectPtr position = entity->getPosition();
	renderer->setUVRect(m_uvx, m_uvy, m_uvw, m_uvh);
	for (TexturePtr texture : m_textures) {
		renderer->drawSpriteTransformed3x3(texture->get(), &position->getGlobalTransform()[0][0], m_width, m_height, 0, m_xOrigin, m_yOrigin);

	}
}
