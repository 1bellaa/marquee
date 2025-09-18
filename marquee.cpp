#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <conio.h>

using namespace std;

/* Marquee State*/
atomic<bool> RUNNING_MARQUEE(false);
atomic<bool> EXIT_MARQUEE(false);

/* Command History */
vector<string> RECENT_COMMANDS; // might remove
mutex COMMANDS_MUTEX; // might remove

/* Current Input */
mutex INPUT_MUTEX;
string CURRENT_INPUT = ""; 

/* Marquee Layout */
const int CONSOLE_WIDTH = 80; 
const int CONSOLE_HEIGHT = 25;

/* Marquee Positions */
int marquee_x = 1, marquee_y = 5;
int dx = 1, dy = 1;

/* Marquee Text Default */
string MARQUEE_TEXT = "Hello world in marquee!";
mutex MARQUEE_TEXT_MUTEX;

/* Marquee Speed Default */
int SPEED = 50; 
mutex SPEED_MUTEX;

/* Marquee Help Command */
string HELP_TEXT;
mutex HELP_MUTEX;

/* To set the cursor position to (x,y) in the console */
void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* To hide the blinking cursor */
void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/* To show the blinking cursor */
void ShowCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/* To set the display text based on user input */
void SetMarqueeText(const string& text) {
    lock_guard<mutex> lock(MARQUEE_TEXT_MUTEX);
    if (!text.empty()) {
        MARQUEE_TEXT = text;
    }
}

/* To set the speed of the animation in milliseconds based on user input */
void SetMarqueeSpeed(int speed) {
    lock_guard<mutex> lock(SPEED_MUTEX);
    if (speed > 0) {
        SPEED = speed;
    }
}

/* To render the marquee animation and user interface */
void MarqueeConsole() {
    system("cls");

    // Header
    SetCursorPosition(0, 0);
    cout << "*********************************" << endl;
    cout << "*     Displaying a marquee !    *" << endl;
    cout << "*********************************" << endl;

    // Marquee position
    marquee_x += dx;
    marquee_y += dy;

    string marquee_text_animation;
    {
        lock_guard<mutex> lock(MARQUEE_TEXT_MUTEX);
        marquee_text_animation = MARQUEE_TEXT;
    }

    // Bounce like dvd
    if (marquee_x <= 0 || marquee_x + marquee_text_animation.length() >= CONSOLE_WIDTH - 1) {
        dx = -dx;
        marquee_x = max(1, min(marquee_x, CONSOLE_WIDTH - (int)marquee_text_animation.length() - 1));
    }
    if (marquee_y <= 3 || marquee_y >= 15) {
        dy = -dy;
        marquee_y = max(4, min(marquee_y, 14));
    }

    // Draw marquee text at current position
    SetCursorPosition(marquee_x, marquee_y);
    cout << marquee_text_animation;

    // Draw input prompt
    SetCursorPosition(0, 17);
    cout << "Command: ";

    {
        lock_guard<mutex> lock(INPUT_MUTEX);
        cout << CURRENT_INPUT;
    }

    // Draw Help 
    {
        lock_guard<mutex> lock(HELP_MUTEX);
        if (!HELP_TEXT.empty()) {
            SetCursorPosition(0, 19);
            cout << HELP_TEXT;
        }
    }

    cout.flush(); // Display output immediately
}

/* Display thread of the marquee */
void MarqueeWorkerThread() {
    while (RUNNING_MARQUEE && !EXIT_MARQUEE) {
        if (!EXIT_MARQUEE) {
            MarqueeConsole();
        }

        int refresh_speed;
        {
            lock_guard<mutex> lock(SPEED_MUTEX);
            refresh_speed = SPEED;
        }
        
        this_thread::sleep_for(chrono::milliseconds(refresh_speed)); // flicker speed
    }
}

/* To process the commands based on user input */
void ProcessMarqueeCommand(const string& command) {
    if (command == "stop_marquee") {
        EXIT_MARQUEE = true;
        RUNNING_MARQUEE = false;
    } else if (command == "help") {
        lock_guard<mutex> lock(HELP_MUTEX);
        HELP_TEXT =
            "--------------------------------------------------------------------------------------------------------\n"
            "| Command       | Description                                            | Usage                       |\n"
            "--------------------------------------------------------------------------------------------------------\n"
            "| help          | displays the commands and its description              | help                        |\n"
            "| start_marquee | starts the marquee \"animation\"                         | start_marquee               |\n"
            "| stop_marquee  | stops the marquee \"animation\"                          | stop_marquee                |\n"
            "| set_text      | accepts a text input and displays it as                | set_text <input text>       |\n"
            "| set_speed     | sets the marquee animation refresh in milliseconds     | set_speed <an integer>      |\n"
            "| exit          | terminates the console                                 | exit                        |\n"
            "--------------------------------------------------------------------------------------------------------\n";
    } else if (command == "exit") {
        exit(0); 
    } else if (!command.empty()) {
        {
            lock_guard<mutex> lock(COMMANDS_MUTEX);
            RECENT_COMMANDS.push_back(command);
        }
    }
}

/* Keyboard handler thread for input in the marquee console */
void MarqueeInputThread() {
    while (RUNNING_MARQUEE && !EXIT_MARQUEE) {
        if (_kbhit()) {
            char ch = _getch();

            if (ch == 13) { 
                string command;
                {
                    lock_guard<mutex> lock(INPUT_MUTEX);
                    command = CURRENT_INPUT;
                    CURRENT_INPUT = "";
                }

                if (!command.empty()) {
                    ProcessMarqueeCommand(command);
                }
            } else if (ch == 8) { 
                {
                    lock_guard<mutex> lock(INPUT_MUTEX);
                    if (!CURRENT_INPUT.empty()) {
                        CURRENT_INPUT.pop_back();
                    }
                }
            } else if (ch >= 32 && ch <= 126) { // Printable chars
                {
                    lock_guard<mutex> lock(INPUT_MUTEX);
                    CURRENT_INPUT += ch;
                }
            }
        }

        int refresh_speed;
        {
            lock_guard<mutex> lock(SPEED_MUTEX);
            refresh_speed = SPEED;
        }

        this_thread::sleep_for(chrono::milliseconds(refresh_speed));
    }
}

/* Entry point of the marquee console */
void StartMarqueeConsole() {
    system("cls");
    HideCursor();

    RUNNING_MARQUEE = true;
    EXIT_MARQUEE = false;
    marquee_x = 1;
    marquee_y = 5;
    dx = 1;
    dy = 1;

    {
        lock_guard<mutex> lock(INPUT_MUTEX);
        CURRENT_INPUT = "";
    }

    thread animation_thread(MarqueeWorkerThread);
    thread input_thread(MarqueeInputThread);

    while (RUNNING_MARQUEE && !EXIT_MARQUEE) {}

    RUNNING_MARQUEE = false;
    if (animation_thread.joinable()) {
        animation_thread.join();
    }

    if (input_thread.joinable()) {
        input_thread.join();
    }

    ShowCursor();
    system("cls");
}