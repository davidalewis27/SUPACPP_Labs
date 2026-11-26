# SUPACPP Assignment 1 – AnalyseData

Author: David Lewis  
Date: 26/11/2026

Reads 2D (x, y) data from `input2D_float.txt` and lets the user analyse it through a command-line menu.

## Files
- `AnalyseData.cxx` – main program (menu and task selection)
- `CustomFunctions.h` / `CustomFunctions.cxx` – reading, printing, saving, and analysis functions
- `makefile` – build rules
- `input2D_float.txt` – input (x, y) data
- `error2D_float.txt` – errors on each data point (used for the chi-squared test)

## Build and run
```bash
make            # compile
./AnalyseData   # run
make clean      # remove object files and executable
```

## Menu options
| Option | Task | Output file |
|---|---|---|
| 0 | Exit | – |
| 1 | Print the first N lines of data (if N exceeds the number of points, a warning is shown and only 5 lines are printed) | `Outputs/selected_N_lines.txt` |
| 2 | Magnitude of each (x, y) point as a vector from the origin | `Outputs/vector_magnitudes.txt` |
| 3 | Least squares straight-line fit, y = mx + c | `Outputs/least_squares_fit.txt` |
| 4 | Least squares fit with chi-squared and chi-squared/NDOF | `Outputs/least_squares_fit.txt` |
| 5 | x^y for each point, with y rounded to the nearest integer, computed recursively | `Outputs/x_pow_y.txt` |

After each task the menu is shown again until option 0 is chosen. 
Invalid (non-integer) input is rejected and the user is asked again.
