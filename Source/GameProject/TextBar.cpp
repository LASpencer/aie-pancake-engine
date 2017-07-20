#include "stdafx.h"
#include "TextBar.h"
#include "Renderer2D.h"

const float TextBar::def_linespace = 0.1;
const float TextBar::def_margin = 3;
const unsigned int TextBar::def_box_colour = 0x101010FF;
const unsigned int TextBar::def_text_colour = 0xFFFFFFFF;

TextBar::TextBar(FontPtr font, const std::string& content, float x , float y, unsigned int textColour , unsigned int boxColour)
	: m_font(font), m_content(content), m_xPos(x),m_yPos(y),m_textColour(textColour),m_boxColour(boxColour),m_lineSpace(def_linespace), m_margin(def_margin)
{
	assert((*font).get() != nullptr);
}


TextBar::~TextBar()
{
}

void TextBar::setPosition(float x, float y)
{
	m_xPos = x;
	m_yPos = y;
}

void TextBar::setContent(const char * content)
{
	m_content = content;
}

void TextBar::setContent(const std::string& content)
{
	m_content = content;
}

void TextBar::setBoxColour(unsigned int colour)
{
	m_boxColour = colour;
}

void TextBar::setTextColour(unsigned int colour)
{
	m_textColour = colour;
}

void TextBar::setFont(FontPtr font)
{
	if (!font) {
		throw std::invalid_argument("Font shared_ptr expired.");
	}
	m_font = font;
}

void TextBar::draw(aie::Renderer2D * renderer)
{
	if (!m_font) {
		throw std::logic_error("Cannot draw text without valid font");
	}
	// If no text, don't draw anything
	if (!m_content.empty()) {
		float width, height;
		(*m_font)->getStringSize(m_content.c_str(), width, height);
		renderer->setRenderColour(m_boxColour);
		renderer->drawBox(m_xPos, m_yPos, width + m_margin, height * (1.0 + m_margin));
		renderer->setRenderColour(m_textColour);
		renderer->drawText((*m_font).get(), m_content.c_str(), m_xPos - (width / 2.0f), m_yPos - (height / 2.0f));
		renderer->setRenderColour(0xffffffff);
	}
}
