
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
    //CREATE WINDOW
    sf::RenderWindow window;
    //  Set window details
    float screenx=1920.0f;//variables
    float screeny=1080.0f;
    sf::Vector2f windowSize=sf::Vector2f(screenx,screeny);
    sf::Vector2f windowMiddle=sf::Vector2f(screenx/2.0f,screeny/2.0f);
    std::string title="Jack App";
    window.create(sf::VideoMode({windowSize.x, windowSize.y}), title);//settings
    window.setFramerateLimit(60);
    sf::WindowHandle hWnd = window.getNativeHandle();//window's window handle

    //EVENTS VARIABLES
    int pause=0;
    sf::Vector2f mousePos;
    float mouseWheelSpeed;
    sf::Vector2f mouseCurrentPos;
    sf::Vector2f mouseClickPosRight;
    sf::Vector2f mouseClickPosLeft;
    sf::Vector2f mouseClickPosMiddle;

    //Our packed up scene
    sceneBalls sceneBall(1920,1080,0,0,std::string("gui/index.txt"),  &mouseCurrentPos, &mouseClickPosRight, &mouseClickPosLeft, &mouseClickPosMiddle);

    //Clock
    sf::Clock clock;
    clock.start();
    float dt=0.0;

    while (window.isOpen())
    {
        dt=clock.restart().asSeconds();
        events(&window,&screenx,&screeny,&windowSize,&windowMiddle,&mouseWheelSpeed,&pause, &hWnd, sceneBall.guiFramePointer->window, &mouseCurrentPos, &mouseClickPosRight, &mouseClickPosLeft, &mouseClickPosMiddle);
        window.clear(sf::Color::Transparent);
        sceneBall.whileLoop(dt,&window);
        window.display();
    }

}
