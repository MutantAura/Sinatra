const int rows = 20;
const int cols = 30;

int row_line();
int EvaluateNeighbourCount(int state[rows][cols], int cellRow, int cellCol);
void Render(int renderState[rows][cols], int* state1Ptr);