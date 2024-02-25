#include "stdafx.h"
#include "GUI.h"

/*-----------------FUNCTIONS------------------*/

const float gui::percentToPixelX(const float percent, const sf::VideoMode& videoMode) {
	/*
	*  Converts a percentage value to pixels relative to the current resolution in the x-axis.
	*
	*  @param		float percent				The percentage value.
	*  @param		sf::VideoMode& videoMode	The current VideoMode for a window (resolution)
	*
	*  @return		float						The calculated pixel value
	*
	*/

	return std::floor(static_cast<float>(videoMode.width) * (percent / 100.f));
}

const float gui::percentToPixelY(const float percent, const sf::VideoMode& videoMode) {
	/*
	*  Converts a percentage value to pixels relative to the current resolution in the y-axis.
	*
	*  @param		float percent				The percentage value.
	*  @param		sf::VideoMode& videoMode	The current VideoMode for a window (resolution)
	*
	*  @return		float						The calculated pixel value
	*
	*/


	return std::floor(static_cast<float>(videoMode.height) * (percent / 100.f));
}

const unsigned gui::calcCharSize(const unsigned modifier, const sf::VideoMode& videoMode) {
	/*
	*  Calculate the character size for text using the current resolution and a constant
	*
	*  @param		int							The value which we divide for getting dynamic size
	*  @param		unsigned modifier			Used to modify the character size
	*
	*  @return		unsigned					The calculated character size value
	*
	*/

	return static_cast<unsigned>(videoMode.width + videoMode.height) / (modifier);
}



/*-----------------BUTTONS------------------*/

/*       CONSTRUCTORS/DESTRUCTORS      */

gui::Button::Button(
	float x, float y, float width, float height, 
	sf::Font* font, std::string text, unsigned character_size, 
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color, 
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color, 
	unsigned short id
)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y
		// this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{
}

/*				ACCESSORS               */
const bool gui::Button::isPressed() const {
	if (this->buttonState == BTN_ACTIVE) {
		return true;
	} 
	return false;
}

const std::string gui::Button::getText() const {
	return this->text.getString();
}

const unsigned short& gui::Button::getId() const {
	return this->id;
}

/*				MODIFIERS               */
void gui::Button::setText(const std::string text) {
	this->text.setString(text);
}

void gui::Button::setId(const unsigned short id) {
	this->id = id;
}

/*				FUNCTION               */
void gui::Button::update(const sf::Vector2i& mousePosWindow) {
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
		this->buttonState = BTN_HOVER;

		// Pressed 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState) {
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target) {
	target.draw(this->shape);
	target.draw(this->text);
}

