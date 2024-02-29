Mouse and Cat Game - Daniel Dalal & Tzach Hondiashvili
Description

This is a simple console-based game where a mouse (you) tries to avoid being caught by cats. The goal is to survive as long as possible.

How to Play:

    Use arrow keys to move the mouse.
    Avoid the cats (^) on the board. 
    Collect keys "F" to open doors "D".
    Collect presents "$" to vanish a cat & gain points "^".
    Take all the cheeses "*" or finish all the levels to win.
    Skip a turn by pressing "Space".	
    Close the game by pressing "Escape".

How to add & change levels:

    Open Board.txt file: \oop1_ex02-\resources\board.txt
    Each level is seperated by empty line.
    Edit the world as you like!	

Run the game using the command: ./oop1_ex02

List of files:
	
	board.cpp & board.h -  
		 Implement the game board logic, including the movement of the mouse and cats, collision detection, and game state management.

	mouse.cpp & mouse.h -
		Define the behavior and attributes of the player-controlled mouse, handling its movement, interactions with the cats, and victory conditions.

	cat.cpp & cat.h -
		Specify the characteristics and actions of the cats, managing their movement patterns, interactions with the mouse, and handling their 			
		positions on the game board.

Algorithms:

	The cats use a combination of distance calculation, blocking strategies, and dynamic adaptation to engage with the mouse.
	The difficulty in countering their engagement increases with their ability to strategically position themselves and limit the mouse's available paths.
	The main idea is to move the cats closer to the mouse by calculating the x,y distanced from the mouse.
	The cat chooses the closest path to the mouse.

Object Oriented Design:

	Board Class:
		Manages the game board, handling the placement of the mouse, cats, and obstacles.
		It orchestrates the game flow, ensuring interaction between different elements.	
	Mouse Class:
		Represents the player-controlled mouse, tracking its position and providing methods for movement.
		It interacts with the board, cats, and other elements during the game.

	Cat Class:
		Models the behavior of the cats, including movement decisions based on the mouse's position and strategies for blocking the mouse's path.
		It interacts with the board and the mouse during gameplay.

Known Bugs:
	**OPEN TO BETA TESTING** ;)

License

	This project is licensed under the HAC students:
	Daniel Dalal - 211375324
	Tzach Hondiashvili - 212048037

Enjoy the game! 🐭🐾