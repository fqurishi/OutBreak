#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>

//game object
class GameObject
{
private:
    //position coordinates and radius (used for colllisions)
    int x,y, R;
    //is it alive? is it engaged (zombie)?
    bool life, engage;
    //name of object
    std::string name;
    //sprite of object
    sf::Sprite sprite;
//getters and setters for game object
public:
    GameObject();
    virtual ~GameObject();
    int getX();
    int getY();
    int getR();
    bool getLife();
    sf::Sprite getSprite();
    std::string getName();
    void setX(int a);
    void setY(int a);
    void setR(int a);
    void setLife(bool a);
    void setName(std::string a);
    //used to set sprite texture of sprite and textureRect
    void setTexture(sf::Texture &t);
    void setTextureRect(sf::IntRect &r);
    //used to update anything the object needs to update
    virtual void update();
    //used to draw the sprite
    void draw(sf::RenderWindow &app);
};
//bullet game object
class Bullet: public GameObject
{
private:
    //left and right to check which way the bullet is facing
    bool left, right;
    //used to get the direction the bullet will travel
    int bulletDirection;
//getters and setters
public:
    //created with set position
    Bullet(int a, int b);
    bool getLeft();
    bool getRight();
    int getBulletDirection();
    void setLeft(bool a);
    void setRight(bool a);
    void setBulletDirection(int a);
    //update bullet position
    void update();

};
//player game object
class Player: public GameObject
{
private:
    //left, right, up, and down to check which way the player is going
    bool left, right, up, down;
    //width and height for textureRect and ammo for bullets in gun
    int width, height, ammo, health;
    //IntRect values to be used for textureRect
    sf::IntRect r, l;
//getters and setters
public:
    Player();
    bool getLeft();
    bool getRight();
    bool getUp();
    bool getDown();
    int getWidth();
    int getHeight();
    int getAmmo();
    int getHealth();
    sf::IntRect getR();
    sf::IntRect getL();
    void setLeft(bool a);
    void setRight(bool a);
    void setUp(bool a);
    void setDown(bool a);
	//used when player is damaged
    void damaged(int a);
    //used when player shoots his gun
    void shotGun();
    //updates player position
    void update();

};
//zombie game object
class Zombie: public GameObject
{
private:
    //left, right to check which way the zombie is going. Respawn activate if out of bounds
    bool left, right, respawn;
    //width and height for textureRect and speed for pace of zombie
    int width, height, speed;
    sf::IntRect r, l;
public:
//getters and setters
    Zombie();
    bool getLeft();
    bool getRight();
    bool getRespawn();
    int getWidth();
    int getHeight();
    int getSpeed();
    sf::IntRect getR();
    sf::IntRect getL();
    void setLeft(bool a);
    void setRight(bool a);
    void setSpeed(int a);
    void setRespawn(bool a);
    void update();

};

#endif // CLASSES_H_INCLUDED
