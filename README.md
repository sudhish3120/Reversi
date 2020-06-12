# Reversi

## Introduction
Reversi, also called Othello, is a two player game that is played on a nxn board where n is an even number. The game uses tiles that are white on one side and black on the other side. One player plays white and the other player plays black. More details on how to play the game is posted on http://www.ludoteka.com/reversi-en.html. The game was programmed in C and the gameplay is played and displayed in the command line interface. 

## Layout and set-up 
The first component of this program is the layout and setting-up rules for gameplay. This involves checking legality of moves, handling special cases, flipping tiles with each turn, calculating all possible moves and so on. 

## Computer player 
The second component of this program is the generation of an algorithm that the computer can use to play against a human player (or another computer player). The computer player was programmed using a combination of the Game Tree algorithm and a composite scoring system. The scoring system outputs a score for each possible move on the board with the highest score being the most desirable move. It was built upon tactics used by professional players. 

