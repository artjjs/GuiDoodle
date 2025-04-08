
//Pack up window size, midpoint into Vector2f
struct windowData
{
    //Window data
    float screenx, screeny;
    sf::Vector2f windowSize;
    sf::Vector2f windowMiddle;
};

//Define lists to store everything inside a scene
struct sceneData
{
    //SFML shaders
    std::vector<sf::Shader> shaders;
    //SFML textures
    std::vector<sf::Texture> textures;
    //SFML texts
    std::vector<sf::Text> texts;
    std::vector<sf::Font> fonts;
    //SFML shapes
    std::vector<sf::RectangleShape> rectangleShapes;
    std::vector<sf::CircleShape> circleShapes;
    //SFML sprites
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Vector2f> velocities;
    //GUI OBJECTS
    std::vector<JGUI> guis;
    //WindowData
    windowData windowDataHolder;
};

