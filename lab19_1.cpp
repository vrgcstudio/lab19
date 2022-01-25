#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    int x , y, z;
    
    while (getline(source,textline)) {
        const char * c_textline = textline.c_str();
        char cur_name[100];

        sscanf(c_textline, "%[^:]: %d %d %d", cur_name, &x, &y, &z);
        names.push_back(cur_name);
        scores.push_back(x + y + z);
        grades.push_back(score2grade(x + y + z));  
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    string textline;
    char textline_command[100], textline_key[100];
    getline(cin,textline);
    sscanf(textline.c_str(),"%s %[^\n]",textline_command,textline_key);
    command = textline_command;
    key = textline_key;  
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool none = true;
    cout << "---------------------------------"<<endl;
    for(unsigned int i = 0; i < names.size() ;i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            none = false;
        }
    }

    if(none == true ){
        cout << "Cannot found." <<endl;
    }

    cout << "---------------------------------"<<endl;
}


void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------"<<endl;
    const char *grade = key.c_str();
    bool none = true;
    for( unsigned int i = 0; i < names.size() ;i++){
        if(grades[i] == *grade){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            none = false;
        }
    }
    if(none == true ){
        cout << "Cannot found." <<endl;
    }
    cout << "---------------------------------"<<endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);

    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
