# Marquee Operator

A **CSOPESY Semi-Major Output** that shows an OS emulator, requiring a command interpreter and a display output.

**Group developer:** 
- Lim, Nathan
- Magabo, Julianna
- Manlapig, Rachel
- Sanchez, Jeck

## Requirements

There are three requirements for this project:
1. An "OS emulator" that accepts a command input with display output; and
2. Command interpreter for the OS emulator that accepts the following commands:

| Command | Description | Usage |
| --- | --- | --- |
| help | displays the commands and its description | `help` |
| start_marquee | starts the marquee "animation" | `start_marquee` |
| stop_marquee | stops the marquee "animation" | `stop_marquee` |
| set_text | accepts a text input and displays it as a marquee | `set_text <input text>` |
| set_speed | sets the marquee animation refresh in milliseconds | `set_speed <an integer>` |
| exit | terminates the console | `exit` |

3. The OS emulator must have the following components:

| Component | Description |
| --- | --- |
| Command interpreter | accepts command and control the marquee logic |
| Display handler | handles the display for the command interpreter and marquee logic |
| Keyboard handler | handles keyboard buffering and polling |
| Marquee logic | handles the animation logic for the marquee text |

## Implementation

There are two files for this project: `emulator.cpp`, which serves as the main entry point of the program, and the `marquee.cpp`, which performs the animation of the marquee console.

The following functions and their descriptions are listed below:

### `emulator.cpp`

| Function | Description |
| --- | --- |
| `HelpCommand()` | displays the commands and its description using cout |
| `Welcome()` | shows the welcome message, including the developer names and version date of the code |
| `main()` | main entry point of the program | 

### `marquee.cpp`

| Function | Description |
| --- | --- |
| `SetCursorPosition()` | Sets the cursor position in the console window to the specified (x, y) coordinates |
| `HideCursor()` | Hides the blinking cursor in the console window |
| `ShowCursor()` | Shows the blinking cursor in the console window |
| `SetMarqueeText(const string& text)` | Sets the marquee display text based on user input |
| `SetMarqueeSpeed(int speed)` | Sets the speed of the marquee animation in milliseconds, based on user input |
| `MarqueeConsole()` | Renders the marquee animation and user interface, updates position, handles bouncing, and displays input and help text |
| `MarqueeWorkerThread()` | Animation thread that repeatedly calls `MarqueeConsole()` and controls the refresh rate of the marquee |
| `ProcessMarqueeCommand(const string& command)` | Processes user commands such as starting/stopping the marquee, displaying help, setting text/speed, and exiting |
| `MarqueeInputThread()` | Handles keyboard input in a separate thread, processes commands, and updates the current input string |
| `StartMarqueeConsole()` |  Entry point for the marquee console; initializes state, starts animation and input threads |

## How to run 

Step-by-step on how to run the project

1. Make sure to clone the repository. Current implementation was developed using **Visual Studio Code**, ***not Visual Studio***  
2. On the CLI, go to the cloned repo folder
3. Input `g++ -std=c++20 emulator.cpp -o emulator`, then run the exe file
