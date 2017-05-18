/* 
Nicholas Moore 
Course: COSC1337 Summer 2016 MW16
Instructor: Thayer
Lab 8: Tic-tac-toe
I worked and tested with Jerry S. on this lab
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
using namespace std;

enum color {red = 12, yellow = 14, white = 7}; //Player colors
HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

class Board
{
	private:
		char board[3][3]; //Private - board 
		char winner = ' ';
		char player;
	public:	
		void drawBoard();
		void getMove(char player);
		char getWinner();
		char setWinner(char win_value);
		char switchPlayer(char currentPlayer);
		char checkWinner();
		
		Board(){ //Default constructor for the game board
			for (int i = 0; i <= 9; i++)
        		board[abs((-(3 - 1))+((i - 1) / 3))][(i - 1) % 3] = '0' + i;}
};

char Board::setWinner(char win_value){
	winner = win_value;
}

char Board::getWinner(){
	return winner;
}

void Board::drawBoard(){ 
	system("cls");
	cout << "Welcome to Tic-Tac-Toe!" << endl; cout << "\n";
	for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
        	if (board[i][j] == 'X') SetConsoleTextAttribute (screen, red);
        	if (board[i][j] == 'O') SetConsoleTextAttribute (screen, yellow);
        		cout << setw(4) << board[i][j];
       			SetConsoleTextAttribute (screen, white);}
        		cout << endl;}
    cout << "\n";
}
     
void Board::getMove(char player) 
{
	retry: if (player == 'X'){
		SetConsoleTextAttribute (screen, red); //Red for player 1
    	cout << "Player 1 (X) - enter your move: (1-9) ";}
    else{
    	SetConsoleTextAttribute (screen, yellow); //Yellow for player 2
    	cout << "Player 2 (O) - enter your move: (1-9) ";}
    int move;
    cin >> move;
    //input validation
    if (move < 1 || move > 9){ 
    	cout << "Error: Please enter a number between 1 and 9.\n";
    	goto retry;
	}
	//Determine player placement on board
    SetConsoleTextAttribute (screen, white);
	int row = abs((-(3 - 1))+((move - 1) / 3));
	int col = (move - 1) % 3;	
	//input validation
	if (board[row][col] == 'X' || board[row][col] == 'O'){ 
		cout << "Error: That spot is already taken!" << endl;
		goto retry;}
	else
		board[row][col] = player; //Set the board move
}

char Board::switchPlayer(char currentPlayer){	
    if (currentPlayer == 'X'){
        player = 'O';}
    else if (currentPlayer == 'O'){
        player = 'X';}
    return player;
}
    
char Board::checkWinner(){
	for (int horiz = 0; horiz < 3; horiz++){
    	if (board[horiz][0] == board[horiz][1] && board[horiz][1] == board[horiz][2]){
        	winner = board[horiz][0];
        	return winner;}} //Horizonal check
        
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || 
		(board[0][2] == board[1][1] && board[1][1] == board[2][0])){
    	winner = board[1][1];
    	return winner;} //Diagonal check

    for (int vertical = 0; vertical < 3; vertical++)
    	if (board[0][vertical] == board[1][vertical] && board[1][vertical] == board[2][vertical])
        	winner = board[0][vertical];
        	return winner; //Vertical check
}

int main(){
	while(true){
		static double player1_win = 0, player1_loss = 0, player2_win = 0, player2_loss = 0; 
		static int tiedGames = 0;
		Board grid; //Create grid object
		int catGameTotal = 0;  //Accumulate number of board moves
		char player = 'X'; //Initial player 1 assigned to 'X'
		bool winner_bool = false;
			
		while (!winner_bool){
			grid.drawBoard(); //Draw board/update on next loop around
			grid.getMove(player); //Get the player move
			catGameTotal++; //Total up cat status
			
			//Winner functions
			char temp_winner = grid.checkWinner(); //The actual winner is assigned to a temporary winner variable
			grid.setWinner(temp_winner); //Pass the temp_winner character to the setWinner function
			char winner = grid.getWinner(); //get the winner (private variable)
			grid.drawBoard(); //This line ensures that the final move by the winner is drawn
			
			player = grid.switchPlayer(player); //Switch players if nobody has won yet
			
			// Win/draw outcomes
			if (winner == 'X'){
				player1_win++;
				player2_loss++;
				SetConsoleTextAttribute (screen, red); //Red for player 1
				cout << "Player 1 is the winner!\n";
				SetConsoleTextAttribute (screen, white);
				winner_bool = true;
				}
			else if (winner == 'O'){
				player2_win++;
				player1_loss++;
				SetConsoleTextAttribute (screen, yellow); //Yellow for player 2
				cout << "Player 2 is the winner!\n";
				SetConsoleTextAttribute (screen, white);
				winner_bool = true;
				}
			//9 moves results in a tie game if nobody has won yet
			else if (catGameTotal == 9){ 
				cout << "Draw game!\n";
				tiedGames++;
				winner_bool = true;
				}
		}
		//Results display
		//Draw games are factored into the win % for both players
		cout << "\n"; 
		cout << "Player 1: " << setprecision(0) << player1_win << " wins and " 
		<< player1_loss << " losses." << " Win percentage: " 
		<< fixed << setprecision(2) << (player1_win/(player1_win + player1_loss + tiedGames) * 100)<< "%" << endl;
		cout << "Player 2: " << setprecision(0) << player2_win << " wins and " 
		<< player2_loss << " losses." << " Win percentage: " 
		<< fixed << setprecision(2) << (player2_win/(player2_win + player2_loss + tiedGames) * 100) << "%" << endl;
		cout << "Draw games: " << tiedGames << "," << " Total games: " << setprecision(0) << (player2_win + player2_loss + tiedGames) << "\n" << endl;
			
		//Play again prompt with input validation
		char user_input;
		while (user_input != 'N' && user_input != 'n'){
			cout << "Would you like to play again? (Y/N): "; 
			cin >> user_input;
				 
			if (user_input == 'N' || user_input == 'n'){
				cout << "Thanks for playing!" << endl;
				return 0;}
			else if (user_input == 'Y' || user_input == 'y') 
				break;
			else
				cout << "Error: Please enter Y or N." << endl;
		}		
	}
}

	
	

		

