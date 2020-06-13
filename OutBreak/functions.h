#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include "classes.h"

//functions class that way main file isnt cluttered
class functions
{
    public:
        //used for loading resource files into sound, font, and texture
        sf::SoundBuffer LoadBufferFromResource(const std::string& name);
        sf::Font LoadFontFromResource(const std::string& name);
        sf::Texture LoadTextureFromResource(const std::string& name);
        //ladder check functions used for player movement
        bool ladderUpCollision(int x, int y);
        bool ladderDownCollision(int x, int y);
        bool usingLadder(int y);
		//collision detection
        bool isCollide(GameObject *a,GameObject *b);
		//zombie "ai" functions for in game
        bool sameFloor(Zombie *a,Player *b);
        void attack(Zombie *a, Player *b);
};


#endif // FUNCTIONS_H_INCLUDED
