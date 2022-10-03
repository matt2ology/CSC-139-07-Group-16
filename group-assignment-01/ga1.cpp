#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <pthread.h>

using namespace std;  

void* executeUserFunction(void* arg1) {
  vector <string>* b = (vector <string>*)arg1;
  string input;
  for(string i: *b) {
    input += i + " ";
  }
  cout << system((input).c_str());
  pthread_exit(NULL);
  return 0;
}

int main() {
  const string commandsList[9] = {"dir", "help", "vol", "path", "tasklist", "notepad", "echo", "color", "ping"};
  while(1){ 
    string userInput;
    int choice;
    string tempString;
    vector<string> userInputArr;
    pthread_t tId;
    bool falseInput = false;
  
    cout << "Enter a command: ";
    getline(cin, userInput);
    if(userInput.compare("exit") == 0) {
      break;
    }
    istringstream ss(userInput);
    while(ss >> tempString) {
      userInputArr.push_back(tempString);
    }
    for(string i: commandsList) {
      if(userInputArr[0].compare(i) == 0) {
        pthread_create(&tId, 0, &executeUserFunction,     
          &userInputArr);
        pthread_join(tId, 0);
        falseInput = false;
      }
    }
  }
  return 0;
}


