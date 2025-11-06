# Worm Vircon32
![screenshot 1](screenshots/screenshot1.png)  ![screenshot 2](screenshots/screenshot2.png)

This is my [Vircon32 fantasy console](http://www.vircon32.com/) worm game, which is a remake of the classic copter / worm game with multiple gameplay modes

## Controls

| Key        | Action                                        |
|------------|-----------------------------------------------|
| A          | Start GAME, Repeadetly tap to move Worm       |
| LEFT/RIGHT | Select Game Mode on Titlescreen               |
| UP/DOWN    | Select Level on Titlescreen                   |
| L/R        | Select Level, increases or decreases by 10    |
| START      | Holding Start for half a second resets scores |

## Aim of the game
Repeadetly Press / hold A button to move the worm around, dont hit obstacles and walls, try to gain highest score.

## High Scores
High Scores are only saved for levels 1 to 99 per game mode. If you select rnd2 levels, it will also select levels randomly higher than 99 but those all share a common highscore.
If you want to compete with friends select a level manually to compare scores.

## Seed System
The game has a seed system, you can choose a number between 1 and 99 for the seed.
Selecting Rnd1 will select random levels between 1 and 99 on every (re)start, where highscore is saved for them.
Rnd2 will also select random levels higher than 99 but it will use a common highscore for these levels. This is similar to how it was initially implemented in the previous Vircon32 version.
It allows you to play random levels different from the fixed 99 ones.

## Game Modes
There are 5 Game modes to play on, each with their own specifics

### Mode A
- decreasing space for the worm to move in
- 5 obstacles
- Constant slower speed

### Mode B
- Fixed space for the worm to move in
- No obstacles
- Increasing speed

### Mode C
- Fixed space for the worm to move in
- 2 obstacles
- Increasing speed 

### Mode D
- Decreasing space for the worm to move in
- No obstacles
- Increasing speed

### Mode E
- Pacman mode: Collect the yellow squares, missing one is game over
- Fixed space for the worm to move in
- No obstacles
- Constant slower speed

## History

### V1.1
- Fixed 99 levels so people can play same levels
- RND1 (random level between level 1 & 99)
- RND2 (random level but higher than 99 also this is how version 1.0 worked)
- Highscores for first 99 levels per game mode
- global, shared highscore for levels > 99, this is how version 1.0 worked
- Fixed tunnel gaps appearing, removed addition of tunnelspeed when creating new tunnelsections, all tunnel sections adhere to tunnelsectionwidth
- UP/DOWN increases / Decreases level by 1
- L/R increases / decreases level 10
- Better collision checking, it now checks also on intersections instead of player being fully inside somewhere (like a wall, obstacle, or collectable)
- Obstaclewidth increased from 8 to 10 to make sure we can't fly through it
- Speed optimazations (not that they were required but it can help on lower specced devices not being able to run the vircon32 core full speed)
- Renamed "Seed" to "Lvl" to make it more clear

## Credits
The game was made possible after watching this youtube movie: [https://www.youtube.com/watch?v=W-3okcjOFnY](https://www.youtube.com/watch?v=W-3okcjOFnY)

## License
* License of my part of game's code is MIT
* Game uses DrawPrimitives and TextFonts from [@vircon32](https://www.github.com/vircon32) in libs dir it's license is 3-Clause BSD License.
* game uses a font Asset (TextureFont22x32.png) created by [@vircon32](https://www.github.com/vircon32) provided under CC BY 4.0 License
