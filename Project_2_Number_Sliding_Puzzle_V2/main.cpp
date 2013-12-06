/*
    Jazmine Crane
    December 6th, 2013
    Project 2 : Number Slider Puzzle v2
*/

//Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;

//Global Constants

//Function Prototypes
void menu();    //Outputs menu
void rules();   //Outputs the instructions
void play();    //Handles Move Input
void showBoard();//Outputs board from file
int solved(int board[4][4]);//Check If Puzzle Is Solved
void mix(int board[4][4]);//Scrambles the board
void bSize();   //handles board size selection  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void bOut(int [4][4]);//output board to file

// Main Execution Begins Here!!
int main(int argv,char** argc){
    //Declare Variables
    char choice;
    //seed random number
    srand(time(0));
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
// *****************************************************************************

//Output Board to file
//------------------------------------------------------------------------------
void bOut(int b[4][4]){
    ofstream tempOut("board.dat");
    
    for(int r=0;r<4;r++){
        for(int c=0;c<4;c++){
            tempOut<<b[r][c]<<" ";
        }
    }
    tempOut.close();
}

//Choose board size
//------------------------------------------------------------------------------
void bSize(){
    int size;
    cout<<"                         Select a puzzle size"<<endl;
    cout<<"                              1) 3 x 3"<<endl;
    cout<<"                              2) 4 x 4"<<endl;
    cout<<"                              3) 5 x 5"<<endl;
    cout<<"                         Enter # of choice: ";
    cin>>size;
    cout<<endl;
    
    
}

// Handles Move Input
//------------------------------------------------------------------------------
void play(){
    //Declare Variables
    char move;
    int board [4][4],check;
    
    bSize();
    mix(board); //Scramble the board
    bOut(board);//output board to file 
    showBoard();   //sets up and outputs the board
    
    
    do{
        cout<<endl<<"[W - Up] [S - Down] [A - Left] [D - Right]"<<endl;
        cout<<"Enter Q at any time to quit."<<endl;
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
            case 'Q':
            case 'q':{
                return;
            }
            default:{
                cout<<"!!Invalid Move!!"<<endl;
            }
        }
       
        bOut(board); //updates the output board in file 
        
        showBoard();//updates the board
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

// Outputs Board from file
//------------------------------------------------------------------------------
void showBoard(){
    //Declare Variables
    int count=0, b[4][4];
    //open file for input
    ifstream tempIn("board.dat");
    
    //Cycle through array and output each #
    cout<<"  +++++++++++++++++++++"<<endl<<"  +";
    for (int r=0; r<=3;r++){
        for(int c=0;c<=3;c++){
            //assign array from file
            tempIn>>b[r][c];
            //if count==1 signals beginning of a new row
            if (count==1){
                cout<<"   +"<<endl<<"  +";
                count=0;
            }
            //0 marks the empty spot on the board; replace with a -
            if (b[r][c]==0) cout<<setw(4)<<"-";
            //if # on board is not 0 then output it
            if (b[r][c]!=0) cout<<setw(4)<<b[r][c];
        }
        count++;
    }
    cout<<"   +"<<endl;
    cout<<"  +++++++++++++++++++++"<<endl;
    //close the file
    tempIn.close();
}

//Check If Puzzle Is Solved
//------------------------------------------------------------------------------
int solved(int board[4][4]){
    //Declare Variables
    int solved[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0},count=0;
    //Cycle through current board and compare it to solved
    for(int row=0;row<4;row++){
        for(int col=0;col<4;col++){
            if(board[row][col]==solved[row][col]){
                count++;
            }
        }
    }
    //if board and solved are the same return 1 - the game is won
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