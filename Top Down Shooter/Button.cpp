/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer,
Auckland,    New Zealand
(c) 2026 Media Design School at Strayer
Author      :   Huntress Jones
Mail        :   hunter.jones@mds.ac.nz
File Name   :	Button.cpp
Description :	This is the script that handles the code for buttons and how
				they function.
**************************************************************************/
#include "Button.h"
#include <iostream>


// Constructor
Button::Button(sf::Window* _window, sf::Vector2f _position, sf::Vector2f _size, sf::Font* m_font, std::string _name, void (*_function)()) : m_windowPointer(_window), m_position(_position)
{
	// Set variables
	m_width = _size.x;
	m_height = _size.y;
	m_functionPointer = _function;

	// Setup the button
	setPosition(_position);
	setSize({m_width, m_height});
	setFillColor(sf::Color::White);

	// Setup text on the button
	m_text = new sf::Text(*m_font);
	m_text->setString(_name);
	m_text->setPosition(_position);
	m_text->setCharacterSize(24);
	m_text->setFillColor(sf::Color::Black);
}


// Update loop
void Button::ButtonUpdate()
{
	CheckIfMouseInArea();
}


// Check for mouse on the button and input
bool Button::CheckIfMouseInArea()
{
	// Check Mouse X pos compared to the rect's X pos and its width
	if (sf::Mouse::getPosition(*m_windowPointer).x < m_position.x + m_width && sf::Mouse::getPosition(*m_windowPointer).x > m_position.x)
	{
		// Check Mouse Y pos compared to the rect's Y pos and its width
		if (sf::Mouse::getPosition(*m_windowPointer).y < m_position.y + m_height && sf::Mouse::getPosition(*m_windowPointer).y > m_position.y)
		{
			setFillColor(sf::Color::Green);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseDown)
			{
				mouseDown = true;

				// run the function pointer assigned to the button
				if (m_functionPointer != nullptr)
				{
					m_functionPointer();
				}
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				mouseDown = false;
			}

			return true;
		}
	}

	setFillColor(sf::Color::White);
	return false;
}
