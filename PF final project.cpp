#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

string rSentence() {
    const string s[] = {
        "Practice makes a man perfect",
        "The quick brown fox jumps over the lazy dog",
        "Typing games improve your speed",
        "Hard work is the key to success",
        "Time and tide wait for none"
    };
    return s[rand() % 5];
}

int countw(string s) {
    int count = 0;
    bool inWord = false;
    for (int i = 0; i < s.length(); i++) {
        if (isspace(s[i])) {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            count++;
        }
    }
    return count;
}

int countCw(string org, string typ) {
    int count = 0;
    int i = 0, j = 0;
    string w1 = "", w2 = "";

    while (i <= org.length() && j <= typ.length()) {
        if (i < org.length() && !isspace(org[i]))
            w1 += org[i];
        else if (w1 != "") {
            while (j < typ.length() && isspace(typ[j])) j++;
            w2 = "";
            while (j < typ.length() && !isspace(typ[j])) {
                w2 += typ[j];
                j++;
            }
            if (w1 == w2)
                count++;
            w1 = "";
        }
        i++;
    }

    return count;
}

void game(string (&players)[2], string s,int i) {
    cout << "\n" << players[i] << ", it's your turn." << endl;
    cout << "Type the following sentence:\n\n";
    cout << "\"" << s << "\"" << endl;
    cout << "\nPress Enter when you're ready...";
    cin.get();

    auto start = steady_clock::now();

    cout << "\nStart typing:\n";
    string input;
    getline(cin, input);

    auto end = steady_clock::now();
    auto time= duration_cast<milliseconds>(end - start).count();

    int tw = countw(s);
    int cw = countCw(s, input);
    float acc = (float(cw) / tw) * 100;

    cout << "\nResults for " << players[i] << ":\n";
    cout << "Time taken: " << time/1000 << " seconds\n";
    cout << "Total words: " << tw << endl;
    cout << "Correct words: " << cw << endl;
    cout << "Accuracy: " << acc << "%" << endl;
}

bool play() {
    char choice;
    cout << "Welcome to the 1v1 Typing Battle Game!\n";
    cout << "Do you want to play? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main() {
    srand(time(0)); 
    if (!play()) {
        cout << "Maybe next time. Goodbye!\n";
        return 0;
    }

    string players[2];
    cin.ignore();
    for(int i=0; i<2;i++){
    cout << "Enter name of Player "<<i+1<<" : ";
    getline(cin, players[i]);
    }

    string s= rSentence();
     
    for(int i=0; i<2;i++){ 
    game(players, s,i);
    }

    cout << "\nThanks for playing!\n";
    return 0;
}