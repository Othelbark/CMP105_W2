#include "Level.h"
#include <iostream>
#include <string>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0, 0);

	int xPos = input->getMouseX();
	int yPos = input->getMouseY();
	std::string textString = "Mouse: " + std::to_string(xPos) + ", " + std::to_string(yPos);
	text.setString(textString);

	circle.setFillColor(sf::Color::Green);
	circle.setRadius(30);
	circle.setOrigin(30, 30);
	input->setMouseRDown(false);
	circle.setPosition(-100, -100);

	//initalise mouse drag variables
	mouseDragInProces = false;
	mouseDragStartPos = { 0, 0 };
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{

	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W is pressed." << std::endl;
	}

	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "J, K, and L are pressed." << std::endl;
	}

	//mouse drag
	if (input->isMouseLDown() && !mouseDragInProces)
	{
		mouseDragInProces = true;
		mouseDragStartPos = { input->getMouseX(), input->getMouseY() };
	}
	if (!input->isMouseLDown() && mouseDragInProces)
	{
		mouseDragInProces = false;
		//calculate the x and y distances
		int xDrag = abs(mouseDragStartPos.x - input->getMouseX());
		int yDrag = abs(mouseDragStartPos.y - input->getMouseY());

		float diagonalDrag = sqrt((xDrag * xDrag) + (yDrag * yDrag));

		std::cout << "You dragged the mouse " << diagonalDrag << " pixels." << std::endl;
	}

	//draw/move and redraw circle on right click
	if (input->isMouseRDown())
	{
		input->setMouseRDown(false);
		circle.setPosition(input->getMouseX(), input->getMouseY());
	}

	//escape to quit
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}
}

// Update game objects
void Level::update()
{
	int xPos = input->getMouseX();
	int yPos = input->getMouseY();
	std::string textString = "Mouse: " + std::to_string(xPos) + ", " + std::to_string(yPos);
	text.setString(textString);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(text);
	window->draw(circle);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}