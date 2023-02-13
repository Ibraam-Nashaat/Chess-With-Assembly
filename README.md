# Real-time Chess Game and Chatting System with Assembly Language
- A two-player real-time chess game and chatting system implemented in Assembly language. The two PCs are connected through the serial port and use serial communication to exchange information. The application runs in console mode and makes use of video-RAM functionalities for a graphical presentation.

## Features
- Connect 2 PCs through a Simple network, using serial communication
- Chatting between two players
- Two-player real-time chess game
## How to run
- The program requires two PCs connected through a serial port. The user must enter a username that starts with a letter and is not more than 15 characters long. After both users have entered their names, the main screen will appear, showing a list of available functionalities and how to navigate to each of them.

## Chatting
- To start chatting, one of the users presses F1 to send a chat invitation. The invitation appears in the notification bar on the main screen of both machines. Once the other user accepts the invitation by pressing F1, both users enter the chatting mode. The screen is divided into two halves, with the first half showing data written by the current user and the second half showing data sent by the second user.

## Real-time Chess Game
- To start the chess game, one of the users presses F2 to send a game invitation. The invitation appears in the notification bar on the main screen of both machines. Once the other user accepts the invitation by pressing F2, the game starts. The game is like standard chess, with each piece moving exactly like standard chess. The only difference is that there are no turns, which means one player can move multiple pieces while the other player does not move any pieces. There is a countdown for each piece to be moved again. The game takes up the whole screen, leaving the lower part of the screen for inline chatting, usernames, and game time.

## Requirements
- Two PCs connected through the serial port
- Assembly language compiler
