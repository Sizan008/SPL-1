#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<algorithm>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<random>
using namespace std;
const int NUM_PLAYERS = 4;
const int MAX_ROUNDS = 20;
const string ROLES[NUM_PLAYERS] ={"Police", "Chor", "Dakat", "Babu"};
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

void displayRolesSFML(sf::RenderWindow &window, Player players[]);
void displayPointsSFML(sf::RenderWindow &window, Player players[]);
void displayMessage(sf::RenderWindow &window, const string &message);
void displayUsernameInput(sf::RenderWindow &window, string &userName);
void displayMainMenu(sf::RenderWindow &window, bool &inMainMenu, string &userName);
void displayRoundSelection(sf::RenderWindow &window, int &rounds);
void displayRoleAssignment(sf::RenderWindow &window, Player players[], int &policeIndex);
void displayGuessingPhase(sf::RenderWindow &window, Player players[], int round, int policeIndex);

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600),"Chor Dakat Police Babu Game");

    string userName;
    bool inMainMenu=true;
    int rounds=0;
    Player players[NUM_PLAYERS];

    while (window.isOpen()){
        if (inMainMenu){
            displayMainMenu(window, inMainMenu, userName);
        } else{
            displayUsernameInput(window, userName);
            cout<< "Username set to: " << userName << endl;

            displayRoundSelection(window, rounds);
            cout<<"Rounds selected: "<<rounds<<endl;

            initializePlayers(players, userName);

            for (int round=1;round<=rounds;++round){
                cout <<"\n--- Round "<<round<<" ---\n";

                int policeIndex;
                displayRoleAssignment(window, players, policeIndex);

                string guessResult;
                if (policeIndex==0){
                    displayGuessingPhase(window, players, round, policeIndex);
                } else{
                    int guessIndex;
                    do {
                        guessIndex = rand() % NUM_PLAYERS;
                    } while (guessIndex == policeIndex);

                    string targetRole = (round % 2 != 0) ? "Chor" : "Dakat";
                    bool guessedCorrectly = (players[guessIndex].role == targetRole);

                    if (guessedCorrectly) {
                        players[policeIndex].score += 80;
                        guessResult = players[policeIndex].name + " (Computer) guessed correctly! " +
                                      players[guessIndex].name + " is the " + targetRole + "!";
                    } else {
                        guessResult = players[policeIndex].name + " (Computer) guessed wrong! " +
                                      players[guessIndex].name + " is not the " + targetRole + "!";
                    }

                    calculatePoints(players, policeIndex, guessIndex, round);
                }

                sf::Font font;
                if (!font.loadFromFile("arial.ttf")){
                    cerr << "Error: Could not load font file!" << endl;
                    return 0;
                }

                sf::Text resultText(guessResult, font, 25);
                resultText.setPosition(50, 250);
                resultText.setFillColor(sf::Color::White);

                sf::Clock clock;
                while (window.isOpen()){
                    sf::Event event;
                    while (window.pollEvent(event)){
                        if (event.type == sf::Event::Closed){
                            window.close();
                            return 0;
                        }
                    }

                    if (clock.getElapsedTime().asSeconds() > 3){
                        break;
                    }

                    window.clear(sf::Color::Black);
                    window.draw(resultText);
                    window.display();
                }
                clock.restart();
                while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)){
                        if (event.type == sf::Event::Closed){
                            window.close();
                            return 0;
                        }
                    }

                    if (clock.getElapsedTime().asSeconds() > 5){
                        break;
                    }

                    window.clear(sf::Color::Black);
                    displayRolesSFML(window, players);
                    displayPointsSFML(window, players);
                    window.display();
                }
            }
            mergeSort(players, 0, NUM_PLAYERS - 1);
            Player winner = players[0];

            sf::Font font;
            if (!font.loadFromFile("arial.ttf")) {
                cerr << "Error: Could not load font file!" << endl;
                return 0;
            }

            sf::Text leaderboardTitle("Leaderboard", font, 40);
            leaderboardTitle.setPosition(250, 50);
            leaderboardTitle.setFillColor(sf::Color::White);

            vector<sf::Text> leaderboardTexts;
            for (int i = 0; i < NUM_PLAYERS; ++i){
                sf::Text playerText(players[i].name + ": " + to_string(players[i].score) + " points", font, 25);
                playerText.setPosition(100, 150 + i * 50);
                playerText.setFillColor(sf::Color::White);
                leaderboardTexts.push_back(playerText);
            }

            sf::Text winnerText("Winner: " + winner.name + " with " + to_string(winner.score) + " points!", font, 30);
            winnerText.setPosition(100, 400);
            winnerText.setFillColor(sf::Color::Green);

            sf::Text gameEndText("Game Ends. Thank you for playing!", font, 30);
            gameEndText.setPosition(100, 450);
            gameEndText.setFillColor(sf::Color::Yellow);

            sf::Clock clock;
            while (window.isOpen()){
                sf::Event event;
                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                        return 0;
                    }
                }

                if (clock.getElapsedTime().asSeconds() > 10){
                    break;
                }

                window.clear(sf::Color::Black);
                window.draw(leaderboardTitle);
                for (auto &text : leaderboardTexts){
                    window.draw(text);
                }
                window.draw(winnerText);
                window.draw(gameEndText);
                window.display();
            }
          inMainMenu = true;
        }
    }
    return 0;
}
void initializePlayers(Player players[], string userName){
    players[0].name = userName;
    players[0].score = 0;
    for (int i = 1; i < NUM_PLAYERS; ++i){
        players[i].name = "Player " + to_string(i + 1);
        players[i].score = 0;
    }
}

void shuffleRolesMarkov(string roles[], int size){
    double transitionMatrix[NUM_PLAYERS][NUM_PLAYERS] = {
        {0.1, 0.3, 0.3, 0.3},
        {0.3, 0.1, 0.3, 0.3},
        {0.3, 0.2, 0.2, 0.3},
        {0.3, 0.3, 0.2, 0.2}
    };
    int currentState = rand() % size;
    for (int i = 0; i < size; ++i) {
        double randVal = (rand() % 100) / 100.0;
        double cumulativeProbability = 0.0;

        for (int j = 0; j < size; ++j){
            cumulativeProbability += transitionMatrix[currentState][j];
            if (randVal <= cumulativeProbability){
                swap(roles[i], roles[j]);
                currentState = j;
                break;
            }
        }
    }
    random_device rd;
    default_random_engine rng(rd());
    shuffle(roles, roles + size, rng);
}

void playRound(Player players[], int round, bool &recordBroken, int &highestScore){
    string roles[NUM_PLAYERS] = {"Police", "Chor", "Dakat", "Babu"};
    shuffleRolesMarkov(roles, NUM_PLAYERS);

    for (int i = 0; i < NUM_PLAYERS; ++i){
        players[i].role = roles[i];
    }

    int policeIndex = -1;
    for (int i = 0; i < NUM_PLAYERS; ++i){
        if (players[i].role == "Police"){
            policeIndex = i;
            cout << players[i].name << " is the Police!\n";
            break;
        }
    }

    int guessIndex = -1;
    if (policeIndex == 0){
        string guess;
        if(round % 2 != 0){
            cout<<"Police, guess the Chor (Enter Player Name from: ";
        } else{
            cout<<"Police, guess the Dakat (Enter Player Name from: ";
        }

        for(int i = 0; i < NUM_PLAYERS; ++i){
            if(i!= policeIndex){
                cout<<players[i].name;
                if(i < NUM_PLAYERS - 1) cout<<", ";
            }
        }
        cout<<"): ";

        cin>>guess;
        cout<<"Debug: User entered: '" << guess << "'\n";
        guessIndex = findPlayerIndex(players, NUM_PLAYERS, guess);
        while (guessIndex == -1 || guessIndex == policeIndex) {
            cout<< "Invalid guess! Please enter a valid player name: ";
            cin>> guess;
            cout<< "Debug: User entered: '" << guess << "'\n";
            guessIndex = findPlayerIndex(players, NUM_PLAYERS, guess);
        }
    } else{
        do{
            guessIndex = rand() % NUM_PLAYERS;
        } while (guessIndex == policeIndex);
    }

    calculatePoints(players, policeIndex, guessIndex, round);
    displayRoles(players);
}

int findPlayerIndex(Player players[], int size, string name){
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    name.erase(remove(name.begin(), name.end(), ' '), name.end());
    cout<< "Debug: Input name after normalization: '"<<name<<"'\n";

    for (int i = 0; i < size; ++i){
        string playerName = players[i].name;
        transform(playerName.begin(), playerName.end(), playerName.begin(), ::tolower);
        playerName.erase(remove(playerName.begin(), playerName.end(), ' '), playerName.end());

        cout<<"Debug: Comparing with normalized stored name: '"<< playerName<<"'\n";

        if (playerName == name)
         return i;
    }
    return -1;
}

void displayRoles(Player players[]){
    cout<< "\nRoles revealed:\n";
    for (int i = 0; i < NUM_PLAYERS; ++i){
        cout<<players[i].name << ": " << players[i].role << "\n";
    }
}

void displayPoints(Player players[]){
    cout << "\n--- Points ---\n";
    for (int i = 0; i < NUM_PLAYERS; ++i){
        cout<< players[i].name<< ": "<< players[i].score<< " points\n";
    }
    cout<<"--------------\n";
}

void updateHighScores(int userScore, const string &userName, bool &recordBroken, int &highestScore){
    ifstream inputFile(SCORE_FILE);
    ofstream outputFile;
    int savedScore = 0;
    string savedName;

    if (inputFile.is_open()){
        inputFile >> savedName >> savedScore;
        inputFile.close();
    }

    if (userScore > savedScore){
        highestScore = userScore;
        recordBroken = true;
        outputFile.open(SCORE_FILE);
        if (outputFile.is_open()) {
            outputFile<< userName<< " "<<userScore;
            outputFile.close();
        }
    } else{
        highestScore = savedScore;
        recordBroken = false;
    }
}

void showLeaderboard(){
    ifstream inputFile(SCORE_FILE);
    if (inputFile.is_open()){
        string name;
        int score;
        cout<< "\n--- Leaderboard ---\n";
        while (inputFile >> name >> score){
            cout<< name<< ": " <<score <<" points\n";
        }
        inputFile.close();
        cout<< "-------------------\n";
    } else{
        cout<<"\nNo high scores available.\n";
    }
}

void mergeSort(Player players[], int left, int right){
    if (left < right){
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
        if (L[i].score >= R[j].score){
            players[k] = L[i];
            i++;
        } else {
            players[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        players[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
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

    if (round % 2 != 0){
        if (players[guessIndex].role == "Chor"){
            players[policeIndex].score += 80;
            guessedCorrectly = true;
        }

        for (int i = 0; i < NUM_PLAYERS; ++i){
            if (players[i].role == "Chor") {
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

    cout<< (guessedCorrectly ? "Police guessed correctly!" : "Police guessed wrong!") << "\n";
}

void displayRolesSFML(sf::RenderWindow &window, Player players[]){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr<< "Error: Could not load font file!"<< endl;
        return;
    }

    sf::Text title("Roles Revealed", font, 30);
    title.setPosition(300, 50);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    for (int i = 0; i < NUM_PLAYERS; ++i){
        sf::Text playerText(players[i].name + ": " + players[i].role, font, 20);
        playerText.setPosition(100, 100 + i * 50);
        playerText.setFillColor(sf::Color::White);
        window.draw(playerText);
    }
}

void displayPointsSFML(sf::RenderWindow &window, Player players[]){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr<< "Error: Could not load font file!"<< endl;
        return;
    }

    sf::Text title("Points", font, 30);
    title.setPosition(350, 300);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    for (int i = 0; i < NUM_PLAYERS; ++i){
        sf::Text playerText(players[i].name + ": " + to_string(players[i].score) + " points", font, 20);
        playerText.setPosition(100, 350 + i * 50);
        playerText.setFillColor(sf::Color::White);
        window.draw(playerText);
    }
}

void displayMessage(sf::RenderWindow &window, const string &message){
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text(message, font, 25);
    text.setPosition(200, 300);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void displayUsernameInput(sf::RenderWindow &window, string &userName){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr << "Error: Could not load font file!" << endl;
        return;
    }

    sf::Text prompt("Enter your username:", font, 30);
    prompt.setPosition(150, 150);
    prompt.setFillColor(sf::Color::White);
    sf::Text input("", font, 30);
    input.setPosition(150, 250);
    input.setFillColor(sf::Color::White);

    userName = "";
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }

            if (event.type == sf::Event::TextEntered){
                if (event.text.unicode == '\b'){
                    if (!userName.empty()) {
                        userName.pop_back();
                    }
                } else if (event.text.unicode < 128 && event.text.unicode != '\r'){
                    userName += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
                if (!userName.empty()){
                    return;
                }
            }
        }
        input.setString(userName);
        window.clear(sf::Color::Black);
        window.draw(prompt);
        window.draw(input);
        window.display();
    }
}

void displayMainMenu(sf::RenderWindow &window, bool &inMainMenu, string &userName){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr<< "Error: Could not load font file!" << endl;
        return;
    }

    sf::Text title("Chor Dakat Police Babu Game", font, 40);
    title.setPosition(150, 50);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape box1(sf::Vector2f(400, 50));
    box1.setPosition(200, 200);
    box1.setFillColor(sf::Color::Blue);

    sf::Text option1("Single Player Mode", font, 30);
    option1.setPosition(220, 205);
    option1.setFillColor(sf::Color::White);

    sf::RectangleShape box2(sf::Vector2f(400, 50));
    box2.setPosition(200, 300);
    box2.setFillColor(sf::Color::Red);

    sf::Text option2("Exit", font, 30);
    option2.setPosition(220, 305);
    option2.setFillColor(sf::Color::White);

    while (window.isOpen() && inMainMenu){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (box1.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        cout << "Single Player Mode selected.\n";
                        inMainMenu = false; // Exit the main menu
                        return; // Proceed to username input
                    } else if (box2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        cout<< "Exiting the game.\n";
                        window.close();
                    }
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(box1);
        window.draw(option1);
        window.draw(box2);
        window.draw(option2);
        window.display();
    }
}

void displayRoundSelection(sf::RenderWindow &window, int &rounds){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr<< "Error: Could not load font file!"<< endl;
        return;
    }

    sf::Text title("Select Number of Rounds", font, 40);
    title.setPosition(150, 50);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape box1(sf::Vector2f(400, 50));
    box1.setPosition(200, 200);
    box1.setFillColor(sf::Color::Blue);

    sf::Text option1("8 Rounds", font, 30);
    option1.setPosition(220, 205);
    option1.setFillColor(sf::Color::White);

    sf::RectangleShape box2(sf::Vector2f(400, 50));
    box2.setPosition(200, 300);
    box2.setFillColor(sf::Color::Green);

    sf::Text option2("16 Rounds", font, 30);
    option2.setPosition(220, 305);
    option2.setFillColor(sf::Color::White);

    sf::RectangleShape box3(sf::Vector2f(400, 50));
    box3.setPosition(200, 400);
    box3.setFillColor(sf::Color::Red);

    sf::Text option3("20 Rounds", font, 30);
    option3.setPosition(220, 405);
    option3.setFillColor(sf::Color::White);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (box1.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        rounds = 8;
                        return;
                    } else if (box2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        rounds = 16;
                        return;
                    } else if (box3.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        rounds = 20;
                        return;
                    }
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(box1);
        window.draw(option1);
        window.draw(box2);
        window.draw(option2);
        window.draw(box3);
        window.draw(option3);
        window.display();
    }
}

void displayRoleAssignment(sf::RenderWindow &window, Player players[], int &policeIndex){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr<< "Error: Could not load font file!"<< endl;
        return;
    }

    sf::Text title("Select a Box to Assign Roles", font, 40);
    title.setPosition(100, 50);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape box1(sf::Vector2f(150, 150));
    box1.setPosition(100, 200);
    box1.setFillColor(sf::Color::White);

    sf::RectangleShape box2(sf::Vector2f(150, 150));
    box2.setPosition(300, 200);
    box2.setFillColor(sf::Color::White);

    sf::RectangleShape box3(sf::Vector2f(150, 150));
    box3.setPosition(500, 200);
    box3.setFillColor(sf::Color::White);

    sf::RectangleShape box4(sf::Vector2f(150, 150));
    box4.setPosition(700, 200);
    box4.setFillColor(sf::Color::White);

    bool rolesAssigned = false;

    while (window.isOpen() && !rolesAssigned){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (box1.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                        box2.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                        box3.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
                        box4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        shuffleRolesMarkov(const_cast<string*>(ROLES), NUM_PLAYERS);
                        for (int i = 0; i < NUM_PLAYERS; ++i) {
                            players[i].role = ROLES[i];
                            if (players[i].role == "Police"){
                                policeIndex = i;
                            }
                        }
                        rolesAssigned = true;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(box1);
        window.draw(box2);
        window.draw(box3);
        window.draw(box4);
        window.display();
    }
    sf::Text policeRole("Police: " + players[policeIndex].name, font, 30);
    policeRole.setPosition(100, 400);
    policeRole.setFillColor(sf::Color::White);

    sf::Clock clock;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }
        }

        if (clock.getElapsedTime().asSeconds() > 3){
            return;
        }
        window.clear(sf::Color::Black);
        window.draw(policeRole);
        window.display();
    }
}

void displayGuessingPhase(sf::RenderWindow &window, Player players[], int round, int policeIndex){
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        cerr << "Error: Could not load font file!" << endl;
        return;
    }

    string targetRole = (round % 2 != 0) ? "Chor" : "Dakat";
    sf::Text title("Police, Identify the " + targetRole + "!", font, 40);
    title.setPosition(100, 50);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape box2(sf::Vector2f(200, 50));
    box2.setPosition(200, 200);
    box2.setFillColor(sf::Color::White);

    sf::Text option2(players[1].name, font, 30);
    option2.setPosition(220, 205);
    option2.setFillColor(sf::Color::Black);

    sf::RectangleShape box3(sf::Vector2f(200, 50));
    box3.setPosition(200, 300);
    box3.setFillColor(sf::Color::White);

    sf::Text option3(players[2].name, font, 30);
    option3.setPosition(220, 305);
    option3.setFillColor(sf::Color::Black);

    sf::RectangleShape box4(sf::Vector2f(200, 50));
    box4.setPosition(200, 400);
    box4.setFillColor(sf::Color::White);

    sf::Text option4(players[3].name, font, 30);
    option4.setPosition(220, 405);
    option4.setFillColor(sf::Color::Black);

    bool guessMade = false;
    int guessIndex = -1;

    while (window.isOpen() && !guessMade){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (box2.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        guessIndex = 1;
                        guessMade = true;
                    } else if (box3.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        guessIndex = 2;
                        guessMade = true;
                    } else if (box4.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        guessIndex = 3;
                        guessMade = true;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(box2);
        window.draw(option2);
        window.draw(box3);
        window.draw(option3);
        window.draw(box4);
        window.draw(option4);
        window.display();
    }
    bool guessedCorrectly = (players[guessIndex].role == targetRole);
    sf::Text result("", font, 30);
    if (guessedCorrectly) {
        result.setString("Correct! " + players[guessIndex].name + " is the " + targetRole + "!");
        result.setFillColor(sf::Color::Green);
        players[policeIndex].score += 80;
    } else {
        result.setString("Wrong! " + players[guessIndex].name + " is not the " + targetRole + "!");
        result.setFillColor(sf::Color::Red);
    }
    result.setPosition(100, 500);
    calculatePoints(players, policeIndex, guessIndex, round);

    sf::Clock clock;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }
        }

        if (clock.getElapsedTime().asSeconds()>3){
            break;
        }
        window.clear(sf::Color::Black);
        window.draw(result);
        window.display();
    }
    sf::Text rolesTitle("Roles Revealed:", font, 30);
    rolesTitle.setPosition(100, 50);
    rolesTitle.setFillColor(sf::Color::White);

    vector<sf::Text> roleTexts;
    for (int i = 0; i < NUM_PLAYERS; ++i){
        sf::Text roleText(players[i].name + ": " + players[i].role + " (" + to_string(players[i].score) + " points)", font, 20);
        roleText.setPosition(100, 100 + i * 30);
        roleText.setFillColor(sf::Color::White);
        roleTexts.push_back(roleText);
    }

    clock.restart();
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
            }
        }

        if (clock.getElapsedTime().asSeconds()>5){
            return;
        }
        window.clear(sf::Color::Black);
        window.draw(rolesTitle);
        for (auto &roleText : roleTexts){
            window.draw(roleText);
        }
        window.display();
    }
}
