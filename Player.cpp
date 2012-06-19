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
		
		void Player::onJoyData(st::input::JoyData &evt){
			
			velocity.x =  ((abs(evt.LSAxisX) > 20) ? evt.LSAxisX:0) * (0.1f * speed);
			velocity.y =  ((abs(evt.LSAxisY) > 20) ? evt.LSAxisY:0 )* (0.1f * speed);
			shootingDir.x = evt.RSAxisX * 0.01;
			shootingDir.y = evt.RSAxisY * 0.01;
			
			isShooting = (abs(shootingDir.x) > 0.5 || abs(shootingDir.y) > 0.5);
			
			//isShooting = evt.actionX || evt.A;
			// std::cout << shootingDir.y<<  "\n";//slowDown();
			/*if(evt.actionA ) std::cout << "A\n";//slowDown();
			if(evt.actionB ) std::cout << "B\n";//slowDown();
			if(evt.actionY ) std::cout << "Y\n";//slowDown();
			if(evt.actionX ) std::cout << "X\n";//slowDown();
			if(evt.actionL ) std::cout << "L\n";//slowDown();
			if(evt.actionR ) std::cout << "R\n";//slowDown();
			if(evt.actionLS ) std::cout << "LS\n";//slowDown();
			if(evt.actionRS ) std::cout << "RS\n";//slowDown();
			if(evt.povX != 0) std::cout << evt.povX << "\n";//slowDown();
			if(evt.povY != 0) std::cout << evt.povY<< "\n";//slowDown();*/
			
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