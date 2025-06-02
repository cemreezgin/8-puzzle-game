#ifndef DATA_TYPES_H
#define DATA_TYPES_H



#define PUZZLE_DIMENSION 3
#define PUZZLE_SIZE      (PUZZLE_DIMENSION * PUZZLE_DIMENSION)  // 9
#define BLANK_TILE       0


enum ACTIONS 
{
	Move_Up,
    Move_Down,
    Move_Left,
    Move_Right

};

#define ACTIONS_NUMBER 4

typedef struct State {
    int tiles[PUZZLE_SIZE];
    int blank_pos;
    float h_n;
    unsigned int hash;  
} State;


void Compute_State_Hash(State *state);


enum METHODS
{
	BreastFirstSearch = 1,   UniformCostSearch = 2,        DepthFirstSearch = 3,    
	DepthLimitedSearch= 4,   IterativeDeepeningSearch = 5, GreedySearch = 6,
    AStarSearch = 7, GeneralizedAStarSearch = 8  
};


typedef struct Transition_Model
{
    State new_state;
    float step_cost;
}Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; 
    struct Node *parent;
    int Number_of_Child; 
}Node;

typedef struct Queue  
{
    Node *node;
    struct Queue *next;
}Queue;

void Compute_State_Hash(State *state);


#endif
