# Console Minecraft 1.0.0

## Description

This is Console Minecraft. It is a C++ console application where you can do various Minecraft inspired things. All of it follows the real Minecraft logic such as tick mechanics, dailylight cycle, and etc. Has only a few features at the moment but I will definitely be adding more in the future!

## Commands/Features

The app fully follows Minecrafts day/night system, that being 24,000 ticks for one whole minecraft day with a tick happening every .05 seconds. It follows Minecraft Bedrock logic which means one game tick, ticks 3 blocks (randomTickSpeed).

Below are the current commands you can do in the app:
- G - Place Grass: Click anywhere to place the one grass block. If the grass is ticked, it will spread to a nearby dirt block if applicable.
- M - Place Mycelium: Same logic as grass. 
- W - Place Wheat: This will place a whole wheat field. Start with clicking where you want the top left of your field to be, then click where you want the bottom right part to be. Follows the logic of dry wheat (non hydrated soil).
Up/Down Keys - Change Speed: This will change randomTickSpeed by multiples of 5 to increase the speed of the game. 

![Screenshot 2025-03-13 at 10 11 17 AM](https://github.com/user-attachments/assets/5e7e773d-d540-47c9-998f-cdf4bd72c141)
(Image of a growing wheat field surrounded by grass)

## Running the App

Download all the code, navigate to the directory and type "make brun". This will compile all the files and run the program. You will most likely have to download ncurses if you haven't already. Currently only works on Mac because of the Usleep function. Can easily be swapped out however. 

### Updates

1.0.0 (03/13/25):
- App set up. 
- Main interface for the app created.
- Added Grass and Mycelium.
- Logging system added.
- Added Wheat fields.
- Day/Night cycle added with visual.

### Plans for Future
This is just a small personal list for me to keep track of what I want to add and what I have already added. 

- Add passive mobs (Sheep, Cow, Etc)
- Add Builder NPC
- Add stone
- Add water
- Add color war fun mode
- Add Farmer NPC
- (Done 02/25/25) Add Grass and Mycelium 
- (Done 03/04/25) Add a logging system, log everything and put in textfile
- (Done 03/04/25) Get main interface completed
- (Done 03/08/25) Add time elapsed
- (Done 03/11/25) Improve time elapsed
- (Done 03/11/25) Add wheat field placeable. 
