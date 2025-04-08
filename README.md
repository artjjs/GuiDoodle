# :thumbsup: GUI fun SFML C++ :thumbsup:

## Simple overview :
1. Packed basic SFML window into a class
   - Scene Object
      - Chooses how the scene is drawn exactly
      - Creates a instance of the GUI class
2. Seperated event handling
   - Moved the keyboard handler and window events into there own file
3. Pack layout description into gui class
   - GUI class
      - Read .txt SUDO HTML for list of tags
      - Execute functions for given parameters for given tag
      - Run animations presented as tag parameters
   - Dependency
      - SFML-3.0.0
   - Compiler used : gcc-14.2.0-mingw-w64ucrt-12.0.0-r2

## TO DO :
## Allow a gui instance to point to other instances's renderTexture
## use said renderTexture as the image of a shape tag
## This would allow me to have index.txt SUDO HTML layout files for the layout of another gui's shape tag

## SUDO HTML :
## Allow any set of parameters defaulting to generic tag object for each undefined parameter :
![ScreenShot2](https://github.com/user-attachments/assets/400dd095-cef5-4be4-9b02-544e7ab74a9e)

## A few instances of my scene class with diffrent index.txt files positioned at each 4th of the screen :
![download2 (1)](https://github.com/user-attachments/assets/e9ed4f4e-8af9-4544-b50b-52f883e132b7)
