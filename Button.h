#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include "Karta.h"

class Button {
private:
	sf::RectangleShape button;	//Kształt przycisku
	sf::Text text;				//tekst wyświetlany na przycisku
	sf::Texture texture;		//załadowana tekstura przycisku
	std::string string_text;	//string przechowujący tekst przycisku w przypadku jego zmiany
	sf::Texture black_texture;	//czarna tekstura

public:
	Button() {};
	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		text.setString(t);
		string_text = t;
		text.setFillColor(textColor);						//ustawienie koloru tekstu
		text.setCharacterSize(charSize);					//ustawienie wielkości znaków
		button.setSize(size);								//ustawienie wielkości
		button.setFillColor(bgColor);						//ustawienie koloru wypełnienia
		black_texture.loadFromFile("Photos/czarny.png");	//załadowanie czarnej tekstury
	}
	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, 
		sf::Color textColor, sf::Texture _texture) : texture(_texture) {//tekstura się od razu przypisuje
		text.setString(t);
		string_text = t;
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
		button.setSize(size);
		button.setFillColor(bgColor);
		black_texture.loadFromFile("Photos/czarny.png");
	}

	void setFont(sf::Font& font) {
		text.setFont(font);
	}

	void setBackColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setPosition(sf::Vector2f pos) {

		float xPos = (pos.x + button.getGlobalBounds().width / 2);// - (text.getGlobalBounds().width / 2);
		float yPos = (pos.x + button.getGlobalBounds().height / 2);// - (text.getGlobalBounds().height / 2);
		text.setPosition( pos );
		button.setPosition(pos);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
		window.draw(text);
		
	}

	void UstawTeksture() {
		//sf::Texture texture;
		//texture.loadFromFile(s);
		const sf::Texture* pTexture = &texture;
		button.setTexture(pTexture);
		//delete pTexture;
	}

	
	void LoadPhoto(const std::string s) {
		texture.loadFromFile(s);
		const sf::Texture* pTexture = &texture;
		button.setTexture(pTexture);
		//delete pTexture;
	}



	bool isMouseOver(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY > btnPosY && mouseY < btnyPosHeight) {
			return true;
		}
		return false;
	}


	bool isMouseOver1(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		if (button.getGlobalBounds().contains({ mouseX, mouseY }))
			return true;
		else
			return false;

	}

	void LoadCardTexture(Karta k) {
		texture = k.getTexture();
		const sf::Texture* pTexture = &texture;
		button.setTexture(pTexture);
	}
	

	void setButton(sf::Vector2f size, sf::Color bgColor) {
		button.setSize(size);
		button.setFillColor(bgColor);
	}

	std::string get_text() {
		return string_text;
	}
	void setText(std::string s) {
		text.setString(s);
	}

	void LoadBlack() {
		
		const sf::Texture* pTexture = &black_texture;
		button.setTexture(pTexture);
		
	}
};
