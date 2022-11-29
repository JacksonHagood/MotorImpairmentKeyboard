# Pi Software

## Prerequisites

- Install WiringPi
- Enable the Raspberry Pi for Key Mime Pi: https://mtlynch.io/key-mime-pi/

## Components

### dictionary.txt

Dictionary file compiling 10000 words in frequency order. This is important for Trie construction. https://github.com/first20hours/google-10000-english.

### driver.cpp

Driver program that is the entry point for the Raspberri Pi. Main runs infinitely and waits for hardware interrupts in GPIO 21. Hardware interrupts indicate a key being pressed. When a key is pressed, the Pi recieves a MENA value that is decoded into its components. Using this, the auto-complete suggestions are updates and any keystrokes are sent using Key Mime Pi shell commands.

### err.txt

Programs output (redirected from cout).

### LCD.h

Class definitions for interracting with the three LCD's to display auto-complete suggestions.

### Node.H

Class definition for a node object used by the Trie data structure.

### run_keyboard.sh

Command to execute serial.sh and run driver with cout redirected to err.txt.

### serial.sh

Bash script to send MENA signals from Pico to driver program.

### Trie.h

Class definition for Trie data structure used for auto-complete suggestion determination.

## Commands

Use the makefile to compile and then execute the binary file

### Driver Program Execution
- Compile: make driver
- Execute: ./driver

### clean
- Clean: make clean
