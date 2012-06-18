#include "Player.h"
#include <iostream>
namespace st{
	namespace gameobject{
		
		Player::Player(){
			sf::Texture t;
			t.loadFromFile("assets/player.png");
			setTexture(t);
			speed = 20;
			fireCounter = 0;
			fireRate = .1;
		}
		
		void Player::onJoyEvent(st::input::JoyEvent evt){
			
			velocity.x =  ((abs(evt.axisX) > 20) ? evt.axisX:0) * (0.1f * speed);
			velocity.y =  ((abs(evt.axisY) > 20) ? evt.axisY:0 )* (0.1f * speed);
			
			 isShooting = evt.buttonX;
			/*if(evt.buttonA) std::cout << "A";//slowDown();
			if(evt.buttonB) std::cout << "B";//slowDown();
			if(evt.buttonY) std::cout << "Y";//slowDown();
			if(evt.buttonL) std::cout << "L";//slowDown();
			if(evt.buttonR) std::cout << "R";//slowDown();
			if(evt.buttonLS) std::cout << "LS";//slowDown();
			if(evt.buttonRS) std::cout << "RS";//slowDown();*/
			
		}
		
		void Player::addEventListener(const std::string& type,st::event::function listener, int priority){
			dispatcher.addEventListener(type,listener,priority);
		}
		
		void Player::removeEventListener(const std::string& type,st::event::function listener){
			dispatcher.removeEventListener(type,listener);
		}
		
		
		void Player::shoot(float dt){
			
			fireCounter+= dt;
			if(isShooting){
			if(fireCounter > fireRate)
			{
				dispatcher.dispatchEvent(st::event::Event("shoot"));
				fireCounter = 0;
			}
			
			}
			else
			{
				fireCounter = fireRate;
			}
			
		};
		
		void Player::slowDown(){

			dispatcher.dispatchEvent(st::event::Event("slowDown"));
		}
		
		void Player::update(float dt){
			
			move((velocity) * dt);
			shoot(dt);
			
		};
		
	};
};