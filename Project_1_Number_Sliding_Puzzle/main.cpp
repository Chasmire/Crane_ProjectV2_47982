/*
    Jazmine Crane
    October 21st, 2013
    Project 1 : Number Slider Puzzle
*/

//Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Global Constants

//Function Prototypes
void menu();    //Outputs menu
void rules();   //Outputs the instructions
void play();    //Handles Move Input
void showBoard(int board[4][4]);//Outputs board
int solved(int board[4][4]);//Check If Puzzle Is Solved
void mix(int board[4][4]);//Scrambles the board

// Main Execution Begins Here!!
int main(int argv,char** argc){
    //Declare Variables
    char choice;
    //Output Title
    cout<<"                 +++++++++++++++++++++++++++++++++"<<endl;
    cout<<"                 +                               +"<<endl;
    cout<<"                 +  N u m b e r __+__ S l i d e  +"<<endl;
    cout<<"                 +                               +"<<endl;
    cout<<"                 +++++++++++++++++++++++++++++++++"<<endl;

    do{
        menu();//call menu function
        do{
            //Prompt for menu option input
            cout<<"                         Enter # of choice: ";
            cin>>choice;
            cout<<endl;
        }while(choice!='1'&&choice!='2'&&choice!='3');

        switch (choice){
            case '1':{
                play();	//Call move Function
                cout<<"Return to the menu? (Y/N): ";
                cin>>choice;
                break;
            }
            case '2':{
                rules(); //Call Rules function
                break;
            }
            case '3':{
                break;
            }
        }
    }while(choice=='2'||choice=='y'||choice=='Y');

    cout<<endl<<"                          !+!+!GoodBye!+!+!"<<endl<<endl;

    //Exit Main
    return 0;
}


//  Function Definitions!
// ******************************************************************************

// Handles Move Input
//------------------------------------------------------------------------------
void play(){
    //Declare Variables
    char move;
    int board [4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},check;
    
    mix(board); //Scramble the board
    showBoard(board);   //sets up and outputs the board

    do{
        cout<<endl<<"[W - Up] [S - Down] [A - Left] [D - Right]"<<endl;
        cout<<"Move: ";
        cin>>move;
        cout<<endl;

        switch (move){
            case 'S':
            case 's':{
                for(int row=0;row<4;row++){
                    for(int col=0;col<4;col++){
                        if(board [row][col]==0){
                            if(row-1>=0){
                            board[row][col]=board[row-1][col];
                            board[row-1][col]=0;
                            }
                        }
                    }
                }
                break;
            }
            case 'W':
            case 'w':{
                for(int row=0;row<4;row++){
                    for(int col=0;col<4;col++){
                        if(board [row][col]==0){
                            if(row+1<4){
                            board[row][col]=board[row+1][col];
                            board[row+=1][col]=0;
                            }
                        }
                    }
                }
                break;
            }
            case 'D':
            case 'd':{
                for(int row=0;row<4;row++){
                    for(int col=0;col<4;col++){
                        if(board [row][col]==0){
                            if(col-1>=0){
                            board[row][col]=board[row][col-1];
                            board[row][col-1]=0;
                            }
                        }
                    }
                }
                break;
            }
            case 'A':
            case 'a':{
                for(int row=0;row<4;row++){
                    for(int col=0;col<4;col++){
                        if(board [row][col]==0){
                            if(col+1<4){
                            board[row][col]=board[row][col+1];
                            board[row][col+=1]=0;
                            }
                        }
                    }
                }
                break;
            }
            default:{
                cout<<"!!Invalid Move!!"<<endl;
            }
        }
        showBoard(board);//updates the board
        check=solved(board);//Check if the board is solved
    }while(check==0);

    cout<<endl<<"                        ++++++++++++++++++++"<<endl;
    cout<<"                        +  PUZZLED SOLVED  +"<<endl;
    cout<<"                        ++++++++++++++++++++"<<endl;
}

// Outputs Menu
//------------------------------------------------------------------------------
void menu(){
    cout<<endl;
    cout<<"                                Menu"<<endl;
    cout<<"                           ---------------"<<endl;
    cout<<"                           1) Play Game"<<endl;
    cout<<"                           2) Instructions"<<endl;
    cout<<"                           3) Exit"<<endl;
}

// Outputs Board
//------------------------------------------------------------------------------
void showBoard(int board[4][4]){
    //Declare Variables
    int count=0;
    //Cycle through array and output each #
    cout<<"  +++++++++++++++++++++"<<endl<<"  +";
    for (int r=0; r<=3;r++){
        for(int c=0;c<=3;c++){
            if (count==1){
                cout<<"   +"<<endl<<"  +";
                count=0;
            }
            if (board[r][c]==0) cout<<setw(4)<<"-";
            if (board[r][c]!=0) cout<<setw(4)<<board[r][c];
        }
        count++;
    }
    cout<<"   +"<<endl;
    cout<<"  +++++++++++++++++++++"<<endl;
}

//Check If Puzzle Is Solved
//------------------------------------------------------------------------------
int solved(int board[4][4]){
    //Declare Variables
    int solved[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},count=0;
    //Cycle through current board and compare it to winning conditions
    for(int row=0;row<4;row++){
        for(int col=0;col<4;col++){
            if(board[row][col]==solved[row][col]){
                count++;
            }
        }
    }
    if (count==16) return 1;
    else return 0;
}

// Outputs Rules
//------------------------------------------------------------------------------
void rules(){
    cout<<endl<<" + The goal of this puzzle game is to place the numbers"<<endl;
    cout<<"   in order; smallest to largest, left to right, top to bottom."<<endl<<endl;
    cout<<" + Turn this --> 3   9  14   4       Into this -->  1   2   3   4"<<endl;
    cout<<"                 8   2  10  11                      5   6   7   8"<<endl;
    cout<<"                15   6   7  12                      9  10  11  12"<<endl;
    cout<<"                 5  13   1   +                     13  14  15   -"<<endl<<endl;
    cout<<" + Move numbers into the place of the '-' to solve the puzzle."<<endl;
    cout<<"   As you move numbers around the '-'  will swap places with" <<endl;
    cout<<"   that number."<<endl<<endl;
    cout<<" + Use the W,A,S,D keys to move numbers INTO  the '-' space:"<<endl;
    cout<<"     [W - Up] [S - Down] [A - Left] [D - Right]"<<endl<<endl;
}

// function to shuffle the board
//------------------------------------------------------------------------------
void mix(int board[4][4]){
    //Declare Variables
    int temp, size = 16, p[size];
    int dup;
    srand(time(0));//seed random numbers from clock
    //set up a randomized 1D array
    for (int c = 0; c < size; ++c){
        do{
            dup=0;
            temp=rand() % size;
            for(int i = 0; i < size; ++i){   //check for duplicates
                if(p[i] == temp){
                    ++dup;
                }
            }
        } while(dup != 0);
        p[c] = temp;
    }
    //assign 1D array numbers to the 2D board array
    int count=0;
    for(int i = 0; i < 4; ++i){
        for(int t = 0; t < 4; ++t){
            board[i][t]=p[count];
            count++;
        }
    }
}