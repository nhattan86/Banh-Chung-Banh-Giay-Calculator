# Banh Chung & Banh Giay Calculator

This is a product I developed during my time at university to that calculates the optimal number of Banh Chung (square sticky rice cake) and Banh Giay (round sticky rice cake) that can be made based on given ingredients and weather conditions. This program is based on the Vietnamese legend of Lang Lieu and the origin of these traditional cakes.

## Problem Description
Given an amount of sticky rice, leaf wrappings, and dimensions for both types of cakes, calculate the optimal number of each cake that can be made while:
1. Minimizing leftover rice (highest priority)
2. Optimizing the number of cakes based on weather conditions
3. Respecting the leaf wrapping constraints

## Input Format (input.inp)
The input file contains five values separated by spaces:
```
n dc dg ld w
```
Where:
- n: Amount of sticky rice (integer ≤ 1000)
- dc: Side length of Banh Chung (positive integer)
- dg: Diameter of Banh Giay (positive integer)
- ld: Number of dong leaves available (1-300)
- w: Weather condition ("Rain", "Sun", "Cloud", "Fog", "Wind")

## Output Format (output.out)
```
bc bg nd
```
Where:
- bc: Number of Banh Chung to make (non-negative integer)
- bg: Number of Banh Giay to make (non-negative integer)
- nd: Amount of leftover rice (float with 3 decimal places)

For invalid input: `-1 -1 n`

## Calculations
1. Rice needed for one Banh Chung: dc²
2. Rice needed for one Banh Giay: (dg² * π)/4
- Each cake requires one dong leaf
- π = 3.1415926535

## Weather Conditions & Rules

### Wind
- Prioritize making Banh Chung
- Use remaining rice for Banh Giay
- Consider leaf constraints

### Rain
- Try to balance the number of both types of cakes
- Maintain minimum difference if perfect balance impossible
- Consider leaf constraints

### Sun
1. Adds X% bonus rice (rounded to integer)
2. Reduces leaves by X
3. X is determined by:
   - G = dc mod 6
   - H = ld mod 5
   - Lookup in provided bonus table
4. Weather changes based on (dc+dg) mod 3:
   - 0: Rain
   - 1: Wind
   - 2: Cloud

### Fog
- Returns input dimensions and rice amount as is
- bc = dc
- bg = dg
- nd = n

### Cloud
Two cases:
1. If n and ld are amicable numbers:
   - Return all rice as remainder
   - bc = bg = 0
2. Otherwise:
   - Prioritize making Banh Giay
   - Use remaining rice for Banh Chung
   - Consider leaf constraints

## Compilation & Execution
```bash
gcc program.c -o program
./program
```

## Constraints
- 0 < n ≤ 1000
- 1 ≤ ld ≤ 300
- Weather must be one of: Rain, Sun, Cloud, Fog, Wind
- No intermediate rounding of calculations

## Error Handling
Returns `-1 -1 n` when:
- n > 1000
- ld < 1 or ld > 300
- Invalid weather condition

# GUI version of Banh Chung & Banh Giay Calculator

## Overview
The GUI Banh Chung & Banh Giay Calculator is a desktop application built with Qt that performs weather-based calculations. It provides a graphical user interface for inputting weather parameters and viewing results. The application processes various weather conditions (Rain, Sun, Cloud, Fog, and Wind) and calculates specific metrics based on the input parameters.

## Prerequisites
Before installing the Weather Calculator, ensure you have the following installed on your system:

- Qt 6.x or later
- MinGW C++ compiler (64-bit)
- Git (optional, for version control)

## Installation

### Setting Up the Development Environment

1. Install Qt:
   - Download the Qt Online Installer from https://www.qt.io/download-qt-installer
   - Run the installer and select the following components:
     - Qt 6.x for MinGW
     - Qt Creator
     - MinGW compiler

2. Configure System Environment:
   - Add Qt binary directory to your system PATH:
     ```
     C:\Qt\6.x.x\mingw_64\bin
     C:\Qt\Tools\mingw1120_64\bin
     ```

### Building the Project

1. Clone or download the project files to your local machine

2. Open a Command Prompt in the project directory

3. Generate the Makefile:
   ```bash
   qmake weather-calculator.pro
   ```

4. Build the project:
   ```bash
   mingw32-make
   ```

5. The executable will be generated in the debug or release folder

## Usage

1. Launch the application by running the executable

2. Enter the following parameters in the input fields:
   - N: Primary calculation value (must be ≤ 1000)
   - DC: First dimensional constant
   - DG: Second dimensional constant
   - LD: Limit value (must be between 1 and 300)

3. Select the weather condition from the dropdown menu:
   - Rain
   - Sun
   - Cloud
   - Fog
   - Wind

4. Click the "Calculate" button to process the inputs

5. View the results displayed at the bottom of the window in the format:
   ```
   Result: [BC] [BG] [ND]
   ```
   where BC and BG are calculated values, and ND is the final metric

## Project Structure

- `main.cpp`: Application entry point
- `mainwindow.h`: Header file containing class declarations
- `mainwindow.cpp`: Implementation of the MainWindow class and calculation logic
- `weather-calculator.pro`: Qt project file containing build configurations

## Error Handling

The application includes validation for:
- Invalid input values
- Out-of-range parameters
- Non-numeric inputs
- Boundary conditions

Error messages will be displayed in a popup dialog when invalid inputs are detected.

## Maintenance and Support

For bug reports and feature requests, please create an issue in the project repository. When reporting issues, include:
- Steps to reproduce the problem
- Expected behavior
- Actual behavior
- Screenshots (if applicable)

## Technical Notes

- Built using Qt 6 framework
- Implements C++17 features
- Uses the Qt Widgets module for GUI components
- Calculations use double precision floating-point arithmetic
- PI constant defined as 3.1415926535
