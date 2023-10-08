# ASGF
Build on top of the framework by expanding the Game class. 
User input can be retrieved via the Input singleton. 
Use Text and Texture classes to draw to screen. Each must call Render() to be draw. Uses painter's method. 

Put image files in /Assets/Sprites/ 
Put font files in /Assets/Fonts/ 
Fonts can be pre-loaded using Text::LoadFont(...) 

Dependencies:
- SDL
- SDL image
- SDL ttf
