    //==================================================================================================
    //time from system
    SYSTEMTIME st;
    //CPU INFO
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    //MEMORY INFO
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx(&memStatus);
    //spacing for text
    float spacing= fontSize+4;
    //Year
    sf::Text year(font);
    year.setString(std::to_string(st.wYear));
    year.setCharacterSize(fontSize);
    year.setFillColor(sf::Color::Red);
    year.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*1) ));
    //Month
    sf::Text month(font);
    month.setString(std::to_string(st.wMonth));
    month.setCharacterSize(fontSize);
    month.setFillColor(sf::Color::Red);
    month.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*2) ));
    //Day
    sf::Text day(font);
    day.setString(std::to_string(st.wDay));
    day.setCharacterSize(fontSize);
    day.setFillColor(sf::Color::Red);
    day.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*3) ));
    //Hour
    sf::Text hour(font);
    hour.setString(std::to_string(st.wHour));
    hour.setCharacterSize(fontSize);
    hour.setFillColor(sf::Color::Red);
    hour.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*4) ));
    //min
    sf::Text minute(font);
    minute.setString(std::to_string(st.wMinute));
    minute.setCharacterSize(fontSize);
    minute.setFillColor(sf::Color::Red);
    minute.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*5) ));
    //second
    sf::Text second(font);
    second.setString(std::to_string(st.wSecond));
    second.setCharacterSize(fontSize);
    second.setFillColor(sf::Color::Red);
    second.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*6) ));
    //millisecond
    sf::Text millisecond(font);
    millisecond.setString(std::to_string(st.wMilliseconds));
    millisecond.setCharacterSize(fontSize);
    millisecond.setFillColor(sf::Color::Red);
    millisecond.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*7) ));
    //Processor Architecture
    sf::Text ProcessorArchitecture(font);
    ProcessorArchitecture.setString("ProcessorArchitecture: " + std::to_string(sysInfo.wProcessorArchitecture) );
    ProcessorArchitecture.setCharacterSize(fontSize);
    ProcessorArchitecture.setFillColor(sf::Color::Red);
    ProcessorArchitecture.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*8) ));
    //Number of Processors
    sf::Text NumberofProcessors(font);
    NumberofProcessors.setString("Number of Processors: " + std::to_string(sysInfo.dwNumberOfProcessors));
    NumberofProcessors.setCharacterSize(fontSize);
    NumberofProcessors.setFillColor(sf::Color::Red);
    NumberofProcessors.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*9) ));
    //Page Size
    sf::Text PageSize(font);
    PageSize.setString("Page Size: " + std::to_string(sysInfo.dwPageSize));
    PageSize.setCharacterSize(fontSize);
    PageSize.setFillColor(sf::Color::Red);
    PageSize.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*10) ));
    //Memory in use
    sf::Text Memoryinuse(font);
    Memoryinuse.setString("Memory in use: " + std::to_string(memStatus.dwMemoryLoad));
    Memoryinuse.setCharacterSize(fontSize);
    Memoryinuse.setFillColor(sf::Color::Red);
    Memoryinuse.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*11) ));
    //Total physical memory
    sf::Text Totalphysicalmemory(font);
    Totalphysicalmemory.setString("Total physical memory: " + std::to_string(memStatus.ullTotalPhys));
    Totalphysicalmemory.setCharacterSize(fontSize);
    Totalphysicalmemory.setFillColor(sf::Color::Red);
    Totalphysicalmemory.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*12) ));
    //Available physical memory
    sf::Text Availablephysicalmemory(font);
    Availablephysicalmemory.setString("Available physical memory: " + std::to_string(memStatus.ullAvailPhys));
    Availablephysicalmemory.setCharacterSize(fontSize);
    Availablephysicalmemory.setFillColor(sf::Color::Red);
    Availablephysicalmemory.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*13) ));
    //Total virtual memory
    sf::Text Totalvirtualmemory(font);
    Totalvirtualmemory.setString("Total virtual memory: " + std::to_string(memStatus.ullTotalVirtual));
    Totalvirtualmemory.setCharacterSize(fontSize);
    Totalvirtualmemory.setFillColor(sf::Color::Red);
    Totalvirtualmemory.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*14) ));
    //Available virtual memory
    sf::Text Availablevirtualmemory(font);
    Availablevirtualmemory.setString("Available virtual memory: " + std::to_string(memStatus.ullAvailVirtual));
    Availablevirtualmemory.setCharacterSize(fontSize);
    Availablevirtualmemory.setFillColor(sf::Color::Red);
    Availablevirtualmemory.setPosition(sf::Vector2f(0.0f,0.0f+(spacing*15) ));

    //==================================================================================================
