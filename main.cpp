
#include <iostream>
#include <windows.h>
#include <random>
#include <map>
#include <fstream>
#include <vector>
//SFML includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//Handles window events
#include "events.h"
//Some useful functions i use
#include "helperFunctions.h"
//My SUDO HTML system
#include "gui.h"
//Basic SFML Scene data storage
#include "sceneCore.h"
//Specific scenes
#include "sceneBalls.h"
#include "sceneData.h"

//Main is a SFML object machine
int main()
{
    sf::RenderWindow window;
    float screenx=1920.0f;
    float screeny=1080.0f;
    sf::Vector2f windowSize=sf::Vector2f(screenx,screeny);
    sf::Vector2f windowMiddle=sf::Vector2f(screenx/2.0f,screeny/2.0f);
    std::string title="Jack App";//TITLE
    window.create(sf::VideoMode({windowSize.x, windowSize.y}), title);
    window.setFramerateLimit(60);
    //Our packed up scene
    //sceneStats sceneData(960,540,960,540);
    sceneBalls sceneBall(1920,1080,0,0,std::string("gui/index.txt"));
    //sceneBalls sceneBall2(960,540,960,0,std::string("gui/index2.txt"));
    //sceneBalls sceneBall3(960,540,0,540,std::string("gui/index3.txt"));
    //Windows window handle
    sf::WindowHandle hWnd = window.getNativeHandle();
    //Clock
    sf::Clock clock;
    clock.start();
    float dt=0.0;
    //EVENTS VARIABLES
    int pause=0;
    sf::Vector2f mousePos;
    float mouseWheelSpeed;
    sf::Vector2f mouseCurrentPos;
    sf::Vector2f mouseClickPosRight;
    sf::Vector2f mouseClickPosLeft;
    sf::Vector2f mouseClickPosMiddle;

    while (window.isOpen())
    {
        dt=clock.restart().asSeconds();
        events(&window,&screenx,&screeny,&windowSize,&windowMiddle,&mouseWheelSpeed,&pause, &hWnd);
        window.clear(sf::Color::Transparent);
        //scene.whileLoop();
        //sceneData.whileLoop(dt,&window);
        sceneBall.whileLoop(dt,&window);
        //sceneBall2.whileLoop(dt,&window);
        //sceneBall3.whileLoop(dt,&window);
        window.display();
    }

}
