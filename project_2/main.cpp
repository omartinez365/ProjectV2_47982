/* 
 * File:   main.cpp
 * Author: Oscar Martinez 
 * Created on October 10, 2013, 7:37 PM
 * Purpose: Tic-Tac-Toe Final Project 
 */

//Libraries 
#include <iostream>
using namespace std;

//Global constants 
const short int BIGBRD = 9;

//Function prototypes
void header();                 //Outputs rules and header 
void getUser(char &, char &);  //Gets user 
void dsplOBd(char[]);          //Displays big board
void isValid(char[][BIGBRD], short int &, short int &, char &, char &, char &);  //Validates the move 
void wLTOBrd(char[], char &, char &, char &, char &);             //Checks is someone won the overall game
void wnLsTie(char [][BIGBRD], short int &, char[], char &, char &, char &, char &);  //Checks if someone won individual game
void dsplBrd(char[][BIGBRD],const short int);       //Displays big board 
void fillBrd(char[][BIGBRD], const short int, const short int);   //Fills big board with numbers 


//Execution begins here
int main(int argc, char** argv) {
    //Declare variables here
    char crntply,                  //Current Player
         user1, user2,             //Player one and player two 
         winner,                   //Winner of game
         again;                    //Choice to play again
    short int choice;              //choice within individual board 
    short int square;              //Choice of square
    const int SIZE = 9;            //Size of individual boards 
    const short int BIGBRD = 9;    //Number of squares in big board 
    const short int INDBRD = 9;    //Number of squares in each individual board
    

    do{ 
        //Create the board
        char outrBrd[9]={'1','2','3','4','5','6','7','8','9'}; 
        
        //Create board containing individual boards
        char board[BIGBRD][INDBRD];
        
        //fill the board
        fillBrd(board, BIGBRD, INDBRD);
        
        //Heading 
        header();
        
        //Ask user if they want to be X's or O's 
        getUser(user1, user2);
       
        //Sets user1 to the current player 
        crntply = user1; 
        
        //Display the board containing individual boards 
        dsplBrd(board,INDBRD); 
        
        //Display Outer Board 
        dsplOBd(outrBrd); 
        
        //Prompts user for a move and validates 
        //Keeps switching between players and asking for a play while there is no winner 
        do{
            //Checks that the move made by user is one of the choices on the grid 
            do{ 
                cout << "Chose a board: "; 
                cin >> square; 
                cout << "Enter a number: "; 
                cin >> choice;
            }while(choice < 0 || choice > 9); 
            
            //Changes the number on the grid to the current player's letter
            //Checks to see if the move made by current user is valid
            //meaning there is no X or O
            isValid(board, square, choice, crntply, user1, user2);
            
            //Display board
            dsplBrd(board,BIGBRD); 
            
          
         //Checks to see if current player won square
         //Checks if the rows, columns or diagonals are the same 
         if(board[square-1][0] == board[square-1][1] && board[square-1][1] == board[square-1][2] || 
            board[square-1][3] == board[square-1][4] && board[square-1][4] == board[square-1][5] || 
            board[square-1][6] == board[square-1][7] && board[square-1][7] == board[square-1][8] || 
            board[square-1][0] == board[square-1][4] && board[square-1][4] == board[square-1][8] || 
            board[square-1][2] == board[square-1][4] && board[square-1][4] == board[square-1][6] || 
            board[square-1][0] == board[square-1][3] && board[square-1][3] == board[square-1][6] ||
            board[square-1][1] == board[square-1][4] && board[square-1][4] == board[square-1][7] || 
            board[square-1][2] == board[square-1][5] && board[square-1][5] == board[square-1][8]){ 
            //If a row, diagonal, or column is the same the player that 
            //just went is the winner 
             outrBrd[square-1]=crntply; 
             cout<< crntply <<"'s win square " <<(square) <<endl; 
             //Switches players 
             if(crntply==user1) crntply=user2; 
             else crntply= user1; 
        }
        //If all the boxes have either an O or X, and no one won, 
        //the game is tied 
        else if( board[square-1][0] != '1' &&
                 board[square-1][1] != '2' &&
                 board[square-1][2] != '3' &&
                 board[square-1][3] != '4' &&
                 board[square-1][4] != '5' &&
                 board[square-1][5] != '6' &&
                 board[square-1][6] != '7' &&
                 board[square-1][7] != '8' &&
                 board[square-1][8] != '9'){
            //Displays tie game message 
            cout << "It's a tie game for square " << (square) <<" !!" <<endl;    
            //Sets the square in the big board to T to signal a tie
            outrBrd[square-1]= 'T';
            //Switches Player 
            if(crntply==user1) crntply=user2; 
            else crntply= user1;
        }
        //There is no winner 
        else{ 
            //Sets winner to 0 so it can keep asking for moves 
            winner = '0';
            //Switches players 
            if(crntply == user1){ 
                crntply = user2;
            }
            else{ 
                crntply = user1; 
            }
        }
            //Checks to see if the current player won the big board
            //Checks if the rows, columns or diagonals are the same 
            //Checks if there is a tie
            wLTOBrd(outrBrd,winner, crntply, user1, user2);
            dsplOBd(outrBrd);
        }while(winner == '0'); 
        //Prompts the user if they want to play again
        cout << "Do you want to play again? "; 
        cin >> again; 
    }while(again == 'Y' || again == 'y');
    return 0;
}
void header(){ 
    //Displays the header and the rules 
    cout << "**********ULTIMATE TIC-TAC-TOE**********" <<endl <<endl;
    cout << "This game of TIC-TAC-TOE involves a game within a game."<<endl <<"The object is to "
         <<"win three boards to win the whole game."<<endl <<"Wherever the last player went in the individual "
         <<"board is where"<<endl <<"the next player goes in the big board. Should an individual board be tied, "
         <<endl <<"it doesn't count for either player. " <<endl <<endl;
}
void getUser(char &user1,char &user2){ 
    //Ask the user if they want to be X's or O's 
    cout << "Player 1, do you want to be X or O: ";
    cin >> user1; 
        
    //Displays each player with their corresponding letter (X or O)
    if(user1 == 'X' || user1 == 'x'){ 
        user1='X';
        user2 = 'O'; 
        cout << "Player 1 is X's" <<endl
                 << "Player 2 is O's" <<endl; 
    }
    else if( user1=='o'||user1=='O'){   
        user1=='O'; 
        user2 = 'X';
        cout << "Player 1 is O's" <<endl
             << "Player 2 is X's" <<endl; 
    }
}

void dsplOBd(char brd[]){ 
    //Displays the big board
    cout << "     |     |     "  << endl
         << "  " <<brd[0] <<"  |  " <<brd[1] <<"  |  " <<brd[2] <<endl
         << "     |     |     "  << endl
         << "-----------------"  << endl
         << "     |     |     "  << endl
         << "  " <<brd[3] <<"  |  " <<brd[4] <<"  |  " <<brd[5] <<endl
         << "     |     |     "  << endl
         << "-----------------"  << endl
         << "     |     |     "  << endl
         << "  " <<brd[6] <<"  |  " <<brd[7] <<"  |  " <<brd[8] <<endl
         << "     |     |     "  << endl;
}

void isValid(char brd[][BIGBRD],short int & sqre, short int & chce, char & crntply, char & usr1, char & usr2){ 
    //Changes the number on the grid to the current player's letter
    //Checks to see if the move made by current user is valid
    //meaning there is no X or O
    if (brd[sqre-1][chce-1] =='X' || brd[sqre-1][chce-1]=='O'){
        cout<< "Invalid move!!" <<endl; 
        //If the move is invalid, the current user is changed 
        //so that the same player can go again
        if(crntply==usr1) crntply = usr2; 
        else crntply = usr1; 
    }
    //If the move is valid, the number chosen by player changes
    //to X or O
    else brd[sqre-1][chce-1] = crntply; 
    
}

void wLTOBrd(char oBrd[],char & winner, char & crntply, char & usr1, char & usr2){ 
     //Checks to see if the current player won
     //Checks if the rows, columns or diagonals are the same 
     if(oBrd[0] == oBrd[1] && oBrd[1] == oBrd[2] || 
        oBrd[3] == oBrd[4] && oBrd[4] == oBrd[5] || 
        oBrd[6] == oBrd[7] && oBrd[7] == oBrd[8] || 
        oBrd[0] == oBrd[4] && oBrd[4] == oBrd[8] || 
        oBrd[2] == oBrd[4] && oBrd[4] == oBrd[6] || 
        oBrd[0] == oBrd[3] && oBrd[3] == oBrd[6] ||
        oBrd[1] == oBrd[4] && oBrd[4] == oBrd[7] || 
        oBrd[2] == oBrd[5] && oBrd[5] == oBrd[8]){ 
        //If a row, diagonal, or column is the same the player that 
        //just went is the winner 
         if(crntply==usr1) crntply=usr2; 
         else crntply= usr1;
        winner = crntply; 
       
        //Displays the winner 
        cout << winner <<"'s Win!!" <<endl; 
    }
    //If all the boxes have either an O or X, and no one won, 
    //the game is tied 
    else if( oBrd[0] != '1' &&
             oBrd[1] != '2' &&
             oBrd[2] != '3' &&
             oBrd[3] != '4' &&
             oBrd[4] != '5' &&
             oBrd[5] != '6' &&
             oBrd[6] != '7' &&
             oBrd[7] != '8' &&
             oBrd[8] != '9'){
        //Displays tie game message 
        cout << "It's a tie game!!" <<endl;    
        //Sets winner to 1 so that it can exit the loop and stop asking for moves 
        winner = '1'; 
    }
    
}

void wnLsTie(char brd[][BIGBRD],int sqre, char oBrd[],char & winner, char & crntply, char & usr1, char & usr2){ 
     //Checks to see if the current player won
     //Checks if the rows, columns or diagonals are the same 
     if(brd[sqre][0] == brd[sqre][1] && brd[sqre][1] == brd[sqre][2] || 
        brd[sqre][3] == brd[sqre][4] && brd[sqre][4] == brd[sqre][5] || 
        brd[sqre][6] == brd[sqre][7] && brd[sqre][7] == brd[sqre][8] || 
        brd[sqre][0] == brd[sqre][4] && brd[sqre][4] == brd[sqre][8] || 
        brd[sqre][2] == brd[sqre][4] && brd[sqre][4] == brd[sqre][6] || 
        brd[sqre][0] == brd[sqre][3] && brd[sqre][3] == brd[sqre][6] ||
        brd[sqre][1] == brd[sqre][4] && brd[sqre][4] == brd[sqre][7] || 
        brd[sqre][2] == brd[sqre][5] && brd[sqre][5] == brd[sqre][8]){ 
        //If a row, diagonal, or column is the same the player that 
        //just went is the winner 
         oBrd[sqre-1]=crntply; 
         cout<< crntply <<"'s win square " <<(sqre-1); 
    }
    //If all the boxes have either an O or X, and no one won, 
    //the game is tied 
    else if( brd[sqre][0] != '1' &&
             brd[sqre][1] != '2' &&
             brd[sqre][2] != '3' &&
             brd[sqre][3] != '4' &&
             brd[sqre][4] != '5' &&
             brd[sqre][5] != '6' &&
             brd[sqre][6] != '7' &&
             brd[sqre][7] != '8' &&
             brd[sqre][8] != '9'){
        //Displays tie game message 
        cout << "It's a tie game for square " << (sqre-1) <<" !!" <<endl;    
        //Sets winner to 1 so that it can exit the loop and stop asking for moves 
        oBrd[sqre-1]= 'T';
    }
    //There is no winner 
    else{ 
        //Sets winner to 0 so it can keep asking for moves 
        winner = '0';
        //Switches players 
        if(crntply == usr1){ 
            crntply = usr2;
        }
        else{ 
            crntply = usr1; 
        }
    }
}

void dsplBrd(char brd[][BIGBRD], const short int COL){ 
    //Displays the big board, which is a tic-tac-toe board but in each square there is another tic-tac-toe game inbedded. 
     cout<<  "     |     |      |"  <<  "|      |     |      |" <<  "|      |     |     "<< endl
         << "  " <<brd[0][0] <<"  |  " <<brd[0][1] <<"  |  " <<brd[0][2] << "   ||   " <<brd[1][0] <<"  |  " <<brd[1][1] <<"  |  " <<brd[1][2] << "   ||   " <<brd[2][0] <<"  |  " <<brd[2][1] <<"  |  " <<brd[2][2] <<endl
         << "     |     |      |"  <<  "|      |     |      |" << "|      |     |     " << endl
         << "----------------- |"  << "| ----------------- |" << "| -----------------"<< endl
         << "     |     |      |"  <<  "|      |     |      |" <<  "|      |     |     "<< endl
         << "  " <<brd[0][3] <<"  |  " <<brd[0][4] <<"  |  " <<brd[0][5] << "   ||   " <<brd[1][3] <<"  |  " <<brd[1][4] <<"  |  " <<brd[1][5] << "   ||   " <<brd[2][3] <<"  |  " <<brd[2][4] <<"  |  " <<brd[2][5] <<endl
         << "     |     |      |"  << "|      |     |      |" << "|      |     |     "<< endl
         << "----------------- |"  << "| ----------------- |" << "| -----------------"<< endl
         << "     |     |      |"  << "|      |     |      |" << "|      |     |     "<< endl
         << "  " <<brd[0][6] <<"  |  " <<brd[0][7] <<"  |  " <<brd[0][8] << "   ||   " <<brd[1][6] <<"  |  " <<brd[1][7] <<"  |  " <<brd[1][8] << "   ||   " <<brd[2][6] <<"  |  " <<brd[2][7] <<"  |  " <<brd[2][8] <<endl
         << "     |     |      |"  << "|      |     |      |"  << "|      |     |     " << endl;
    cout <<"==========================================================="<<endl;
    cout<<  "     |     |      |"  <<  "|      |     |      |" <<  "|      |     |     "<< endl
         << "  " <<brd[3][0] <<"  |  " <<brd[3][1] <<"  |  " <<brd[3][2] << "   ||   " <<brd[4][0] <<"  |  " <<brd[4][1] <<"  |  " <<brd[4][2] << "   ||   " <<brd[5][0] <<"  |  " <<brd[5][1] <<"  |  " <<brd[5][2] <<endl
         << "     |     |      |"  <<  "|      |     |      |" << "|      |     |     " << endl
         << "----------------- |"  << "| ----------------- |" << "| -----------------"<< endl
         << "     |     |      |"  <<  "|      |     |      |" <<  "|      |     |     "<< endl
         << "  " <<brd[3][3] <<"  |  " <<brd[3][4] <<"  |  " <<brd[3][5] << "   ||   " <<brd[4][3] <<"  |  " <<brd[4][4] <<"  |  " <<brd[4][5] << "   ||   " <<brd[5][3] <<"  |  " <<brd[5][4] <<"  |  " <<brd[5][5] <<endl
         << "     |     |      |"  << "|      |     |      |" << "|      |     |     "<< endl
         << "----------------- |"  << "| ----------------- |" << "| -----------------"<< endl
         << "     |     |      |"  << "|      |     |      |" << "|      |     |     "<< endl
         << "  " <<brd[3][6] <<"  |  " <<brd[3][7] <<"  |  " <<brd[3][8] << "   ||   " <<brd[4][6] <<"  |  " <<brd[4][7] <<"  |  " <<brd[4][8] << "   ||   " <<brd[5][6] <<"  |  " <<brd[5][7] <<"  |  " <<brd[5][8] <<endl
         << "     |     |      |"  << "|      |     |      |"  << "|      |     |     " << endl;
    cout <<"==========================================================="<<endl;
    cout<<  "     |     |      |"  <<  "|      |     |      |" <<  "|      |     |     "<< endl
         << "  " <<brd[6][0] <<"  |  " <<brd[6][1] <<"  |  " <<brd[6][2] << "   ||   " <<brd[7][0] <<"  |  " <<brd[7][1] <<"  |  " <<brd[7][2] << "   ||   " <<brd[8][0] <<"  |  " <<brd[8][1] <<"  |  " <<brd[8][2] <<endl
         << "     |     |      |"  <<  "|      |     |      |" << "|      |     |     " << endl
         << "----------------- |"  << "| ----------------- |" << "| -----------------"<< endl
         << "     |     |      |"  <<  "|      |     |      |" <<  "|      |     |     "<< endl
         << "  " <<brd[6][3] <<"  |  " <<brd[6][4] <<"  |  " <<brd[6][5] << "   ||   " <<brd[7][3] <<"  |  " <<brd[7][4] <<"  |  " <<brd[7][5] << "   ||   " <<brd[8][3] <<"  |  " <<brd[8][4] <<"  |  " <<brd[8][5] <<endl
         << "     |     |      |"  << "|      |     |      |" << "|      |     |     "<< endl
         << "----------------- |"  << "| ----------------- |" << "| -----------------"<< endl
         << "     |     |      |"  << "|      |     |      |" << "|      |     |     "<< endl
         << "  " <<brd[6][6] <<"  |  " <<brd[6][7] <<"  |  " <<brd[6][8] << "   ||   " <<brd[7][6] <<"  |  " <<brd[7][7] <<"  |  " <<brd[7][8] << "   ||   " <<brd[8][6] <<"  |  " <<brd[8][7] <<"  |  " <<brd[8][8] <<endl
         << "     |     |      |"  << "|      |     |      |"  << "|      |     |     " << endl;

}

void fillBrd(char brd[][BIGBRD], const short int ROW,const short int COL) { 
    //Fills each individual board with numbers 1-9
    for(int i = 0; i<ROW; i++){ 
        for(int j =0; j<COL; j++){ 
            brd[i][j]=('1'+j); 
        }
    }
}