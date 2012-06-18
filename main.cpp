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


float timeSpeed = 1;

class Bullet : public sf::Sprite{
	
private:
	static sf::Texture * img; 
public:
	bool isActive;
	float speed;
	sf::Vector2f dVector;
	Bullet(){
		if(!img)
		{
			img = new sf::Texture();
			img->loadFromFile("assets/bullet.png");
			if(img != 0) std::cout << "Image set";
		}
		
		this->setTexture(*img);
		speed = 1000;
	}
	
	void update(float dt){
		move((dVector * (speed * dt) * timeSpeed));
	}
};

sf::Texture * Bullet::img; 


void processBullet(ObjectPool<Bullet> &bulletPool, std::list<Bullet*> &bulletList, float dt){
	
	std::list<Bullet*>::iterator it;
	Bullet * b;
	
	it = bulletList.begin();
	 while ( it != bulletList.end())
	{
		
		b = *it;
		b->update(dt);
		
		if(b->getPosition().x > 800){
			
			it = bulletList.erase(it);
			bulletPool.resturnResource(b);
		}
		else
			it++;
	}
}

void shoot(const st::event::Event& evt){
	std::cout << evt.type << std::endl;
};

void slowDown(const st::event::Event& evt){
	std::cout << evt.type << std::endl;
};


int main(int argc, char **argv)
{
	std::list<Bullet*> bulletList;
	ObjectPool<Bullet> bulletPool;
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600,32), "SFML window");
	//sf::Joystick::update();
	
	//std::cout << sf::Joystick::ButtonCount;
	
	sf::Sprite player;
	sf::Texture t;
	t.loadFromFile("assets/player.png");
	player.setTexture(t);
	float xj = 0.0f;
	float yj = 0.0f;
	sf::Vector2f newPos;
	
	std::list<Bullet*>::iterator it;
	
	
	sf::Clock deltaClock;
	sf::Time dt;
	
	Bullet * b;
	
	float counter = 0.0f;
	
	
	//thor::ActionMap<std::string> map(window);
	
	//thor::Action moveEvent(sf::Joystick::X);
	//thor::Action moveEvent(sf::Joystick::Y);
	//map["MoveX"] = moveEventX;
	//map["MoveY"] = moveEventY;
	
	//thor::ActionMap<std::string>::CallbackSystem system;
	//system.connect("MoveX", &onShoot);
	//system.connect("MoveY", &onShoot);
	
	//map.invokeCallbacks(system);
	
	//player.getLocalBounds().intersects()
	window.setFramerateLimit(60);
	

	st::input::JoyInput joyInput;
	st::gameobject::Player p;
	p.addEventListener("shoot",shoot);
	p.addEventListener("slowDown",slowDown);
	//p.removeEventListener("slowDown",slowDown);
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

		if(sf::Joystick::isButtonPressed(0,2)){
			if(counter > .05f)
			{
				b = bulletPool.getResource();
				b->setPosition(player.getPosition());
				b->dVector.x = 1; 
				b->dVector.y = 0; 
				bulletList.push_back(b);
				//std::cout << bulletList.size() << std::endl;
				counter = 0;
				
			}
		}
		else{
			counter = 1;
		}
		
		if(sf::Joystick::isButtonPressed(0,0)){
			timeSpeed  = 0.1f;
		}
		else{
			timeSpeed = 1;
		}
		
		
		processBullet(bulletPool,bulletList,dt.asSeconds());
		
		
		xj = sf::Joystick::getAxisPosition(0,sf::Joystick::X);
		yj = sf::Joystick::getAxisPosition(0,sf::Joystick::Y);
		
		newPos.x =  ((abs(xj) > 20) ? xj:0) * 0.05f;
		newPos.y =  ((abs(yj) > 20) ? yj:0 )* 0.05f;
		
		player.move(newPos);
		
		p.update(dt.asSeconds());
		// Clear screen
		window.clear();

		//Draw bullets
		for ( it = bulletList.begin(); it != bulletList.end(); ++it)
		 {
			b = *it;
			window.draw(*b);
			
		 }
		
		window.draw(p);

		// Update the window
		window.display();
		
		
	}

	return EXIT_SUCCESS;
}
