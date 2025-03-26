"Pong Attack"
A game for the Lilygo T-Embed
https://lilygo.cc/products/t-embed-cc1101

Game written by Jus Godden 2025

Game play:
It's a bit like Pong but you can also shoot at your opponent etc.
Collect the different coloured diamonds to add additional weaponry, change bat size or add additional balls.
Note that diamonds may also remove weapons and return bat size to default size.
You can only collect diamonds floating towards your direction from the other side of the screen, not the diamonds floating towards your opponent.
Getting shot enough times may also remove additional weaponry.

Scoring:
3 hits with a weapon is a point to the opposition. Failing to return the ball is also a point to the opposition.
As per common competition table tennis rules, first to reach 11 points or higher with at least 2 points difference between scores wins a game.
Thus a game might continue on past 11 points until a player reaches 2 points higher than their opponent.

A video demonstrating the game can be found here...
https://www.youtube.com/watch?v=6fcaI3d6fmU

This is a work in progress.
Do feel free to contribute or fork.

Developed using Arduino IDE and a Lilygo T-Embed CC1101

To compile. First follow the Arduino IDE configuration guide found on this page...
https://github.com/Xinyuan-LilyGO/T-Embed-CC1101
(instructions are for Windows, I used Ubuntu).
Then in the library file "libraries/TFT_eSPI/User_Setup_Select.h"
Add this line near the top...
#define USE_HSPI_PORT 1
