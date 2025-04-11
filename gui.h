
//ABLE TO READ A FILE FOR SPECIFC FLAGS AND THEN SETUP SFML DRAWABLE OBJECTS
//IN THE CONFIG DESCRIBED IN MY SUDO HTML LANGUAGE

class JGUI
{
public:

    //Our Lists
    std::vector<std::string> tags_List;
    std::vector<std::string> contents_List;

    //SFML type lists
    std::vector<sf::Text> text_List;
    std::vector<sf::Sprite> sprite_List;
    std::vector<sf::Texture> texture_List;
    std::vector<sf::RectangleShape> shape_List;
    std::vector<sf::Texture> texture_shapes_List;

    //Temp vars
    std::string tag;
    std::string contents;
    std::string parameterName;
    std::string parameter;

    //The parameter map of each tag we read in
    std::map<std::string, std::string> parameters_Map;
    std::vector<std::map<std::string, std::string>> parameters_All;
    std::map<std::string, std::vector<float>> parent_Map;
    //Track relative position in list of all objects
    std::map<std::string, int> text_id_List;
    std::map<std::string, int> shape_id_List;
    //for animation
    std::map<std::string, sf::Vector2f> text_origin_id_List;
    std::map<std::string, sf::Vector2f> text_Velocity_List;
    std::map<std::string, sf::Vector2f> shape_origin_id_List;
    std::map<std::string, sf::Vector2f> shape_Velocity_List;
    std::map<std::string, sf::Color> shape_Color_List;
    int color_Tracker_r=1;
    int color_Tracker_g=1;
    int color_Tracker_b=1;
    int color_Tracker_a=1;

    //State flag
    int readingTag=0;
    int readingParameterName=0;
    int readingParameter=0;

    //SFML font for text
    sf::Font* font;

    //window pointer
    sf::RenderTexture* window;

    sf::Clock time;

    //INI WINDOW PTR AND FONT
    JGUI(sf::RenderTexture* windowIn, sf::Font* fontIn)
    {
        window = windowIn;
        time.start();
        //Load font
        font = fontIn;
    }

    void setWindow(sf::RenderTexture* windowIn)
    {
        window=windowIn;
    }

    //LOAD TXT FILE AND READ OUT EACH TAG AND IT'S CONTENT
    int load(std::string path)
    {
        std::ifstream myFile(path);
        if (myFile.is_open())
        {
            std::string line;
            while (getline(myFile, line))
            {
                //FOR CHAR IN LINE
                for(unsigned int i=0; i < line.length(); i++)
                {
                    //GET CHAR
                    char charPhased = line[i];
                    //Support up to 3 indents
                    if(charPhased == '\t')
                    {

                    }
                    else
                    {
                        //IF COMMENT
                        if(charPhased == '*')
                        {
                            //SKIP LINE
                            i=line.length();
                        }
                        //NOT END OF TAG AND READING TAG
                        else if(readingTag==1 && charPhased != '>')
                        {
                            //SKIP SPACES
                            if(charPhased != ' ')
                            {
                                //RECORD TAG CHAR
                                tag += charPhased;
                            }
                        }
                        //START OF TAG CHAR
                        else if(charPhased == '<')
                        {
                            //INDICATE WE ARE NOW READING TAG
                            readingTag=1;
                        }
                        //IF END OF TAG CHAR
                        else if(charPhased == '>')
                        {
                            //INDICATE WE ARE NOW NOT READING A TAG
                            readingTag=0;
                        }
                        //IF READINGTAG==0 WE ARE RECORDING CONTENTS
                        else if(readingTag==0)
                        {
                            contents += charPhased;
                        }
                    }
                }

                //As long as we have a tag and some contents
                if(tag != "" && contents != "")
                {
                    //std::cout << "CONTENTS :start: " << std::endl;
                    //std::cout << contents << std::endl;
                    //std::cout << ":end:" << std::endl;
                    //First save the tag name
                    tags_List.push_back(tag);
                    //Also save the entire line's content as a string
                    contents_List.push_back(contents);

                    //Now we have a tag and contents
                    //Go over the contents and break it into parameter names and parameters
                    readingParameterName=0;
                    readingParameter=0;
                    parameterName="";
                    parameter="";
                    //std::cout << "CUTUP CONTENTS :start: " << std::endl;
                    int toggle=0;
                    int content=0;
                    for(unsigned int i=0; i < contents.length();i++)
                    {
                        char charPhased = contents[i];
                        if(charPhased == '"' && toggle == 0)
                        {
                            //std::cout << "(" << "Starting parameter name" << ")" << std::endl;
                            toggle=1;
                        }
                        else if(charPhased == '=' && toggle == 1)
                        {
                            //std::cout << "(" << "parameter name = " << parameterName << ")" <<  std::endl;
                            toggle=2;
                        }
                        else if(charPhased == '"' && toggle == 2)
                        {
                            //std::cout << "(" << "parameter content = " << parameter << ")" << std::endl;
                            parameters_Map.insert(std::make_pair(parameterName, parameter));
                            parameterName="";
                            parameter="";
                            toggle=0;
                        }
                        if(charPhased != '"' && charPhased != '=')
                        {
                            if(toggle == 0)
                            {
                            }
                            else if(toggle == 1)
                            {
                                parameterName += charPhased;
                            }
                            else if(toggle == 2)
                            {
                                parameter += charPhased;
                            }
                        }
                    }
                    //Now we have a map of parameter names to parameters for this tag lets save it into a list of parameter lists
                    parameters_All.push_back(parameters_Map);
                    parameters_Map.clear();
                }
                tag="";
                contents="";
            }
            myFile.close();
        }
        else
        {
            std::cerr << "Unable to open file";
            return 1;
        }
        return 0;
    }

    //MAP OF TAG TO ID
    std::map<std::string, int> tags_IDS =
    {
        {"p", 1},
        {"shape", 2},
        {"button", 3},
        {"img", 4},
        {"in", 5},
    };

    //GO OVER ALL TAGS
    int execute_Tags()
    {
        //Go over all the tags we collected
        for(unsigned int i=0; i < tags_List.size();i++)
        {
            execute_Tag(tags_List[i], contents_List[i],i);
        }
        return 0;
    }

    //USE TAG ID TO INDICATE THE FUNCTION TO RUN
    int execute_Tag(std::string tag, std::string contents,int index)
    {
        int tag_id = tags_IDS[tag];
        //Execute a specific function for a given tag id number
        if(tag_id == 1)
        {
            tag_P(index);
        }
        if(tag_id == 2)
        {
            tag_Shape(index);
        }
        return 0;
    }

    //GO OVER ALL TAGS
    int execute_Tags_Animations(float dt)
    {
        //Go over all the tags we collected
        for(unsigned int i=0; i < tags_List.size();i++)
        {
            execute_Tag_Animation(tags_List[i], contents_List[i],i,dt);
        }
        return 0;
    }

    //DURRING THE MAIN LOOP RUN ALL ANIMATION FOR ALL TAGS
    int execute_Tag_Animation(std::string tag, std::string contents,int index,float dt)
    {
        int tag_id = tags_IDS[tag];
        //Execute a specific function for a given tag id number
        if(tag_id == 1)
        {
            tag_P_Animation(index,dt);
        }
        if(tag_id == 2)
        {
            tag_Shape_Animation(index,dt);
        }
        return 0;
    }

    //FUNCTIONS TO RUN ANIMATIONS IN THE MAIN LOOP
    int tag_P_Animation(int index, float dt)
    {
        //HOVER ANIMATION
        if(
           parameters_All[index].find("hover")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("size")!=parameters_All[index].end() &&
           parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["hover"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = text_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int size_X = std::stoi( parameters_All[index]["size"] );
                int size_Y = size_X;

                //The index of our sf::text object
                int text_List_Index = text_id_List[ nameP ];

                //Pull our original position
                sf::Vector2f text_object_start = text_origin_id_List[ nameP ];

                //We need a fixed point to check distance from
                sf::Vector2f text_object = text_List[ text_List_Index ].getPosition();

                //check for passing a distance above and below 0 from our fixed point
                if (text_object.y < text_object_start.y-size_Y)
                {
                    //flip direction
                    text_Velocity_List[ nameP ].y = -text_Velocity_List[ nameP ].y;
                    //push back above check distance so we don't re flip our speed multiple times
                    text_List[ text_List_Index ].setPosition(sf::Vector2f(text_object.x,text_object_start.y+(size_Y-1)));
                }
                else if (text_object.y > text_object_start.y+size_Y)
                {
                    //flip direction
                    text_Velocity_List[ nameP ].y = -text_Velocity_List[ nameP ].y;
                    text_List[ text_List_Index ].setPosition(sf::Vector2f(text_object.x,text_object_start.y-(size_Y-1)));
                }

                //Move object by our speed
                text_List[ text_List_Index ].setPosition(sf::Vector2f(text_object.x,text_object.y+ (text_Velocity_List[ nameP ].y ) ));

            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //Color change
        if(
           parameters_All[index].find("cpulse")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_r")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_g")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_b")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_a")!=parameters_All[index].end() &&
           parameters_All[index].find("color_r")!=parameters_All[index].end() &&
           parameters_All[index].find("color_g")!=parameters_All[index].end() &&
           parameters_All[index].find("color_b")!=parameters_All[index].end() &&
           parameters_All[index].find("color_a")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["cpulse"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = text_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );

                int animation_color_r = std::stoi( parameters_All[index]["animation_color_r"] );
                int animation_color_g = std::stoi( parameters_All[index]["animation_color_g"] );
                int animation_color_b = std::stoi( parameters_All[index]["animation_color_b"] );
                int animation_color_a = std::stoi( parameters_All[index]["animation_color_a"] );

                int color_r = std::stoi( parameters_All[index]["color_r"] );
                int color_g = std::stoi( parameters_All[index]["color_g"] );
                int color_b = std::stoi( parameters_All[index]["color_b"] );
                int color_a = std::stoi( parameters_All[index]["color_a"] );

                //The index of our sf::text object
                int text_List_Index = text_id_List[ nameP ];

                //Copy obj color and modify it
                sf::Color temp_Color = text_List[ text_List_Index ].getFillColor();

                //R
                if(color_r<animation_color_r)
                {
                    if(color_Tracker_r < color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                    else if(color_Tracker_r > animation_color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                }
                else if(color_r>animation_color_r)
                {
                    if(color_Tracker_r < animation_color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                    else if(color_Tracker_r > color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                }
                //G
                if(color_g<animation_color_g)
                {
                    if(color_Tracker_g < color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                    else if(color_Tracker_g > animation_color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                }
                else if(color_g>animation_color_g)
                {
                    if(color_Tracker_g < animation_color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                    else if(color_Tracker_g > color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                }
                //B
                if(color_b<animation_color_b)
                {
                    if(color_Tracker_b < color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                    else if(color_Tracker_b > animation_color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                }
                else if(color_b>animation_color_b)
                {
                    if(color_Tracker_b < animation_color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                    else if(color_Tracker_b > color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                }
                //A
                if(color_a<animation_color_a)
                {
                    if(color_Tracker_a < color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                    else if(color_Tracker_a > animation_color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                }
                else if(color_a>animation_color_a)
                {
                    if(color_Tracker_a < animation_color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                    else if(color_Tracker_a > color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                }

                //modify our color value
                temp_Color.r+=color_Tracker_r;
                temp_Color.g+=color_Tracker_g;
                temp_Color.b+=color_Tracker_b;
                temp_Color.a+=color_Tracker_a;

                //speed here is our input scale factor for the circle
                text_List[ text_List_Index ].setFillColor(temp_Color);
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //SizePulse animation
        //RELATIVE CHANGE
        if(
           parameters_All[index].find("spulse")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = text_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int animation_size = std::stoi( parameters_All[index]["animation_size"] );
                //The index of our text object
                int text_List_Index = text_id_List[ nameP ];

                //Pull our original position
                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                //if our border size is over the spulse parameter size
                if(text_List[ text_List_Index ].getScale().x>animation_size)
                {
                    //velocity is -
                    text_Velocity_List[ nameP ].x = -(std::stoi( parameters_All[index]["spulse"] )*0.01f);
                }
                if(text_List[ text_List_Index ].getScale().x<0)
                {
                    //velocity is +
                    text_Velocity_List[ nameP ].x = std::stoi( parameters_All[index]["spulse"] )*0.01f;
                }
                text_Velocity_List[ nameP ].x += text_Velocity_List[ nameP ].y;
                text_Velocity_List[ nameP ].y = text_Velocity_List[ nameP ].x;
                //sf::Vector2f( text_Velocity_List[ nameP ].y + (text_Velocity_List[ nameP ].x)*0.01 ,text_Velocity_List[ nameP ].y + (text_Velocity_List[ nameP ].x)*0.01 )
                //speed here is our input scale factor for the text
                text_List[ text_List_Index ].setScale( sf::Vector2f( text_Velocity_List[ nameP ].x, text_Velocity_List[ nameP ].x ) );
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        return 0;
    }

    int tag_Shape_Animation(int index, float dt)
    {
        //Each animation has a setup in the tag phaser

        //Set animations that make non relative changes to do there change first
        //Then relative to the fixed change add ons to the position are run after

        //Color change
        if(
           parameters_All[index].find("cpulse")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_r")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_g")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_b")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_color_a")!=parameters_All[index].end() &&
           parameters_All[index].find("color_r")!=parameters_All[index].end() &&
           parameters_All[index].find("color_g")!=parameters_All[index].end() &&
           parameters_All[index].find("color_b")!=parameters_All[index].end() &&
           parameters_All[index].find("color_a")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["cpulse"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = shape_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );

                int animation_color_r = std::stoi( parameters_All[index]["animation_color_r"] );
                int animation_color_g = std::stoi( parameters_All[index]["animation_color_g"] );
                int animation_color_b = std::stoi( parameters_All[index]["animation_color_b"] );
                int animation_color_a = std::stoi( parameters_All[index]["animation_color_a"] );

                int color_r = std::stoi( parameters_All[index]["color_r"] );
                int color_g = std::stoi( parameters_All[index]["color_g"] );
                int color_b = std::stoi( parameters_All[index]["color_b"] );
                int color_a = std::stoi( parameters_All[index]["color_a"] );

                //The index of our sf::text object
                int shape_List_Index = shape_id_List[ nameP ];

                //Copy obj color and modify it
                sf::Color temp_Color = shape_List[ shape_List_Index ].getFillColor();

                //R
                if(color_r<animation_color_r)
                {
                    if(color_Tracker_r < color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                    else if(color_Tracker_r > animation_color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                }
                else if(color_r>animation_color_r)
                {
                    if(color_Tracker_r < animation_color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                    else if(color_Tracker_r > color_r)
                    {
                        color_Tracker_r=-color_Tracker_r;
                    }
                }
                //G
                if(color_g<animation_color_g)
                {
                    if(color_Tracker_g < color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                    else if(color_Tracker_g > animation_color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                }
                else if(color_g>animation_color_g)
                {
                    if(color_Tracker_g < animation_color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                    else if(color_Tracker_g > color_g)
                    {
                        color_Tracker_g=-color_Tracker_g;
                    }
                }
                //B
                if(color_b<animation_color_b)
                {
                    if(color_Tracker_b < color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                    else if(color_Tracker_b > animation_color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                }
                else if(color_b>animation_color_b)
                {
                    if(color_Tracker_b < animation_color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                    else if(color_Tracker_b > color_b)
                    {
                        color_Tracker_b=-color_Tracker_b;
                    }
                }
                //A
                if(color_a<animation_color_a)
                {
                    if(color_Tracker_a < color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                    else if(color_Tracker_a > animation_color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                }
                else if(color_a>animation_color_a)
                {
                    if(color_Tracker_a < animation_color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                    else if(color_Tracker_a > color_a)
                    {
                        color_Tracker_a=-color_Tracker_a;
                    }
                }

                //modify our color value
                temp_Color.r+=color_Tracker_r;
                temp_Color.g+=color_Tracker_g;
                temp_Color.b+=color_Tracker_b;
                temp_Color.a+=color_Tracker_a;

                //speed here is our input scale factor for the circle
                shape_List[ shape_List_Index ].setFillColor(temp_Color);
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //Cos animation
        //ABSOLUTE CHANGE
        if(
           parameters_All[index].find("cos")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["cos"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = shape_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int size_X = std::stoi( parameters_All[index]["animation_size_x"] );
                int size_Y = std::stoi( parameters_All[index]["animation_size_y"] );

                //The index of our sf::text object
                int shape_List_Index = shape_id_List[ nameP ];

                //Pull our original position
                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                //speed here is our input scale factor for the circle
                shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object_start.x+( std::cos( time.getElapsedTime().asSeconds()*std::stoi( parameters_All[index]["cos"] ) ) *size_X),
                                                                        shape_object_start.y+( std::sin( time.getElapsedTime().asSeconds()*std::stoi( parameters_All[index]["cos"] ) ) *size_Y)
                                                                        )
                                                           );
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //borderPulse animation
        //RELATIVE CHANGE
        if(
           parameters_All[index].find("bpulse")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = shape_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int animation_size_X = std::stoi( parameters_All[index]["animation_size_x"] );
                int animation_size_Y = std::stoi( parameters_All[index]["animation_size_y"] );
                int size_X = std::stoi( parameters_All[index]["size_x"] );
                int size_Y = std::stoi( parameters_All[index]["size_y"] );
                //The index of our sf::rectangleshape object
                int shape_List_Index = shape_id_List[ nameP ];

                int shape_size_X = shape_List[ shape_List_Index ].getSize().x;
                int shape_size_Y = shape_List[ shape_List_Index ].getSize().y;

                //Pull our original position
                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                //if our border size is over the bpulse parameter size
                if(shape_List[ shape_List_Index ].getOutlineThickness()<-animation_size_X)
                {
                    //velocity is -
                    shape_Velocity_List[ nameP ].x = std::stoi( parameters_All[index]["bpulse"] );
                }
                if(shape_List[ shape_List_Index ].getOutlineThickness()>0)
                {
                    //velocity is +
                    shape_Velocity_List[ nameP ].x = -std::stoi( parameters_All[index]["bpulse"] );
                }
                //speed here is our input scale factor for the shape
                shape_List[ shape_List_Index ].setOutlineThickness(shape_List[ shape_List_Index ].getOutlineThickness()+shape_Velocity_List[ nameP ].x);
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //rotation animation
        //RELATIVE CHANGE
        if(
           parameters_All[index].find("rotate")!=parameters_All[index].end() &&
           parameters_All[index].find("size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                std::string nameP = parameters_All[index]["pName"];

                int shape_List_Index = shape_id_List[ nameP ];

                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                if(shape_List[ shape_List_Index ].getRotation().asDegrees()>360)
                {
                    shape_List[ shape_List_Index ].setRotation(sf::Angle(sf::degrees(0)));
                }
                //Change relative origin point
                sf::Vector2f Position(std::stoi(parameters_All[index]["size_x"]) / 2.0, std::stoi( parameters_All[index]["size_y"]) / 2.0);
                shape_List[ shape_List_Index ].setOrigin(Position);

                //apply rotation
                shape_List[ shape_List_Index ].setRotation(sf::degrees(shape_List[ shape_List_Index ].getRotation().asDegrees()+shape_Velocity_List[ nameP ].x));
                shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object_start.x+std::stoi(parameters_All[index]["size_x"]) / 2.0,shape_object_start.y+std::stoi(parameters_All[index]["size_y"]) / 2.0));
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //Pulse animation
        //RELATIVE CHANGE
        if(
           parameters_All[index].find("pulse")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["pulse"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = shape_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int animation_size_X = std::stoi( parameters_All[index]["animation_size_x"] );
                int animation_size_Y = std::stoi( parameters_All[index]["animation_size_y"] );
                int size_X = std::stoi( parameters_All[index]["size_x"] );
                int size_Y = std::stoi( parameters_All[index]["size_y"] );
                //The index of our sf::rectangleshape object
                int shape_List_Index = shape_id_List[ nameP ];

                int shape_size_X = shape_List[ shape_List_Index ].getSize().x;
                int shape_size_Y = shape_List[ shape_List_Index ].getSize().y;

                //Pull our original position
                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                //just track our x size
                if(shape_size_X>size_X+animation_size_X)
                {
                    shape_Velocity_List[ nameP ]=-shape_Velocity_List[ nameP ];
                }
                if(shape_size_X<size_X-animation_size_X)
                {
                    shape_Velocity_List[ nameP ]=-shape_Velocity_List[ nameP ];
                }
                //speed here is our input scale factor for the shape
                shape_List[ shape_List_Index ].setSize(sf::Vector2f(shape_size_X+(shape_Velocity_List[ nameP ].x),
                                                                    shape_size_Y+(shape_Velocity_List[ nameP ].y)
                                                                    )
                                                           );
                //speed here is our input scale factor for the shape
                shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_List[ shape_List_Index ].getPosition().x-((shape_Velocity_List[ nameP ].x)*0.5),
                                                                        shape_List[ shape_List_Index ].getPosition().y-((shape_Velocity_List[ nameP ].y)*0.5)
                                                                        )
                                                           );
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //HOVER ANIMATION
        //RELATIVE CHANGE
        if(
           parameters_All[index].find("hover")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["hover"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = text_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int size_X = std::stoi( parameters_All[index]["animation_size_x"] );
                int size_Y = std::stoi( parameters_All[index]["animation_size_y"] );

                //The index of our sf::Rectangle object
                int shape_List_Index = shape_id_List[ nameP ];

                //Pull our original position
                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                //We need a fixed point to check distance from
                sf::Vector2f shape_object = shape_List[ shape_List_Index ].getPosition();

                //check for passing a distance above and below 0 from our fixed point
                if (shape_object.y < shape_object_start.y-size_Y)
                {
                    //flip direction
                    shape_Velocity_List[ nameP ].y = -shape_Velocity_List[ nameP ].y;
                    shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object.x,shape_object_start.y+size_Y));
                }
                else if (shape_object.y > shape_object_start.y+size_Y)
                {
                    //flip direction
                    shape_Velocity_List[ nameP ].y = -shape_Velocity_List[ nameP ].y;
                    shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object.x,shape_object_start.y-size_Y));
                }

                //Move object by our speed
                shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object.x,shape_object.y+ (shape_Velocity_List[ nameP ].y*dt ) ));

            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        //WIGGLE ANIMATION
        //RELATIVE CHANGE
        if(
           parameters_All[index].find("wiggle")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("animation_size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
           parameters_All[index].find("pName")!=parameters_All[index].end()
           )
        {
            int speed;
            try {
                parameters_All[index]["wiggle"];
                //c++ parameter index to text_List index
                std::string nameP = parameters_All[index]["pName"];
                //Velocity for this tag is at nameP in text_Velocity_List
                sf::Vector2f speed = text_Velocity_List[ nameP ];
                int pos_X = std::stoi( parameters_All[index]["position_x"] );
                int pos_Y = std::stoi( parameters_All[index]["position_y"] );
                int size_X = std::stoi( parameters_All[index]["animation_size_x"] );
                int size_Y = std::stoi( parameters_All[index]["animation_size_y"] );

                //The index of our sf::text object
                int shape_List_Index = shape_id_List[ nameP ];

                //Pull our original position
                sf::Vector2f shape_object_start = shape_origin_id_List[ nameP ];

                //We need a fixed point to check distance from
                sf::Vector2f shape_object = shape_List[ shape_List_Index ].getPosition();

                //check for passing a distance above and below 0 from our fixed point
                if (shape_object.x < shape_object_start.x-size_X)
                {
                    //flip direction
                    shape_Velocity_List[ nameP ].x = -shape_Velocity_List[ nameP ].x;
                    shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object.x+size_X,shape_object_start.y));
                }
                else if (shape_object.x > shape_object_start.x+size_X)
                {
                    //flip direction
                    shape_Velocity_List[ nameP ].x = -shape_Velocity_List[ nameP ].x;
                    shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object.x-size_X,shape_object_start.y));
                }

                //Move object by our speed
                shape_List[ shape_List_Index ].setPosition(sf::Vector2f(shape_object.x+shape_Velocity_List[ nameP ].x*dt,shape_object.y ));
            }
            catch (const std::invalid_argument& e)
            {
            }
        }
        return 0;
    }

    //FUNCTIONS FOR ALL NON MAIN LOOP STUFF AKA EXECUTES 1 TIME
    //P_TAG
    int tag_P(int index)
    {
        //Construct a text obj for each p tag
        sf::Text text(*font);
        text.setCharacterSize(24); // in pixels, not points!
        text.setFillColor(sf::Color::Black);
        sf::Vector2f bounds;
        //PARAMETER LIST---------------------------------------------------------------------------------------------
        //string
        //size
        //color_r
        //color_g
        //color_b
        //color_a
        //parent
        //pName
        //align_left
        //align_right
        //align_bottom
        //align_top
        //align_horizontal_center
        //align_vertical_center
        //style
        //position_x
        //position_y

        //CHOOSE STYLE OF TEXT
        if(parameters_All[index].find("style")!=parameters_All[index].end())
        {
            //set the style
            if(parameters_All[index]["style"]=="bold")
            {
                text.setStyle(sf::Text::Bold);
            }
            else if(parameters_All[index]["style"]=="underlined")
            {
                text.setStyle(sf::Text::Underlined);
            }
            else if(parameters_All[index]["style"]=="italic")
            {
                text.setStyle(sf::Text::Italic);
            }
            else if(parameters_All[index]["style"]=="strikethrough")
            {
                text.setStyle(sf::Text::StrikeThrough);
            }
        }

        //IF HAD A STRING TO DISPLAY
        if(parameters_All[index].find("string")!=parameters_All[index].end())
        {
            //we need to break the string up into chunks for wrap function
            text.setString(parameters_All[index]["string"]);
            bounds = text.getLocalBounds().size;
        }

        //IF HAS A SIZE
        if(parameters_All[index].find("size")!=parameters_All[index].end())
        {
            text.setCharacterSize(std::stoi(parameters_All[index]["size"]));
        }

        //IF RGBA INPUT
        if(parameters_All[index].find("color_r")!=parameters_All[index].end() && parameters_All[index].find("color_g")!=parameters_All[index].end() && parameters_All[index].find("color_b")!=parameters_All[index].end() && parameters_All[index].find("color_a")!=parameters_All[index].end())
        {
        text.setFillColor(
                          sf::Color(std::stoi(parameters_All[index]["color_r"]),
                                    std::stoi(parameters_All[index]["color_g"]),
                                    std::stoi(parameters_All[index]["color_b"]),
                                    std::stoi(parameters_All[index]["color_a"])
                                    )
                          );
        }

        //ALIGNMENT OPERATIONS
        //PARENT---------------------------------------------------------------------------------------------
        if(
           parameters_All[index].find("parent")!=parameters_All[index].end()
           )
        {
            //PARENT DATA
            std::string parentName= parameters_All[index]["parent"];
            std::vector<float> maper;
            maper = parent_Map.at(parentName);
            float size_x = maper[0];
            float size_y = maper[1];
            float position_x = maper[2];
            float position_y = maper[3];

            //ALIGN_RIGHT
            if(parameters_All[index].find("align_right")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //the full window size - sprites size so it still shows
                text.setPosition(
                                    sf::Vector2f(
                                                float(size_x-(bounds.x/2.0f)),
                                                text.getPosition().y
                                                )
                                    );
            }
            //ALIGN_LEFT
            if(parameters_All[index].find("align_left")!=parameters_All[index].end())
            {
                //Just push left
                text.setPosition(
                                   sf::Vector2f(
                                                0.0f,
                                                text.getPosition().y
                                                )
                                   );
            }

            if(parameters_All[index].find("align_horizontal_center")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //half the window - half the sprite size
                text.setPosition(
                                   sf::Vector2f(
                                                (size_x/2.0f) - (bounds.x/2.0f),
                                                 text.getPosition().y
                                                 )
                                   );
            }

            if(parameters_All[index].find("align_top")!=parameters_All[index].end())
            {
                //just 0 y
                text.setPosition(
                                   sf::Vector2f(text.getPosition().x,
                                                0.0f
                                                )
                                   );
            }

            if(parameters_All[index].find("align_vertical_center")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //same align but on y
                text.setPosition(
                                   sf::Vector2f(
                                                text.getPosition().x,
                                                (size_y/2.0f) - (std::stoi(parameters_All[index]["size"])/2.0f)
                                                )
                                   );
            }

            if(parameters_All[index].find("align_bottom")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //force to bottom on y
                text.setPosition(
                                   sf::Vector2f(
                                                text.getPosition().x,
                                                size_y - std::stoi(parameters_All[index]["size"])
                                                )
                                   );
            }

        }
        //NO PARENT---------------------------------------------------------------------------------------------
        else
        {
            //ALIGN_RIGHT
            if(parameters_All[index].find("align_right")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //the full window size - sprites size so it still shows
                text.setPosition(
                                    sf::Vector2f(
                                                float(getWindowWidth(window)-std::stoi(parameters_All[index]["size"])),
                                                text.getPosition().y
                                                )
                                    );
            }
            //ALIGN_LEFT
            if(parameters_All[index].find("align_left")!=parameters_All[index].end())
            {
                //Just push left
                text.setPosition(
                                   sf::Vector2f(
                                                0.0f,
                                                text.getPosition().y
                                                )
                                   );
            }
            //ALIGN_HORIZONTAL_CENTER
            if(parameters_All[index].find("align_horizontal_center")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //half the window - half the sprite size
                text.setPosition(
                                   sf::Vector2f(
                                                (float(getWindowWidth(window))/2.0f) - (std::stoi(parameters_All[index]["size"])/2.0f),
                                                 text.getPosition().y
                                                 )
                                   );
            }
            //ALIGNTOP
            if(parameters_All[index].find("align_top")!=parameters_All[index].end())
            {
                //just 0 y
                text.setPosition(
                                   sf::Vector2f(text.getPosition().x,
                                                0.0f
                                                )
                                   );
            }
            //ALIGN_VERTICAL_CENTER
            if(parameters_All[index].find("align_vertical_center")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //same align but on y
                text.setPosition(
                                   sf::Vector2f(
                                                text.getPosition().x,
                                                (float(getWindowHeight(window))/2.0f) - (std::stoi(parameters_All[index]["size"])/2.0f)
                                                )
                                   );
            }
            //ALIGN_BOTTOM
            if(parameters_All[index].find("align_bottom")!=parameters_All[index].end() && parameters_All[index].find("size")!=parameters_All[index].end())
            {
                //force to bottom on y
                text.setPosition(
                                   sf::Vector2f(
                                                text.getPosition().x,
                                                float(getWindowHeight(window)) - std::stoi(parameters_All[index]["size"])
                                                )
                                   );
            }
        }

        //PARENT---------------------------------------------------------------------------------------------
        if(
           parameters_All[index].find("parent")!=parameters_All[index].end()
           )
        {
            //PARENT DATA
            std::string parentName= parameters_All[index]["parent"];
            std::vector<float> maper;
            maper = parent_Map.at(parentName);
            float size_x = maper[0];
            float size_y = maper[1];
            float position_x = maper[2];
            float position_y = maper[3];

            //SET POSTION
            if(parameters_All[index].find("position_x")!=parameters_All[index].end() && parameters_All[index].find("position_y")!=parameters_All[index].end())
            {
                text.setPosition(
                                   sf::Vector2f(
                                                text.getPosition().x + std::stoi(parameters_All[index]["position_x"]) + position_x,
                                                text.getPosition().y + std::stoi(parameters_All[index]["position_y"]) + position_y
                                                )
                                   );
            }
        }

        //IF NO PARENT---------------------------------------------------------------------------------------------
        else
        {
            //SET POSITION
            if(parameters_All[index].find("position_x")!=parameters_All[index].end() && parameters_All[index].find("position_y")!=parameters_All[index].end())
            {
                text.setPosition(
                                   sf::Vector2f(
                                                text.getPosition().x + std::stoi(parameters_All[index]["position_x"]),
                                                text.getPosition().y + std::stoi(parameters_All[index]["position_y"])
                                                )
                                   );
            }
        }

        //IF IS A PARENT IT'S SELF
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end()
           )
        {
            std::vector<float> data_List;
            data_List.push_back( float(std::stoi( parameters_All[index]["size_x"] )) );
            data_List.push_back( float(std::stoi( parameters_All[index]["size_y"] )) );
            data_List.push_back( float(std::stoi( parameters_All[index]["position_x"] ))+text.getPosition().x );
            data_List.push_back( float(std::stoi( parameters_All[index]["position_y"] ))+text.getPosition().y );
            parent_Map.insert ( std::pair<std::string,std::vector<float>>( parameters_All[index]["pName"],data_List ) );
        }

        //HOVER ANIMATION
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("hover")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            text_origin_id_List.insert( std::make_pair(a , text.getPosition()));

            //Store a velocity to track on this tag
            text_Velocity_List.insert( std::make_pair(a , sf::Vector2f( 0.0, std::stoi( parameters_All[index]["hover"]) ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<text_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            text_id_List.insert( std::make_pair(a , in));
        }

        //COLOR ANIMATION
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("cpulse")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            text_origin_id_List.insert( std::make_pair(a , text.getPosition()));

            //Store a velocity to track on this tag
            text_Velocity_List.insert( std::make_pair(a , sf::Vector2f( 0.0, std::stoi( parameters_All[index]["cpulse"]) ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<text_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            text_id_List.insert( std::make_pair(a , in));
        }

        //Size ANIMATION
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("spulse")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            text_origin_id_List.insert( std::make_pair(a , text.getPosition()));

            //Store a velocity to track on this tag
            text_Velocity_List.insert( std::make_pair(a , sf::Vector2f( std::stoi( parameters_All[index]["spulse"]) , 1 ) ) );

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<text_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            text_id_List.insert( std::make_pair(a , in));
        }

        //PUSH TEXT OBJECT AND RETURN
        text_List.push_back(text);

        return 0;
    }

    //Shape_TAG
    int tag_Shape(int index)
    {

        //DEFAULT SHAPE
        //I could just have this render to the screen with no adjustment
        sf::RectangleShape rectangle({10.f, 10.f});
        rectangle.setPosition(sf::Vector2f(1,1));
        rectangle.setOutlineColor(sf::Color(100.0, 100.0, 100.0));
        rectangle.setOutlineThickness( 0.0 );

        //Now read parameters and adjust our rectangle

        //Load texture
        sf::Texture texture;
        if(
            parameters_All[index].find("path")!=parameters_All[index].end() &&
            parameters_All[index].find("origin_x")!=parameters_All[index].end() &&
            parameters_All[index].find("origin_y")!=parameters_All[index].end() &&
            parameters_All[index].find("size_x_img")!=parameters_All[index].end() &&
            parameters_All[index].find("size_y_img")!=parameters_All[index].end()
           )
        {
            //Construct a texture and sprite for each IMG tag
            texture.loadFromFile(
                                parameters_All[index]["path"],
                                false,
                                sf::IntRect(
                                                {std::stoi(parameters_All[index]["origin_x"]),std::stoi(parameters_All[index]["origin_y"])},
                                                {std::stoi(parameters_All[index]["size_x_img"]),std::stoi(parameters_All[index]["size_y_img"])}
                                            )
                                 );
            //Sprite
            texture_shapes_List.push_back(texture);
        }

        //Set outline color
        if(
           parameters_All[index].find("outline_color_r")!=parameters_All[index].end() &&
           parameters_All[index].find("outline_color_g")!=parameters_All[index].end() &&
           parameters_All[index].find("outline_color_b")!=parameters_All[index].end()
           )
        {
            rectangle.setOutlineColor(sf::Color(std::stoi(parameters_All[index]["outline_color_r"]), std::stoi(parameters_All[index]["outline_color_g"]), std::stoi(parameters_All[index]["outline_color_b"])));
        }
        //Set outline size
        if(
           parameters_All[index].find("outline_size")!=parameters_All[index].end()
           )
        {
            rectangle.setOutlineThickness( std::stoi( parameters_All[index]["outline_size"]) );
        }


        //If (r g b a) color
        if(
           parameters_All[index].find("color_r")!=parameters_All[index].end() &&
           parameters_All[index].find("color_g")!=parameters_All[index].end() &&
           parameters_All[index].find("color_b")!=parameters_All[index].end() &&
           parameters_All[index].find("color_a")!=parameters_All[index].end()
           )
        {
            rectangle.setFillColor(
                          sf::Color(std::stoi(parameters_All[index]["color_r"]),
                                    std::stoi(parameters_All[index]["color_g"]),
                                    std::stoi(parameters_All[index]["color_b"]),
                                    std::stoi(parameters_All[index]["color_a"])
                                    )
                          );
        }

        //ALIGNMENT OPERATIONS
        //PARENT---------------------------------------------------------------------------------------------
        if(
           parameters_All[index].find("parent")!=parameters_All[index].end()
           )
        {
            //PARENT DATA
            std::string parentName= parameters_All[index]["parent"];
            std::vector<float> maper;
            maper = parent_Map.at(parentName);
            float size_x = maper[0];
            float size_y = maper[1];
            float position_x = maper[2];
            float position_y = maper[3];

            //ALIGN_RIGHT
            if(
               parameters_All[index].find("align_right")!=parameters_All[index].end() &&
               parameters_All[index].find("size_x")!=parameters_All[index].end()
               )
            {
                rectangle.setPosition(
                                    sf::Vector2f(
                                                float(size_x-std::stoi(parameters_All[index]["size_x"])),
                                                rectangle.getPosition().y
                                                )
                                    );
            }

            //ALIGN_LEFT
            if(
               parameters_All[index].find("align_left")!=parameters_All[index].end()
               )
            {
                //Just push left
                rectangle.setPosition(
                                   sf::Vector2f(
                                                0.0f,
                                                rectangle.getPosition().y
                                                )
                                   );
            }

            //ALIGN_HORIZONTAL_CENTER
            if(
               parameters_All[index].find("align_horizontal_center")!=parameters_All[index].end() &&
               parameters_All[index].find("size_x")!=parameters_All[index].end()
               )
            {
                //half the window - half the sprite size
                rectangle.setPosition(
                                   sf::Vector2f(
                                                (size_x/2.0f) - (std::stoi(parameters_All[index]["size_x"])/2.0f),
                                                 rectangle.getPosition().y
                                                 )
                                   );
            }

            //ALIGN_TOP
            if(
               parameters_All[index].find("align_top")!=parameters_All[index].end()
               )
            {
                //just 0 y
                rectangle.setPosition(
                                   sf::Vector2f(rectangle.getPosition().x,
                                                0.0f
                                                )
                                   );
            }

            //ALIGN_VERTICAL_CENTER
            if(
               parameters_All[index].find("align_vertical_center")!=parameters_All[index].end() &&
               parameters_All[index].find("size_y")!=parameters_All[index].end()
               )
            {
                //same align but on y
                rectangle.setPosition(
                                   sf::Vector2f(
                                                rectangle.getPosition().x,
                                                (size_y/2.0f) - (std::stoi(parameters_All[index]["size_y"])/2.0f)
                                                )
                                   );
            }

            //ALIGN_BOTTOM
            if(
               parameters_All[index].find("align_bottom")!=parameters_All[index].end() &&
               parameters_All[index].find("size_y")!=parameters_All[index].end()
               )
            {
                //force to bottom on y
                rectangle.setPosition(
                                   sf::Vector2f(
                                                rectangle.getPosition().x,
                                                size_y - std::stoi(parameters_All[index]["size_y"])
                                                )
                                   );
            }

        }
        //The tag had no parent then apply relative to the window
        else
        {
            //ALIGN_RIGHT
            if(
               parameters_All[index].find("align_right")!=parameters_All[index].end() &&
               parameters_All[index].find("size_x")!=parameters_All[index].end()
               )
            {
                //the full window size - sprites size so it still shows
                rectangle.setPosition(
                                    sf::Vector2f(
                                                float(getWindowWidth(window)-std::stoi(parameters_All[index]["size_x"])),
                                                rectangle.getPosition().y
                                                )
                                    );
            }

            //ALIGN_LEFT
            if(
               parameters_All[index].find("align_left")!=parameters_All[index].end()
               )
            {
                //Just push left
                rectangle.setPosition(
                                   sf::Vector2f(
                                                0.0f,
                                                rectangle.getPosition().y
                                                )
                                   );
            }

            //ALIGN_HORIZONTAL_CENTER
            if(
               parameters_All[index].find("align_horizontal_center")!=parameters_All[index].end() &&
               parameters_All[index].find("size_x")!=parameters_All[index].end()
               )
            {
                //half the window - half the sprite size
                rectangle.setPosition(
                                   sf::Vector2f(
                                                (float(getWindowWidth(window))/2.0f) - (std::stoi(parameters_All[index]["size_x"])/2.0f),
                                                 rectangle.getPosition().y
                                                 )
                                   );
            }

            //ALIGN_TOP
            if(
               parameters_All[index].find("align_top")!=parameters_All[index].end()
               )
            {
                //just 0 y
                rectangle.setPosition(
                                   sf::Vector2f(rectangle.getPosition().x,
                                                0.0f
                                                )
                                   );
            }

            //ALIGN_VERTICAL_CENTER
            if(
               parameters_All[index].find("align_vertical_center")!=parameters_All[index].end() &&
               parameters_All[index].find("size_y")!=parameters_All[index].end()
               )
            {
                //same align but on y
                rectangle.setPosition(
                                   sf::Vector2f(
                                                rectangle.getPosition().x,
                                                (float(getWindowHeight(window))/2.0f) - (std::stoi(parameters_All[index]["size_y"])/2.0f)
                                                )
                                   );
            }

            //ALIGN_BOTTOM
            if(
               parameters_All[index].find("align_bottom")!=parameters_All[index].end() &&
               parameters_All[index].find("size_y")!=parameters_All[index].end()
               )
            {
                //force to bottom on y
                rectangle.setPosition(
                                   sf::Vector2f(
                                                rectangle.getPosition().x,
                                                float(getWindowHeight(window)) - std::stoi(parameters_All[index]["size_y"])
                                                )
                                   );
            }


        }

        //IF SIZE X Y SET SIZE
        if(
           parameters_All[index].find("size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("size_y")!=parameters_All[index].end()
           )
        {
            rectangle.setSize({std::stoi(parameters_All[index]["size_x"]), std::stoi(parameters_All[index]["size_y"])});
        }

        //TRANSLATIONS
        if(
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end()
           )
        {
            //PARENT
            if(
               parameters_All[index].find("parent")!=parameters_All[index].end()
               )
            {
                //PARENT_DATA
                std::string parentName= parameters_All[index]["parent"];
                std::vector<float> maper;
                maper = parent_Map.at(parentName);
                float size_x = maper[0];
                float size_y = maper[1];
                float position_x = maper[2];
                float position_y = maper[3];

                //SET POSITION
                rectangle.setPosition(
                   sf::Vector2f(
                                rectangle.getPosition().x + std::stoi(parameters_All[index]["position_x"]) + position_x,
                                rectangle.getPosition().y + std::stoi(parameters_All[index]["position_y"]) + position_y
                                )
                   );
            }
            else
            {
                //SET_POSITION
                rectangle.setPosition(
                   sf::Vector2f(
                                rectangle.getPosition().x + std::stoi(parameters_All[index]["position_x"]),
                                rectangle.getPosition().y + std::stoi(parameters_All[index]["position_y"])
                                )
                   );
            }
        }

        //IF IS A PARENT SAVE DATA
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("position_x")!=parameters_All[index].end() &&
           parameters_All[index].find("position_y")!=parameters_All[index].end()
           )
        {
            std::vector<float> data_List;
            data_List.push_back( float(std::stoi( parameters_All[index]["size_x"] )) );
            data_List.push_back( float(std::stoi( parameters_All[index]["size_y"] )) );
            data_List.push_back( float(std::stoi( parameters_All[index]["position_x"] ))+rectangle.getPosition().x );
            data_List.push_back( float(std::stoi( parameters_All[index]["position_y"] ))+rectangle.getPosition().y );
            parent_Map.insert ( std::pair<std::string,std::vector<float>>( parameters_All[index]["pName"],data_List ) );
        }
        //IF HAS HOVER ANIMATION TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("hover")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this tag
            shape_Velocity_List.insert( std::make_pair(a , sf::Vector2f( 0.0, std::stoi( parameters_All[index]["hover"]) ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        //IF HAS WIGGLE TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("wiggle")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this pName
            shape_Velocity_List.insert( std::make_pair(a , sf::Vector2f( std::stoi( parameters_All[index]["wiggle"]), 0.0 ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        //IF HAS COS TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("cos")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this pName
            //for this velocity x is a scale factor for the unit cos, sin circle
            shape_Velocity_List.insert( std::make_pair(a , sf::Vector2f( std::stoi( parameters_All[index]["cos"]), 0.0 ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        //IF HAS pulse TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("pulse")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this pName
            //for this velocity x is a scale factor for the unit cos, sin circle
            shape_Velocity_List.insert( std::make_pair(a , sf::Vector2f( std::stoi( parameters_All[index]["pulse"]), std::stoi( parameters_All[index]["pulse"]) ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        //IF HAS bpulse TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("bpulse")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this pName
            //for this velocity x is a scale factor for the unit cos, sin circle
            shape_Velocity_List.insert( std::make_pair(a , sf::Vector2f( std::stoi( parameters_All[index]["bpulse"]), std::stoi( parameters_All[index]["bpulse"]) ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        //IF HAS cpulse TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("cpulse")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this pName
            //for this velocity x is a scale factor for the unit cos, sin circle
            shape_Color_List.insert( std::make_pair(a , sf::Color(
                                                                    std::stoi( parameters_All[index]["animation_color_r"]),
                                                                      std::stoi( parameters_All[index]["animation_color_g"]),
                                                                       std::stoi( parameters_All[index]["animation_color_b"]),
                                                                      std::stoi( parameters_All[index]["animation_color_a"])
                                                                    )
                                                       )
                                       );
            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        //IF HAS rotate TAG
        if(
           parameters_All[index].find("pName")!=parameters_All[index].end() &&
           parameters_All[index].find("size_y")!=parameters_All[index].end() &&
           parameters_All[index].find("size_x")!=parameters_All[index].end() &&
           parameters_All[index].find("rotate")!=parameters_All[index].end()
           )
        {
            //Store a copy of the starting position
            std::string a=parameters_All[index]["pName"];
            shape_origin_id_List.insert( std::make_pair(a , rectangle.getPosition()));

            //Store a velocity to track on this pName
            //for this velocity x is a scale factor for the unit cos, sin circle
            shape_Velocity_List.insert( std::make_pair(a , sf::Vector2f( std::stoi( parameters_All[index]["rotate"]), std::stoi( parameters_All[index]["rotate"]) ) ));

            //Just count the list size ATM
            int in=0;
            for(int j=0;j<shape_List.size();j++){
                in++;
            }

            //Record the position we pushed this item into
            shape_id_List.insert( std::make_pair(a , in));
        }
        shape_List.push_back(rectangle);
        return 0;
    }

};
