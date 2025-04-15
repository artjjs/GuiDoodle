
class sceneBalls
{
public:
    sceneData sceneData;
    sf::RenderTexture renderTexture;
    float posX, posY;
    JGUI *guiFramePointer;
    sf::Vector2f* mouseCurrentPos;
    sf::Vector2f* mouseClickPosRight;
    sf::Vector2f* mouseClickPosLeft;
    sf::Vector2f* mouseClickPosMiddle;
    //OPENING ACTIONS
    sceneBalls(float x,float y,float posXin, float posYin, std::string path, sf::Vector2f* mouseCurrentPosIn,sf::Vector2f* mouseClickPosRightIn,sf::Vector2f* mouseClickPosLeftIn,sf::Vector2f* mouseClickPosMiddleIn)
    {
        mouseCurrentPos=mouseCurrentPosIn;
        mouseClickPosRight=mouseClickPosRightIn;
        mouseClickPosLeft=mouseClickPosLeftIn;
        mouseClickPosMiddle=mouseClickPosMiddleIn;
        //Record the position of the render texture
        posX=posXin;
        posY=posYin;

        //Create window
        sceneData.windowDataHolder.screenx=x;
        sceneData.windowDataHolder.screeny=y;
        sceneData.windowDataHolder.windowSize=sf::Vector2f(sceneData.windowDataHolder.screenx,sceneData.windowDataHolder.screeny);
        sceneData.windowDataHolder.windowMiddle=sf::Vector2f(sceneData.windowDataHolder.screenx/2.0f,sceneData.windowDataHolder.screeny/2.0f);

        //our font
        sf::Font font("arial.ttf");
        sceneData.fonts.push_back(font);//Use vector member that will remain after ini

        //RenderTexture to draw into
        renderTexture.resize(sf::Vector2u(sceneData.windowDataHolder.screenx,sceneData.windowDataHolder.screeny));
        renderTexture.setActive();
        //Search the image directory
        std::vector<std::string> dirList = getDirectoryContents("images\\");
        std::vector<sf::Texture> texList;
        std::map<std::string, int> texPathToName;
        //Load the static textures
        loadDir(&dirList, &texList, &texPathToName);
        //Create a instance of my SUDO HTML GUI class
        JGUI guiFrame(&renderTexture,&sceneData.fonts.at(0),mouseCurrentPos,mouseClickPosRight,mouseClickPosLeft,mouseClickPosMiddle);
        guiFramePointer = &guiFrame;
        guiFrame.load(path);
        guiFrame.execute_Tags();
        sceneData.guis.push_back(guiFrame);
    }
    //Here we run our time based simulations
    void update(float dt)
    {
        //Do rotations translations scaling and color animations
        sceneData.guis.at(0).execute_Tags_Clickable(dt);
        sceneData.guis.at(0).execute_Tags_Animations(dt);
    }
    void whileLoop(float dt, sf::RenderWindow* window)
    {
        //Clear window
        renderTexture.clear(sf::Color::Transparent);

        //Update all the internal scene dynamics
        update(dt);

        if(sceneData.guis.at(0).shape_List.size()!=0)
        {
            //Since JGUI stores all it's own members we draw them out here
            for(unsigned int i=0;i<sceneData.guis.at(0).shape_List.size();i++)
            {
                //relocate the texture for the sprite in memory
                sceneData.guis.at(0).shape_List[i].setTexture(&sceneData.guis.at(0).texture_shapes_List[i]);
                renderTexture.draw(sceneData.guis.at(0).shape_List[i]);
            }
        }
        else
        {

        }
        if(sceneData.guis.at(0).sprite_List.size()!=0)
        {
            for(unsigned int i=0;i<sceneData.guis.at(0).sprite_List.size();i++)
            {
                //relocate the texture for the sprite in memory
                sceneData.guis.at(0).sprite_List[i].setTexture(sceneData.guis.at(0).texture_List[i]);
                renderTexture.draw(sceneData.guis.at(0).sprite_List[i]);
            }
        }
        else
        {

        }
        if(sceneData.guis.at(0).text_List.size()!=0)
        {
            for(unsigned int i=0;i<sceneData.guis.at(0).text_List.size();i++)
            {
                renderTexture.draw(sceneData.guis.at(0).text_List[i]);
            }
        }
        else
        {

        }
        //SPRITES
        if (sceneData.sprites.size()!=0)
        {
            for(int i=0;i < sceneData.sprites.size();i++)
            {
                //Queue up draws
                renderTexture.draw(sceneData.sprites.at(i));
            }
        }
        //RECT SHAPES
        if (sceneData.rectangleShapes.size()!=0)
        {
            for(int i=0;i < sceneData.rectangleShapes.size();i++)
            {
                //Queue up draws
                renderTexture.draw(sceneData.rectangleShapes.at(i));
            }
        }
        //CIRCLE SHAPES
        if (sceneData.circleShapes.size()!=0)
        {
            for(int i=0;i < sceneData.circleShapes.size();i++)
            {
                //Queue up draws
                renderTexture.draw(sceneData.circleShapes.at(i));
            }
        }
        //TEXTS
        if (sceneData.texts.size()!=0)
        {
            for(int i=0;i < sceneData.texts.size();i++)
            {
                //Queue up draws
                renderTexture.draw(sceneData.texts.at(i));
            }
        }

        //Apply the queued up draw calls to the render texture
        renderTexture.display();
        //Save the RenderTexture to a Texture
        const sf::Texture& texture = renderTexture.getTexture();
        sf::Sprite sprite(texture);
        sprite.setPosition(sf::Vector2f(posX,posY));

        //Draw our entire RenderTexture to the main window
        window->draw(sprite);

    }
private:

};
