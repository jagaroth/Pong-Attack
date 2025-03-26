Lilygo T-Embed game

Written by Jus Godden 2025

This is a work in progress.
Do feel free to contribute or fork.

Developed using Arduino IDE

To compile. First follow the Arduino IDE configuration guide found on this page...
https://github.com/Xinyuan-LilyGO/T-Embed-CC1101
(instructions are for Windows, I used Ubuntu).
Then in the library file "libraries/TFT_eSPI/User_Setup_Select.h"
Add this line near the top...
#define USE_HSPI_PORT 1
