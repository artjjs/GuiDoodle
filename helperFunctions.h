
float lerp(float a, float b, float t);
int randomNum(int a, int b, int i);
void pollEvents(sf::RenderWindow* window);
std::vector<std::string> get_directory_contents(const std::string& dir_path);
void loadDir(std::vector<std::string>* dirList, std::vector<sf::Texture>* texList);
std::vector<std::string> getDirectoryContents(const std::string& dir_path);
void pollEvents(sf::RenderWindow* window, unsigned int *cardIndex,unsigned int i);
void testingOpencv();
std::vector<std::string> getDirectoryContents(const std::string& dir_path);

//Return the larger of 2 numbers
#define getmax(a,b) ((a)>(b)?(a):(b))

//Windows window helper
int getWindowWidth(sf::RenderTexture* window) {
        return int(window->getSize().x);
    return 0; // Return 0 if the function fails
}

//Windows window helper
int getWindowHeight(sf::RenderTexture* window) {
        return int(window->getSize().y);
    return 0; // Return 0 if the function fails
}

//Linear interpolation
float lerp(float a, float b, float t)
{
    return a * (1.0 - t) + (b * t);
}

//Generate a random number given a seed
int randomNum(int a, int b, int i){
    //NameSpaces
    using namespace std;
    // Seed the random number generator
    std::mt19937 generator(i);
    // Define the distribution (range 1 to 100)
    std::uniform_int_distribution<int> distribution(a, b);
    // Generate and print a random number
    return distribution(generator);
}

//SFML poll window events function
void pollEvents(sf::RenderWindow* window, unsigned int *cardIndex,unsigned int i,int* switchPictures){
    //NameSpaces
    using namespace std;
    using namespace sf;
    //The function
    while (const optional event = window->pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window->close();
        }
        else if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
        {
            if (keyPressed->scancode == Keyboard::Scancode::Escape)
            {
                window->close();
            }
        }
        else if (const auto* keyPressed2 = event->getIf<Event::KeyReleased>())
        {
            if (keyPressed2->scancode == sf::Keyboard::Scan::E )
            {
                *cardIndex+=1;
                if(*cardIndex>i-1)
                {
                    *cardIndex=0;
                }
                //Debug
                //cout << " (" << *cardIndex << ")";
            }
            //easy reach out and alter value pointed at
            *switchPictures = 1;
        }
    }
}

//Gather all the files names in the current directory into a vector<string> list
std::vector<std::string> getDirectoryContents(const std::string& dir_path)
{
    std::vector<std::string> contents;

    std::string search_path = dir_path + "\\*";
    WIN32_FIND_DATA find_data;
    HANDLE hFind = FindFirstFile(search_path.c_str(), &find_data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do
        {
            std::string st=find_data.cFileName;
            if(st=="." || st==".."){
            }
            else{
                contents.push_back(find_data.cFileName);
            }
        }
        while (FindNextFile(hFind, &find_data) != 0);
        FindClose(hFind);
    }
    return contents;
}

void loadDir(std::vector<std::string>* dirList, std::vector<sf::Texture>* texList, std::map<std::string, int>* texPathToName){
    //Pull constant images, all the textures we never unload.
    for (unsigned int i=0; i < dirList->size(); i++)
    {
        //pull all the images from the image folder and load them into a texture list
        //Skip the .. that windows puts at the start of the list
        std::string dir = dirList->at(i);
        //make a entry with the current file into the texture list
        texList->push_back( sf::Texture("images\\" + dirList->at(i)) );
        //Map image names to there index in the texture list
        texPathToName->insert(std::make_pair("images\\" + dirList->at(i),texList->size()-1) );
    }
}
