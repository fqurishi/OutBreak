#include "classes.h"


//create gameObject with life
GameObject::GameObject(){
    life = 1;
}
GameObject::~GameObject(){}
int GameObject::getX(){
    return x;
}
int GameObject::getY(){
    return y;
}
int GameObject::getR(){
    return R;
}
sf::Sprite GameObject::getSprite(){
    return sprite;
}
std::string GameObject::getName(){
    return name;
}
bool GameObject::getLife(){
    return life;
}
void GameObject::setX(int a){
    x = a;
}
void GameObject::setY(int a){
    y = a;
}
void GameObject::setR(int a){
    R = a;
}
void GameObject::setName(std::string a){
    name = a;
}
void GameObject::setLife(bool a){
    life = a;
}
//set texture of gameobject
void GameObject::setTexture(sf::Texture& t){
    sprite.setTexture(t);
}
//set textureRect of gameobject (allows to flip image)
void GameObject::setTextureRect(sf::IntRect &r){
    sprite.setTextureRect(r);
}
void GameObject::update(){}
//draw the object, set its position and draw the sprite
void GameObject::draw(sf::RenderWindow &app){
    sprite.setPosition(x,y);
    app.draw(sprite);
}
//create bullet class, set its x and y coordinates right away as they relate to the players
Bullet::Bullet(int a, int b){
    setName("bullet");
    setX(a);
    setY(b);
    setR(2);
}
bool Bullet::getLeft(){
    return left;
}
bool Bullet::getRight(){
    return right;
}
int Bullet::getBulletDirection(){
    return bulletDirection;
}
void Bullet::setRight(bool a){
    right = a;
}
void Bullet::setLeft(bool a){
    left = a;
}
void Bullet::setBulletDirection(int a){
    bulletDirection = a;
}
//update bullets direction by which way the gun is racing, relates with player
void Bullet::update(){
    if (getRight()){
        setBulletDirection(60);
    }
    else if(getLeft()){
        setBulletDirection(-60);
    }
    setX(getX() + bulletDirection);
}
//create player in the starting position and with 9 bullets
Player::Player(){
    setX(800);
    setY(610);
    setName("player");
    ammo = 9;
    health = 15;
    setR(10);
}
bool Player::getLeft(){
    return left;
}
bool Player::getRight(){
    return right;
}
bool Player::getUp(){
    return up;
}
bool Player::getDown(){
    return down;
}
//get height of the sprite
int Player::getHeight(){
    height = getSprite().getLocalBounds().height;
    return height;
}
//get width of the sprite
int Player::getWidth(){
    width = getSprite().getLocalBounds().width;
    return width;
}
int Player::getAmmo(){
    return ammo;
}
int Player::getHealth(){
    return health;
}
sf::IntRect Player::getL(){
    width = getWidth();
    height = getHeight();
    l = sf::IntRect(0,0,width,height);
    return l;
}
sf::IntRect Player::getR(){
    width = getWidth();
    height = getHeight();
    r = sf::IntRect(width,0,-width,height);
    return r;
}
void Player::setLeft(bool a){
    left = a;
    right = !a;
    up = !a;
    down = !a;
}
void Player::setRight(bool a){
    right = a;
    left = !a;
    up = !a;
    down = !a;
}
void Player::setUp(bool a){
    up = a;
    left = !a;
    right = !a;
    down = !a;
}
void Player::setDown(bool a){
    down = a;
    left = !a;
    right = !a;
    up = !a;
}
void Player::damaged(int a){
    health = health - a;
}
//if player shoots his gun, he loses ammo
void Player::shotGun(){
    ammo = getAmmo() - 1;
}
//update the players direction and position
void Player::update(){
    //sf::IntRect r, l;
    r = getR();
    l = getL();
    if (getRight()){
        if(getX() <= 884){
            setX(getX()+12);
            setTextureRect(r);
        }
    }
    else if(getLeft()){
        if(getX() >= -42){
            setX(getX()-12);
            if(getSprite().getTextureRect() == r){
                setTextureRect(l);
            }
        }
    }
    else if(getUp()){
        setY(getY()-15);
    }
    else if(getDown()){
        setY(getY()+15);
    }
}

Zombie::Zombie(){
    setName("zombie");
    setR(15);
    int floor [5] = {610, 460, 320, 175, 30};
    int leftOrRight [2] = {0, 1};
    setY(floor[rand()%5]);
    setX(rand() % 884);
    setSpeed(6);
    setLeft(leftOrRight[rand()%2]);
    setRespawn(0);
}
//get height of the sprite
int Zombie::getHeight(){
    height = getSprite().getLocalBounds().height;
    return height;
}
//get width of the sprite
int Zombie::getWidth(){
    width = getSprite().getLocalBounds().width;
    return width;
}
sf::IntRect Zombie::getL(){
    width = getWidth();
    height = getHeight();
    l = sf::IntRect(0,0,width,height);
    return l;
}
int Zombie::getSpeed(){
    return speed;
}
sf::IntRect Zombie::getR(){
    width = getWidth();
    height = getHeight();
    r = sf::IntRect(width,0,-width,height);
    return r;
}
bool Zombie::getLeft(){
    return left;
}
bool Zombie::getRight(){
    return right;
}
bool Zombie::getRespawn(){
    return respawn;
}
void Zombie::setLeft(bool a){
    left = a;
    right = !a;
}
void Zombie::setRight(bool a){
    left = !a;
    right = a;
}
void Zombie::setSpeed(int a){
    speed = a;
}
void Zombie::setRespawn(bool a){
    respawn = a;
}
void Zombie::update(){
    r = getR();
    l = getL();
    if(getLeft()){
        if(getX() >= -75){
            if(getSprite().getTextureRect() == r){
                setTextureRect(l);
            }
            setX(getX()-getSpeed());
        }else{
            setRespawn(1);
        }
    }
    if(getRight()){
        if(getX() <= 925){
            setTextureRect(r);
            setX(getX()+getSpeed());
        }else{
            setRespawn(1);
        }
    }
}


