/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer,
Auckland,    New Zealand
(c) 2026 Media Design School at Strayer
Author      :   Huntress Jones
Mail        :   hunter.jones@mds.ac.nz
File Name   :	Button.h
Description :	This is the header file for the button class!
**************************************************************************/
#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once


class Button : public sf::RectangleShape
{
public:
	Button(sf::Window* _window, sf::Vector2f _position, sf::Vector2f _size, sf::Font* m_font, std::string _name, void (*_function)() = nullptr);
	void ButtonUpdate();
	bool CheckIfMouseInArea();
	// the button's text
	sf::Text* m_text = nullptr;
protected:
	// a function pointer that will run when the button is pressed
	void (*m_functionPointer)() = nullptr;
	sf::Window* m_windowPointer = nullptr;
	sf::Vector2f m_position;
	float m_width;
	float m_height;
	bool mouseDown = false;
};

