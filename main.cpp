#include <stdio.h>
#include <iostream>
#include <math.h>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Event.h"
#include "InputEvent.h"
#include "Player.h"
#include "Collision.h"
#include "ObjectHandlers.h"
#include "ObjectPool.h"

using namespace st::gameobject;
using namespace st::objecthandlers;
using namespace st::management;

float timeSpeed = 1;

std::list<Bullet*> bulletList;
ObjectPool<Bullet> bulletPool;
st::gameobject::Player p;

void shoot(const st::event::Event& evt) {
	Bullet * b = bulletPool.getResource();
	b->setPosition(p.getPosition());
	b->dVector.x = 1;
	b->dVector.y = 0;
	bulletList.push_back(b);
	//std::cout << bulletList.size() << std::endl;
	//counter = 0;
};

void slowDown(const st::event::Event& evt) {
	std::cout << evt.type << std::endl;
};


int main(int argc, char **argv) {
	
	sf::RenderWindow window(sf::VideoMode(800, 600,32), "SFML window");

	sf::Clock deltaClock;
	sf::Time dt;

	Bullet * b;

	float counter = 0.0f;

	std::list<Bullet*>::iterator it;

	window.setFramerateLimit(60);


	st::input::JoyInput joyInput;
	
	p.addEventListener("shoot",shoot);
	p.addEventListener("slowDown",slowDown);
	
	joyInput.registerObject(&p,0);
	// Start the game loop
	while (window.isOpen()) {
		// Process events
		dt = deltaClock.restart();
		joyInput.update(dt.asSeconds());
		counter += dt.asSeconds() * (timeSpeed * 5);
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if(sf::Joystick::isButtonPressed(0,2)) {
			if(counter > .05f) {
				

			}
		} else {
			counter = 1;
		}

		if(sf::Joystick::isButtonPressed(0,0)) {
			timeSpeed  = 0.1f;
		} else {
			timeSpeed = 1;
		}


		processBullet(bulletPool,bulletList,dt.asSeconds());

		p.update(dt.asSeconds());
		// Clear screen
		window.clear();

		//Draw bullets
		for ( it = bulletList.begin(); it != bulletList.end(); ++it) {
			b = *it;
			window.draw(*b);

		}

		window.draw(p);

		// Update the window
		window.display();


	}

	return EXIT_SUCCESS;
}
