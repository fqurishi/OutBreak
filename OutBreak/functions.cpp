#include "functions.h"

//load sound from resource
sf::SoundBuffer functions::LoadBufferFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::SoundBuffer buffer;
	if (!buffer.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load buffer from memory.");

	return buffer;
}

//load font from resource
sf::Font functions::LoadFontFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Font font;
	if (!font.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load font from memory.");

	return font;
}


//load Texture from resource
sf::Texture functions::LoadTextureFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Texture texture;
	if (!texture.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load texture from memory.");

	return texture;
}
//ladder methods, used to find position of player character and then
//allow him to use the ladder to go up and down if he is in the position of a ladder
//if he is using ladder he cant move left or right.
bool functions::ladderUpCollision(int x, int y){
    //get y positions of all floors
    int firstFloor=460, secondFloor=320, thirdFloor=175, fourthFloor=30, groundFloor=610;
    //check to see where player currently is, let him move accordingly
    if (y <= groundFloor && y > firstFloor){
        //first floor ladders position
        if (x >= 326 && x <= 360){
            return true;
        }else{
        return false;
        }
    }else if (y <= firstFloor && y > secondFloor){
        //second floor ladders position
        if ((x >= 16 && x <= 48) || (x >= 632 && x<= 656)){
            return true;
        }else{
        return false;
        }
    }else if (y <= secondFloor && y > thirdFloor){
        //third floor ladders position
        if ((x >= 248 && x<= 272) || (x >= 848 && x <= 872)){
            return true;
        }else{
        return false;
        }
    }else if (y <= thirdFloor && y > fourthFloor){
        //fourth floor's ladders position
        if ((x >= 542 && x<= 568) || (x >= 80 && x <= 112)){
            return true;
        }else{
        return false;
        }
	//cant go up if youre on fourth floor
    }else if (y == fourthFloor){
        return false;
    }
    else{
        return false;
    }
}
//same as above but instead going down, slight changes to code
bool functions::ladderDownCollision(int x, int y){
    int firstFloor=460, secondFloor=320, thirdFloor=175, fourthFloor=30, groundFloor=610;
	//cant go down if youre on ground floor
    if (y == groundFloor){
        return false;
    }else if (y < groundFloor && y >= firstFloor){
        if (x >= 326 && x <= 360){
            return true;
        }else{
        return false;
        }
    }else if (y < firstFloor && y >= secondFloor){
        if ((x >= 16 && x <= 48) || (x >= 632 && x<= 656)){
            return true;
        }else{
        return false;
        }
    }else if (y < secondFloor && y >= thirdFloor){
        if ((x >= 248 && x<= 272) || (x >= 848 && x <= 872)){
            return true;
        }else{
        return false;
        }
    }else if (y < thirdFloor && y >= fourthFloor){
        if ((x >= 542 && x<= 568) || (x >= 80 && x <= 112)){
            return true;
        }else{
        return false;
        }
    }
    else{
        return false;
    }
}
//check to see if player character is using a ladder, very simple. If he isnt currently on any of the floors then he is using a ladder
//used in game to not allow horizontal movement or the use of a gun.
bool functions::usingLadder(int y){
    int firstFloor=460, secondFloor=320, thirdFloor=175, fourthFloor=30, groundFloor=610;
    if (y < groundFloor && y > firstFloor){
        return true;
    }
    else if (y < firstFloor && y > secondFloor){
        return true;
    }
    else if (y < secondFloor && y > thirdFloor){
        return true;
    }
    else if (y < thirdFloor && y > fourthFloor){
        return true;
    }
    else {
        return false;
    }

}
//collision detection
bool functions::isCollide(GameObject *a,GameObject *b)
{
	//if game object being collided with is not bullet
    if(b->getName() != "bullet"){
		//checks for collision between player and zombie
        return (b->getX() - a->getX())*(b->getX() - a->getX())+
                (b->getY() - a->getY())*(b->getY() - a->getY())<
                (a->getR() + b->getR())*(a->getR() + b->getR());
    }else{
		//checks for collision between bullet and zombie
        return a->getSprite().getGlobalBounds().intersects(b->getSprite().getGlobalBounds());
    }
}
//checks if zombie and player are on the same floor
bool functions::sameFloor(Zombie *a, Player *b){
    if(a->getY() == b->getY()){
        return true;
    }else{
        return false;
    }
}
//zombie attack function when player is on the same floor as zombie
void functions::attack(Zombie *a, Player *b){
	//set the speed of the zombie as higher
    if(sameFloor(a, b)){
        a->setSpeed(13);
        if(a->getX() > b->getX()){
            a->setLeft(1);
        }
        else if(a->getX() < b->getX()){
            a->setRight(1);
        }
    }else{
		a->setSpeed(6);
	}
}
