const int rows = 30;
const int cols = 30;

int aliveNeighbours;
int isAlive;

int row_line();
int EvaluateNeighbourCount(int state[rows][cols], int cellRow, int cellCol);
void Render(int renderState[rows][cols], int* state1Ptr);