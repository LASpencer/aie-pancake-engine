#pragma once
#include "ResourceManager.h"

// Class for displaying a line of text on the screen
class TextBar
{
public:
	static const float def_linespace;
	static const float def_margin;
	static const unsigned int def_box_colour;
	static const unsigned int def_text_colour;

	TextBar(FontPtr font, const std::string& content = "", float x = 0, float y = 0, unsigned int textColour = def_text_colour, unsigned int boxColour = def_box_colour);
	~TextBar();

	// Sets centre of text bar
	void setPosition(float x, float y);

	// Set content displayed in text bar
	void setContent(const char* content);
	void setContent(const std::string& content);
	
	/** Sets colour of box around text
	* @param colour RGBA value as 4 byte integer*/
	void setBoxColour(unsigned int colour);

	/** Sets colour of text
	* @param colour RGBA value as 4 byte integer*/
	void setTextColour(unsigned int colour);

	/** Sets font of text
	* @param font FontPtr to true type font*/
	void setFont(FontPtr font);
	virtual void update(float deltaTime) {};
	virtual void draw(aie::Renderer2D* renderer);

protected:
	std::string m_content;
	float m_xPos;			// Centre of box
	float m_yPos;			// Centre of box
	float m_margin;			// Pixels either side of text
	float m_lineSpace;		// How must taller box is than text, as proportion of text height

	unsigned int m_boxColour;
	unsigned int m_textColour;
	FontPtr m_font;
};

