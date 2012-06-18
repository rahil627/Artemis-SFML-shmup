#include "InputEvent.h"
#include <SFML/Window.hpp>

namespace st{
	namespace input{
		
		JoyInput::JoyInput(){
			controllerID.resize(4);
		}
		
		void JoyInput::deRegisterObject(st::input::IJoyListener * listener, unsigned int id){
			controllerID.at(id) = 0;
		}
		
		void JoyInput::registerObject(st::input::IJoyListener * listener, unsigned int id){
			controllerID.at(id) = listener;
		}
		
		void JoyInput::update(float dt){
			
			st::input::JoyEvent event;
			
			for(unsigned int i=0; i<controllerID.size(); i++)
			{
				
				if(controllerID.at(i) == 0) return;
				
			
				
				event.dt = dt;
				
				event.axisX = sf::Joystick::getAxisPosition(i,sf::Joystick::X);
				event.axisY = sf::Joystick::getAxisPosition(i,sf::Joystick::Y);
				
				event.buttonA = sf::Joystick::isButtonPressed(i,st::input::A);
				event.buttonB = sf::Joystick::isButtonPressed(i,st::input::B);
				event.buttonX = sf::Joystick::isButtonPressed(i,st::input::X);
				event.buttonY = sf::Joystick::isButtonPressed(i,st::input::Y); 
				event.buttonL = sf::Joystick::isButtonPressed(i,st::input::L); 
				event.buttonR = sf::Joystick::isButtonPressed(i,st::input::R); 
				event.buttonStart = sf::Joystick::isButtonPressed(i,st::input::START);
				event.buttonBack = sf::Joystick::isButtonPressed(i,st::input::BACK);
				event.buttonLS = sf::Joystick::isButtonPressed(i,st::input::LS);
				event.buttonRS = sf::Joystick::isButtonPressed(i,st::input::RS);
				
				//etc etc
				
				controllerID.at(i)->onJoyEvent(event);
				
			}

			
		}
	}
}