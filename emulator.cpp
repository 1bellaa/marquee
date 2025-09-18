#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include "marquee.cpp"

using namespace std;
extern void StartMarqueeConsole();
extern void SetMarqueeText(const string& text);
extern void SetMarqueeSpeed(int speed);

void HelpCommand() {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| Command       | Description                                            | Usage                       |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| help          | displays the commands and its description              | help                        |\n";
    cout << "| start_marquee | starts the marquee \"animation\"                         | start_marquee               |\n";
    cout << "| stop_marquee  | stops the marquee \"animation\"                          | stop_marquee                |\n";
    cout << "| set_text      | accepts a text input and displays it as                | set_text <input text>       |\n";
    cout << "| set_speed     | sets the marquee animation refresh in milliseconds     | set_speed <an integer>      |\n";
    cout << "| exit          | terminates the console                                 | exit                        |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";
}

void Welcome() {
    cout << " ____  ____  _____  _____  ____  ____  __  __" << endl;
    cout << "|  __|/  __||  _  ||  _  ||  __|/  __||  ||  |" << endl;
    cout << "| |  |  |__ | | | || |_| || |__ | |__ |  \\/  |" << endl;
    cout << "| |   \\_   || | | || __ / |  __| \\_  | \\_  _/" << endl;
    cout << "| |__  __| || |_| || |    | |__ __|  |  |  |" << endl;
    cout << "|____||____||_____||_|    |____||____|  |__|" << endl;
    //cout << "Welcome to CSOPESY!" << endl;
    cout << "\nGroup developer:" << endl;
    cout << "Lim, Nathan\nMagabo, Julianna\nManlapig, Rachel\nSanchez, Jeck" << endl;
    cout << "\nVersion date: Sept. 18" << endl;
    cout << "" << endl; 
}

int main() {
    Welcome();
    bool running = true;
    
    while (running) {
        string command;
        cout << "Command> ";
        getline(cin, command); 
        
        if (command == "help") {
            HelpCommand();
        } 
        else if (command == "start_marquee") {
            StartMarqueeConsole();
            Welcome();
        } 
        else if (command.rfind("set_text", 0) == 0) {
            SetMarqueeText(command.substr(9)); 
        } 
        else if (command.rfind("set_speed", 0) == 0) {
            SetMarqueeSpeed(stoi(command.substr(10)));
        }
        else if (command == "exit") {
            running = false;
        }
        else {
            cout << "Unrecognizable command.\n" << endl;
        }
    }
    
    return 0;
}