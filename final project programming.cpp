 #include <iostream>
#include <queue>
#include <windows.h>
#include <conio.h>

using namespace std;

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Function to set console text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to display details and instructions
void displayDetails() {
    system("cls");
    setColor(13);  // Pink
    cout << "=========================================================\n";
    setColor(10);  // Green
    cout << "Details and Instructions:\n\n";
    setColor(7);  // Default
    cout << "1. This program determines the last day where it is possible\n";
    setColor(14);  // Yellow
    cout << "   to walk from the top to the bottom of a grid.\n\n";
    setColor(7);  // Default
    cout << "2. Flooded cells are marked, and you can only step on land cells.\n\n";
    setColor(11);  // Cyan
    cout << "3. You will input:\n";
    cout << "   - The number of rows and columns in the grid.\n";
    cout << "   - The number of days and the cells that flood on each day.\n\n";
    setColor(7);  // Default
    cout << "4. The program calculates the last day you can cross the grid.\n";
    setColor(13);  // Pink
    cout << "=========================================================\n";
    setColor(11);  // Cyan
    cout << "Press any key to return to the main menu...\n";
    setColor(7);  // Reset to default color
    _getch();
}

// Function to print the grid (for visualization)
void printGrid(int row, int col, int** grid) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to display the grid for a specific day
void displayGrid(int row, int col, int** grid) {
    setColor(12); // Pink color for grid
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
    setColor(7); // Reset to default color
    cout << endl;
}

// Function to check if it's possible to cross on a given day
bool canCross(int row, int col, int** grid, int day, int cells[][2]) {
    int** tempGrid = new int*[row];
    for (int i = 0; i < row; ++i) {
        tempGrid[i] = new int[col]();
    }

    for (int i = 0; i < day; ++i) {
        int r = cells[i][0] - 1;
        int c = cells[i][1] - 1;
        tempGrid[r][c] = 1;
    }

    queue<pair<int, int>> q;
    for (int c = 0; c < col; ++c) {
        if (tempGrid[0][c] == 0) {
            q.push(make_pair(0, c));
            tempGrid[0][c] = -1;
        }
    }

    bool possible = false;
    while (!q.empty()) {
        pair<int, int> cell = q.front();
        q.pop();

        int r = cell.first;
        int c = cell.second;

        if (r == row - 1) {
            possible = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + directions[i][0];
            int nc = c + directions[i][1];
            if (nr >= 0 && nr < row && nc >= 0 && nc < col && tempGrid[nr][nc] == 0) {
                q.push(make_pair(nr, nc));
                tempGrid[nr][nc] = -1;
            }
        }
    }

    for (int i = 0; i < row; ++i) {
        delete[] tempGrid[i];
    }
    delete[] tempGrid;

    return possible;
}

// Function to play the program
void playProgram() {
    system("cls");
    setColor(13);
    cout << "=========================================================\n";
    setColor(14);
    cout << "          Welcome to the Last Day to Cross Program!        \n";
    setColor(13);
    cout << "=========================================================\n";
    setColor(7);
    int row, col, n;
    setColor(13);
    cout << "Enter number of rows: ";
    setColor(7);
    cin >> row;
    setColor(13);
    cout << "Enter number of columns: ";
    setColor(7);
    cin >> col;
    setColor(13);
    cout << "Enter number of flooded days: ";
    setColor(7);
    cin >> n;

    if (row <= 0 || col <= 0 || n <= 0) {
        setColor(12);
        cout << "Error: Invalid grid size or number of flooded days.\n";
        setColor(7);
        return;
    }

    int cells[n][2];
    int** grid = new int*[row];
    for (int i = 0; i < row; ++i) {
        grid[i] = new int[col]();
    }

    for (int i = 0; i < n; ++i) {
        setColor(12); // Pink color for flooded cell prompt
        cout << "Enter flooded cells for Day " << i + 1 << ":\n";
        setColor(7); // Reset to default color
        cin >> cells[i][0] >> cells[i][1];
        if (cells[i][0] < 1 || cells[i][0] > row || cells[i][1] < 1 || cells[i][1] > col) {
            setColor(12);
            cout << "Error: Invalid cell input (" << cells[i][0] << ", " << cells[i][1] << ").\n";
            setColor(7);
            return;
        }
        grid[cells[i][0] - 1][cells[i][1] - 1] = 1; // Update grid
        displayGrid(row, col, grid); // Display grid for each day
    }

    int lastDay = 0;
    for (int day = 1; day <= n; ++day) {
        if (canCross(row, col, grid, day, cells)) {
            lastDay = day;
        } else {
            break;
        }
    }
    setColor(13);
    cout << "=========================================================\n";
    setColor(10);
    cout << "The last day where it is possible to cross is: Day " << lastDay << "\n";
    setColor(13);
    cout << "=========================================================\n";
    setColor(7);
    cout << "Press any key to return to the main menu...\n";
    _getch();

    for (int i = 0; i < row; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

int main() {
    char choice;
    do {
        system("cls");
        setColor(13);
        cout << "=========================================================\n";
        setColor(14);
        cout << "Welcome to the Last Day to Cross Program!" << endl;
        setColor(13);
        cout << "=========================================================\n";
        setColor(11);
        cout << "1. Play the program\n";
        cout << "2. Details and instructions\n";
        cout << "3. Exit\n";
        setColor(13);
        cout << "=========================================================\n";
        setColor(7);
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                playProgram();
                break;
            case '2':
                displayDetails();
                break;
            case '3':
                system("cls");
                setColor(13);
                cout << "=========================================================\n";
                setColor(10);
                cout << "Thank you for using the program. Goodbye!\n";
                setColor(13);
                cout << "=========================================================\n";
                setColor(7);
                return 0;
            default:
                setColor(12);
                cout << "Invalid choice! Please try again.\n";
                setColor(7);
                _getch();
        }
    } while (true);
}