// Author:               Marla Boeer
// Assignment Number:    Lab 8: Tic-Tac-Toe game
// Due Date:             11/08/2016

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
using namespace std;


//The game board should be a class.
class Board 
{
			
	public:
	//struct to keep track of board values independently
	struct Square 
	{	char value;   		// Currently displayed character.
		boolean open; 		// Availability
		short int x;  		// X-Coordinate
		short int y;  		// Y-Coordinate
	};
	//struct to keep track of player values independently
	struct Player 
	{	char piece;       	// Player's identifying character.
		int playerColor;  	// Character piece color.
		int gamesWon = 0; 	// Win accumulator.
		
	};
	
	//ATTRIBUTES________________________________________________________________________________________
	
	//screen object to place cursor
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);		

	// Create & initialize board squares.
	Square place1{'1', true, 9, 6},
		   place2{'2', true, 13, 6},
		   place3{'3', true, 17, 6},
		   place4{'4', true, 9, 4},
		   place5{'5', true, 13, 4},
		   place6{'6', true, 17, 4},
		   place7{'7', true, 9, 2},
		   place8{'8', true, 13, 2},
		   place9{'9', true, 17, 2};
/*couldn't use properly------------------------------------------------		   
	char boardArray[3][3]{{place7.value, place8.value, place9.value},
						{place4.value, place5.value, place6.value},
						{place1.value, place2.value, place3.value}};*/
	// Create players.
	Player p1, p2;
	
	int totalGames=0;
	int catGames=0;
	//RESET FUNCTION________________________________________________________________________________________
	void resetBoard()
	{   // Resets characters in squares  
		place1.value = '1'; place2.value = '2'; place3.value = '3';
		place4.value = '4'; place5.value = '5'; place6.value = '6';
		place7.value = '7'; place8.value = '8'; place9.value = '9';
		// Resets availability in squares
		place1.open = true; place2.open = true; place3.open = true;
		place4.open = true; place5.open = true; place6.open = true;
		place7.open = true; place8.open = true; place9.open = true;		
		
		// Draw board
		system("cls"); 							// Erase current board 
		SetConsoleTextAttribute(screen, 7); 	//Draw in white
		COORD p = { 0, 0 };
		SetConsoleCursorPosition(screen, p ); 	//Draw at the top of screen
		
		cout << "\n\n";
		cout << setw(10)<<place7.value<<" | "<<place8.value<<" | "<<place9.value<<endl;
		cout << setw(10)<<"-"<<"--------"<< endl;
		cout << setw(10)<<place4.value<<" | "<<place5.value<<" | "<<place6.value<<endl;
		cout << setw(10)<<"-"<<"--------"<< endl;
		cout << setw(10)<<place1.value<<" | "<<place2.value<<" | "<<place3.value<<endl;			
	}
	//SHOW SCOREBOARD________________________________________________________________________________
	void showScore()
	{
		SetConsoleTextAttribute(screen, 15); 	//Draw in white
		COORD a = { 30, 2 };
		SetConsoleCursorPosition(screen, a ); 	
		cout <<"_WINS_"<<"_WIN%_"<<"_LOSS_"<<"_LOSS%_"<<"_CAT_"<<"_CAT%_"<<endl;
		
		int percentCat = (double)catGames/totalGames * 100;
		
		COORD b = { 30, 3 };
		SetConsoleCursorPosition(screen, b ); 
		cout << setw(3)<<p1.gamesWon<<setw(6)<<((int)((double)p1.gamesWon/totalGames * 100))<<"%";
		cout << setw(6)<<(totalGames-p1.gamesWon)<<setw(7)<<((int)((double)(totalGames-p1.gamesWon)/totalGames * 100))<<"%";
		cout << setw(5)<<catGames<<setw(6)<<percentCat<<"%   Player 1"<<endl;	
		
		COORD c = { 30, 4 };
		SetConsoleCursorPosition(screen, c ); 
		cout << setw(3)<<p2.gamesWon<<setw(6)<<((int)((double)p2.gamesWon/totalGames * 100))<<"%";
		cout << setw(6)<<(totalGames-p2.gamesWon)<<setw(7)<<((int)((double)(totalGames-p2.gamesWon)/totalGames * 100))<<"%";
		cout << setw(5)<<catGames<<setw(6)<<percentCat<<"%   Player 2"<<endl;		
	}
	//SET PLAYERS________________________________________________________________________________________
	void setPlayerOptions()
	{	
		// Set Player 1 values
		cout<< "Player 1 "<<endl;
		p1.piece = setValue(); 
		p1.playerColor = setColor();
		SetConsoleTextAttribute(screen, p1.playerColor);
		cout << "Player 1 is playing as "<< p1.piece << endl;
		system("PAUSE");
		system("cls");
		 	
		// Set Player 2 values
		SetConsoleTextAttribute(screen, 7);
		cout<< "Player 2 "<<endl;
		p2.piece = setValue();
		while (p2.piece == p1.piece)
		{
			cout << "Please enter a different value than Player 1: "<<endl;
			p2.piece = setValue();
		}
		p2.playerColor = setColor();
		SetConsoleTextAttribute(screen, p2.playerColor);
		cout << "Player 2 is playing as "<<p2.piece<<endl;
		system("PAUSE");
		system("cls");
		cin.clear();
		p1.gamesWon = 0;
		p2.gamesWon = 0;		
	}
	char setValue() // Used in setPlayers
	{	char value;
		cout<< "Which character would you like to play as? (X or O)\n";
		cin.get(value);	
		cin.sync();
		while (true)
		{
			if(isalpha(value))
			{
				return value;	
			}
			else 
			{	cout<< "Needs to be a valid letter: "<<endl;
				cin.get(value);
				cin.sync();		
			}		 
		}
	}
	int setColor() // Used in setPlayers
	{	int choice = 0;
		cout<< "Type number of the color would you prefer to be: \n";
		cout<< "BlUE = 1, RED = 2, PINK = 3, YELLOW = 4"<<endl;
		cin >> choice;
		cin.sync();
		while (true)
		{	if(choice==1 || choice==2 || choice==3 || choice==4)  	
			{	choice += 10;
				return choice;	
			}
			else
			{	cout<< "BlUE = 1, RED = 2, PINK = 3, YELLOW = 4" <<endl;
				cin.ignore();
				cin >> choice;
				cin.sync();		
			}	 					 
		}			
	}
	
	//CHECK STATUS & CHANGE PLAYER___________________________________________________________________
	bool checkScore(Player currentPlayer)
	{	//currentPlayer.piece == place1.value&& 
		COORD c = { 30, 5 };	
		SetConsoleCursorPosition(screen, c ); 		
		if( place1.value == place2.value && place2.value == place3.value)
		{ //123
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place4.value == place5.value && place5.value == place6.value)
		{ //456
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place7.value == place8.value && place8.value == place9.value)
		{ //789
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place7.value == place4.value && place4.value == place1.value)
		{ //741
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place5.value == place8.value && place8.value == place2.value)
		{ //852
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place9.value == place6.value && place6.value == place3.value)
		{ //963
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place1.value == place5.value && place5.value == place9.value)
		{ //159
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(place3.value == place5.value && place5.value == place7.value)
		{ //357
				if (currentPlayer.piece == p1.piece) 
					p1.gamesWon += 1;
				else if (currentPlayer.piece == p2.piece)
					p2.gamesWon += 1;
				++totalGames;
				cout <<currentPlayer.piece<< " won! Game over.\t";
				system("PAUSE");
				return true;
				
		}
		if(!place1.open && !place2.open && !place3.open && !place4.open &&
				!place5.open && !place6.open && !place7.open && !place8.open && !place9.open)
		{ //123456789
				++catGames;
				++totalGames;
				cout <<"Cat game, losers.\t";
				system("PAUSE");
				return true;		
		}
		else {
			return false;
		}
// USE OF ARRAY THAT DIDN'T WORK-------------------------------------------
//		char boardArray[3][3]{{place7.value, place8.value, place9.value},
//						{place4.value, place5.value, place6.value},
//						{place1.value, place2.value, place3.value}};
//		for(int row=0; row < 3; row++)
//		{
//			for(int col=0; col < 3; col++)
//			{
//				if (boardArray[row][col] == currentPlayer.piece){
//					marks++;
//				}
//			}
//			if(marks == 3)
//			{
//				++currentPlayer.gamesWon;
//				++totalGames;
//				return true;
//				cout <<currentPlayer.piece<< "won. Game over";
//			}
//		}		
		
//		marks = 0;
//		row = 0;
//		col = 0;
//		for(int col = 0; col < 3; col++)
//		{
//			for(int row = 0; row < 3; row++)
//			{
//				if (boardArray[row][col] == currentPlayer.piece){
//					marks++;
//				}
//			}
//			if(marks == 3)
//			{
//				++currentPlayer.gamesWon;
//				++totalGames;
//				return true;
//			}
//		}	
//			
//		if (boardArray[0][0] == currentPlayer.piece){
//			if (boardArray[1][1] == currentPlayer.piece){
//				if (boardArray[2][2] == currentPlayer.piece){
//					++currentPlayer.gamesWon;
//					++totalGames;
//					return true;	
//				}
//			}		
//		}
//			
//		if (boardArray[2][0] == currentPlayer.piece){
//			if (boardArray[1][1] == currentPlayer.piece){
//				if (boardArray[0][2] == currentPlayer.piece){
//					++currentPlayer.gamesWon;
//					++totalGames;
//					return true;	
//				}
//			}		
//		}
//			
//		if (place1.value == '1' || place2.value == '2'|| place3.value == '3'||
//			place4.value == '4'|| place5.value == '5'|| place6.value == '6'||
//			place7.value == '7'|| place8.value == '8'|| place9.value == '9')
//		{
//			++catGames;
//			++totalGames;
//			return true;	
//		}
				
	}

	//CHECK SWITCH___________________________________________________________________________________
	bool checkChoice(int squareChoice, Player currentPlayer)
	{
		COORD p = { 0, 0 };
		SetConsoleCursorPosition(screen, p ); 	// Reset cursor to match gameboard display.
		switch(squareChoice)					//VALIDATE SQUARE IS OPEN, PLACE PIECE, CLAIM SQUARE
		{
			case 1: 
			{	if (place1.open){
					COORD p = { place1.x, place1.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place1.open = false;
					place1.value = currentPlayer.piece;
					return true;	
				}
			}	break;
				
			case 2: 
			{	if (place2.open){
					COORD p = { place2.x, place2.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place2.open = false;
					place2.value = currentPlayer.piece;
					return true;	
				}
				
			}	break;
						
			case 3: 
			{	if (place3.open){
					COORD p = { place3.x, place3.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place3.open = false;
					place3.value = currentPlayer.piece;
					return true;	
				}
				
			}	break;
					
			case 4: 
			{	if (place4.open){
					COORD p = { place4.x, place4.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place4.open = false;
					place4.value = currentPlayer.piece;
					return true;	
				}		
			}	break;
						
			case 5: 
			{	if (place5.open){
					COORD p = { place5.x, place5.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place5.open = false;
					place5.value = currentPlayer.piece;
					return true;	
				}	
			}	break;
				
			case 6: 
			{	if (place6.open){
					COORD p = { place6.x, place6.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place6.open = false;
					place6.value = currentPlayer.piece;
					return true;	
				}
				
			}	break;
						
			case 7: 
			{
				if (place7.open){
					COORD p = { place7.x, place7.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place7.open = false;
					place7.value = currentPlayer.piece;
					return true;	
				}
			}	break;
				
			case 8: 
			{	if (place8.open){
					COORD p = { place8.x, place8.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place8.open = false;
					place8.value = currentPlayer.piece;
					return true;	
				}	
			}	break;
						
			case 9: 
			{	if (place9.open){
					COORD p = { place9.x, place9.y };
					SetConsoleCursorPosition(screen, p );
					cout<<currentPlayer.piece<<endl;
					place9.open = false;
					place9.value = currentPlayer.piece;
					return true;	
				}	
			}	break;
						
			default : 
			{	
 				COORD p = { 0, 8 };
 				SetConsoleCursorPosition(screen, p );
				cout<< squareChoice <<" is not available.";
 				return false;
			}			
		} 						
	}				

	//GET MOVE_______________________________________________________________________________________
	void getMove(Player currentPlayer)
	{	int squareChoice = 0; 					// Variable to hold player's choice.
		
		SetConsoleTextAttribute(screen, currentPlayer.playerColor); // Set color to current player.
		
		bool done = false;						// Flag for usable choice.
		while(!done)
		{
			
			COORD q = { 0, 9 };
			SetConsoleCursorPosition(screen, q ); 	// Dispay prompts below gameboard.
			cout << "What number position would you like to occupy?"<<endl;
			cin >> squareChoice; 
			cin.sync();
			cin.clear();
			if (squareChoice > 9 || squareChoice < 0 || isalpha(squareChoice)) //VALIDATE INPUT
			{	do {
					cout <<"Choice needs to be between 1 and 9: ";
					cin >> squareChoice;
					cin.sync();
					cin.clear();
				} while (squareChoice > 9 || squareChoice < 0 || isalpha(squareChoice));
			}
			done = checkChoice(squareChoice, currentPlayer); 
		}							
	}

};

int main()
{	
	bool reset = false;
	bool moves = true;
	Board newGame; // Create a Board class object
	newGame.setPlayerOptions();
 	
	while(true)
	{
		cin.sync();
		cin.clear();
		newGame.resetBoard();
		if (newGame.totalGames)
			newGame.showScore();
		newGame.getMove(newGame.p1);
		moves = true;
		while(moves)
		{
			
				if(!newGame.checkScore(newGame.p1))
				{
					newGame.getMove(newGame.p2);
					if(!newGame.checkScore(newGame.p2))
					newGame.getMove(newGame.p1);
					else moves = false;
				}		
				else moves = false;	
			
						
					
		}	
	}
	
		
	
	return 0;
}
/*
         
         
         X | Z | Z            _WINS__WIN%__LOSS__LOSS%__CAT__CAT%_
         ---------              1    33%     2     66%    1    33%   Player 1
         Z | X | X              1    33%     2     66%    1    33%   Player 2
         ---------            Cat game, losers. Press any key to continue . . .
         X | X | Z


What number position would you like to occupy?
7


*/
