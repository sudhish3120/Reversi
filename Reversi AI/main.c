//
//  main.c
//  Lab8Part2
//
//  Created by Sudhish M on 2020-03-23.
//  Copyright © 2020 Sudhish. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>



void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool checkLegalAllDirections(char board[][26], int n, char colour, char storeUPos[][2], int rowsOfStoreUPos);

void determineDirectionsForFlip(char board[][26], int n, int row, int col, char colour, bool* N, bool* S, bool* E, bool* W, bool* NE, bool* NW, bool* SE, bool* SW);
void flipInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);

bool playMove (int n, char board[][26], char colour, char userRow, char userCol);
void positionSelectedByComp(int n, char board[][26], char colour, char* compRow, char* compCol);

int computeScoreInOneDirec(int n, char board[][26], char colour, int row, int col, int deltaRow, int deltaCol);
int computeScoreInAllDirec(int n, char board[][26], int row, int col, char colour);

bool checkForAnyValidPos(int n, char board[][26], char colour);
char mostPiecesOnBoard(int n, char board[][26]);
bool UnoccupiedPosInBoard(int n, char board[][26]);
bool checkForWinLoseOrDraw (int n, char board[][26]);

int NumOfOpponentMoves (int n, char board[][26], char colour, int row, int col);
bool playMoveMod (int n, char board[][26], char colour, char userRow, char userCol);
int scoreCornerPos(int n, char board [][26], int row, int col, char colour);

//determine all valid positions for a given colour-unoccupied pos array and filter
//compute score for each position
//add all of the scores
//if score==0, then no valid positions

int main() {
    
 int n;
        char comPlays;
        
        int i,j;
          char board[26][26];
          char white='W';
          char black='B';
        
        printf("Enter the board dimension: ");
        scanf("%d", &n);
        
        printf("Computer plays (B/W): ");
        scanf(" %c", &comPlays);
        
        for (i=0;i<n;i++) {
            for (j=0;j<n;j++) {
               board[i][j]='U';
            }
        }
           
        board[n/2-1][n/2-1]=white;
        board[n/2-1][n/2]=black;
        board[n/2][n/2-1]=black;
        board[n/2][n/2]=white;
           
        printBoard(board,n);
        
    
    //Do I need to check if comPlays is either black or white? what if its something else?
    
    if (comPlays==white) { //CASE 1
    //Human player gets first turn (black)
//        int sRow;
//        int sCol;
        char userRow;
        char userCol;
        printf("Enter move for colour B (RowCol): ");
//        findSmartestMove(board, n, black, &sRow, &sCol);
//        findSmarterMove(board, n, black, &sRow, &sCol);
       scanf(" %c%c", &userRow, &userCol);
//        printf("Testing AI move (row, col): %c%c\n", sRow + 'a', sCol + 'a');
//        userRow='a'+sRow;
//        userCol='a'+sCol;
        bool invMove=playMove (n, board, black, userRow, userCol);
        
        if (invMove==false) {
            printf("W player wins.\n");
            return 0;
        }

    } else { //comp is black. CASE 2
        char compRow, compCol;
        positionSelectedByComp(n,board, black, &compRow, &compCol);
        printf("Computer places B at %c%c.\n", compRow, compCol);
        playMove (n, board, black, compRow, compCol);
    }
    
    
    
    
    if (comPlays==white) { //CASE 1
        // it is now computer's turn
        char compRow, compCol;
        char userRow, userCol;
//        int sRow;
//        int sCol;
        
        
        for (i=0; ;i++) {
            
       
            if (checkForWinLoseOrDraw (n, board)) {
                return 0;
            }
            
            if (checkForAnyValidPos(n, board, white)==false) {
                printf("W player has no valid move.\n");
                } else {
            positionSelectedByComp(n,board,white,&compRow,&compCol);
            printf("Computer places W at %c%c.\n", compRow, compCol);
            playMove (n, board, white, compRow, compCol);
            }
            
            if (checkForWinLoseOrDraw (n, board)) {
                return 0;
            }
            //When the human player has no more moves. returns true if moves available. returns false when no move available
            if (checkForAnyValidPos(n, board, black)==false) {
                printf("B player has no valid move.\n");
            } else {
            printf("Enter move for colour B (RowCol): ");
//                findSmartestMove(board, n, black, &sRow, &sCol);
//                findSmarterMove(board, n, black, &sRow, &sCol);
            scanf(" %c%c", &userRow, &userCol);
//                printf("Testing AI move (row, col): %c%c\n", sRow + 'a', sCol + 'a');
//                userRow='a'+sRow;
//                userCol='a'+sCol;
            bool invMove=playMove(n,board,black,userRow,userCol);
            if (invMove==false) {
                printf("W player wins.\n");
                return 0;
                    }
                
                }
            
        }
        
    } else { //where computer is black. It is now human player's turn. CASE 2
           
        char compRow, compCol;
        char userRow, userCol;
//        int sRow;
//        int sCol;
        
        for (i=0; ;i++) {
            
            if (checkForWinLoseOrDraw (n, board)) {
                return 0;
            }
            if (checkForAnyValidPos(n, board, white)==false) {
                printf("W player has no valid move.\n");
            } else {
            printf("Enter move for colour W (RowCol): ");
//                findSmartestMove(board, n, white, &sRow, &sCol);
//                findSmarterMove(board, n, white, &sRow, &sCol);
//                printf("Testing AI move (row, col): %c%c\n", sRow + 'a', sCol + 'a');
            scanf(" %c%c", &userRow, &userCol);
//                userRow='a'+sRow;
//                userCol='a'+sCol;
            bool invMove=playMove(n,board,white,userRow,userCol);
            if (invMove==false) {
                printf("B player wins.\n");
                return 0;
                }
            }
            
            if (checkForWinLoseOrDraw (n, board)) {
                return 0;
            }
            if (checkForAnyValidPos(n, board, black)==false) {
                printf("B player has no valid move.\n");
            } else {
            positionSelectedByComp( n, board, black, &compRow, &compCol);
            printf("Computer places B at %c%c.\n", compRow, compCol);
            playMove (n, board, black, compRow, compCol);
            
                }
            
            }
            
        }
        
   
    
    
    return 0;
}






//FUNCTIONS


void printBoard(char board[][26], int n) {
    int i, j;
    printf("  ");
    for (i=0;i<n;i++) {
        printf("%c",'a'+i);
    }
    printf("\n");
    for (i=0;i<n;i++) {
        printf("%c ",'a'+i);
        for (j=0;j<n;j++) {
            printf("%c",board[i][j]);
        }
        printf("\n");
    }

}


bool positionInBounds(int n, int row, int col) { //passing in actual indices
    if (row>n-1 || row<0) {
        return false;
    } else if (col>n-1 || col<0) {
        return false;
    } else {
        return true;
    }
}

//The inputs have to be the actual positions of the array not the positions of the board
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int i;
    if (board[row+deltaRow][col+deltaCol]==colour || board[row+deltaRow][col+deltaCol]=='U' || !positionInBounds(n, row+deltaRow, col+deltaCol)) {
        return false;
    } else {
        for(i=2; ;i++) { //starting with one is redundant because we checked already that at this position there is an opponent colour
            if(board[row+deltaRow*i][col+deltaCol*i]=='U' || !positionInBounds(n, row+deltaRow*i, col+deltaCol*i)) {
                return false;
            } else if (board[row+deltaRow*i][col+deltaCol*i]==colour) {
                return true;
            } else {
                continue;
            }
        }
        
    }
}

bool checkLegalAllDirections(char board[][26], int n, char colour, char storeUPos[][2], int rowsOfStoreUPos) { //rowStoreUPos is i that is incrementing the main function

if (checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, -1, 0)==true  ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, 1, 0)==true   ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, 0, 1)==true   ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, 0, -1)==true  ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, -1, 1)==true  ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, -1, -1)==true ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, 1, 1)==true   ||
    checkLegalInDirection(board, n, storeUPos[rowsOfStoreUPos][0]-'a', storeUPos[rowsOfStoreUPos][1]-'a', colour, 1, -1)==true  ) {
    return true;
    }
    else {
        return false;
    }

}

void determineDirectionsForFlip(char board[][26], int n, int row, int col, char colour, bool* N, bool* S, bool* E, bool* W, bool* NE, bool* NW, bool* SE, bool* SW) {
    //the received row and col are actual indices
    
    if (checkLegalInDirection(board, n, row, col, colour, -1, 0)==true)   //checking N
        *N=true;
    if (checkLegalInDirection(board, n, row, col, colour, 1, 0)==true)   //checking S
        *S=true;
    if (checkLegalInDirection(board, n, row, col, colour, 0, 1)==true)    //checking E
        *E=true;
    if (checkLegalInDirection(board, n, row, col, colour, 0, -1)==true)   //checking W
        *W=true;
    if (checkLegalInDirection(board, n, row, col, colour, -1, 1)==true)   //checking NE
        *NE=true;
    if (checkLegalInDirection(board, n, row, col, colour, -1, -1)==true)  //checking NW
        *NW=true;
    if (checkLegalInDirection(board, n, row, col, colour, 1, 1)==true)    //checking SE
        *SE=true;
    if (checkLegalInDirection(board, n, row, col, colour, 1, -1)==true)   //checking SW
        *SW=true;
                    
}

void flipInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) { //row & col refer to actual indices of the matrix
    int i;
    for (i=1; ;i++) {
        if (board[row+deltaRow*i][col+deltaCol*i]==colour)
            break;
        board[row+deltaRow*i][col+deltaCol*i]=colour;
        
    }
    
}

//the below function generates a list of valid moves and checks if the inputted move matches one of the given moves. If it does, it makes the move, returns true and prints the board, if it does not, it returns false
bool playMove (int n, char board[][26], char colour, char userRow, char userCol) { //had to make playMove return bool to ensure that the position entered is valid
    
    int i,j;
    // to determine the number of Unoccupied positions from the intermediate board configuration
           int countU=0;
           for (i=0;i<n;i++) {
               for (j=0;j<n;j++) {
                   if (board[i][j]=='U')
                       countU++;
               }
           }
    
    char storeUPos[countU][2]; //stores all unoccupied positions
    int p=0;
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            if (board[i][j]=='U') {
                storeUPos[p][0]='a'+i;
                storeUPos[p][1]='a'+j;
                p++;
            }
        }
    }
    //stores all of human player's valid positions
           char ValidPosArrC[countU][2];
           int NumValidPosC=0; //number of rows in firstConditionB-1
           for(i=0;i<countU;i++) {  //traversing through the storeUPos array which consists of all unoccupied positions
               
              if (checkLegalAllDirections(board,n,colour,storeUPos,i)==true) {
                  
                  ValidPosArrC[NumValidPosC][0]=storeUPos[i][0];
                  ValidPosArrC[NumValidPosC][1]=storeUPos[i][1];
                  NumValidPosC++;
              }
           }
    
    //Now, using the given input, I need to check if it is a valid position and if it is, I need to make the move (and flip)
    bool N=false, S=false, E=false, W=false, NE=false, NW=false, SE=false, SW=false, invalidM=true;
    
    for(i=0;i<NumValidPosC;i++) {
        if (userRow==ValidPosArrC[i][0] && userCol==ValidPosArrC[i][1]) {
            invalidM=false;
            board[ValidPosArrC[i][0]-'a'][ValidPosArrC[i][1]-'a']=colour;
            
            //flip the tiles
            determineDirectionsForFlip(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, &N, &S, &E, &W, &NE, &NW, &SE, &SW);
            
            if (N==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, -1, 0);
            if (S==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 1, 0);
            if (E==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 0, 1);
            if (W==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 0, -1);
            if (NE==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, -1, 1);
            if (NW==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, -1, -1);
            if (SE==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 1, 1);
            if (SW==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 1, -1);
            
            printBoard(board, n);
            
        }
    }
    if (invalidM==true) {
        printf("Invalid Move.\n");
        return false;
    }
    
    return true;
}


// This function computes the number of tiles that will be flipped in a specified direction
int computeScoreInOneDirec(int n, char board[][26], char colour, int row, int col, int deltaRow, int deltaCol) {
    int i;
    int scoreOneDirec=0;
    for(i=1; ;i++) {
        if(board[row+deltaRow*i][col+deltaCol*i]==colour) {
            return scoreOneDirec;
        } else {
            scoreOneDirec++;
            continue;
        }
    }
    
}

int computeScoreInAllDirec(int n, char board[][26], int row, int col, char colour) {
    int scoreAllDirec=0;
    
    if (checkLegalInDirection(board,n,row,col,colour,-1,0)==true) //N
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, -1, 0);
    
    if (checkLegalInDirection(board,n,row,col,colour,1,0)==true) //S
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, 1, 0);
    
    if (checkLegalInDirection(board,n,row,col,colour,0,1)==true) //E
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, 0, 1);
    
    if (checkLegalInDirection(board,n,row,col,colour,0,-1)==true) //W
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, 0, -1);
    
    if (checkLegalInDirection(board,n,row,col,colour,-1,1)==true) //NE
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, -1, 1);
    
    if (checkLegalInDirection(board,n,row,col,colour,-1,-1)==true) //NW
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, -1, -1);
    
    if (checkLegalInDirection(board,n,row,col,colour,1,1)==true) //SE
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, 1, 1);
    
   if (checkLegalInDirection(board,n,row,col,colour,1,-1)==true) //SW
        scoreAllDirec+=computeScoreInOneDirec(n, board, colour, row, col, 1, -1);
    
    return scoreAllDirec;
    
}



//This function will determine the position the computer will pay when it is its turn

void positionSelectedByComp(int n, char board[][26], char colour, char* compRow, char* compCol) {
    
    int i,j;
       // to determine the number of Unoccupied positions
        int countU=0;
        for (i=0;i<n;i++) {
            for (j=0;j<n;j++) {
                if (board[i][j]=='U')
                    countU++;
            }
        }
    
    char storeUPos[countU][2];
       int p=0;
       for (i=0;i<n;i++) {
           for (j=0;j<n;j++) {
               if (board[i][j]=='U') {
                   storeUPos[p][0]='a'+i;
                   storeUPos[p][1]='a'+j;
                   p++;
               }
           }
       }
    
    //stores all of computer's valid positions
              char ValidPosArrC[countU][2];
              int NumValidPosC=0; //number of rows in firstConditionB-1
              for(i=0;i<countU;i++) {  //traversing through the storeUPos array which consists of all unoccupied positions
                  
                 if (checkLegalAllDirections(board,n,colour,storeUPos,i)==true) {
                     
                     ValidPosArrC[NumValidPosC][0]=storeUPos[i][0];
                     ValidPosArrC[NumValidPosC][1]=storeUPos[i][1];
                     NumValidPosC++;
                 }
              }
    //NOW IS WHEN THE COMPUTER CHOOSES THE VALID POSITION.
    //if any of the valid positions are corners we want them right away regardless of how many tiles are flipped
    bool cornerPos=false;
    for (i=0;i<NumValidPosC;i++) {
        if ((ValidPosArrC[i][0]=='a' && ValidPosArrC[i][1]=='a') || (ValidPosArrC[i][0]==('a'+n-1) && ValidPosArrC[i][1]=='a') || (ValidPosArrC[i][0]=='a' && ValidPosArrC[i][1]==('a'+n-1)) || (ValidPosArrC[i][0]==('a'+n-1) && ValidPosArrC[i][1]==('a'+n-1))) {
            cornerPos=true;
        }
    }
    
    if (cornerPos==true) {
        for (i=0;i<NumValidPosC;i++) {
            
        if (ValidPosArrC[i][0]=='a' && ValidPosArrC[i][1]=='a') {
            *compRow='a';
            *compCol='a';
            return;
        } else if (ValidPosArrC[i][0]==('a'+n-1) && ValidPosArrC[i][1]=='a') {
            *compRow=('a'+n-1);
            *compCol='a';
            return;
        } else if (ValidPosArrC[i][0]=='a' && ValidPosArrC[i][1]==('a'+n-1)) {
            *compRow='a';
            *compCol=('a'+n-1);
            return;
        } else if (ValidPosArrC[i][0]==('a'+n-1) && ValidPosArrC[i][1]==('a'+n-1)) {
           *compRow=('a'+n-1);
            *compCol=('a'+n-1);
            return;
        }
        
    }
                   
    } else {
      
        //Now I need to use the score(number of tiles flipped) and NumPosAvailableForOpponent for each of my moves and decide which one is the optimal move. Total score = score-NumOfOpponentMoves
        
        int rowHighestScore=0;
        int totalScore=0;
     //  int NumOppMoves=0;//flips-NumOfOpponentMoves
        int cornerScore=0;
        
    //store this total score in a new array that stores total scores. this array has NumValidPosC elements.
        int NumOppMoves=0;
    for (i=0;i<NumValidPosC;i++) {
        
        NumOppMoves=NumOfOpponentMoves(n,board,colour, ValidPosArrC[i][0], ValidPosArrC[i][1]);
        cornerScore= scoreCornerPos( n, board, ValidPosArrC[i][0], ValidPosArrC[i][1], colour); //rows and columns are as alphabets
        
      //  NumOppMoves=NumOfOpponentMoves(n,board,colour, ValidPosArrC[i][0], ValidPosArrC[i][1]);
        
        if (totalScore<computeScoreInAllDirec(n, board, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour)+0.9*cornerScore+NumOppMoves) {
            totalScore=computeScoreInAllDirec(n, board, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour)+0.9*cornerScore+NumOppMoves;
            rowHighestScore=i;
        }
    }
    
    *compRow=ValidPosArrC[rowHighestScore][0];
    *compCol=ValidPosArrC[rowHighestScore][1];
        
  }
    
}

//Below function returns true if there are any valid positions. Returns false if not.
bool checkForAnyValidPos(int n, char board[][26], char colour) {
    
    int i,j;
    // to determine the number of Unoccupied positions
     int countU=0;
     for (i=0;i<n;i++) {
         for (j=0;j<n;j++) {
             if (board[i][j]=='U')
                 countU++;
         }
     }
    
    char storeUPos[countU][2];
    int p=0;
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            if (board[i][j]=='U') {
                storeUPos[p][0]='a'+i;
                storeUPos[p][1]='a'+j;
                p++;
            }
        }
    }
    
    //stores all of colour's valid positions
    char ValidPosArrC[countU][2];
    int NumValidPosC=0; //number of rows in firstConditionB-1
    for(i=0;i<countU;i++) {  //traversing through the storeUPos array which consists of all unoccupied positions
                     
    if (checkLegalAllDirections(board,n,colour,storeUPos,i)==true) {
                        
        ValidPosArrC[NumValidPosC][0]=storeUPos[i][0];
        ValidPosArrC[NumValidPosC][1]=storeUPos[i][1];
        NumValidPosC++;
        }
    }
    
    if (NumValidPosC>0) {
        return true;
    } else {
        return false; //condition includes 0;
    }
        
}

char mostPiecesOnBoard(int n, char board[][26]) {
    int i,j;
    int blackPieces=0;
    int whitePieces=0;
    
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            if (board[i][j]=='B')
                blackPieces++;
            else if (board[i][j]=='W')
                whitePieces++;
        }
    }
    
    if (blackPieces>whitePieces)
        return 'B';
    else if (whitePieces>blackPieces)
        return 'W';
    else if (blackPieces==whitePieces)
        return 'D';
    else
        return 'N';
}

bool UnoccupiedPosInBoard(int n, char board[][26]) {
      int i,j;
    
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
           if (board[i][j]=='U')
               return true;
        }
    }
    
    return false;
    
}

bool checkForWinLoseOrDraw (int n, char board[][26]) {
    char black='B';
    char white='W';
    //if board has no 'U' in it or if checkForAnyValidPos is false for both players, the game is over and winner is one with more tiles. draw if both has same tiles
    
    if (UnoccupiedPosInBoard(n,board)==false || (!checkForAnyValidPos(n, board, black) && !checkForAnyValidPos(n, board, white)) ) {
        if (mostPiecesOnBoard(n, board)=='W') {
            printf("W player wins.\n");
        } else if (mostPiecesOnBoard(n, board)=='B') {
            printf("B player wins.\n");
        } else if (mostPiecesOnBoard(n, board)=='D') {
            printf("Draw!\n");
        } else {
            printf("Error, recheck code\n");
            }
        return true; //game has ended
        }
    else {
        return false;
    }

}

int NumOfOpponentMoves (int n, char board[][26], char colour, int row, int col) { //the colour here refers to the computer's colour
    
    int i, j;
    char copyboard[26][26];
    for (i=0;i<n;i++) {
           for (j=0;j<n;j++) {
               copyboard[i][j]=board[i][j];
           }
    }
    
    playMoveMod(n, copyboard, colour, row, col);
    //Now its the opponents turns. I have to calculate their number of moves.
    
    if (colour=='W') {
        //check how many black moves
        
         // to determine the number of Unoccupied positions from the intermediate board configuration
                int countU=0;
                for (i=0;i<n;i++) {
                    for (j=0;j<n;j++) {
                        if (copyboard[i][j]=='U')
                            countU++;
                    }
                }
         
         char storeUPos[countU][2]; //stores all unoccupied positions
         int p=0;
         for (i=0;i<n;i++) {
             for (j=0;j<n;j++) {
                 if (copyboard[i][j]=='U') {
                     storeUPos[p][0]='a'+i;
                     storeUPos[p][1]='a'+j;
                     p++;
                 }
             }
         }
         //stores all of human player's valid positions
                char ValidPosArrB[countU][2];
                int NumValidPosB=0; //number of rows in firstConditionB-1
                for(i=0;i<countU;i++) {  //traversing through the storeUPos array which consists of all unoccupied positions
                    
                   if (checkLegalAllDirections(copyboard,n,'B',storeUPos,i)==true) {
                       
                       ValidPosArrB[NumValidPosB][0]=storeUPos[i][0];
                       ValidPosArrB[NumValidPosB][1]=storeUPos[i][1];
                       NumValidPosB++;
                   }
                }
      
        
        for (i=0;i<NumValidPosB;i++) {
            row = ValidPosArrB[i][0];
            col = ValidPosArrB[i][1];
            if ( (row == 'a' && col=='a') || (row==('a'+n-1) && col=='a')  || (row=='a' && col==('a'+n-1)) || (row=='a' && col==('a'+n-1)) ) {
                return -7;
            }
        }
        
        if (NumValidPosB==0) {
            return 10;
        } else {
            return 0;
        }
        
    } else { //colour is definitely going to be 'B'. I am not going to pass anything else
        
        //check how many white moves
        
        // to determine the number of Unoccupied positions from the intermediate board configuration
                int countU=0;
                for (i=0;i<n;i++) {
                    for (j=0;j<n;j++) {
                        if (copyboard[i][j]=='U')
                            countU++;
                    }
                }
         
         char storeUPos[countU][2]; //stores all unoccupied positions
         int p=0;
         for (i=0;i<n;i++) {
             for (j=0;j<n;j++) {
                 if (copyboard[i][j]=='U') {
                     storeUPos[p][0]='a'+i;
                     storeUPos[p][1]='a'+j;
                     p++;
                 }
             }
         }
         //stores all of human player's valid positions
                char ValidPosArrW[countU][2];
                int NumValidPosW=0; //number of rows in firstConditionB-1
                for(i=0;i<countU;i++) {  //traversing through the storeUPos array which consists of all unoccupied positions
                    
                   if (checkLegalAllDirections(copyboard,n,'W',storeUPos,i)==true) {
                       
                       ValidPosArrW[NumValidPosW][0]=storeUPos[i][0];
                       ValidPosArrW[NumValidPosW][1]=storeUPos[i][1];
                       NumValidPosW++;
                   }
                }
        
        for (i=0;i<NumValidPosW;i++) {
                   row = ValidPosArrW[i][0];
                   col = ValidPosArrW[i][1];
                   if ( (row == 'a' && col=='a') || (row==('a'+n-1) && col=='a')  || (row=='a' && col==('a'+n-1)) || (row=='a' && col==('a'+n-1)) ) {
                       return -7;
                   }
               }
        
        if (NumValidPosW==0) {
            return true;
        } else {
            return false;
        }
        
    }
    
    
}



//MODFIED VERSION OF PLAYMOVE FOR USE IN COMPUTER SELECTED MOVE FUNCTION
bool playMoveMod (int n, char board[][26], char colour, char userRow, char userCol) { //had to make playMove return bool to ensure that the position entered is valid
    
    int i,j;
    // to determine the number of Unoccupied positions from the intermediate board configuration
           int countU=0;
           for (i=0;i<n;i++) {
               for (j=0;j<n;j++) {
                   if (board[i][j]=='U')
                       countU++;
               }
           }
    
    char storeUPos[countU][2]; //stores all unoccupied positions
    int p=0;
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            if (board[i][j]=='U') {
                storeUPos[p][0]='a'+i;
                storeUPos[p][1]='a'+j;
                p++;
            }
        }
    }
    //stores all of human player's valid positions
           char ValidPosArrC[countU][2];
           int NumValidPosC=0; //number of rows in firstConditionB-1
           for(i=0;i<countU;i++) {  //traversing through the storeUPos array which consists of all unoccupied positions
               
              if (checkLegalAllDirections(board,n,colour,storeUPos,i)==true) {
                  
                  ValidPosArrC[NumValidPosC][0]=storeUPos[i][0];
                  ValidPosArrC[NumValidPosC][1]=storeUPos[i][1];
                  NumValidPosC++;
              }
           }
    
    //Now, using the given input, I need to check if it is a valid position and if it is, I need to make the move (and flip)
    bool N=false, S=false, E=false, W=false, NE=false, NW=false, SE=false, SW=false, invalidM=true;
    
    for(i=0;i<NumValidPosC;i++) {
        if (userRow==ValidPosArrC[i][0] && userCol==ValidPosArrC[i][1]) {
            invalidM=false;
            board[ValidPosArrC[i][0]-'a'][ValidPosArrC[i][1]-'a']=colour;
            
            //flip the tiles
            determineDirectionsForFlip(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, &N, &S, &E, &W, &NE, &NW, &SE, &SW);
            
            if (N==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, -1, 0);
            if (S==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 1, 0);
            if (E==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 0, 1);
            if (W==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 0, -1);
            if (NE==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, -1, 1);
            if (NW==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, -1, -1);
            if (SE==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 1, 1);
            if (SW==true)
                flipInDirection(board, n, ValidPosArrC[i][0]-'a', ValidPosArrC[i][1]-'a', colour, 1, -1);
            
            
        }
    }
    if (invalidM==true) {
        printf("Invalid Move.\n");
        return false;
    }
    
    return true;
}

int scoreCornerPos(int n, char board [][26], int row, int col, char colour) { //the rows and columns are alphabets not actual indices
    
    int cornerScore=0;
    
    int i,j;
       int countU=0;
       for (i=0;i<n;i++) {
           for (j=0;j<n;j++) {
               if (board[i][j]=='U')
                   countU++;
           }
       }
    
   
    
    
    if (countU<(n*n)/2-10) { //after half the game is done
        
        if ( (col=='a' && row=='a') || (col=='a'+n-1 && row=='a') || (col=='a' && row=='a'+n-1) || (col=='a'+n-1 && row=='a'+n-1) )
               cornerScore=-9; //ALL CORNERS
        
        //all positions near corners
          if ( (row=='b' && col=='a') || (row=='b' && col=='b') || (row=='a' && col=='b') ) //top left
              cornerScore=-9;
          
          if ( (row=='a' && col=='a'+n-2) || (row=='b' && col=='a'+n-2) || (row=='b' && col=='a'+n-1) ) //top right
              cornerScore=-9;
          
          if ( (row=='a'+n-2 && col=='a') || (row=='a'+n-2 && col=='b') || (row=='a'+n-1 && col=='b') ) //bottom left
              cornerScore=-9;
          
          if ( (row=='a'+n-2 && col=='a'+n-2) ||  (row=='a'+n-1 && col=='a'+n-2) || (row=='a'+n-2 && col=='a'+n-1) ) //bottom right
              cornerScore=-9;
          
        
        //all position adjacent to spots near corner
        if ( (row=='c' && col=='a') || (row=='c' && col=='c') || (row=='a' && col=='c') )
            cornerScore=9;
        else if ( (row=='a' && col=='a'+n-3) || (row=='c' && col=='a'+n-3) || (row=='c' && col=='a'+n-1) ) {
            cornerScore=9;
        }
        else if ( (row=='a'+n-3 && col=='a') || (row=='a'+n-3 && col=='c') || (row=='a'+n-1 && col=='c')  )
            cornerScore=9;
        else if ( (row=='a'+n-1 && col=='a'+n-3) || (row=='a'+n-3 && col=='a'+n-3) || (row=='a'+n-3 && col=='a'+n-1) )
            cornerScore=9;
        
        
        
    } else { //before half the game is done
        
        if ( (col=='a' && row=='a') || (col=='a'+n-1 && row=='a') || (col=='a' && row=='a'+n-1) || (col=='a'+n-1 && row=='a'+n-1) )
        cornerScore=9; //ALL CORNERS
        
          //all positions near corners
          if ( (row=='b' && col=='a') || (row=='b' && col=='b') || (row=='a' && col=='b') ) //top left
              cornerScore=-7;
          
          if ( (row=='a' && col=='a'+n-2) || (row=='b' && col=='a'+n-2) || (row=='b' && col=='a'+n-1) ) //top right
              cornerScore=-7;
          
          if ( (row=='a'+n-2 && col=='a') || (row=='a'+n-2 && col=='b') || (row=='a'+n-1 && col=='b') ) //bottom left
              cornerScore=-7;
    
          if ( (row=='a'+n-2 && col=='a'+n-2) ||  (row=='a'+n-1 && col=='a'+n-2) || (row=='a'+n-2 && col=='a'+n-1) ) //bottom right
              cornerScore=-7;
        
    //all position adjacent to spots near corner
    if ( (row=='c' && col=='a') || (row=='c' && col=='c') || (row=='a' && col=='c') )
        cornerScore=7;
    else if ( (row=='a' && col=='a'+n-3) || (row=='c' && col=='a'+n-3) || (row=='c' && col=='a'+n-1) ) {
        cornerScore=7;
    }
    else if ( (row=='a'+n-3 && col=='a') || (row=='a'+n-3 && col=='c') || (row=='a'+n-1 && col=='c')  )
        cornerScore=7;
    else if ( (row=='a'+n-1 && col=='a'+n-3) || (row=='a'+n-3 && col=='a'+n-3) || (row=='a'+n-3 && col=='a'+n-1) )
        cornerScore=7;
    
        
    }
    
    return cornerScore;
}
