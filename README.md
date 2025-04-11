# :thumbsup: Gui Doodle :thumbsup:

## Simple overview :
### This project is currently in pre alpha stage :
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
      - Run a function as Click responce when clickable parameter exists
   - Dependency
      - SFML-3.0.0
   - Compiler used : gcc-14.2.0-mingw-w64ucrt-12.0.0-r2

   - TO DO :
      - Have layout file that uses sudo html ✔️
      - Read all images in images folder into memory for quick use ✔️
      - Package scene into it's own class ✔️
      - Create Gui class to execute the given sudo html tags ✔️
      - Have animation tags border pulse, hover, color pulse, rotate, wiggle, size pulse ✔️
      - Have any element able to respond to clicks ✔️
      - Have temp animation for click responces
      - Have Gui class take pointer to another Gui classes rendertexture as a texture to use on shapes "Entire layout as shape's texture"
      - Create scene swapping as click responce
      - Fix freeze on resize issue
      - Create cmake build system
      - Make proof of use clone of a popular website's layout

## SUDO HTML :
## Allow any set of parameters defaulting to generic tag object for each undefined parameter :
![ScreenShot2](https://github.com/user-attachments/assets/400dd095-cef5-4be4-9b02-544e7ab74a9e)

## A few instances of my scene class with diffrent index.txt files positioned at each 4th of the screen :
![download2 (1)](https://github.com/user-attachments/assets/e9ed4f4e-8af9-4544-b50b-52f883e132b7)
