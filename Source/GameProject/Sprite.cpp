#include "stdafx.h"
#include "Entity.h"
#include "Sprite.h"
#include "SceneObject.h"

Sprite::Sprite() : SpriteBase(), m_texture()
{
}

Sprite::Sprite(TexturePtr texture, float width, float height, float uvx, float uvy, float uvw, float uvh, float xOrigin, float yOrigin)
	: SpriteBase(width,height,uvx,uvy,uvw,uvh,xOrigin,yOrigin), m_texture(texture)
{
}


Sprite::~Sprite()
{
}

void Sprite::setTexture(TexturePtr texture)
{
	m_texture = texture;
}


void Sprite::draw(aie::Renderer2D* renderer)
{
	EntityPtr entity(m_entity);
	SceneObjectPtr position = entity->getPosition();
	renderer->setRenderColour(0xffffffff);
	renderer->setUVRect(m_uvx, m_uvy, m_uvw, m_uvh);
	renderer->drawSpriteTransformed3x3(m_texture->get(), &position->getGlobalTransform()[0][0], m_width,m_height,0,m_xOrigin,m_yOrigin);
}
