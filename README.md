# Real-time Chess Game and Chatting System with Assembly Language
- A two-player real-time chess game and chatting system implemented in Assembly language. The two PCs are connected through the serial port and use serial communication to exchange information.

## Features
- Connect 2 PCs through a Simple network, using serial communication
- Chatting between two players
- Two-player real-time chess game
- Inline chatting during playing chess
## How to run
- The program requires two PCs connected through a serial port. The user must enter a username that starts with a letter and is not more than 15 characters long. 

<img src="assets/Name.png" >

- After both users have entered their names, the main screen will appear, showing a list of available functionalities and how to navigate to each of them.
<img src="assets/Menu.png" >

## Chatting
- To start chatting, both users press F1 to start chatting. The screen is divided into two halves, with the first half showing data written by the current user and the second half showing data sent by the second user.

<img src="assets/Chat.png" >



## Real-time Chess Game
- To start the chess game, both users press F2 to start the game. The game is like standard chess, with each piece moving exactly like standard chess. The only difference is that there are no turns, which means one player can move multiple pieces while the other player does not move any pieces. There is a 3 seconds countdown for each piece to be moved again. The game takes up the whole screen, leaving the right part of the screen for inline chatting and notifications.

<img src="assets/Game.png" >


## Requirements
- Two PCs connected through the serial port
- Assembly language compiler
