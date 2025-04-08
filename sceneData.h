
class sceneStats
{
public:
    sceneData sceneData;
    sf::RenderTexture renderTexture;
    float posX, posY;
    //OPENING ACTIONS
    sceneStats(float x,float y,float posXin, float posYin)
    {
        //Record the position of the render texture
        posX=posXin;
        posY=posYin;

        //System info
        SYSTEMTIME st;
        SYSTEM_INFO sysInfo;
        MEMORYSTATUSEX memStatus;

        // Seed the random number generator
        std::random_device rd; // Obtain a random seed from the OS
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(-100, 100);
        int randomNumber = distrib(gen);// Generate and print a random number
        int randomNumber2 = distrib(gen);

        //Create window
        sceneData.windowDataHolder.screenx=x;
        sceneData.windowDataHolder.screeny=y;
        sceneData.windowDataHolder.windowSize=sf::Vector2f(sceneData.windowDataHolder.screenx,sceneData.windowDataHolder.screeny);
        sceneData.windowDataHolder.windowMiddle=sf::Vector2f(sceneData.windowDataHolder.screenx/2.0f,sceneData.windowDataHolder.screeny/2.0f);

        //RenderTexture to draw into
        renderTexture.resize(sf::Vector2u(sceneData.windowDataHolder.screenx,sceneData.windowDataHolder.screeny));
        renderTexture.setActive(true);

        //Get info on system
        GetSystemInfo(&sysInfo);
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);

        //Font
        sf::Font font("arial.ttf");
        sceneData.fonts.push_back(font);//Use vector member that will remain after ini
        float fontSize=24;
        float spacing= fontSize+4;
        int s=sceneData.fonts.size()-1;//Use a pointer to the vector of textures item

        //Year
        sf::Text yearw(sceneData.fonts.at(s));
        yearw.setString("Year : ");
        yearw.setCharacterSize(fontSize);
        yearw.setFillColor(sf::Color::Green);
        yearw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*1) ));
        sceneData.texts.push_back(yearw);

        sf::FloatRect textWidthRect = yearw.getLocalBounds();
        sf::Vector2f textWidth = textWidthRect.size;

        sf::Text year(sceneData.fonts.at(s));
        year.setString(std::to_string(st.wYear));
        year.setCharacterSize(fontSize);
        year.setFillColor(sf::Color::Red);
        year.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*1) ));
        sceneData.texts.push_back(year);

        //Month
        sf::Text monthw(sceneData.fonts.at(s));
        monthw.setString("Month : ");
        monthw.setCharacterSize(fontSize);
        monthw.setFillColor(sf::Color::Green);
        monthw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*2) ));
        sceneData.texts.push_back(monthw);

        textWidthRect = monthw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text month(sceneData.fonts.at(s));
        month.setString(std::to_string(st.wMonth));
        month.setCharacterSize(fontSize);
        month.setFillColor(sf::Color::Red);
        month.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*2) ));
        sceneData.texts.push_back(month);

        //Day
        sf::Text dayw(sceneData.fonts.at(s));
        dayw.setString("Day : ");
        dayw.setCharacterSize(fontSize);
        dayw.setFillColor(sf::Color::Green);
        dayw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*3) ));
        sceneData.texts.push_back(dayw);

        textWidthRect = dayw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text day(sceneData.fonts.at(s));
        day.setString(std::to_string(st.wDay));
        day.setCharacterSize(fontSize);
        day.setFillColor(sf::Color::Red);
        day.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*3) ));
        sceneData.texts.push_back(day);

        //Hour
        sf::Text hourw(sceneData.fonts.at(s));
        hourw.setString("Hour : ");
        hourw.setCharacterSize(fontSize);
        hourw.setFillColor(sf::Color::Green);
        hourw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*4) ));
        sceneData.texts.push_back(hourw);

        textWidthRect = hourw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text hour(sceneData.fonts.at(s));
        hour.setString(std::to_string(st.wHour));
        hour.setCharacterSize(fontSize);
        hour.setFillColor(sf::Color::Red);
        hour.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*4) ));
        sceneData.texts.push_back(hour);

        //min
        sf::Text minutew(sceneData.fonts.at(s));
        minutew.setString("Min : ");
        minutew.setCharacterSize(fontSize);
        minutew.setFillColor(sf::Color::Green);
        minutew.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*5) ));
        sceneData.texts.push_back(minutew);

        textWidthRect = minutew.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text minute(sceneData.fonts.at(s));
        minute.setString(std::to_string(st.wMinute));
        minute.setCharacterSize(fontSize);
        minute.setFillColor(sf::Color::Red);
        minute.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*5) ));
        sceneData.texts.push_back(minute);

        //second
        sf::Text secondw(sceneData.fonts.at(s));
        secondw.setString("Sec : ");
        secondw.setCharacterSize(fontSize);
        secondw.setFillColor(sf::Color::Green);
        secondw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*6) ));
        sceneData.texts.push_back(secondw);

        textWidthRect = secondw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text second(sceneData.fonts.at(s));
        second.setString(std::to_string(st.wSecond));
        second.setCharacterSize(fontSize);
        second.setFillColor(sf::Color::Red);
        second.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*6) ));
        sceneData.texts.push_back(second);

        //millisecond
        sf::Text millisecondw(sceneData.fonts.at(s));
        millisecondw.setString("MilliSec : ");
        millisecondw.setCharacterSize(fontSize);
        millisecondw.setFillColor(sf::Color::Green);
        millisecondw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*7) ));
        sceneData.texts.push_back(millisecondw);

        textWidthRect = millisecondw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text millisecond(sceneData.fonts.at(s));
        millisecond.setString(std::to_string(st.wMilliseconds));
        millisecond.setCharacterSize(fontSize);
        millisecond.setFillColor(sf::Color::Red);
        millisecond.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*7) ));
        sceneData.texts.push_back(millisecond);

        //Processor Architecture
        sf::Text ProcessorArchitecturew(sceneData.fonts.at(s));
        ProcessorArchitecturew.setString("ProcessorArchitecture : " );
        ProcessorArchitecturew.setCharacterSize(fontSize);
        ProcessorArchitecturew.setFillColor(sf::Color::Green);
        ProcessorArchitecturew.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*8) ));
        sceneData.texts.push_back(ProcessorArchitecturew);

        textWidthRect = ProcessorArchitecturew.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text ProcessorArchitecture(sceneData.fonts.at(s));
        ProcessorArchitecture.setString(std::to_string(sysInfo.wProcessorArchitecture) );
        ProcessorArchitecture.setCharacterSize(fontSize);
        ProcessorArchitecture.setFillColor(sf::Color::Red);
        ProcessorArchitecture.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*8) ));
        sceneData.texts.push_back(ProcessorArchitecture);

        //Number of Processors
        sf::Text NumberofProcessorsw(sceneData.fonts.at(s));
        NumberofProcessorsw.setString("NumberOfProcessors : ");
        NumberofProcessorsw.setCharacterSize(fontSize);
        NumberofProcessorsw.setFillColor(sf::Color::Green);
        NumberofProcessorsw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*9) ));
        sceneData.texts.push_back(NumberofProcessorsw);

        textWidthRect = NumberofProcessorsw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text NumberofProcessors(sceneData.fonts.at(s));
        NumberofProcessors.setString(std::to_string(sysInfo.dwNumberOfProcessors));
        NumberofProcessors.setCharacterSize(fontSize);
        NumberofProcessors.setFillColor(sf::Color::Red);
        NumberofProcessors.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*9) ));
        sceneData.texts.push_back(NumberofProcessors);

        //Page Size
        sf::Text PageSizew(sceneData.fonts.at(s));
        PageSizew.setString("PageSize : ");
        PageSizew.setCharacterSize(fontSize);
        PageSizew.setFillColor(sf::Color::Green);
        PageSizew.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*10) ));
        sceneData.texts.push_back(PageSizew);

        textWidthRect = PageSizew.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text PageSize(sceneData.fonts.at(s));
        PageSize.setString(std::to_string(sysInfo.dwPageSize/1024.0f));
        PageSize.setCharacterSize(fontSize);
        PageSize.setFillColor(sf::Color::Red);
        PageSize.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*10) ));
        sceneData.texts.push_back(PageSize);

        //Memory in use
        sf::Text Memoryinusew(sceneData.fonts.at(s));
        Memoryinusew.setString("MemoryLoad : ");
        Memoryinusew.setCharacterSize(fontSize);
        Memoryinusew.setFillColor(sf::Color::Green);
        Memoryinusew.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*11) ));
        sceneData.texts.push_back(Memoryinusew);

        textWidthRect = Memoryinusew.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text Memoryinuse(sceneData.fonts.at(s));
        Memoryinuse.setString(std::to_string(memStatus.dwMemoryLoad/1024.0f));
        Memoryinuse.setCharacterSize(fontSize);
        Memoryinuse.setFillColor(sf::Color::Red);
        Memoryinuse.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*11) ));
        sceneData.texts.push_back(Memoryinuse);

        //Total physical memory
        sf::Text Totalphysicalmemoryw(sceneData.fonts.at(s));
        Totalphysicalmemoryw.setString("TotalPhys : ");
        Totalphysicalmemoryw.setCharacterSize(fontSize);
        Totalphysicalmemoryw.setFillColor(sf::Color::Green);
        Totalphysicalmemoryw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*12) ));
        sceneData.texts.push_back(Totalphysicalmemoryw);

        textWidthRect = Totalphysicalmemoryw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text Totalphysicalmemory(sceneData.fonts.at(s));
        Totalphysicalmemory.setString(std::to_string(memStatus.ullTotalPhys/1024.0f));
        Totalphysicalmemory.setCharacterSize(fontSize);
        Totalphysicalmemory.setFillColor(sf::Color::Red);
        Totalphysicalmemory.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*12) ));
        sceneData.texts.push_back(Totalphysicalmemory);

        //Available physical memory
        sf::Text Availablephysicalmemoryw(sceneData.fonts.at(s));
        Availablephysicalmemoryw.setString("AvailPhys : ");
        Availablephysicalmemoryw.setCharacterSize(fontSize);
        Availablephysicalmemoryw.setFillColor(sf::Color::Green);
        Availablephysicalmemoryw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*13) ));
        sceneData.texts.push_back(Availablephysicalmemoryw);

        textWidthRect = Availablephysicalmemoryw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text Availablephysicalmemory(sceneData.fonts.at(s));
        Availablephysicalmemory.setString(std::to_string(memStatus.ullAvailPhys/1024.0f));
        Availablephysicalmemory.setCharacterSize(fontSize);
        Availablephysicalmemory.setFillColor(sf::Color::Red);
        Availablephysicalmemory.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*13) ));
        sceneData.texts.push_back(Availablephysicalmemory);

        //Total virtual memory
        sf::Text Totalvirtualmemoryw(sceneData.fonts.at(s));
        Totalvirtualmemoryw.setString("TotalVirtual : ");
        Totalvirtualmemoryw.setCharacterSize(fontSize);
        Totalvirtualmemoryw.setFillColor(sf::Color::Green);
        Totalvirtualmemoryw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*14) ));
        sceneData.texts.push_back(Totalvirtualmemoryw);

        textWidthRect = Totalvirtualmemoryw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text Totalvirtualmemory(sceneData.fonts.at(s));
        Totalvirtualmemory.setString(std::to_string(memStatus.ullTotalVirtual/1024.0f));
        Totalvirtualmemory.setCharacterSize(fontSize);
        Totalvirtualmemory.setFillColor(sf::Color::Red);
        Totalvirtualmemory.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*14) ));
        sceneData.texts.push_back(Totalvirtualmemory);

        //Available virtual memory
        sf::Text Availablevirtualmemoryw(sceneData.fonts.at(s));
        Availablevirtualmemoryw.setString("AvailVirtual : ");
        Availablevirtualmemoryw.setCharacterSize(fontSize);
        Availablevirtualmemoryw.setFillColor(sf::Color::Green);
        Availablevirtualmemoryw.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*15) ));
        sceneData.texts.push_back(Availablevirtualmemoryw);

        textWidthRect = Availablevirtualmemoryw.getLocalBounds();
        textWidth = textWidthRect.size;

        sf::Text Availablevirtualmemory(sceneData.fonts.at(s));
        Availablevirtualmemory.setString(std::to_string(memStatus.ullAvailVirtual/1024.0f));
        Availablevirtualmemory.setCharacterSize(fontSize);
        Availablevirtualmemory.setFillColor(sf::Color::Red);
        Availablevirtualmemory.setPosition(sf::Vector2f(textWidth.x,0.0f+(spacing*15) ));
        sceneData.texts.push_back(Availablevirtualmemory);
    }

    //Here we run our time based simulations
    void update(float dt)
    {
        //time from system
        SYSTEMTIME st;
        GetSystemTime(&st);

        //CPU INFO
        SYSTEM_INFO sysInfo;

        //MEMORY INFO
        MEMORYSTATUSEX memStatus;

        //Get info on system
        GetSystemInfo(&sysInfo);
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);

        //Update
        sceneData.texts.at(1).setString(std::to_string(st.wYear));
        sceneData.texts.at(3).setString(std::to_string(st.wMonth));
        sceneData.texts.at(5).setString(std::to_string(st.wDay));
        sceneData.texts.at(7).setString(std::to_string(st.wHour));
        sceneData.texts.at(9).setString(std::to_string(st.wMinute));
        sceneData.texts.at(11).setString(std::to_string(st.wSecond));
        sceneData.texts.at(13).setString(std::to_string(st.wMilliseconds));
        sceneData.texts.at(15).setString(std::to_string(sysInfo.wProcessorArchitecture) );
        sceneData.texts.at(17).setString(std::to_string(sysInfo.dwNumberOfProcessors) );
        sceneData.texts.at(19).setString(std::to_string(sysInfo.dwPageSize));
        sceneData.texts.at(21).setString(std::to_string(memStatus.dwMemoryLoad));
        sceneData.texts.at(23).setString(std::to_string(memStatus.ullTotalPhys));
        sceneData.texts.at(25).setString(std::to_string(memStatus.ullAvailPhys));
        sceneData.texts.at(27).setString(std::to_string(memStatus.ullTotalVirtual));
        sceneData.texts.at(29).setString(std::to_string(memStatus.ullAvailVirtual));
    }

    void whileLoop(float dt, sf::RenderWindow* window)
    {
        //Clear window
        renderTexture.clear(sf::Color::Transparent);

        //Update all the internal scene dynamics
        update(dt);

        //SPRITES
        if (sceneData.sprites.size()!=0)
        {
            for(int i=0;i < sceneData.sprites.size();i++)
            {
                renderTexture.draw(sceneData.sprites.at(i));
            }
        }
        //RECT SHAPES
        if (sceneData.rectangleShapes.size()!=0)
        {
            for(int i=0;i < sceneData.rectangleShapes.size();i++)
            {
                renderTexture.draw(sceneData.rectangleShapes.at(i));
            }
        }
        //CIRCLE SHAPES
        if (sceneData.circleShapes.size()!=0)
        {
            for(int i=0;i < sceneData.circleShapes.size();i++)
            {
                renderTexture.draw(sceneData.circleShapes.at(i));
            }
        }
        //TEXTS
        if (sceneData.texts.size()!=0)
        {
            for(int i=0;i < sceneData.texts.size();i++)
            {
                renderTexture.draw(sceneData.texts.at(i));
            }
        }
        renderTexture.display();
        const sf::Texture& texture = renderTexture.getTexture();
        sf::Sprite sprite(texture);
        sprite.setPosition(sf::Vector2f(posX,posY));
        window->draw(sprite);
    }
private:

};

