#include "stdafx.h"
#include "SpriteBase.h"
#include "SceneObject.h"

SpriteBase::SpriteBase() : m_uvx(0), m_uvy(0), m_uvw(1.0f), m_uvh(1.0f), m_width(0), m_height(0), m_xOrigin(0.5f), m_yOrigin(0.5f)
{
}

SpriteBase::SpriteBase(float width, float height, float uvx, float uvy, float uvw, float uvh, float xOrigin, float yOrigin)
	: m_width(width), m_height(height), m_uvx(uvx), m_uvy(uvy), m_uvw(uvw), m_uvh(uvh), m_xOrigin(xOrigin), m_yOrigin(yOrigin)
{
	if (uvx < 0.0f || uvx > 1.0f ||
		uvy < 0.0f || uvy > 1.0f ||
		uvw < 0.0f || uvw > 1.0f ||
		uvh < 0.0f || uvh > 1.0f) {
		throw std::invalid_argument("UVRect parameters must be between 0 and 1");
	}
}

SpriteBase::~SpriteBase()
{
}

void SpriteBase::setUVRect(float uvx, float uvy, float uvw, float uvh)
{
	if (uvx < 0.0f || uvx > 1.0f ||
		uvy < 0.0f || uvy > 1.0f ||
		uvw < 0.0f || uvw > 1.0f ||
		uvh < 0.0f || uvh > 1.0f) {
		throw std::invalid_argument("UVRect parameters must be between 0 and 1");
	}
	m_uvx = uvx;
	m_uvy = uvy;
	m_uvw = uvw;
	m_uvh = uvh;
}

void SpriteBase::setDimensions(float width, float height)
{
	m_width = width;
	m_height = height;
}

void SpriteBase::setOrigin(float x, float y)
{
	m_xOrigin = x;
	m_yOrigin = y;
}

Component::Identifier SpriteBase::getID()
{
	return sprite;
}
