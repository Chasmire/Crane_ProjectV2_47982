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
void play();    //Handles gameplay
void showBoard(int);//Outputs board from file
int solved(int [5][5],int);//Check If Puzzle Is Solved
void mix(int [5][5],int );//Scrambles the board
int bSize();   //handles board size selection
void bOut(int [5][5],int);//output board to file
bool isValid(int [],int,int);//Checks if generated board is possible to solve

// Main Execution Begins Here!!
int main(int argv,char** argc){
    //Declare Variables
    char choice;
    //seed random number
    srand(time(0));
    cout<<"                 +++++++++++++++++++++++++++++++++"<<endl;
    cout<<"                 +                               +"<<endl;
    cout<<"                 +  N u m b e r   +   S l i d e  +"<<endl;
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
                cout<<"Return to main menu? (Y/N): ";
                cin>>choice;
                break;
            }
            case '2':{
                rules(); //Call Rules function
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

// Handles Gameplay
//------------------------------------------------------------------------------
void play(){
    //Declare Variables
    char move;
    int board [5][5]={}, check=0, grid, nMove=0;
    
    grid=bSize();//Select board size
    mix(board,grid);; //Scramble the board
    bOut(board,grid);//store board to file 
    showBoard(grid);   //output stored board
    
    //Handles player move input
    do{
        cout<<endl<<"[W - Up] [S - Down] [A - Left] [D - Right]"<<endl;
        cout<<" -Enter Q at any time to stop game."<<endl;
        cout<<"Move: ";
        cin>>move;
        cout<<endl;
      
        //Finds the index of the element that holds 0 in the board array and
        //depending on move, swaps the 0 with another element
        //Move determines the element to be swapped with 0 by incrementing
        //or decrementing the row or col index.
        switch (move){
            case 'S':
            case 's':{
                for(int row=0;row<grid;row++){
                    for(int col=0;col<grid;col++){
                        if(board [row][col]==0){
                            if(row-1>=0){
                            board[row][col]=board[row-1][col];
                            board[row-1][col]=0;
							nMove++;
                            }
                        }
                    }
                }
                break;
            }
            case 'W':
            case 'w':{
                for(int row=0;row<grid;row++){
                    for(int col=0;col<grid;col++){
                        if(board [row][col]==0){
                            if(row+1<grid){
                            board[row][col]=board[row+1][col];
                            board[row+=1][col]=0;
							nMove++;
                            }
                        }
                    }
                }
                break;
            }
            case 'D':
            case 'd':{
                for(int row=0;row<grid;row++){
                    for(int col=0;col<grid;col++){
                        if(board [row][col]==0){
                            if(col-1>=0){
                            board[row][col]=board[row][col-1];
                            board[row][col-1]=0;
							nMove++;
                            }
                        }
                    }
                }
                break;
            }
            case 'A':
            case 'a':{
                for(int row=0;row<grid;row++){
                    for(int col=0;col<grid;col++){
                        if(board [row][col]==0){
                            if(col+1<grid){
                            board[row][col]=board[row][col+1];
                            board[row][col+=1]=0;
							nMove++;
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
        
        bOut(board,grid); //update the file that stores the board 
        showBoard(grid);//output stored board again
        check=solved(board,grid);//Check if the board is solved
    }while(check==0);

    cout<<endl<<"                        ++++++++++++++++++++"<<endl;
    cout<<"                        +  PUZZLED SOLVED  +"<<endl;
    cout<<"                        ++++++++++++++++++++"<<endl;
    cout<<"                  You beat the puzzle in "<<nMove<<" moves!"<<endl<<endl;
}

//Choose board size
//------------------------------------------------------------------------------
int bSize(){
    //Declare Variables
    int size;
    //Prompt for input and validate
    do{
        cout<<"                         Select a puzzle size"<<endl;
        cout<<"                              1) 3 x 3"<<endl;
        cout<<"                              2) 4 x 4"<<endl;
        cout<<"                              3) 5 x 5"<<endl;
        cout<<"                         Enter # of choice: ";
        cin>>size;
        cout<<endl;
    }while(size!=1&&size!=2&&size!=3);
    //Return the board dimensions
    if(size==1) return 3;
    else if(size==2) return 4;
    else return 5;
}

//Output Board to file
//------------------------------------------------------------------------------
void bOut(int b[5][5],int range){
    //Open file to write to
    ofstream tempOut("board.dat");
    //copy array to file
    for(int i=0;i<range;i++){
        for(int t=0;t<range;t++){
            tempOut<<b[i][t]<<" "; //Writes to file
        }
    }
    //close file
    tempOut.close();
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
void showBoard(int range){
    //Declare Variables
    int count=0,a[5][5];
    //open file to read from
    ifstream tempIn("board.dat");
    
    //board layout
    cout<<"  +++++";
    for(int i=0;i<range;i++){ 
        cout<<"++++";
    }
    cout<<endl<<"  +";
    
    //Cycle through array and output each #
    for (int r=0; r<range;r++){
        for(int c=0;c<range;c++){
            //read in array from file
            tempIn>>a[r][c];
            //signals beginning of a new row
            if (count==1){
                cout<<"   +"<<endl<<"  +";
                count=0;
            }
            //0 marks the empty spot on the board; output a - instead of the #
            if (a[r][c]==0) cout<<setw(4)<<"-";
            //if # on board is not 0 then output it
            else cout<<setw(4)<<a[r][c];
        }
        count++;
    }
    //board layout
    cout<<"   +"<<endl<<"  +++++";
    for(int i=0;i<range;i++){ 
        cout<<"++++";
    }
    //close the file
    tempIn.close();
}

//Check If Puzzle Is Solved
//------------------------------------------------------------------------------
int solved(int b[5][5],int range){
    //Declare Variables
    int size=range*range, count=0;
    int *solved=new int[size];
    
    //Fill the solved board array
    for(int i=0;i<size-1;i++){
        solved[i]=i+1;
    }
    solved[size-1]=0;
    
    //Cycle through current board and compare it to solved
    for(int x=0;x<range;x++){
        for(int y=0;y<range;y++){
            if(b[x][y]==solved[count]){
                count++;
            }
        }
    }
    //Clear allocated memory
    delete [] solved;
    solved=0;
    //if board and solved are the same return 1 and the game is won
    if (count==size) return 1;
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
    cout<<"                 5  13   1   -                     13  14  15   -"<<endl<<endl;
    cout<<" + Move numbers into the place of the '-' to solve the puzzle."<<endl;
    cout<<"   As you move numbers around, the '-'  will swap places with" <<endl;
    cout<<"   that number."<<endl<<endl;
    cout<<" + Use the W,A,S,D keys to move numbers from above, below, left,"<<endl;
    cout<<"   or right of the '-' INTO the '-' space:"<<endl;
    cout<<"         [W - Up] [S - Down] [A - Left] [D - Right]"<<endl<<endl;
}

// Randomizes Board
//------------------------------------------------------------------------------
void mix(int b[5][5],int range){
    //Declare Variables
    int temp,dup,size=range*range;
    int *p=new int[size];
    
    do{
        //Initialize/reset array p to all 0
        //(must do this to validate board solvability more than once)
        for(int i=0;i<size-1;i++){
            p[i]=0;
        }

        //set up a randomized 1D array
        for (int t = 0; t < size-1; t++){
            do{
                dup=0;
                //create a random #
                temp=rand() % (size-1)+1;
                //test for duplicates
                for(int i = 0; i < size-1; i++){
                    if(p[i] == temp){
                        dup++;
                    }
                }
             //If there is a duplicate create a new random # to test 
            } while(dup != 0);
            
            //assign the random # to the array if no duplicates are found
            p[t] = temp;
        }
     //checks for board solvability
    }while(!isValid(p,size,range));
    p[size-1] = 0;
    
    //copy 1D array to the 2D array 
    int count=0;
    for(int i = 0; i < range; i++){
        for(int t = 0; t < range; t++){
            b[i][t]=p[count];
            count++;
        }
    }
    //Clear allocated memory
    delete [] p;
    p=0;
}

// Checks if generated board is possible to solve
//------------------------------------------------------------------------------
bool isValid(int a[],int size,int grid){
    //Declare Variables
    int inver=0;
    //Count # of inversions within the array
    for(int i=0;i<size-1;i++){
        for(int t=i;t<size-1;t++){
            if(a[t]<a[i]) inver++;
        }
    }   
    //Board Solvability Conditions
    //Grid width is odd -> # of inversions is even
    //Grid width is even -> # of inversions odd
    if((grid%2==1)&&(inver%2==0) || (grid%2==0)&&(inver%2==1)) return true;
    
    return false;//board is not solvable
}