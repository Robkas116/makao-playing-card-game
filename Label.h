
/*
#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Karta.h"

class Label {
	sf::RectangleShape label;
	std::string basic_string;
	sf::Text text;
public:
	Label() {
		text.setString("");
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(10);

		label.setFillColor(sf::Color::White);
	}
	Label(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		label.setSize(size);
		label.setFillColor(bgColor);

	}

	void setFont(sf::Font& font) {
		text.setFont(font);
	}

	void setBackColor(sf::Color color) {
		label.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setText(std::string t) {
		text.setString(basic_string+t);
	}
	void setSize(sf::Vector2f size) {
		label.setSize(size);
	}

	void setPosition(sf::Vector2f pos) {

		float xPos = (pos.x + label.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
		float yPos = (pos.x + label.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
		text.setPosition({ xPos, yPos });
		label.setPosition(pos);
	}
	void drawTo(sf::RenderWindow& window) {
		window.draw(label);
		window.draw(text);

	}
	void setBasicString(std::string basic) {
		basic_string = basic;
	}

	void setLabelFont(sf::Font& font) {
		text.setFont(font);
	}
};
*/