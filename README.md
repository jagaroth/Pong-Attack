Lilygo T-Embed game

Game play:
It's a bit like Pong but you can also shoot at your opponent etc.
Collect the different coloured diamonds to add additional weaponry, change bat size or add additional balls.
You can only collect diamonds floating towards your direction from the other side of the screen, not the diamonds floating towards your opponent.

Written by Jus Godden 2025
https://www.youtube.com/watch?v=6fcaI3d6fmU

This is a work in progress.
Do feel free to contribute or fork.

Developed using Arduino IDE

To compile. First follow the Arduino IDE configuration guide found on this page...
https://github.com/Xinyuan-LilyGO/T-Embed-CC1101
(instructions are for Windows, I used Ubuntu).
Then in the library file "libraries/TFT_eSPI/User_Setup_Select.h"
Add this line near the top...
#define USE_HSPI_PORT 1
