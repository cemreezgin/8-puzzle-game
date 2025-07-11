#ifndef TREE_SERACH_H
#define TREE_SERACH_H

#include "data_types.h"

// ======== PUZZLE-SPECIFIC CONSTANTS ========
#define PUZZLE_DIMENSION       3               // 3×3’lük bir tahta
#define PUZZLE_SIZE            (PUZZLE_DIMENSION * PUZZLE_DIMENSION)  // 9 hücre
#define BLANK_TILE             0               // Boş kareyi temsil eden değer


// ========  YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) COMMANDS ============ 
#define PREDETERMINED_GOAL_STATE  1 // User will initially determine the goal state if it is true (1)
#define ACTIONS_NUMBER  4          // Move_Up, Move_Down, Move_Right, Move_Left
#define MAX_SEARCHED_NODE 100000000 // exit from the search process if it is exceeded  

// ================== YOU DO NOT NEED TO CHANGE THIS PART ======================
#define NO_ACTION  0
#define TRUE       1
#define FALSE      0
#define FAILURE    NULL
#define NODE_POOL_SIZE 1000000
extern Node node_pool[NODE_POOL_SIZE];
extern int pool_index;
#define MAX_NODES 1000000
extern Node node_pool[MAX_NODES];
extern int pool_index;
#ifdef DEBUG
#define DEBUG_PRINT(msg) printf(msg)
#else
#define DEBUG_PRINT(msg)
#endif


// =========  YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) DECLARATIONS =======
State* Create_State();
void Print_State(const State *const state);
void Print_Action(const enum ACTIONS action);
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model);
float Compute_Heuristic_Function(const State *const state, const State *const goal); 
int Goal_Test(const State *const state, const State *const goal_state);

// ======= YOU DO NOT NEED TO CHANGE THIS COMPULSORY DECLARATIONS EXCEPT INSERTION OF THE GENERALIZED A* ALGORITHM==============
Node* First_GoalTest_Search_TREE(const enum METHODS method, Node *const root, State *const goal_state);
Node* First_InsertFrontier_Search_TREE(const enum METHODS method, Node *const root, State *const goal_state, float alpha); // Update for THE GENERALIZED A* 
Node* DepthType_Search_TREE(const enum METHODS method, Node *const root, State *const goal_state, const int Max_Level);
Node* Child_Node(Node *const parent, const enum ACTIONS action); 
Queue* Start_Frontier(Node *const root);
int Empty(const Queue *const frontier);
Node* Pop(Queue **frontier);
void Insert_FIFO(Node *const child, Queue **frontier);
void Insert_LIFO(Node *const child, Queue **frontier);
void Insert_Priority_Queue_UniformSearch(Node *const child, Queue **frontier); 
void Insert_Priority_Queue_GreedySearch(Node *const child, Queue **frontier);
void Insert_Priority_Queue_A_Star(Node *const child, Queue **frontier); 
void Insert_Priority_Queue_GENERALIZED_A_Star(Node *const child, Queue **frontier, float alpha);  // Update for THE GENERALIZED A* 
void Print_Frontier(Queue *const frontier);
void Show_Solution_Path(Node *const goal);	
void Print_Node(const Node *const node);
int Level_of_Node(Node *const node);
void Clear_All_Branch(Node *node, int *Number_Allocated_Nodes);
void Clear_Single_Branch(Node *node, int *Number_Allocated_Nodes);
void Warning_Memory_Allocation();
int Compare_States(const State *const state1, const State *const state2);
Node* Frontier_search(Queue *const frontier, const State *const state);
void Remove_Node_From_Frontier(Node *const old_child, Queue **const frontier) ; 

// ==================== WRITE YOUR OPTIONAL DECLARATIONS =======================

#endif
