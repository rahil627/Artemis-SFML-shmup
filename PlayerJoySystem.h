#ifndef PLAYER_JOY_SYS_H
#define PLAYER_JOY_SYS_H

#include <SFML/System.hpp>
#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"
#include "MovementComponent.h"
#include "Entity.h"
#include "TextureManager.h"
#include "ColliderSystem.h"

class PlayerJoyComponent : public artemis::Component {
public:

	float speed;
	unsigned int playerId;
	
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	
	bool useJoy;
	
	float delay;
	float delayAcc;
	
	PlayerJoyComponent(float speed, unsigned int playerId) {
		this->speed = speed;
		this->playerId = playerId;
		this->useJoy = false;
		if(playerId == 0)
		{
			left = sf::Keyboard::A;
			right = sf::Keyboard::D;
			up = sf::Keyboard::W;
			down = sf::Keyboard::S;
		}
		
		if(playerId == 1)
		{
			left = sf::Keyboard::Left;
			right = sf::Keyboard::Right;
			up = sf::Keyboard::Up;
			down = sf::Keyboard::Down;
		}
		delay = .1f;
		delayAcc = 0.0f;
	}

};

class PlayerJoySystem : public artemis::EntityProcessingSystem {

	
		typedef struct JoyData{
			
			unsigned int playerId;
			
			float LSAxisX; 
			float LSAxisY;	
			float RSAxisX; 
			float RSAxisY;	

			int povX;
			int povY;
			
			bool A;
			bool B;
			bool X;
			bool Y;
			bool L;
			bool LS;
			bool R;
			bool RS;
			
			bool Start;
			bool Back;
			
			bool actionA;
			bool actionB;
			bool actionX;
			bool actionY;
			bool actionL;
			bool actionLS;
			bool actionR;
			bool actionRS;
			
			bool actionStart;
			bool actionBack;
			
			
		}JoyData;
	
			
		enum Buttons {
		    A = 0,
		    B = 1,
		    X = 2,
		    Y = 3,
		    L = 4,
		    R = 5,
		    Back = 6,
		    START = 7,
		    LS = 8,
		    RS = 9
		};

	private:
		artemis::ComponentMapper<PlayerJoyComponent> pjMapper;
		artemis::ComponentMapper<VelocityComponent>  velMapper;
		artemis::ComponentMapper<PositionComponent>  posMapper;
		
		JoyData padData[4]; 
		JoyData previousState[4]; 
	public:

		virtual ~PlayerJoySystem(){

		}
		PlayerJoySystem() {
			setComponentTypes<PlayerJoyComponent,PositionComponent>();
		}

		virtual void initialize() {
			pjMapper.init(*world);
			velMapper.init(*world);
			posMapper.init(*world);
		}

		virtual void begin() {

		}

		virtual void end() {

		}

		virtual void processEntity(artemis::Entity& e) {
	
			updateJoyStatus();
			
			PlayerJoyComponent & pj = *pjMapper.get(e);
			JoyData& jd = padData[pj.playerId];
			float & velX = velMapper.get(e)->velocity.x;
			float & velY = velMapper.get(e)->velocity.y;
			
			float posX = posMapper.get(e)->position.x;
			float posY = posMapper.get(e)->position.y;
			
			float jX = jd.LSAxisX;
			float jY = jd.LSAxisY;
			
			pj.delayAcc += world->getDelta();
			
			//static int bcount;
			if((jd.actionA || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (pj.delayAcc > pj.delay)){
				//for(int i=0; i<1000; i++)
				//{
					pj.delayAcc = 0.0f;
					artemis::Entity& e = world->createEntity();
					e.addComponent(new PositionComponent(posX,posY));
					e.addComponent(new VelocityComponent(500,0));
					e.addComponent(new SpriteComponent(TextureManager::getInstance().getTexture("bullet.png")));
					e.addComponent(new ColliderComponent(10,10,0,1));
					e.refresh();
					e.setGroup("BULLET");
				//}

		
				//bcount++;
				//std::cout << bcount << "\n";;
				//bool isEmpty = e.getComponents().isEmpty();
				//std::cout << "IsEmpty:" << (isEmpty ?"True":"False") << "\n";
			}
			
			else if(jd.X && pj.delayAcc > pj.delay){
				
				pj.delayAcc = 0.0f;
				artemis::Entity& e = world->createEntity();
				e.addComponent(new PositionComponent(posX,posY));
				e.addComponent(new VelocityComponent(500,0));
				e.addComponent(new SpriteComponent(TextureManager::getInstance().getTexture("bullet.png")));
				e.addComponent(new ColliderComponent(10,10,0,pj.playerId));
				e.refresh();
				e.setGroup("BULLET");
				
				//bcount++;
				//std::cout << bcount << "\n";
				//bool isEmpty = e.getComponents().isEmpty();
				//std::cout << "IsEmpty:" << (isEmpty ?"True":"False") << "\n";
			}
			
			if(jX >15 || jY >15)
				pj.useJoy = true;
			
			if(sf::Keyboard::isKeyPressed(pj.left))
			{
				pj.useJoy = false;
				velX = -100 * pj.speed;
			
			}
			else if(sf::Keyboard::isKeyPressed(pj.right)){
				pj.useJoy = false;
				velX =  100 * pj.speed;
			}
			else velX = 0;
			
			if(sf::Keyboard::isKeyPressed(pj.up))
			{
				pj.useJoy = false;
				velY = -100 * pj.speed;
			
			}
			else if(sf::Keyboard::isKeyPressed(pj.down)){
				pj.useJoy = false;
				velY =  100 * pj.speed;
			}
			else velY = 0;
			
			if(pj.useJoy){
				velX = ((abs(jX) > 15) ? jX:0) * pj.speed; //* world->getDelta();
				velY = ((abs(jY) > 15) ? jY:0) * pj.speed;
			}
			 //* world->getDelta();

		}
		
		void updateJoyStatus(){
			
			
			for(unsigned int i=0; i< 4; i++)
			{
				
				//if(controllerID[i] == 0) return;
				JoyData &data = padData[i];
				JoyData &prev = previousState[i];
				
				data.playerId = i;
				data.LSAxisX = sf::Joystick::getAxisPosition(i,sf::Joystick::X);
				data.LSAxisY = sf::Joystick::getAxisPosition(i,sf::Joystick::Y);
				data.RSAxisX = sf::Joystick::getAxisPosition(i,sf::Joystick::U);
				data.RSAxisY = sf::Joystick::getAxisPosition(i,sf::Joystick::R);
				data.povX  = sf::Joystick::getAxisPosition(i,sf::Joystick::PovX);
				data.povY  = sf::Joystick::getAxisPosition(i,sf::Joystick::PovY);
				
				data.actionA = data.A = sf::Joystick::isButtonPressed(i,A);
				if(prev.A) data.actionA = false; 
				data.actionB = data.B = sf::Joystick::isButtonPressed(i,B);
				if(prev.B) data.actionB = false; 
				data.actionX = data.X = sf::Joystick::isButtonPressed(i,X);
				if(prev.X) data.actionX = false; 
				data.actionY = data.Y = sf::Joystick::isButtonPressed(i,Y); 
				if(prev.Y) data.actionY = false; 
				data.actionL = data.L = sf::Joystick::isButtonPressed(i,L); 
				if(prev.L) data.actionL = false; 
				data.actionR = data.R = sf::Joystick::isButtonPressed(i,R); 
				if(prev.R) data.actionR = false; 
				data.actionStart = data.Start = sf::Joystick::isButtonPressed(i,START);
				if(prev.Start) data.actionStart = false; 
				data.actionBack = data.Back = sf::Joystick::isButtonPressed(i,Back);
				if(prev.Back) data.actionBack = false; 
				data.actionLS = data.LS = sf::Joystick::isButtonPressed(i,LS);
				if(prev.LS) data.actionLS = false; 
				data.actionRS = data.RS = sf::Joystick::isButtonPressed(i,RS);
				if(prev.RS) data.actionRS = false; 
				//etc etc
				previousState[i] = padData[i];
				//controllerID[i]->onJoyData(data);
				
			}
		}
		
};


#endif // $(Guard token)
