#include <iostream>

using namespace std;

const int CHEESE_COORDS[2] = {2, 8};
const int MOUSE_ID = 3;
const int CAT_ID = 4;
const int CHEESE_ID = 5;

/*
* 1 represents a wall, 0 represents an open space
* 3 represents the mouse, 4 represents the cat, and 5 represents the cheese
*/
int maze[11][11] = {{3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
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
int mouse_coords[2] = {0, 0};
int cat_coords[2] = {6, 8};
int mouse_available_moves[4] = {0, 1, 0, 0};
int mouse_previous_move = 6;
int cat_available_moves[4] = {0, 0, 0, 1};
int cat_previous_move = 6;
bool is_success = false;
int total_moves = 0;

void move_left(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords[1] > 0 && maze[mouse_coords[0]][mouse_coords[1] - 1] == 0 || maze[mouse_coords[0]][mouse_coords[1] - 1] == CHEESE_ID){
            maze[mouse_coords[0]][mouse_coords[1]] = 0;
            maze[mouse_coords[0]][mouse_coords[1] - 1] = obj;
            mouse_coords[1]--;
            mouse_previous_move = 0;
        }else{
            cout << "Error, invalid move\n";
    }
    }else if(obj == CAT_ID){
        if(cat_coords[1] > 0 && maze[cat_coords[0]][cat_coords[1] - 1] == 0 || maze[cat_coords[0]][cat_coords[1] - 1] == MOUSE_ID){
            maze[cat_coords[0]][cat_coords[1]] = 0;
            maze[cat_coords[0]][cat_coords[1] - 1] = obj;
            cat_coords[1]--;
            cat_previous_move = 0;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void move_right(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords[1] < (sizeof(maze[1]) - 1) / sizeof(int) && maze[mouse_coords[0]][mouse_coords[1] + 1] == 0 || maze[mouse_coords[0]][mouse_coords[1] + 1] == CHEESE_ID){
            maze[mouse_coords[0]][mouse_coords[1]] = 0;
            maze[mouse_coords[0]][mouse_coords[1] + 1] = obj;
            mouse_coords[1]++;
            mouse_previous_move = 1;
        }else{
            cout << "Error, invalid move\n";
        }
    }else if(obj == CAT_ID){
        if(cat_coords[1] < (sizeof(maze[1]) - 1) / sizeof(int) && maze[cat_coords[0]][cat_coords[1] + 1] == 0 || maze[cat_coords[0]][cat_coords[1] + 1] == MOUSE_ID){
            maze[cat_coords[0]][cat_coords[1]] = 0;
            maze[cat_coords[0]][cat_coords[1] + 1] = obj;
            cat_coords[1]++;
            cat_previous_move = 1;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void move_up(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords[0] > 0 && maze[mouse_coords[0] - 1][mouse_coords[1]] == 0 || maze[mouse_coords[0] - 1][mouse_coords[1]] == CHEESE_ID){
            maze[mouse_coords[0]][mouse_coords[1]] = 0;
            maze[mouse_coords[0] - 1][mouse_coords[1]] = obj;
            mouse_coords[0]--;
            mouse_previous_move = 2;
        }else{
            cout << "Error, invalid move\n";
        }
    }else if(obj == CAT_ID){
        if(cat_coords[0] > 0 && maze[cat_coords[0] - 1][cat_coords[1]] == 0 || maze[cat_coords[0] - 1][cat_coords[1]] == MOUSE_ID){
            maze[cat_coords[0]][cat_coords[1]] = 0;
            maze[cat_coords[0] - 1][cat_coords[1]] = obj;
            cat_coords[0]--;
            cat_previous_move = 2;
        }else{
            cout << "Error, invalid move\n";
        }
    }
}

void move_down(int obj){
    if(obj == MOUSE_ID){
        if(mouse_coords[0] < (sizeof(maze[0]) - 1) / sizeof(int) && maze[mouse_coords[0] + 1][mouse_coords[1]] == 0 || maze[mouse_coords[0] + 1][mouse_coords[1]] == CHEESE_ID){
            maze[mouse_coords[0]][mouse_coords[1]] = 0;
            maze[mouse_coords[0] + 1][mouse_coords[1]] = obj;
            mouse_coords[0]++;
            mouse_previous_move = 3;
        }else{
            cout << "Error, invalid move\n";
        }
    }else if(obj == CAT_ID){
        if(cat_coords[0] < (sizeof(maze[0]) - 1) / sizeof(int) && maze[cat_coords[0] + 1][cat_coords[1]] == 0 || maze[cat_coords[0] + 1][cat_coords[1]] == MOUSE_ID){
            maze[cat_coords[0]][cat_coords[1]] = 0;
            maze[cat_coords[0] + 1][cat_coords[1]] = obj;
            cat_coords[0]++;
            cat_previous_move = 3;
        }else{
            cout << "Error, invalid move\n";
        }
    }
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
    // Check left
    if(mouse_coords[1] > 0 && (maze[mouse_coords[0]][mouse_coords[1] - 1] == 0 || maze[mouse_coords[0]][mouse_coords[1] - 1] == CHEESE_ID)){
        if(maze[mouse_coords[0]][mouse_coords[1] - 1] == CHEESE_ID){
            is_success = true;
            move_left(MOUSE_ID);
            cout << "The mouse has reached the cheese\n";
            return;
        }
        mouse_available_moves[0] = 1;
    }else{
        mouse_available_moves[0] = 0;
    }
    // Check right
    if(mouse_coords[1] < (sizeof(maze[1]) - 1) / sizeof(int) && (maze[mouse_coords[0]][mouse_coords[1] + 1] == 0 || maze[mouse_coords[0]][mouse_coords[1] + 1] == CHEESE_ID)){
        if(maze[mouse_coords[0]][mouse_coords[1] + 1] == CHEESE_ID){
            is_success = true;
            move_right(MOUSE_ID);
            cout << "The mouse has reached the cheese\n";
            return;
        }
        mouse_available_moves[1] = 1;
    }else{
        mouse_available_moves[1] = 0;
    }
    // Check up
    if(mouse_coords[0] > 0 && (maze[mouse_coords[0] - 1][mouse_coords[1]] == 0 || maze[mouse_coords[0] - 1][mouse_coords[1]] == CHEESE_ID)){
        if(maze[mouse_coords[0] - 1][mouse_coords[1]] == CHEESE_ID){
            is_success = true;
            move_up(MOUSE_ID);
            cout << "The mouse has reached the cheese\n";
            return;
        }
        mouse_available_moves[2] = 1;
    }else{
        mouse_available_moves[2] = 0;
    }
    // Check down
    if(mouse_coords[0] < (sizeof(maze[0]) - 1) / sizeof(int) && (maze[mouse_coords[0] + 1][mouse_coords[1]] == 0 || maze[mouse_coords[0] + 1][mouse_coords[1]] == CHEESE_ID)){
        if(maze[mouse_coords[0] + 1][mouse_coords[1]] == CHEESE_ID){
            is_success = true;
            move_down(MOUSE_ID);
            cout << "The mouse has reached the cheese\n";
            return;
        }
        mouse_available_moves[3] = 1;
    }else{
        mouse_available_moves[3] = 0;
    }

    int chosen_dir = rand_dir(mouse_available_moves, MOUSE_ID);

    if(chosen_dir == 0){
        move_left(MOUSE_ID);
        cout << "The mouse is moving left\n";
    }else if(chosen_dir == 1){
        move_right(MOUSE_ID);
        cout << "The mouse is moving right\n";
    }else if(chosen_dir == 2){
        move_up(MOUSE_ID);
        cout << "The mouse is moving up\n";
    }else if(chosen_dir == 3){
        move_down(MOUSE_ID);
        cout << "The mouse is moving down\n";
    }else{
        cout << "No valid moves\n";
    }
}

void move_cat(){
    // Check left
    if(cat_coords[1] > 0 && (maze[cat_coords[0]][cat_coords[1] - 1] == 0 || maze[cat_coords[0]][cat_coords[1] - 1] == MOUSE_ID)){
        if(maze[cat_coords[0]][cat_coords[1] - 1] == MOUSE_ID){
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
    if(cat_coords[1] < (sizeof(maze[1]) - 1) / sizeof(int) && (maze[cat_coords[0]][cat_coords[1] + 1] == 0 || maze[cat_coords[0]][cat_coords[1] + 1] == MOUSE_ID)){
        if(maze[cat_coords[0]][cat_coords[1] + 1] == MOUSE_ID){
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
    if(cat_coords[0] > 0 && (maze[cat_coords[0] - 1][cat_coords[1]] == 0 || maze[cat_coords[0] - 1][cat_coords[1]] == MOUSE_ID)){
        if(maze[cat_coords[0] - 1][cat_coords[1]] == MOUSE_ID){
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
    if(cat_coords[0] < (sizeof(maze[0]) - 1) / sizeof(int) && (maze[cat_coords[0] + 1][cat_coords[1]] == 0 || maze[cat_coords[0] + 1][cat_coords[1]] == MOUSE_ID)){
        if(maze[cat_coords[0] + 1][cat_coords[1]] == MOUSE_ID){
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
    //for(int k = 0; k < 5; k++){
        for(int i = 0; i < 11; i++){
            for(int j = 0; j < 11; j++){
                if(maze[i][j] == 1){
                    cout << "|";
                }else if(maze[i][j] == 3){
                    cout << "M";
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