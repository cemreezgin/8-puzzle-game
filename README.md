# 🧩 8-Puzzle Solver in C

This project is a C implementation of various graph search algorithms designed to solve the classic 8-puzzle problem. It allows users to input custom initial and goal states and supports multiple search strategies including:

- Breadth-First Search (BFS)  
- Depth-First Search (DFS)  
- Depth-Limited Search  
- Iterative Deepening Search  
- Uniform Cost Search (UCS)  
- Greedy Search  
- A* Search  
- Generalized A* Search 

The solver visually prints each puzzle state and displays the complete solution path, showing applied actions, path cost, and number of nodes generated/searched. It is suitable for educational use, experimentation with search algorithms, or understanding heuristic design.

---

## 🔧 How to Compile

Use the provided `makefile.h` to compile:

```bash
make -f makefile.h
