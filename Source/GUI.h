#pragma once

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};


namespace gui {

	/*-----------------FUNCTIONS------------------*/

	const float percentToPixelX(const float percent, const sf::VideoMode& videoMode);
	const float percentToPixelY(const float percent, const sf::VideoMode& videoMode);
	const unsigned calcCharSize(const unsigned modifier, const sf::VideoMode& videoMode);



	/*-----------------BUTTONS------------------*/


	class Button
	{
	private:
		/*                VARIABLES            */
		unsigned short buttonState;
		unsigned short id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;


		/*             INITIALIZATION          */

	public:
		/*       CONSTRUCTORS/DESTRUCTORS      */
		Button(
			float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			unsigned short id = 0
		);
		~Button();


		/*				ACCESSORS               */
		const bool isPressed() const;
		const std::string getText() const;
		const unsigned short& getId() const;

		/*				MODIFIERS               */
		void setText(const std::string text);
		void setId(const unsigned short id);

		/*				FUNCTION               */
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);


	};
}

