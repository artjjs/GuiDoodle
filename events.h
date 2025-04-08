
void events(sf::RenderWindow* window,float* screenx, float* screeny,sf::Vector2f* windowSize,sf::Vector2f* windowMiddle,float* mouseWheelSpeed,int* pause, sf::WindowHandle* hWnd)
{

    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window->close();
        }
        else if (event->is<sf::Event::Resized>())
        {
            const auto* resized = event->getIf<sf::Event::Resized>();
            //Reset all my window size vars to actual window size
            *screenx=resized->size.x;
            *screeny=resized->size.y;
            *windowSize = (sf::Vector2f (*screenx,*screeny));
            *windowMiddle = (sf::Vector2f (*screenx/2.0f,*screeny/2.0f));
            std::cout << "WindowSize (" << windowSize->x << "," << windowSize->y << ")" << std::endl;
            //Change the window into a rounded window after resize
            //HRGN hRgn = CreateRoundRectRgn(0, 0, *screenx, *screeny, 150.0f, 150.0f); // Adjust size and radius as needed
            //SetWindowRgn(*hWnd, hRgn, true);
        }
        //TRACK MOUSE
        else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
        {
            sf::Vector2f mouseCurrentPos = sf::Vector2f(mouseMoved->position.x, mouseMoved->position.y);
        }
        //Track mouse wheel
        if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            switch (mouseWheelScrolled->wheel)
            {
            case sf::Mouse::Wheel::Vertical:
                std::cout << "wheel type: vertical" << std::endl;
                break;
            case sf::Mouse::Wheel::Horizontal:
                std::cout << "wheel type: horizontal" << std::endl;
                break;
            }
            std::cout << "(" << mouseWheelScrolled->delta << ") ";
            *mouseWheelSpeed = mouseWheelScrolled->delta;
        }
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
                std::cout << "the right button was pressed" << std::endl;
                sf::Vector2f mouseClickPosRight = sf::Vector2f(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
            }
            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "the left button was pressed" << std::endl;
                sf::Vector2f mouseClickPosLeft = sf::Vector2f(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
            }
            if (mouseButtonPressed->button == sf::Mouse::Button::Middle)
            {
                std::cout << "the middle button was pressed" << std::endl;
                sf::Vector2f mouseClickPosMiddle = sf::Vector2f(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
            }
        }
        else if (event->is<sf::Event::FocusLost>())
        {
        //SET THE WINDOW TO HAVE BLACK AS ALPHA CHANNEL KEY
        float transparency_value=0.5f;
        //SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        //SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 220, LWA_COLORKEY | LWA_ALPHA);
        //JUST SET ENTIRE WINDOW TO SOME AMOUNT OF TRANSPARENT
        SetLayeredWindowAttributes(*hWnd, 0, 90, LWA_ALPHA);
            *pause=0;
        }
        else if (event->is<sf::Event::FocusGained>())
        {
            float transparency_value=0.5f;
            SetWindowLong(*hWnd, GWL_EXSTYLE, GetWindowLong(*hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
            SetLayeredWindowAttributes(*hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
            *pause=1;
        }
        //Keyboard
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            //KEYBOARD KEYS
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                std::cout << "the Escape key was pressed" << std::endl;
                window->close();
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
            {
                std::cout << "the Enter key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Tab)
            {
                std::cout << "the Tab key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::LShift)
            {
                std::cout << "the Left Shift key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::RShift)
            {
                std::cout << "the Right Shift key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::LControl)
            {
                std::cout << "the Left Ctrl key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::RControl)
            {
                std::cout << "the Right Ctrl key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::LAlt)
            {
                std::cout << "the Left Alt key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::RAlt)
            {
                std::cout << "the Right Alt key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::CapsLock)
            {
                std::cout << "the CapsLock key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Backspace)
            {
                std::cout << "the Backspace key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Insert)
            {
                std::cout << "the Insert key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Delete)
            {
                std::cout << "the Delete key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::PrintScreen)
            {
                std::cout << "the PrintScreen key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Pause)
            {
                std::cout << "the Pause key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumLock)
            {
                std::cout << "the NumLock key was pressed" << std::endl;
            }
            //LETTERS
            if (keyPressed->scancode == sf::Keyboard::Scancode::Q)
            {
                std::cout << "the Q key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::W)
            {
                std::cout << "the W key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::A)
            {
                std::cout << "the A key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::S)
            {
                std::cout << "the S key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::D)
            {
                std::cout << "the D key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::E)
            {
                std::cout << "the E key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::R)
            {
                std::cout << "the R key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::T)
            {
                std::cout << "the T key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Y)
            {
                std::cout << "the Y key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::U)
            {
                std::cout << "the U key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::I)
            {
                std::cout << "the I key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::O)
            {
                std::cout << "the O key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::P)
            {
                std::cout << "the P key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F)
            {
                std::cout << "the F key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::G)
            {
                std::cout << "the G key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::H)
            {
                std::cout << "the H key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::J)
            {
                std::cout << "the J key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::K)
            {
                std::cout << "the K key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::L)
            {
                std::cout << "the L key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Z)
            {
                std::cout << "the Z key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::X)
            {
                std::cout << "the X key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::C)
            {
                std::cout << "the C key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::V)
            {
                std::cout << "the V key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::B)
            {
                std::cout << "the B key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::N)
            {
                std::cout << "the N key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::M)
            {
                std::cout << "the M key was pressed" << std::endl;
            }
            //Numbers
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num0)
            {
                std::cout << "the 0 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num1)
            {
                std::cout << "the 1 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num2)
            {
                std::cout << "the 2 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num3)
            {
                std::cout << "the 3 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num4)
            {
                std::cout << "the 4 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num5)
            {
                std::cout << "the 5 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num6)
            {
                std::cout << "the 6 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num7)
            {
                std::cout << "the 7 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num8)
            {
                std::cout << "the 8 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Num9)
            {
                std::cout << "the 9 key was pressed" << std::endl;
            }
            //CHARS
            if (keyPressed->scancode == sf::Keyboard::Scancode::Grave)
            {
                std::cout << "the ` key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Hyphen)
            {
                std::cout << "the - key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Equal)
            {
                std::cout << "the = key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::LBracket)
            {
                std::cout << "the [ key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::RBracket)
            {
                std::cout << "the ] key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Semicolon)
            {
                std::cout << "the ; key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Apostrophe)
            {
                std::cout << "the ' key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Comma)
            {
                std::cout << "the , key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Period)
            {
                std::cout << "the . key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Slash)
            {
                std::cout << "the / key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Backslash)
            {
                std::cout << "the \\ key was pressed" << std::endl;
            }
            //Numpad
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadMinus)
            {
                std::cout << "the NumPad - key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadMinus)
            {
                std::cout << "the NumPad + key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad1)
            {
                std::cout << "the NumPad 1 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad2)
            {
                std::cout << "the NumPad 2 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad3)
            {
                std::cout << "the NumPad 3 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad4)
            {
                std::cout << "the NumPad 4 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad5)
            {
                std::cout << "the NumPad 5 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad6)
            {
                std::cout << "the NumPad 6 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad7)
            {
                std::cout << "the NumPad 7 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad8)
            {
                std::cout << "the NumPad 8 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad9)
            {
                std::cout << "the NumPad 9 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Numpad0)
            {
                std::cout << "the NumPad 0 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadDecimal)
            {
                std::cout << "the NumPad . key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadEnter)
            {
                std::cout << "the NumPad Enter key was pressed" << std::endl;
            }
            //F KEYS
            if (keyPressed->scancode == sf::Keyboard::Scancode::F1)
            {
                std::cout << "the F1 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F2)
            {
                std::cout << "the F2 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F3)
            {
                std::cout << "the F3 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F4)
            {
                std::cout << "the F4 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F5)
            {
                std::cout << "the F5 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F6)
            {
                std::cout << "the F6 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F7)
            {
                std::cout << "the F7 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F1)
            {
                std::cout << "the F1 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F8)
            {
                std::cout << "the F8 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F9)
            {
                std::cout << "the F9 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F10)
            {
                std::cout << "the F10 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F11)
            {
                std::cout << "the F11 key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::F12)
            {
                std::cout << "the F12 key was pressed" << std::endl;
            }
            //ARROW Keys
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
            {
                std::cout << "the Up key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
            {
                std::cout << "the Down key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
            {
                std::cout << "the Left key was pressed" << std::endl;
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
            {
                std::cout << "the Right key was pressed" << std::endl;
            }
        }
    }
}
