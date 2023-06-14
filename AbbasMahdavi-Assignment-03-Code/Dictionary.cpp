
//By Abbas and Melisa

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
using namespace std;

void loadData(){
    fstream filestr;
    string txtFile;
    cout << "! Opening data file... : ";
    getline(cin, txtFile);
    filestr.open (txtFile);
    while (!filestr.is_open()){
        cout << "<!>ERROR<!> ===> File could not be opened. \n<!>ERROR<!> ===> Provided file path: " << txtFile << endl;
        cout << "Enter CORRECT data file path (hit: '../Data.CS.SFSU.txt') :";
        getline(cin, txtFile);
        filestr.open (txtFile);
    }
}

inline string printInst(){
    string instructions =  "      |\n       PARAMETER HOW-TO,  please enter:\n       1. A search key -then 2. An optional part of speech -then\n       3. An optional 'distinct' -then 4. An optional 'reverse'\n       |\n";
    return instructions;
}


void fixData(std::string& file_contents, const std::string& keyWord, const std::string& replacedKeyWord) {
    auto pos = file_contents.find(keyWord);
    while (pos != std::string::npos) {
        file_contents.replace(pos, keyWord.length(), replacedKeyWord);
        pos = file_contents.find(keyWord, pos);
    }
}

map<string, vector<string> > storeData() {

    string line;

    ifstream file("../Data.CS.SFSU.txt");
    map<string, vector<string> > dictionary;
    while (getline(file, line)) {
        istringstream ss(line);
        string keyword;
        vector<string> vector1;
        while (getline(ss, keyword, '|')) {
            vector1.push_back(keyword);
        }
        vector<string> vector2;
        for (int i = 1; i < vector1.size(); i++) {
            vector2.push_back(vector1[i]);
        }
        string replacedKey = vector1[0];
        vector<string> completeVector3;
        for (auto reformat : vector2) {
            fixData(reformat, "-=>>", " ");
            fixData(reformat, "adverb ", "[adverb] : ");
            fixData(reformat, "pronoun ", "[pronoun] : ");
            fixData(reformat, "noun ", "[noun] : ");
            fixData(reformat, "verb ", "[verb] : ");
            fixData(reformat, "adjective ", "[adjective] : ");
            fixData(reformat, "conjunction ", "[conjunction] : ");
            fixData(reformat, "preposition ", "[preposition] : ");
            fixData(reformat, "interjection ", "[interjection] : ");
            completeVector3.push_back(reformat);
        }
        dictionary.insert(make_pair(replacedKey, completeVector3));
    }
    return dictionary;
}

void splitString(const string& s, vector<string> &v){
    string temp;
    for(char i : s){
        if(i==' '){
            v.push_back(temp);
            temp = "";
        } else{
            temp.push_back(i);
        }
    } v.push_back(temp);
}

string CAPSFirstLetter(string text) {
    for (int x = 0; x < text.length(); x++){
        if (x == 0){
            text[x] = toupper(text[x]);
        }
        else if (text[x - 1] == ' '){
            text[x] = toupper(text[x]);
        }
    }
    return text;
}

bool checker(const string& a, const string& b){
    return a<b;
}
vector<string> sortInOrder(vector<string> a){
    sort(a.begin(),a.end(),checker);
    return a;
}

void getWordsDefs(const string& find, map<string, vector<string> > dictionary){
    cout<<"      |"<<endl;
    vector<string> sortedWords;
    for (const string& s : dictionary.at(find)) {
        vector<string> inputSplit;
        splitString(find, inputSplit);
        const string& sentence=s;
        sortedWords.push_back(sentence);
    }
    sortedWords = sortInOrder(sortedWords);
    for(auto & i : sortedWords){
        vector<string> inputSplit;
        splitString(find, inputSplit);
        cout<<"       "<<CAPSFirstLetter(inputSplit[0])<<" " << i << endl;
    }
    cout<<"      |"<<endl;
}

void getPOS(const string& find, const map<string, vector<string> >& dictionary, const string& find2){
    vector<string> containsSpeech;
    for (const string& x : dictionary.at(find)) {
        string open = "[";
        string close = "]";
        string pos = open+find2+close;

        std::string getPOS = x.substr(0,x.find(' '));
        if(pos == getPOS){
            string keyWordAndDef = "       " + CAPSFirstLetter(find) + " " + x + "\n";
            containsSpeech.push_back(keyWordAndDef);
        }
    }
    for (auto & i : containsSpeech) {
        cout << i;
    }

    if (containsSpeech.empty()){
        cout << "\n       <NOT FOUND> To be considered for the next release. Thank you.\n     |"<< endl;
        cout << printInst();
    }

}

void getDistinctPOS(const string& find, map<string, vector<string> > dictionary){
    vector<string> sortedWords;
    for (const string& s : dictionary.at(find)) {
        vector<string> inputSplit;
        splitString(find, inputSplit);
        string sentence=s;
        sortedWords.push_back(sentence);
    }
    sortedWords = sortInOrder(sortedWords);
    vector<string>::iterator x;
    sort(sortedWords.begin(), sortedWords.end());
    x = unique(sortedWords.begin(), sortedWords.begin() + sortedWords.size());
    sortedWords.resize(distance(sortedWords.begin(), x));
    for (x = sortedWords.begin(); x != sortedWords.end(); ++x) {
        vector<string> inputSplit;
        splitString(find, inputSplit);
        cout << "       " << CAPSFirstLetter(inputSplit[0]) << " " << *x << endl;
    }
}

void getReversePOS(const string& find, map<string, vector<string> > dictionary){
    vector<string> sortedWords;
    for (const string& s : dictionary.at(find)) {
        vector<string> inputSplit;
        splitString(find, inputSplit);
        string sentence=s;
        sortedWords.push_back(sentence);
    }
    sortedWords = sortInOrder(sortedWords);
    reverse(sortedWords.begin(), sortedWords.end());
    for(auto & i : sortedWords){
        vector<string> inputSplit;
        splitString(find, inputSplit);
        cout<<"       "<<CAPSFirstLetter(inputSplit[0])<<" " << i << endl;
    }
}

void checkWordsType(const string& find, const map<string, vector<string> >& dictionary){
    vector<string> inputSplit;
    vector<string> inputSection;
    splitString(find, inputSplit);
    splitString(find, inputSection);

    if (inputSplit.size()==1){
        if (dictionary.count(find)){
            getWordsDefs(find, dictionary);
        } else{
            cout << "      |\n       <NOT FOUND> To be considered for the next release. Thank you.\n      |"<< endl;
            cout << printInst();
        }
    }
    else if (inputSplit.size()==2){
        if (inputSplit[1]=="distinct"){
            cout<<"      |"<<endl;
            getDistinctPOS(inputSection[0], dictionary);
            cout<<"      |"<<endl;
        }else if (inputSplit[1]=="reverse"){
            cout<<"      |"<<endl;
            getReversePOS(inputSection[0], dictionary);
            cout<<"      |"<<endl;
        }
        else if (inputSplit[1]=="adjective" || inputSplit[1]=="adverb" || inputSplit[1]=="conjunction" || inputSplit[1]=="interjection" || inputSplit[1]=="noun" || inputSplit[1]=="preposition" || inputSplit[1]=="pronoun" || inputSplit[1]=="verb" ){
            if(dictionary.count(inputSplit[0])){
                cout<<"      |"<<endl;
                getPOS(inputSplit[0], dictionary, inputSplit[1]);
                cout<<"      |"<<endl;
            } else{
                cout << "      |\n       <NOT FOUND> To be considered for the next release. Thank you.\n      |"<< endl;
                cout << printInst();
            }
        }
        else{
            cout<<"      |"<<endl;
            cout<<"       <The entered 2nd parameter '"<<inputSplit[1]<<"' is NOT a part of speech.>\n"<<
                "       <The entered 2nd parameter '"<<inputSplit[1]<<"' is NOT 'distinct'.>\n"<<
                "       <The entered 2nd parameter '"<<inputSplit[1]<<"' is NOT 'reverse'.>\n" <<
                "       <The entered 2nd parameter '"<<inputSplit[1]<<"' was disregarded.>\n" <<
                "       <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>"<<endl;
            cout<<"      |"<<endl;
            getWordsDefs(inputSplit[0], dictionary);
        }
    }

    else if (inputSplit.size()==3){
        if (inputSplit[2]=="distinct"){
            if(inputSplit[1]=="adjective" || inputSplit[1]=="adverb" || inputSplit[1]=="conjunction" || inputSplit[1]=="interjection" || inputSplit[1]=="noun" || inputSplit[1]=="preposition" || inputSplit[1]=="pronoun" || inputSplit[1]=="verb" ){
                cout<<"      |"<<endl;
                getPOS(inputSplit[0], dictionary, inputSplit[1]);
                cout<<"      |"<<endl;
                cout << "      |" << endl;
                getDistinctPOS(inputSplit[0], dictionary);
                cout << "      |" << endl;
            }else if(inputSection[1] == "reverse") {
                cout << "      |" << endl;
                getReversePOS(inputSection[0], dictionary);
                cout << "      |" << endl;
                cout << "      |" << endl;
                getDistinctPOS(inputSplit[0], dictionary);
                cout << "      |" << endl;
            }else if(inputSection[1] == "distinct"){
                cout<<"      |\n       PARAMETER HOW-TO,  please enter:\n       1. A search key -then 2. An optional part of speech -then\n       3. An optional 'distinct' -then 4. An optional 'reverse'\n       |\n";
            }else {
                cout << "      |" << endl;
                cout << "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT a part of speech.>\n" <<
                     "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT 'distinct'.>\n" <<
                     "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT 'reverse'.>\n" <<
                     "       <The entered 2nd parameter '" << inputSplit[1] << "' was disregarded.>\n" <<
                     "       <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
                cout << "      |" << endl;
                getDistinctPOS(inputSplit[0], dictionary);
            }
        }else if (inputSplit[2]=="reverse"){
            if(inputSplit[1]=="adjective" || inputSplit[1]=="adverb" || inputSplit[1]=="conjunction" || inputSplit[1]=="interjection" || inputSplit[1]=="noun" || inputSplit[1]=="preposition" || inputSplit[1]=="pronoun" || inputSplit[1]=="verb" ){
                cout<<"      |"<<endl;
                getPOS(inputSplit[0], dictionary, inputSplit[1]);
                cout<<"      |"<<endl;
                cout << "      |" << endl;
                getReversePOS(inputSplit[0], dictionary);
                cout << "      |" << endl;
            }else if(inputSection[1] == "distinct") {
                cout << "      |" << endl;
                getDistinctPOS(inputSection[0], dictionary);
                cout << "      |" << endl;
                cout << "      |" << endl;
                getReversePOS(inputSplit[0], dictionary);
                cout << "      |" << endl;
            }else if(inputSection[1] == "reverse"){
                cout<<"      |\n       PARAMETER HOW-TO,  please enter:\n       1. A search key -then 2. An optional part of speech -then\n       3. An optional 'distinct' -then 4. An optional 'reverse'\n       |\n";
            }else {
                cout << "      |" << endl;
                cout << "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT a part of speech.>\n" <<
                     "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT 'distinct'.>\n" <<
                     "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT 'reverse'.>\n" <<
                     "       <The entered 2nd parameter '" << inputSplit[1] << "' was disregarded.>\n" <<
                     "       <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
                cout << "      |" << endl;
                getReversePOS(inputSplit[0], dictionary);
            }
        }else{
            cout<<"      |"<<endl;
            cout<<"       <The entered 3rd parameter '"<<inputSplit[2]<<"' is NOT 'distinct'.>\n"<<
                "       <The entered 3rd parameter '"<<inputSplit[2]<<"' is NOT 'reverse'.>\n" <<
                "       <The entered 3rd parameter '"<<inputSplit[2]<<"' was disregarded.>\n" <<
                "       <The 3rd parameter should be 'distinct' or 'reverse'.>"<<endl;
            cout<<"      |"<<endl;
            string transfer = inputSplit[0]+" "+inputSplit[1];
            checkWordsType(transfer, dictionary);
        }
    }

    else if (inputSplit.size() == 4) {
        if (inputSplit[3] == "reverse") {
            if (inputSplit[1] == "adjective" || inputSplit[1] == "adverb" || inputSplit[1] == "conjunction" ||
                inputSplit[1] == "interjection" || inputSplit[1] == "noun" || inputSplit[1] == "preposition" ||
                inputSplit[1] == "pronoun" || inputSplit[1] == "verb") {
                cout << "      |" << endl;
                getPOS(inputSplit[0], dictionary, inputSplit[1]);
                cout << "      |" << endl;
            }else{
                cout << "      |" << endl;
                cout << "       <The entered 2nd parameter '" << inputSplit[1] << "' is NOT a part of speech.>\n";
                cout << "      |" << endl;
            }

            if (inputSection[2] == "distinct") {
                cout << "      |" << endl;
                getDistinctPOS(inputSection[0], dictionary);
                cout << "      |" << endl;
            } else {
                cout<<"      |"<<endl;
                cout<<"       <The entered 3rd parameter '"<<inputSplit[2]<<"' is NOT 'distinct'.>\n"<<
                    "       <The entered 3rd parameter '"<<inputSplit[2]<<"' is NOT 'reverse'.>\n" <<
                    "       <The entered 3rd parameter '"<<inputSplit[2]<<"' was disregarded.>\n" <<
                    "       <The 3rd parameter should be 'distinct' or 'reverse'.>"<<endl;
                cout<<"      |"<<endl;
            }

            cout << "      |" << endl;
            getReversePOS(inputSplit[0], dictionary);
            cout << "      |" << endl;
        } else {
            cout << "      |" << endl;
            cout << "       <The entered 4th parameter '" << inputSplit[3] << "' is NOT 'reverse'.>\n" <<
                 "       <The entered 4th parameter '" << inputSplit[3] << "' was disregarded.>\n" <<
                 "       <The 4th parameter should be 'reverse'.>\n";
            cout << "      |" << endl;
            string transfer = inputSplit[0] + " " + inputSplit[1] + " " + inputSplit[2];
            checkWordsType(transfer, dictionary);
        }
    }

    else if (inputSplit.size() >= 4){
        cout<<"      |\n       PARAMETER HOW-TO,  please enter:\n       1. A search key -then 2. An optional part of speech -then\n       3. An optional 'distinct' -then 4. An optional 'reverse'\n       |\n";
    }
}

int process(){
    fstream ioFile;
    string userInput;
    int counter = 1;
    loadData();
    cout << "! Loading data... \n";
    map<string, vector<string> > dictionary = storeData();
    cout << "! Loading completed...\n! Closing data file... ../Data.CS.SFSU.txt\n\n";

    int keySize = dictionary.size();
    string title = "===== DICTIONARY 340 C++ =====\n----- Keywords: " + to_string(keySize) + "\n----- Definitions: 61\n\n";
    cout <<title;

    do{
        cout << "Search ["<< counter++ <<"] :"" ";
        std::getline(std::cin, userInput);
        if(userInput != "!help" && !userInput.empty()){
            for (char & i : userInput){
                i=tolower(i);
            }
            while(!userInput.empty() && isspace(userInput.front()))
                userInput.erase(userInput.begin());
            while(!userInput.empty() && isspace(userInput.back()))
                userInput.pop_back();
            checkWordsType(userInput, dictionary);
        }else{
            cout << printInst();
        }
    }while(userInput != "!q" && userInput != "!Q");
    cout << "\n-----THANK YOU-----";
    return 0;
}

//If the root folder contains all 3 cpp files, to run, we must temporally change the main() of two files that we do not want to run.
//For example, we would change main() of TikTakToe to Amain(), and creditCard to Bmain(), so there is one valid main() for dictionary.
//Otherwise, as there are multiple cpp files in this folder with main(), programs won't run.
//Run the cpp files we want to run, repeat the step and run the other programs.
//Ignore if there are no issues with multiple main() errors, or know a better way around this, or running files separately.


int main(){
    process();
}