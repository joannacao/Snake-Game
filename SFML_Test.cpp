// SFML_Test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//globals
//this entire thing represents the background
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //num of pixels, size of each box
int w = size * num_horzBox; //Background num of pixels in width
int h = size * num_vertBox; //Background num of pixels in height

float delay = 0.1, delay2 = 0.1; 

int direction, direction2,snake_length = 4, snake_length2 = 4;
//max size of snake
struct Snake {
	int x, y;
}s[100];

struct Snake2 {
	int x, y; 
}s2[100];

struct Fruit {
	int x, y;
}food;

void Tick() {
	//Move remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	for (int i = snake_length2; i > 0; --i)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}
	//Head of snake depends on direction of user s[0]
	//User up 
	if (direction == 3)
		s[0].y -= 1;
	//User down
	if (direction == 0)
		s[0].y += 1;
	//User left 
	if (direction == 1)
		s[0].x -= 1;
	//User right
	if (direction == 2)
		s[0].x += 1;

	if (direction2 == 3)
		s2[0].y -= 1;
	//User down
	if (direction2 == 0)
		s2[0].y += 1;
	//User left 
	if (direction2 == 1)
		s2[0].x -= 1;
	//User right
	if (direction2 == 2)
		s2[0].x += 1;

	//if snake eats food it should grow
	if (s[0].x == food.x && (s[0].y) == food.y) {
		snake_length++;

		//randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		//snake should get faster 
		delay -= 0.01; 
	}
	if (s2[0].x == food.x && (s2[0].y) == food.y) {
		snake_length2++;

		//randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		//snake should get faster 
		delay2 -= 0.01;
	}
	//Boundary checking screen loop back on other side
	if (s[0].x > num_horzBox)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = num_horzBox;
	//TOP AND BOTTOM
	if (s[0].y > num_vertBox)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].y = num_vertBox;

	if (s2[0].x > num_horzBox)
		s2[0].x = 0;
	if (s2[0].x < 0)
		s2[0].x = num_horzBox;
	//TOP AND BOTTOM
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;
	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	//check if go over snake
	for (int i = 1; i < snake_length; i++) {
		//cut snake in half from place eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			snake_length = i;
	}
	for (int i = 1; i < snake_length2; i++) {
		//cut snake in half from place eaten
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y)
			snake_length2 = i;
	}
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//Textures
	Texture t1, t2, t3, t4;
	t1.loadFromFile("Image/white.png");
	t2.loadFromFile("Image/red.png");
	t3.loadFromFile("Image/Pig-icon.png");
	t4.loadFromFile("Image/green.png"); 

	//Sprite
	//Has physical dimensions
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4); 

	food.x = 10;
	food.y = 10;

	//s2[0].x = w; 
	//s2[0].y = h; 


	Clock clock;
	float timer = 0;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		//Allow us to check when a user does something
		Event e;
		//check when window is closed
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}

		//controls for snake 
		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;

		if (Keyboard::isKeyPressed(Keyboard::W)) direction2 = 3;
		if (Keyboard::isKeyPressed(Keyboard::S)) direction2 = 0;
		if (Keyboard::isKeyPressed(Keyboard::A)) direction2 = 1;
		if (Keyboard::isKeyPressed(Keyboard::D)) direction2 = 2;
		if (timer > delay) {
			timer = 0.0; //reset timer
			Tick(); //move snake one sprite forward
		}
		//Draw
		window.clear();
		//Draw background
		for (int i = 0; i < num_horzBox; i++) {
			for (int j = 0; j < num_vertBox; j++) {
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}
			//window.display(); 
		}

		//Draw snake
		for (int i = 0; i < snake_length; i++) {
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}
		for (int i = 0; i < snake_length2; i++) {
			sprite4.setPosition(s2[i].x*size, s2[i].y*size); 
			window.draw(sprite4); 
		}
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		window.display();
	}
	/*
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	*/
	return 0;
}
