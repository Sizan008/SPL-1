#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
const int NUM_PLAYERS = 4;
const int MAX_ROUNDS = 20;
const string ROLES[NUM_PLAYERS] = {"Police", "Chor", "Dakat", "Babu"};
const string SCORE_FILE = "high_scores.txt";
struct Player{
    string name;
    string role;
    int score;
};
void initializePlayers(Player players[], string userName);
void shuffleRolesMarkov(string roles[], int size);
int findPlayerIndex(Player players[], int size, string name);
void playRound(Player players[], int round, bool &recordBroken, int &highestScore);
void calculatePoints(Player players[], int policeIndex, int guessIndex, int round);
void displayRoles(Player players[]);
void displayPoints(Player players[]);
void updateHighScores(int userScore, const string &userName, bool &recordBroken, int &highestScore);
void showLeaderboard();
void mergeSort(Player players[], int left, int right);
void merge(Player players[], int left, int mid, int right);
int binarySearch(Player players[], int size, const string &name);

int main(){
    srand(time(0)); 
    string userName;
    int rounds;
    cout << "Welcome to the 'Chor, Dakat, Police, Babu' Game!\n";
    cout << "Enter your name: ";
    cin >> userName;
    cout << "Enter the number of rounds (8, 12, 16, or 20): ";
    cin >> rounds;

    while (rounds != 8 && rounds != 12 && rounds != 16 && rounds != 20) {
        cout << "Invalid number of rounds! Please enter 8, 12, 16, or 20: ";
        cin >> rounds;
    }

    Player players[NUM_PLAYERS];
    initializePlayers(players, userName);

    int highestScore = 0;
    bool recordBroken = false;

    cout << "\nLet the game begin!\n";

    for (int round = 1; round <= rounds; ++round){
        cout << "\n--- Round " << round << " ---\n";
        playRound(players, round, recordBroken, highestScore);
        displayPoints(players);
    }
    cout << "\n--- Game Over! ---\n";
    mergeSort(players, 0, NUM_PLAYERS - 1);
    cout << "\nPlayers sorted by scores:\n";
    displayPoints(players);
    int index = binarySearch(players, NUM_PLAYERS, userName);
    if (index != -1) {
        cout << "Your score: " << players[index].score << "\n";
    } else{
        cout << "User not found!\n";
    }

    cout << "The winner is " << players[0].name << " with " << players[0].score << " points!\n";
    updateHighScores(players[0].score, userName, recordBroken, highestScore);
    showLeaderboard();

    if (recordBroken){
        cout << "Congratulations, " << userName << "! You broke the previous high score of " << highestScore << "!\n";
    }
     return 0;
}
void initializePlayers(Player players[], string userName){
    players[0].name = userName;
    players[0].score = 0;
    for (int i = 1; i < NUM_PLAYERS; ++i) {
        players[i].name = "Player " + to_string(i + 1);
        players[i].score = 0;
    }
}
void shuffleRolesMarkov(string roles[], int size){
    double transitionMatrix[NUM_PLAYERS][NUM_PLAYERS] = {
        {0.1, 0.3, 0.3, 0.3},
        {0.3, 0.1, 0.3, 0.3},
        {0.3, 0.3, 0.1, 0.3},
        {0.3, 0.3, 0.3, 0.1}
    };
    int currentState = rand() % size;
    for (int i = 0; i < size; ++i){
        double randVal = (rand() % 100) / 100.0;
        double cumulativeProbability = 0.0;
        for (int j = 0; j < size; ++j) {
            cumulativeProbability += transitionMatrix[currentState][j];
            if (randVal <= cumulativeProbability){
                swap(roles[i], roles[j]);
                currentState = j;
                break;
            }
        }
    }
}

void playRound(Player players[], int round, bool &recordBroken, int &highestScore){
    string roles[NUM_PLAYERS] = {"Police", "Chor", "Dakat", "Babu"};
    shuffleRolesMarkov(roles, NUM_PLAYERS);

    for (int i = 0; i < NUM_PLAYERS; ++i){
        players[i].role = roles[i];
    }
    int policeIndex = -1;
    for (int i = 0; i < NUM_PLAYERS; ++i){
        if (players[i].role == "Police") {
            policeIndex = i;
            cout << players[i].name << " is the Police!\n";
            break;
        }
    }

    if (policeIndex == 0){ 
        string guess;
        if (round % 2 != 0) {
            cout << "Police, guess the Chor (Enter Player Name): ";
        } else {
            cout << "Police, guess the Dakat (Enter Player Name): ";
        }
        cin >> guess;

        int guessIndex = findPlayerIndex(players, NUM_PLAYERS, guess);
        calculatePoints(players, policeIndex, guessIndex, round);
    } else{ 
        int guessIndex = rand() % NUM_PLAYERS;
        while (guessIndex == policeIndex) {
            guessIndex = rand() % NUM_PLAYERS;
        }
        calculatePoints(players, policeIndex, guessIndex, round);
    }
    displayRoles(players);
}

int findPlayerIndex(Player players[], int size, string name){
    for (int i = 0; i < size; ++i) {
        if (players[i].name == name) return i;
    }
    return -1; 
}
void displayRoles(Player players[]){
    cout << "\nRoles revealed:\n";
    for (int i = 0; i < NUM_PLAYERS; ++i){
        cout << players[i].name << ": " << players[i].role << "\n";
    }
}
void displayPoints(Player players[]){
    cout << "\n--- Points ---\n";
    for (int i = 0; i < NUM_PLAYERS; ++i){
        cout << players[i].name << ": " << players[i].score << " points\n";
    }
    cout<< "--------------\n";
}

void updateHighScores(int userScore, const string &userName, bool &recordBroken, int &highestScore){
    ifstream inputFile(SCORE_FILE);
    ofstream outputFile;
    int savedScore = 0;
    string savedName;
    if (inputFile.is_open()) {
        inputFile >> savedName >> savedScore;
        inputFile.close();
    }
    if (userScore > savedScore){
        highestScore = userScore;
        recordBroken = true;
        outputFile.open(SCORE_FILE);
        if (outputFile.is_open()){
            outputFile << userName << " " << userScore;
            outputFile.close();
        }
    } else {
        highestScore = savedScore;
        recordBroken = false;
    }
}

void showLeaderboard(){
    ifstream inputFile(SCORE_FILE);
    if (inputFile.is_open()) {
        string name;
        int score;
        cout << "\n--- Leaderboard ---\n";
        while (inputFile >> name >> score) {
            cout << name << ": " << score << " points\n";
        }
        inputFile.close();
        cout << "-------------------\n";
    } else {
        cout << "\nNo high scores available.\n";
    }
}

void mergeSort(Player players[], int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(players, left, mid);
        mergeSort(players, mid + 1, right);
        merge(players, left, mid, right);
    }
}

void merge(Player players[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Player *L = new Player[n1];
    Player *R = new Player[n2];
    for (int i = 0; i < n1; ++i)
        L[i] = players[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = players[mid + 1 + j];

    int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
        if (L[i].score >= R[j].score) {
            players[k] = L[i];
            i++;
        } else {
            players[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        players[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        players[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

int binarySearch(Player players[], int size, const string &name){
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (players[mid].name == name)
            return mid;
        else if (players[mid].name < name)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; 
}
void calculatePoints(Player players[], int policeIndex, int guessIndex, int round){
    bool guessedCorrectly = false;

    if (round % 2 != 0) { 
        if (players[guessIndex].role == "Chor"){
            players[policeIndex].score += 80; 
            guessedCorrectly = true;
        } else {
            players[policeIndex].score += 0;
        }

        for (int i = 0; i < NUM_PLAYERS; ++i){
            if (players[i].role == "Chor"){
                players[i].score += guessedCorrectly ? 0 : 50;
            } else if (players[i].role == "Dakat"){
                players[i].score += 60;
            } else if (players[i].role == "Babu"){
                players[i].score += 100;
            }
        }
    } else { 
        if (players[guessIndex].role == "Dakat"){
            players[policeIndex].score += 80;
            guessedCorrectly = true;
        } else {
            players[policeIndex].score += 0;
        }

        for (int i = 0; i < NUM_PLAYERS; ++i){
            if (players[i].role == "Dakat"){
                players[i].score += guessedCorrectly ? 0 : 60;
            } else if (players[i].role == "Chor"){
                players[i].score += 50;
            } else if (players[i].role == "Babu"){
                players[i].score += 100;
            }
        }
    }

    cout<<(guessedCorrectly? "Police guessed correctly!" : "Police guessed wrong!") << "\n";
}

