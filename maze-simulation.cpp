#include <iostream>
#include <set>
#include <stack>

using namespace std;

typedef pair<double, pair<int, int>> pPair;

const pair<int, int> CHEESE_COORDS = make_pair(8, 2);
const int MOUSE_ID = 3;
const int CAT_ID = 4;
const int CHEESE_ID = 5;
const int NUM_ROWS = 11;
const int NUM_COLS = 11;

/*
* 1 represents a wall, 0 represents an open space
* 3 represents the mouse, 4 represents the cat, and 5 represents the cheese
*/
int maze[NUM_ROWS][NUM_COLS] = {{3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
                                {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
                                {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
                                {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
                                {0, 0, 0, 1, 0, 0, 0, 1, 4, 1, 0},
                                {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                                {0, 1, 5, 1, 0, 1, 0, 0, 0, 1, 0},
                                {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
                                {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

// Top left of maze is (0, 0)
pair<int, int> mouse_coords = make_pair(0, 0);
pair<int, int> cat_coords = make_pair(6, 8);
int mouse_available_moves[4] = {0, 1, 0, 0};
int mouse_previous_move = 6;
int cat_available_moves[4] = {0, 0, 0, 1};
int cat_previous_move = 6;
bool is_success = false;
int total_moves = 0;

struct cell{
    int parent_x, parent_y;
    double f, g, h;
};

bool isTraversable(int row, int col){
    if(maze[row][col] == 0 || maze[row][col] == CHEESE_ID){
        return true;
    }else{
        return false;
    }
}

double calc_h(int row, int col, pair<int, int> dest){
    return abs(row - dest.first) + abs(col - dest.second);
}

void move_left(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords.second > 0 && maze[mouse_coords.first][mouse_coords.second - 1] == 0 || maze[mouse_coords.first][mouse_coords.second - 1] == CHEESE_ID){
            maze[mouse_coords.first][mouse_coords.second] = 0;
            maze[mouse_coords.first][mouse_coords.second - 1] = obj;
            mouse_coords.second--;
            mouse_previous_move = 0;
        }else{
            cout << "Error, invalid move\n";
    }
    }else if(obj == CAT_ID){
        if(cat_coords.second > 0 && maze[cat_coords.first][cat_coords.second - 1] == 0 || maze[cat_coords.first][cat_coords.second - 1] == MOUSE_ID){
            maze[cat_coords.first][cat_coords.second] = 0;
            maze[cat_coords.first][cat_coords.second - 1] = obj;
            cat_coords.second--;
            cat_previous_move = 0;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void move_right(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords.second < (sizeof(maze[1]) - 1) / sizeof(int) && maze[mouse_coords.first][mouse_coords.second + 1] == 0 || maze[mouse_coords.first][mouse_coords.second + 1] == CHEESE_ID){
            maze[mouse_coords.first][mouse_coords.second] = 0;
            maze[mouse_coords.first][mouse_coords.second + 1] = obj;
            mouse_coords.second++;
            mouse_previous_move = 1;
        }else{
            cout << "Error, invalid move\n";
        }
    }else if(obj == CAT_ID){
        if(cat_coords.second < (sizeof(maze[1]) - 1) / sizeof(int) && maze[cat_coords.first][cat_coords.second + 1] == 0 || maze[cat_coords.first][cat_coords.second + 1] == MOUSE_ID){
            maze[cat_coords.first][cat_coords.second] = 0;
            maze[cat_coords.first][cat_coords.second + 1] = obj;
            cat_coords.second++;
            cat_previous_move = 1;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void move_up(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords.first > 0 && maze[mouse_coords.first - 1][mouse_coords.second] == 0 || maze[mouse_coords.first - 1][mouse_coords.second] == CHEESE_ID){
            maze[mouse_coords.first][mouse_coords.second] = 0;
            maze[mouse_coords.first - 1][mouse_coords.second] = obj;
            mouse_coords.first--;
            mouse_previous_move = 2;
        }else{
            cout << "Error, invalid move\n";
        }
    }else if(obj == CAT_ID){
        if(cat_coords.first > 0 && maze[cat_coords.first - 1][cat_coords.second] == 0 || maze[cat_coords.first - 1][cat_coords.second] == MOUSE_ID){
            maze[cat_coords.first][cat_coords.second] = 0;
            maze[cat_coords.first - 1][cat_coords.second] = obj;
            cat_coords.first--;
            cat_previous_move = 2;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void move_down(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords.first < (sizeof(maze[0]) - 1) / sizeof(int) && maze[mouse_coords.first + 1][mouse_coords.second] == 0 || maze[mouse_coords.first + 1][mouse_coords.second] == CHEESE_ID){
            maze[mouse_coords.first][mouse_coords.second] = 0;
            maze[mouse_coords.first + 1][mouse_coords.second] = obj;
            mouse_coords.first++;
            mouse_previous_move = 3;
        }else{
            cout << "Error, invalid move\n";
        }
    }else if(obj == CAT_ID){
        if(cat_coords.first < (sizeof(maze[0]) - 1) / sizeof(int) && maze[cat_coords.first + 1][cat_coords.second] == 0 || maze[cat_coords.first + 1][cat_coords.second] == MOUSE_ID){
            maze[cat_coords.first][cat_coords.second] = 0;
            maze[cat_coords.first + 1][cat_coords.second] = obj;
            cat_coords.first++;
            cat_previous_move = 3;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void takeFirstMove(cell cellDetails[][NUM_COLS], pair<int, int> dest){
    int row = dest.first;
    int col = dest.second;

    stack<pair<int, int>> Path;

    while (!(cellDetails[row][col].parent_x == row && cellDetails[row][col].parent_y == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_x;
        int temp_col = cellDetails[row][col].parent_y;
        row = temp_row;
        col = temp_col;
    }

    pair<int, int> p = Path.top();
    if(p.first == row && p.second < col){
        move_left(MOUSE_ID);
    }else if(p.first == row && p.second > col){
        move_right(MOUSE_ID);
    }else if(p.first < row && p.second == col){
        move_up(MOUSE_ID);
    }else if(p.first > row && p.second == col){
        move_down(MOUSE_ID);
    }else{
        cout << "Error, path not found\n";
    }

    if(p.first == dest.first && p.second == dest.second){
        cout << "The mouse has reached the cheese\n";
        is_success = true;
    }

    return;
}

void aStar(pair<int, int> start, pair<int, int> dest){
    if(start.first == dest.first && start.second == dest.second){
        cout << "The destination has already been reached\n";
        return;
    }

    bool closedList[NUM_ROWS][NUM_COLS];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[NUM_ROWS][NUM_COLS];

    int i;
    int j;
    for(i = 0; i < NUM_ROWS; i++){
        for(j = 0; j < NUM_COLS; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_x = -1;
            cellDetails[i][j].parent_y = -1;
        }
    }

    i  = start.first;
    j = start.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_x = i;
    cellDetails[i][j].parent_y = j;

    set<pPair> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool dest_achieved = false;

    while(!openList.empty()){
        pPair p = *openList.begin();

        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double fNew, gNew, hNew;

        // Check left
        if(j - 1 >= 0){
            if(i == dest.first && j - 1 == dest.second){
                cellDetails[i][j - 1].parent_x = i;
                cellDetails[i][j - 1].parent_y = j;
                cout << "The destination has been found!\n";
                takeFirstMove(cellDetails, dest);
                dest_achieved = true;
                return;
            }else if(closedList[i][j - 1] == false && isTraversable(i, j - 1)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calc_h(i, j - 1, dest);
                fNew = gNew + hNew;

                if(cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i, j - 1)));
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_x = i;
                    cellDetails[i][j - 1].parent_y = j;
                }
            }
        }

        // Check right
        if(j + 1 < NUM_COLS){
            if(i == dest.first && j + 1 == dest.second){
                cellDetails[i][j + 1].parent_x = i;
                cellDetails[i][j + 1].parent_y = j;
                cout << "The destination has been found!\n";
                takeFirstMove(cellDetails, dest);
                dest_achieved = true;
                return;
            }else if(closedList[i][j + 1] == false && isTraversable(i, j + 1)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calc_h(i, j + 1, dest);
                fNew = gNew + hNew;
                if(cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i, j + 1)));
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_x = i;
                    cellDetails[i][j + 1].parent_y = j;
                }
            }
        }

        // Check up
        if(i - 1 >= 0){
            if(i - 1 == dest.first && j == dest.second){
                cellDetails[i - 1][j].parent_x = i;
                cellDetails[i - 1][j].parent_y = j;
                cout << "The destination has been found!\n";
                takeFirstMove(cellDetails, dest);
                dest_achieved = true;
                return;
            }else if(closedList[i - 1][j] == false && isTraversable(i - 1, j)){
                gNew = cellDetails[i - 1][j].g + 1.0;
                hNew = calc_h(i - 1, j, dest);
                fNew = gNew + hNew;
                if(cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_x = i;
                    cellDetails[i - 1][j].parent_y = j;
                }
            }
        }

        // Check down
        if(i + 1 < NUM_ROWS){
            if(i + 1 == dest.first && j == dest.second){
                cellDetails[i + 1][j].parent_x = i;
                cellDetails[i + 1][j].parent_y = j;
                cout << "The destination has been found!\n";
                takeFirstMove(cellDetails, dest);
                dest_achieved = true;
                return;
            }else if(closedList[i + 1][j] == false && isTraversable(i + 1, j)){
                gNew = cellDetails[i + 1][j].g + 1.0;
                hNew = calc_h(i + 1, j, dest);
                fNew = gNew + hNew;
                if(cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew){
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_x = i;
                    cellDetails[i + 1][j].parent_y = j;
                }
            }
        }
    }

    if(dest_achieved == false){
        cout << "Couldn't reach destination\n";
    }

    return;
}

int rand_dir(int arr[4], int obj){
    int move_total = 0;
    for(int i = 0; i < sizeof(arr); i++){
        move_total += arr[i];
    }
    if(obj == MOUSE_ID){
        if(move_total > 1){
            if(mouse_previous_move == 0){
                if(arr[1] == 1){
                    arr[1] = 0;
                    move_total--;
                }
            }else if(mouse_previous_move == 1){
                if(arr[0] == 1){
                    arr[0] = 0;
                    move_total--;
                }
            }else if(mouse_previous_move == 2){
                if(arr[3] == 1){
                    arr[3] = 0;
                    move_total--;
                }
            }else if(mouse_previous_move == 3){
                if(arr[2] == 1){
                    arr[2] = 0;
                    move_total--;
                }
            }
        }else if(move_total == 0){
            return 6;
        }
    }else if(obj == CAT_ID){
        if(move_total > 1){
            if(cat_previous_move == 0){
                if(arr[1] == 1){
                    arr[1] = 0;
                    move_total--;
                }
            }else if(cat_previous_move == 1){
                if(arr[0] == 1){
                    arr[0] = 0;
                    move_total--;
                }
            }else if(cat_previous_move == 2){
                if(arr[3] == 1){
                    arr[3] = 0;
                    move_total--;
                }
            }else if(cat_previous_move == 3){
                if(arr[2] == 1){
                    arr[2] = 0;
                    move_total--;
                }
            }
        }else if(move_total == 0){
            return 6;
        }
    }
    srand(time(NULL));
    int random_dir = rand() % move_total + 1;
    for(int i = 0; i < sizeof(arr); i++){
        random_dir -= arr[i];
        if(random_dir == 0){
            return i;
        }
    }
    return 6;
}

void move_mouse(){
    aStar(mouse_coords, CHEESE_COORDS);
}

void move_cat(){
    // Check left
    if(cat_coords.second > 0 && (maze[cat_coords.first][cat_coords.second - 1] == 0 || maze[cat_coords.first][cat_coords.second - 1] == MOUSE_ID)){
        if(maze[cat_coords.first][cat_coords.second - 1] == MOUSE_ID){
            is_success = true;
            move_left(CAT_ID);
            cout << "The cat has caught the mouse\n";
            return;
        }
        cat_available_moves[0] = 1;
    }else{
        cat_available_moves[0] = 0;
    }
    // Check right
    if(cat_coords.second < (sizeof(maze[1]) - 1) / sizeof(int) && (maze[cat_coords.first][cat_coords.second + 1] == 0 || maze[cat_coords.first][cat_coords.second + 1] == MOUSE_ID)){
        if(maze[cat_coords.first][cat_coords.second + 1] == MOUSE_ID){
            is_success = true;
            move_right(CAT_ID);
            cout << "The cat has caught the mouse\n";
            return;
        }
        cat_available_moves[1] = 1;
    }else{
        cat_available_moves[1] = 0;
    }
    // Check up
    if(cat_coords.first > 0 && (maze[cat_coords.first - 1][cat_coords.second] == 0 || maze[cat_coords.first - 1][cat_coords.second] == MOUSE_ID)){
        if(maze[cat_coords.first - 1][cat_coords.second] == MOUSE_ID){
            is_success = true;
            move_up(CAT_ID);
            cout << "The cat has caught the mouse\n";
            return;
        }
        cat_available_moves[2] = 1;
    }else{
        cat_available_moves[2] = 0;
    }
    // Check down
    if(cat_coords.first < (sizeof(maze[0]) - 1) / sizeof(int) && (maze[cat_coords.first + 1][cat_coords.second] == 0 || maze[cat_coords.first + 1][cat_coords.second] == MOUSE_ID)){
        if(maze[cat_coords.first + 1][cat_coords.second] == MOUSE_ID){
            is_success = true;
            move_down(CAT_ID);
            cout << "The cat has caught the mouse at\n";
            return;
        }
        cat_available_moves[3] = 1;
    }else{
        cat_available_moves[3] = 0;
    }

    int chosen_dir = rand_dir(cat_available_moves, CAT_ID);

    if(chosen_dir == 0){
        move_left(CAT_ID);
        cout << "The cat is moving left\n";
    }else if(chosen_dir == 1){
        move_right(CAT_ID);
        cout << "The cat is moving right\n";
    }else if(chosen_dir == 2){
        move_up(CAT_ID);
        cout << "The cat is moving up\n";
    }else if(chosen_dir == 3){
        move_down(CAT_ID);
        cout << "The cat is moving down\n";
    }
}

void main(){
    while(!is_success){
    //for(int k = 0; k < 1; k++){
        for(int i = 0; i < 11; i++){
            for(int j = 0; j < 11; j++){
                if(maze[i][j] == 1){
                    cout << "|";
                }else if(maze[i][j] == 3){
                    cout << "m";
                }else if(maze[i][j] == 4){
                    cout << "C";
                }else if(maze[i][j] == 5){
                    cout << "c";
                }else{
                    cout << " ";
                }
            }
        cout << "\n";
    }

    move_mouse();
    move_cat();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    total_moves++;
    }
    cout << "Total moves: " << total_moves;
}