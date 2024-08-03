#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

short rounds, playerScore = 0, computerScore = 0, drawTimes = 0;
string winner;

enum enRPS
{
	Rock = 1, Paper = 2, Scissors = 3
};

string getChoiceName(short choice) {
	switch (choice)
	{
	case Rock:
		return "Stone";
	case Paper:
		return "Paper";
	case Scissors:
		return "Scissors";
	default:
		break;
	}
}

int RandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}

void print_round_completed(short playerChoice, short computerChoice, short round) {
	winner = "";

	if (playerChoice == computerChoice) {
		system("color 60"); //  console yellow
		drawTimes++;
		winner += "[No Winner]";
	}
	else if ((playerChoice == enRPS::Rock) && (computerChoice == enRPS::Scissors) ||
		(playerChoice == enRPS::Paper) && (computerChoice == enRPS::Rock) ||
		(playerChoice == enRPS::Scissors) && (computerChoice == enRPS::Paper)) {
		system("color 20"); //  console green
		playerScore++;
		winner += "[Player]";
	}
	else {
		system("color 4F"); //  console red
		computerScore++;
		winner += "[Computer]";
		cout << '\a';	//	bell
	}

	cout << "\n_____________Round [" << round << "]_____________\n\n";
	cout << "Player Choice\t: " << getChoiceName(playerChoice) << '\n';
	cout << "Computer Choice\t: " << getChoiceName(computerChoice) << '\n';
	cout << "Round Winner\t: " << winner << '\n';
	cout << "___________________________________\n" << endl;
}

void play_rounds(int rounds) {
	short playerChoice, computerChoice;
	for (short i = 1; i <= rounds; i++)
	{
		cout << "Round [" << i << "] begins: \n\n";
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> playerChoice;
		if (playerChoice > 3 || playerChoice < 1) {
			i--;    //  repeats round entry
			cout << endl;
		}
		else {
			computerChoice = RandomNumber(1, 3);
			print_round_completed(playerChoice, computerChoice, i);
		}
	}
}

void welcome_screen() {
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n";
	cout << "\t\tWELCOME TO\n";
	cout << "\t  ROCK PAPER SCISSORS!!\n\n";
	cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n";
}

short how_many_rounds() {
	do
	{
		cout << "How many rounds do you want? (1 to 10): ";
		cin >> rounds;
	} while (rounds > 10 || rounds < 1);

	cout << '\n';
	return rounds;
}

bool keep_playing() {
	char choice;
	cout << "Do you want to play another game? (Y or N): ";
	cin >> choice;
	system("color 0F");	//	color black
	cout << endl;
	if (choice == 'Y' || choice == 'y') {
		rounds, playerScore = 0, computerScore = 0, drawTimes = 0;
		return true;
	}
	return false;
}

void game_over() {
	cout << "_____________________________________________\n\n";
	cout << "\t+++ G a m e  O v e r +++\n";
	cout << "_____________________________________________\n\n";
	cout << "______________[ Game Results ]_______________\n\n";
	cout << "Game Rounds\t: " << rounds << '\n';
	cout << "Player Won\t: " << playerScore << '\n';
	cout << "Computer Won\t: " << computerScore << '\n';
	cout << "Drawn Rounds\t: " << drawTimes << '\n';
	cout << "Fianl Winner\t: ";
	if (playerScore > computerScore)
		cout << "Player Won\n";
	else if (playerScore < computerScore)
		cout << "Computer Won\n";
	else
		cout << "No Winner\n";
	cout << endl;
}

int main() {
	srand(static_cast<unsigned int>(time(0)));  //  Seed the random number generator

	welcome_screen();
	do
	{
		play_rounds(how_many_rounds());
		game_over();
	} while (keep_playing());
	return 0;
}
