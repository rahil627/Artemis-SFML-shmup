#include "Player.h"
#include <iostream>
#include "ShootEvent.h"
#include <math.h>
namespace st {
	namespace gameobject {

		Player::Player() {
			static sf::Texture * img;
			if(!img){
				img = new sf::Texture();
				img->loadFromFile("assets/player.png");
				setTexture(*img);
				setOrigin((img->getSize().x * 0.5f), (img->getSize().y* 0.5f));				
			}
			speed = 20;
			
			fireCounter = 0;
			fireRate = .1;
			powerBoost = 0.0f;
			powerShotReady = false;
		}

		void Player::onJoyData(st::input::JoyData &evt) {

			velocity.x =  ((abs(evt.LSAxisX) > 20) ? evt.LSAxisX:0) * (0.1f * speed);
			velocity.y =  ((abs(evt.LSAxisY) > 20) ? evt.LSAxisY:0)* (0.1f * speed);
			shootingDir.x = evt.RSAxisX * 0.01;
			shootingDir.y = evt.RSAxisY * 0.01;
			
			if((fabs(shootingDir.x) > .2f) || (fabs(shootingDir.y) > .2f))
			isShooting = true;
			else if(evt.actionX || evt.A){
				
				shootingDir.x = 1;
				shootingDir.y = 0;
				
				isShooting = true;
			}
			else{
				isShooting = false;
			}
			
			if(evt.X)
			{
				powerBoost+= 0.01f;
				std::cout << powerBoost << "\n";
				if(powerBoost > 1.0f){
					powerShotReady = true;
				}
			}
			else{
				if(powerShotReady){
					
					shootingDir.x = 1;
					shootingDir.y = 0;
					fireCounter = 10;
					isShooting = true;
					powerShotReady = false;
				}
				powerBoost = 0.0f;
			}
			
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

		void Player::addEventListener(const std::string& type,st::event::function listener, int priority) {
			dispatcher.addEventListener(type,listener,priority);
		}

		void Player::removeEventListener(const std::string& type,st::event::function listener) {
			dispatcher.removeEventListener(type,listener);
		}


		void Player::shoot(float dt) {

			fireCounter+= dt;

			if(isShooting) {
				if(fireCounter > fireRate) {

					st::event::ShootEvent evt("shoot");
					evt.direction = shootingDir;
					evt.position = getPosition() + ((sf::Vector2f)getTexture()->getSize()) * 0.5f;
					evt.familyID = 0;
					if(powerShotReady) evt.powerShot = true;
					dispatcher.dispatchEvent(evt);
					fireCounter = 0;
				}

			} else {
				fireCounter = fireRate;
			}

		};

		void Player::slowDown() {

			dispatcher.dispatchEvent(st::event::Event("slowDown"));
		}

		void Player::update(float dt) {

			move((velocity) * dt);
			shoot(dt);

		};
		
		sf::Texture * Player::img;

	};
};
