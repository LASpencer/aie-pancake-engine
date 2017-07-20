#pragma once
#include "TextBar.h"
#include "Subject.h"
#include "EventManager.h"
#include "ResourceManager.h"

/*	Button class
	On being clicked, toggles between pressed and unpressed state
	
	Buttons are subjects, producing events when moused over or clicked, 
	allowing its observers to be controlled by the user clicking on the button
*/
class Button :
	public Subject
{
public:
	static const unsigned int def_button_colour;
	static const unsigned int def_hover_colour;
	static const unsigned int def_pressed_colour;
	static const unsigned int def_text_colour;
	static const float def_width;
	static const float def_height;

	Button(FontPtr font, std::string content = "", float x = 0, float y = 0, float width = def_width, float height = def_height, unsigned int textColour = def_text_colour, unsigned int colour = def_button_colour,
		unsigned int hoverColour = def_hover_colour, unsigned int pressedColour = def_pressed_colour);
	~Button();

	Button(const Button& other);

	Button& operator=(const Button& other);

	// Sets button position on screen
	void setPosition(float x, float y);

	void setDimensions(float width, float height);

	// Sets button unpressed colour
	void setColour(unsigned int colour);

	// Sets button colour while mouse over button
	void setHoverColour(unsigned int colour);

	// Sets button pressed colour
	void setPressedColour(unsigned int colour);

	/** Sets colour of text
	* @param colour RGBA value as 4 byte integer*/
	void setTextColour(unsigned int colour);

	// Set text displayed in button
	void setContent(const char* content);
	void setContent(const std::string& content);

	/** Sets font of text
	* @param font FontPtr to true type font*/
	void setFont(FontPtr font);

	bool isPressed();
	void setPressed(bool press);

	// Sets button to unpressed and not hovered over
	void reset();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	float			m_xPos, m_yPos;			// Position of button
	float			m_xExtent, m_yExtent;	// Dimensions of button
	bool			m_pressed;
	bool			m_hover;				// Mouse was over button last update
	unsigned int	m_colour;				
	unsigned int	m_hoverColour;
	unsigned int	m_pressedColour;
	unsigned int	m_textColour;
	EventManager	m_eventManager;			// Holds observers and notifies them for button
	FontPtr			m_font;					// Font for text
	std::string		m_content;				// Text written in button
};

