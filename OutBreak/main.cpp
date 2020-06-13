#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <list>
#include "functions.h"
#include "classes.h"
using namespace sf;



int main()
{
    //creating function object to call functions
    functions myFunctions;
	//use current time as seed for random num generator
    srand(time(0));
	//set the render window and framelimit
    RenderWindow app(VideoMode(960, 720), "OutBreak By Faisl Qurishi");
    app.setFramerateLimit(8);

    //making textures and loading them up
    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    t1 = myFunctions.LoadTextureFromResource("TEXTURE1");
    t2 = myFunctions.LoadTextureFromResource("TEXTURE2");
    t3 = myFunctions.LoadTextureFromResource("TEXTURE3");
    t4 = myFunctions.LoadTextureFromResource("TEXTURE4");
    t5 = myFunctions.LoadTextureFromResource("TEXTURE5");
    t6 = myFunctions.LoadTextureFromResource("TEXTURE6");
    t7 = myFunctions.LoadTextureFromResource("TEXTURE7");
    t8 = myFunctions.LoadTextureFromResource("TEXTURE8");
    t9 = myFunctions.LoadTextureFromResource("TEXTURE9");
    t10 = myFunctions.LoadTextureFromResource("TEXTURE10");

    //making background sprite
    Sprite sBackground(t5);

    //make lists for gameObjects and zombies
    std::list<GameObject*> gameObjects;
    std::list<Zombie*> zombies;
    //creating player character and setting him up
    Player *p = new Player();
	//set texture for player
    p->setTexture(t1);
	//set player as facing left
    p->setLeft(1);
	//put player into game objects list
    gameObjects.push_back(p);

    //create zombies and set them up
    for(int i=0;i<10;i++){
        Zombie *z = new Zombie();
		//give zombies their texture
        z->setTexture(t9);
		//make sure zombies dont spawn on players position
        if(z->getX() == p->getX() && z->getY() == p->getY()){
                z->setX(rand() % 884);
        }
		//put the zombies into the zombie list
        zombies.push_back(z);
    }
    //spawn points for zombies later on in game when zombies appear from off screen
    int spawnPoint [2] = {-74, 924};


    //adding sounds
    SoundBuffer sbg, sm, b1, b2, b3, b4, b5, b6, b7, b8;
    Sound bg, m, s1, s2, s3, s4, s5, s6, s7, s8;
    sbg = myFunctions.LoadBufferFromResource("SOUNDBG");
    sm = myFunctions.LoadBufferFromResource("SOUNDM");
    b1 = myFunctions.LoadBufferFromResource("SOUND1");
    b2 = myFunctions.LoadBufferFromResource("SOUND2");
    b3 = myFunctions.LoadBufferFromResource("SOUND3");
    b4 = myFunctions.LoadBufferFromResource("SOUND4");
    b5 = myFunctions.LoadBufferFromResource("SOUND5");
    b6 = myFunctions.LoadBufferFromResource("SOUND6");
    b7 = myFunctions.LoadBufferFromResource("SOUND7");
	b8 = myFunctions.LoadBufferFromResource("SOUND8");
    bg.setBuffer(sbg);
    m.setBuffer(sm);
    s1.setBuffer(b1);
    s2.setBuffer(b2);
    s3.setBuffer(b3);
    s4.setBuffer(b4);
    s5.setBuffer(b5);
    s6.setBuffer(b6);
    s7.setBuffer(b7);
	s8.setBuffer(b8);

    //adding fonts and text used in the game
    Font eightBit;
    eightBit = myFunctions.LoadFontFromResource("FONT1");
    Text startMenu, enter, win, loser;
    startMenu.setFont(eightBit);
    enter.setFont(eightBit);
    win.setFont(eightBit);
    loser.setFont(eightBit);
    startMenu.setCharacterSize(60);
    startMenu.setFillColor(Color::White);
    startMenu.setString("\t  OutBreak\n\n\t\t   By\n\n\tFAISL QURISHI");
    win.setCharacterSize(40);
    win.setFillColor(Color::White);
    win.setString("\n\n\n\n\n\n\t\t\t\tYou Won\n\n\t\tsurvived the night");
    loser.setCharacterSize(40);
    loser.setFillColor(Color::White);
    loser.setString("\n\n\n\n\n\n\t\t\t\tYou Lost\n\n\n\t\t\t\t git gud");
    enter.setCharacterSize(35);
    enter.setString("PRESS\nENTER");
    startMenu.setPosition(100, 120);
    enter.setPosition(400,550);

    //menu code
    //add flash timer for flashing enter in title
    int flash = 0;
    //add flash bool and bool to check if in startMenu, or if won game or lost game
    bool flashBool = true, title = true, won = false, lost = false;

    //play background music
    m.play();
    m.setLoop(true);

    //create clocks
    Clock clock;
    Clock clock2;

    while (app.isOpen())
    {
        //get time
        Time elapsed1 = clock.getElapsedTime();
        Time elapsed2 = clock2.getElapsedTime();

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
    if(title == false && won == false){
        //going down the ladder
        if (Keyboard::isKeyPressed(Keyboard::Down)){
            //checking if going down the ladder
            if (myFunctions.ladderDownCollision(p->getX(), p->getY()) == true){
                //turn bool on going for down
                p->setDown(1);
                //move position
                p->update();
                //get correct textures to use
                if(p->getSprite().getTexture() == &t1 || p->getSprite().getTexture() == &t2 || p->getSprite().getTexture() == &t4 || p->getSprite().getTexture() == &t6 || p->getSprite().getTexture() == &t7){
                    p->setTexture(t3);
                }else if(p->getSprite().getTexture() == &t3){
                    p->setTexture(t4);
                }
                //play sound for ladder
                s3.play();
            }
        }
        //going up the ladder
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            //checking if going up the ladder
            if (myFunctions.ladderUpCollision(p->getX(), p->getY()) == true){
                //turn bool on for going up
                p->setUp(1);
                //move position
                p->update();
                //get correct textures to use
                if(p->getSprite().getTexture() == &t1 || p->getSprite().getTexture() == &t2 || p->getSprite().getTexture() == &t4 || p->getSprite().getTexture() == &t6 || p->getSprite().getTexture() == &t7){
                    p->setTexture(t3);
                }
                else if(p->getSprite().getTexture() == &t3){
                    p->setTexture(t4);
                }
                //play sound for ladder
                s3.play();
            }
        }
        //going right
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            //making sure character isnt using a ladder currently
            if(myFunctions.usingLadder(p->getY()) == false){
                //turn bool on for going right
                p->setRight(1);
                //grab the correct texture to use
                if(p->getSprite().getTexture() == &t1 || p->getSprite().getTexture() == &t3 || p->getSprite().getTexture() == &t4 || p->getSprite().getTexture() == &t6){
                    p->setTexture(t2);
                    //play first step sound
                    s1.play();
                }else if(p->getSprite().getTexture() == &t2 || p->getSprite().getTexture() == &t7){
                    p->setTexture(t1);
                    //play second step sound
                    s2.play();
                }
                //move player if he is in bounds
                p->update();
            }
        }
        //going left, same as going right
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            if(myFunctions.usingLadder(p->getY()) == false){
                //turn bool on for going left
                p->setLeft(1);
                //grab the correct texture to use
                if(p->getSprite().getTexture() == &t1 || p->getSprite().getTexture() == &t3 || p->getSprite().getTexture() == &t4 || p->getSprite().getTexture() == &t6){
                    p->setTexture(t2);
                    //play first step sound
                    s1.play();
                }else if(p->getSprite().getTexture() == &t2 || p->getSprite().getTexture() == &t7){
                    p->setTexture(t1);
                    //play second step sound
                    s2.play();
                }
                //move player if he is in bounds
                p->update();
            }
        }
        //shooting gun
        if (Keyboard::isKeyPressed(Keyboard::Space)){
            //check to see if there is ammo
            if(p->getAmmo() != 0){
                //z to correct height of bullets
                int z;
                //use the correct texture for shooting the gun
                if(p->getSprite().getTexture() == &t1){
                        p->setTexture(t6);
                        //update z
                        z = 28;
                //same as above
                }else if(p->getSprite().getTexture() == &t2){
                        p->setTexture(t7);
                        z = 31;
                }
                //check player is going right
                if(p->getRight()){
                        //sound of gun firing
                        s4.play();
                        //create new bullet with correct position
                        Bullet *b = new Bullet(p->getX() - 13, p->getY() + z);
                        //set the bullets texture
                        b->setTexture(t8);
                        //insert it into gameobjects
                        gameObjects.push_back(b);
                        //set its direction
                        b->setRight(1);
                        b->setLeft(0);
                        //move the bullet
                        b->update();
                }
                //same as above but left this time.
                else if(p->getLeft()){
                        s4.play();
                        Bullet *b = new Bullet(p->getX() + 123, p->getY() + z);
                        b->setTexture(t8);
                        gameObjects.push_back(b);
                        b->setRight(0);
                        b->setLeft(1);
                        b->update();
                }
                //player shot the gun, updates ammo
                p->shotGun();
            }
            //if there is no ammo, just show gun but no actions except updating textures
            else{
                if(p->getSprite().getTexture() == &t1){
                        p->setTexture(t6);
                }else if(p->getSprite().getTexture() == &t2){
                        p->setTexture(t7);
                }
            }
        }
        //killing bugs while climbing ladder up and down (correcting position)
        if (p->getY() == 310){
            p->setY(320);
        }
        if (p->getY() == 170){
            p->setY(175);
        }
        if (p->getY() == 25){
            p->setY(30);
        }
        if (p->getY() == 470){
            p->setY(460);
        }
        if (p->getY() == 180){
            p->setY(175);
        }
        //bullets firing, updates them to move during game
        for(auto b:gameObjects){
            if(b->getName()=="bullet"){
                if(b->getLife()){
                    b->update();
                }
                if(b->getX()==-43 || b->getX()==885){
                    b->setLife(0);
                }
            }
        }
        //zombies walking, updates them to move during game
        for(auto z:zombies){
            if(z->getLife()){
                z->update();
                if(z->getSprite().getTexture() == &t9){
                    z->setTexture(t10);
                }else if(z->getSprite().getTexture() == &t10){
                    z->setTexture(t9);
                }
            }
			//respawning zombies when they move off screen
            if(z->getRespawn()){
				//kill the zombie off
                z->setLife(0);
				//create new zombie
                Zombie *a = new Zombie();
                a->setTexture(t9);
				//set position as one of the spawn points (appear walking in from off screen)
                a->setX(spawnPoint[rand() % 2]);
				//put new zombie into the list
                zombies.push_back(a);
            }
        }
        //collision detection
        for(auto a:gameObjects)
            for(auto b:zombies)
            {	//when zombie collides with bullet
                if (a->getName()=="bullet")
                    if (myFunctions.isCollide(b,a))
                    {	//play zombie death sound and set the life of both objects to false
                        s6.play();
                        a->setLife(0);
                        b->setLife(0);
                    }
				//when zombie and player collide
                if (a->getName()=="player")
                    if (myFunctions.isCollide(a,b))
                    {
                        //add damage sound and damage function
                        s7.play();
                        //reduce health of player
                        if(p->getHealth() > 0){
                            p->damaged(1);
						//if player has no more health, kill him
                        }else{
                            p->setLife(0);
                        }
                    }

            }
        //making zombies attack player
        for(auto z:zombies){
            if(z->getName()=="zombie"){
                myFunctions.attack(z, p);
            }
        }
        //spawning more zombies in every 6 seconds
        if((int)elapsed2.asSeconds() == 6){
			//have zombies growl
			s8.play();
            //create zombies and set them up
            Zombie *z = new Zombie();
            z->setTexture(t9);
            z->setX(spawnPoint[rand() % 2]);
            zombies.push_back(z);
			//reset clock
            clock2.restart();
        }
        //object deletion after they lose life
        for(auto i=gameObjects.begin();i!=gameObjects.end();)
        {
            GameObject *g = *i;
			//get all game objects with no life and delete them
            if (g->getLife()==false){
                    i=gameObjects.erase(i);
                    delete g;

            }
            else i++;
        }
		//zombie deletion after they lose life
        for(auto i=zombies.begin();i!=zombies.end();)
        {
            Zombie *z = *i;
			//get all zombies with no life and delete them
            if (z->getLife()==false){
                    i=zombies.erase(i);
                    delete z;

            }
            else i++;
        }
        //if player is dead, end the game
        if(p->getHealth() == 0){
            lost = true;
        }
	//if game hasnt started show start menu
    }else{
	//repeat flash
    flash++;
	//creating the flash effect for the enter text
    if(5/flash == 1){
        flashBool = !flashBool;
        flash = 0;
    }
	//if flash is true, flash text white
    if(flashBool == true){
        enter.setFillColor(Color::White);
    }
	//otherwise flahs it black
    else{
        enter.setFillColor(Color::Black);
    }
    }
    //begin drawing everything to appear in game
    app.clear();
    //change scene from title to game when enter is pressed
    if (title == true){
        //draw strings for menu
        app.draw(startMenu);
        app.draw(enter);
        //check if enter is pressed
        if(Keyboard::isKeyPressed(Keyboard::Enter)){
            //play outbreak sound and pause bg music
            s5.play();
            m.pause();
            //start counter up (that way theres a dramatic pause before the game is loaded)
            int counter = 1;
            Sleep(1000);
            while (counter >= 1)
            {
                Sleep(1000);
                counter--;
            }
            //play bg for game
            bg.play();
            bg.setLoop(true);
            //change the bool to finally load up the real game
            title = false;
			//restart timeers for the game
            clock.restart();
            clock2.restart();
        }
    }
	//creating won game message
    else if(p->getLife() && elapsed1.asSeconds() >= 100 && lost != true){
        //win message
        app.draw(win);
        //pause music
        bg.pause();
        //deactivate game
        won = true;

    }
	//creating lost game message
    else if(lost){
        //lose message
        app.draw(loser);
        //pause music
        bg.pause();
        //deactivate game
        won = true;

    }
	//creating the actual game
    else{
		//draw all the objects
        app.draw(sBackground);
        for(auto i:gameObjects) i->draw(app);
        for(auto i:zombies) i->draw(app);
    }

    app.display();
}

    return 0;
}

