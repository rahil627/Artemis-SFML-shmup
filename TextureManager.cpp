#include "TextureManager.h"

#include <iostream> 
TextureManager::TextureManager(){
	instance = this;
};

TextureManager::~TextureManager(){
	std::unordered_map<std::string, sf::Texture*>::iterator it;
	
	for (it = texturemap.begin(); it != texturemap.end(); ++it) 
	{
		delete it->second;
	}
	
	instance = nullptr;
};


sf::Texture& TextureManager::getTexture(std::string name){
	sf::Texture * texture = texturemap[name];
	
	if(texture == nullptr){
		for(unsigned int i=0; i < pathlist.size(); i++)
		{
			std::string path = pathlist.at(i);
			texture = new sf::Texture();
			texture->loadFromFile(path + name);
			texturemap[name] = texture;
		}
	}
		return *texture;
}

void TextureManager::addSearchPath(std::string path){
	pathlist.push_back(path);
}

TextureManager * TextureManager::instance;