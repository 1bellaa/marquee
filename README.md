# Marquee Operator

A **CSOPESY Semi-Major Output** that shows an OS emulator, requiring a command interpreter and a display output.

**Group developer:** 
- Lim, Nathan
- Magabo, Julianna
- Manlapig, Rachel
- Sanchez, Jeck

## Requirements

There are two requirements for this project:
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

## Implementation

Provide here a description of the project implementation (technical stuff? how the animation was done in code, significant libraries)

### Implementation: Notes

- I think `set_text`, `set_speed`, `stop_marquee` commands are only accessible or can be invoked when you start the marquee. Therefore, it should be an unrecognizable command in the main menu and only the `help`, `start_marquee`, and `exit` commands will be recognizable.
- Not sure if the `help` command should be accessible also upon invoking the `start_marquee` command. However, current implementation does not support this.
- Not sure but upon invoking the `
- How exactly should stop_marquee work? Mawawala lang ba yung dvd-like animation or is that the equivalent to the exit command sa main menu idkkkk
- In-line documentation could be improved skdjfhss
- Modify the functions to follow the specs: 
> 1. MarqueeConsole()
> 2. ProcessMarqueeCommand()
> 3. MarqueeInputThread()
> 4. StartMarquee
> 5. Optional ??? change the show,hide,setcursor functions + constants 

## How to run (to be updated next time!!)

Step-by-step on how to run the project

1. Make sure to clone the repository. Current implementation was developed using **Visual Studio Code**, ***not Visual Studio***  
2. On the CLI, go to the cloned repo folder
3. Input `g++ -std=c++20 emulator.cpp -o emulator`, then run the exe file
4. See **Implementation: Notes** for more info
