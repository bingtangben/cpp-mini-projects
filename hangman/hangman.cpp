#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <stdexcept>

using namespace std;

string mostFreq(set<string> dict)
{
    int max = 0;
    int count = 0;
    char maxc;

    for(char c = ' '; c <= '~'; ++c){
        count = 0;
        if (c == '_') continue;
        for (set<string>::iterator i = dict.begin(); i != dict.end(); ++i){
            string text = *i;
            if (text.find(c) != string::npos) count++;
        }

        if (count>max){
            max = count;
            maxc = c;
        }
    }

    string res(1, maxc);
    return res;

}

int main(int argc, char* argv[]){

    string word;

    if (argc == 2){
        word = argv[1];
    }
    else {
        throw invalid_argument("Please enter one word for hangman game!");
    }

    string copy(word), underscore;

    for (size_t i = 0; i < word.length(); ++i){
        underscore += "_";
    }

    set<string> dict;
    string wd;
    ifstream file("./linux.words");
    while (getline(file, wd)){
        if (wd.size() == copy.size()){
            dict.insert(wd);
        }
    }
    file.close();

    string guess;
    vector<string> missing;

    while (true){
        if (guess.size() > 0) cout << "guess: " << guess << endl;
        cout << underscore << " missing:";
        for (size_t i = 0; i < missing.size(); ++i){
            cout << " " << missing.at(i);
        }
        cout << endl << endl;;

        if (missing.size() == 6){
            cout << "You Lose! The word was: " << word << endl;
            break;
        }

        if (underscore == word){
            cout << "You win!" << endl;
            break;
        }

        guess = mostFreq(dict);

        if (copy.find(guess) != string::npos){
            vector<size_t> pos;
            size_t t;
            while((t = copy.find(guess)) != string::npos){
                pos.push_back(t);
                underscore.replace(t, 1, guess);
                copy.replace(t, 1, "_");
            }
            set<string> temp;
            for (set<string>::iterator i = dict.begin(); i != dict.end();){
                string text = *i;
                vector<size_t> tpos;
                while((t = text.find(guess)) != string::npos){
                    tpos.push_back(t);
                    text.replace(t, 1, "_");
                }
                if (tpos != pos){
                    dict.erase(i++);
                } else {
                    temp.insert(text);
                    ++i;
                }
            }
            dict = temp;
        } else {
            missing.push_back(guess);
            for (set<string>::iterator i = dict.begin(); i != dict.end();){
                string text = *i;
                if (text.find(guess) != string::npos){
                    dict.erase(i++);
                } else {
                    ++i;
                }
            }
        }

        cout << endl;
    }

    return 0;
}
