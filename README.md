# :thumbsup: Gui Doodle :thumbsup:
- Dependency
   - SFML-3.0.0
- Compiler used : gcc-14.2.0-mingw-w64ucrt-12.0.0-r2
## Simple overview :
### This project is currently in pre alpha stage :
1. Packed basic SFML window into a class ✔️
      - Have internal set of SFML objects to draw ✔️
      - Creates a instance / instances of the GUI class ✔️
      - Auto load all images in images folder ✔️
      - Draw the contents of a GUI class instance ✔️
      - Update animation logic and click responce per cycle ✔️
2. Seperated event handling ✔️
   - Moved the keyboard handler and window events into there own file ✔️
   - Have all keyboard keys report to console when even is thrown ✔️
   - Have window unfocus cause window to go semi transparent ✔️
3. Pack layout description into gui class ✔️
      - Read .txt SUDO HTML for list of tags ✔️
      - Read tag for parameter and value pairs ✔️
      - Create functions to execute actions for the following parameters ✔️
      -    animation✔️
      -    click responce✔️
      -    alignment✔️
      -    color✔️
      -    size✔️
      -    misc properties✔️
      -    ID and parent ID ✔️
      -    Have alignment to parent ✔️
      - Have layout file that uses sudo html ✔️
      - Read all images in images folder into memory for quick use ✔️
      - Package scene into it's own class ✔️
      - Create Gui class to execute the given sudo html tags ✔️
      - Have animation tags border pulse, hover, color pulse, rotate, wiggle, size pulse ✔️
      - Have any element able to respond to clicks ✔️
      - Have clickable cause start animation for shape ✔️
      - Have any animation be selectable as the click responce ✔️
        
   - TO DO :
      - Have life time for animation triggered by click
      - Have Gui class take pointer to another Gui classes rendertexture as a texture to use on shapes "Entire layout as shape's texture"
      - Create scroll boxes and drop down menus
      - Create scene swapping as click responce
      - Have size by % of screen or % of parent
      - Have a configurable map for what keys do what "Key mapping"
      - Refactor code
      - Fix freeze on resize issue
      - Create cmake build system
      - Make proof of use clone of a popular website's layout

## SUDO HTML :
## Allow any set of parameters defaulting to generic tag object for each undefined parameter :
#  This means you can randomly leave out tags or add usless ones with out issue.
# Even when a multi parameter system is missing a tag it just skips.
![ScreenShot2](https://github.com/user-attachments/assets/400dd095-cef5-4be4-9b02-544e7ab74a9e)

## A few instances of my scene class with diffrent index.txt files positioned at each 4th of the screen :
![download2 (1)](https://github.com/user-attachments/assets/e9ed4f4e-8af9-4544-b50b-52f883e132b7)
