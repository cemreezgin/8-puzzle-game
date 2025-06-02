/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//______________________________________________________________________________
int isSolvable(int tiles[]);
State* Create_State() {
    State *state = (State*)malloc(sizeof(State));
    if (state == NULL) {
        Warning_Memory_Allocation();
    }

    printf("Enter 8-puzzle board (3x3), use 0 for empty tile:\n");
    
    // Initialize with invalid values to force user input
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        state->tiles[i] = -1;
    }

    int used[PUZZLE_SIZE] = {0};
    int valid_input = 0;
    
    while (!valid_input) {
        valid_input = 1; // Assume input will be valid
        
        // Reset tracking arrays
        memset(used, 0, sizeof(used));
        state->blank_pos = -1;

        // Get user input
        for (int i = 0; i < PUZZLE_SIZE; i++) {
            printf("Tile[%d]: ", i);
            scanf("%d", &state->tiles[i]);
            
            // Validate input
            if (state->tiles[i] < 0 || state->tiles[i] >= PUZZLE_SIZE) {
                printf("Error: Numbers must be between 0-8\n");
                valid_input = 0;
                break;
            }
            
            // Check for duplicates
            if (used[state->tiles[i]]) {
                printf("Error: Number %d already used!\n", state->tiles[i]);
                valid_input = 0;
                break;
            }
            
            used[state->tiles[i]] = 1;
            
            // Track blank position
            if (state->tiles[i] == BLANK_TILE) {
                state->blank_pos = i;
            }
        }

        // Verify we have exactly one blank tile
        if (valid_input && state->blank_pos == -1) {
            printf("Error: Puzzle must contain exactly one blank tile (0)\n");
            valid_input = 0;
            continue;
        }

        // Check solvability
        if (valid_input && !isSolvable(state->tiles)) {
            printf("Warning: This puzzle configuration is unsolvable!\n");
            printf("You may continue with this unsolvable puzzle or re-enter.\n");
            printf("Continue anyway? (1=Yes, 0=No): ");
            int choice;
            scanf("%d", &choice);
            valid_input = choice;
        }
    }

    state->h_n = 0.0f;
    Compute_State_Hash(state);
    return state;
}

// Improved solvability check for 8-puzzle
int isSolvable(int tiles[PUZZLE_SIZE]) {
    int inversions = 0;
    int blank_row = 0;
    
    // Count inversions
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (tiles[i] == BLANK_TILE) {
            blank_row = i / PUZZLE_DIMENSION;
            continue;
        }
        
        for (int j = i + 1; j < PUZZLE_SIZE; j++) {
            if (tiles[j] != BLANK_TILE && tiles[i] > tiles[j]) {
                inversions++;
            }
        }
    }

    /*
     * Solvability rules for 8-puzzle:
     * 1. If grid width is odd, then solvable if number of inversions is even
     * 2. If grid width is even:
     *    - blank on odd row from bottom (0=bottom) and number of inversions is even -> solvable
     *    - blank on even row from bottom and number of inversions is odd -> solvable
     */
    if (PUZZLE_DIMENSION % 2 == 1) { // Odd grid (3x3)
        return (inversions % 2 == 0);
    } else { // Even grid (not needed for 8-puzzle but included for completeness)
        return ((blank_row % 2) != (inversions % 2));
    }
}





//______________________________________________________________________________

void Print_State(const State *const state) {
    // Her bir satırın üst çerçevesi
    for (int r = 0; r < PUZZLE_DIMENSION; ++r) {
        printf("+");
        for (int c = 0; c < PUZZLE_DIMENSION; ++c)
            printf("---+");
        printf("\n|");

        // Satırdaki her hücre
        for (int c = 0; c < PUZZLE_DIMENSION; ++c) {
            int idx = r * PUZZLE_DIMENSION + c;  // Doğru 1D dizin
            if (state->tiles[idx] == BLANK_TILE) {
                printf("   |");                 // Boş kare
            } else {
                printf(" %d |", state->tiles[idx]);
            }
        }
        printf("\n");
    }

    // Son satır çerçevesi
    printf("+");
    for (int c = 0; c < PUZZLE_DIMENSION; ++c)
        printf("---+");
    printf("\n");
}



//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
   switch(action){
         case  Move_Up:    printf("Move Up"); break;
         case  Move_Down:  printf("Move Down"); break;
         case  Move_Left:  printf("Move Left"); break;
         case  Move_Right: printf("Move Right"); break;
         default:          printf("Unknown Action"); break;
         
    }        
}

//______________________________________________________________________________
int Result(const State *const parent_state,
    const enum ACTIONS action,
    Transition_Model *const trans_model)
{
// 1) Önce tek boyutlu indeksi satır/sütuna çevir
int pos = parent_state->blank_pos;
int r = pos / PUZZLE_DIMENSION;
int c = pos % PUZZLE_DIMENSION;
int nr = r, nc = c;

// 2) Eyleme göre yeni konumu hesapla
switch(action) {
case Move_Up:    nr = r - 1; break;
case Move_Down:  nr = r + 1; break;
case Move_Left:  nc = c - 1; break;
case Move_Right: nc = c + 1; break;
default:         return FALSE;
}

// 3) Sınır dışı kontrolü
if (nr < 0 || nr >= PUZZLE_DIMENSION ||
 nc < 0 || nc >= PUZZLE_DIMENSION)
 return FALSE;

// 4) Yeni indeksi hesapla
int new_pos = nr * PUZZLE_DIMENSION + nc;

// 5) Durumu kopyala ve swap et
State new_s = *parent_state;
new_s.tiles[pos]       = new_s.tiles[new_pos];
new_s.tiles[new_pos]   = BLANK_TILE;
new_s.blank_pos        = new_pos;

// 6) Transition model’i doldur
trans_model->new_state = new_s;
trans_model->step_cost = 1;

Compute_State_Hash(&trans_model->new_state); // Yeni durum için hash hesapla
        return TRUE;
}


//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal) {
    
    int total = 0;
    // Manhattan mesafesi
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (state->tiles[i] == BLANK_TILE) continue;
        int goal_pos;
        for (goal_pos = 0; goal_pos < PUZZLE_SIZE; goal_pos++)
            if (goal->tiles[goal_pos] == state->tiles[i]) break;
        int row = i / 3, col = i % 3;
        int goal_row = goal_pos / 3, goal_col = goal_pos % 3;
        total += abs(row - goal_row) + abs(col - goal_col);
    }
    // Linear Conflict ekle (aynı satır/sütunda hedefe ters sırada olanlar)
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        for (int j = i + 1; j < PUZZLE_SIZE; j++) {
            if (state->tiles[i] == BLANK_TILE || state->tiles[j] == BLANK_TILE) continue;
            if ((i / 3 == j / 3) && (state->tiles[i] > state->tiles[j]))
                total += 2; // Her çakışma +2 maliyet
        }
    }
    
    return total;
}
int Goal_Test(const State *const state, const State *const goal_state) {
    if(goal_state == NULL) return FALSE;
    for(int i = 0; i < PUZZLE_SIZE; ++i)
        if(state->tiles[i] != goal_state->tiles[i])
            return FALSE;
    return TRUE;
}






