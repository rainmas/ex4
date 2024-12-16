/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define PYRAMID_SIZE 5
#define WEIGHT_LOAD 0.5

#define MAX_BOARD_SIZE 20

#define MAX_CROSSWORD_SIZE 30
#define MAX_CROSSWORD_WORDS 100
#define MAX_WORD_SIZE 15


int task1RobotPaths(int x, int y);
float task2HumanPyramid(int x, int y, float pyramid[][PYRAMID_SIZE], int pyramidSize, float weightLoad);
char task3ParenthesisValidator();
int task3Helper();
int task4QueensBattle(char board[][MAX_BOARD_SIZE], int maxBoardSize, int boardSize, int x, int y);
void printBoard(char board[][MAX_BOARD_SIZE], int boardSize);
void copyBoard(char board1[][MAX_BOARD_SIZE], char board2[][MAX_BOARD_SIZE], int boardSize, int x, int y);
void markBoardHorizontal(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y);
void markBoardVertical(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y);
void markDiagonals(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y);
void markRegion(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y, char region);
void task5CrosswordGenerator();

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                printf("Please enter the coordinates of the robot (column, row):\n");
                int x, y, paths;
                scanf("%d %d", &x, &y);
                paths = task1RobotPaths(x, y);
                printf("The total number of paths the robot can take to reach home is: %d\n", paths);
                break;
            case 2:
                printf("Please enter the weights of the cheerleaders:\n");
                float pyramid[PYRAMID_SIZE][PYRAMID_SIZE];
                for (int i = 0; i < PYRAMID_SIZE; i++)
                {
                    for (int j = 0; j < PYRAMID_SIZE; j++)
                    {
                        if (j < i + 1)
                            scanf("%f", &pyramid[i][j]);
                        else
                            pyramid[i][j] = 0;
                    }
                }
                for (int i = 0; i < PYRAMID_SIZE; i++)
                {
                    for (int j = 0; j < i + 1; j++)
                    {
                        printf("%.2f ", task2HumanPyramid(j, i, pyramid, PYRAMID_SIZE, WEIGHT_LOAD));
                    }
                    printf("\n");
                }
                break;
            case 3:
                printf("Please enter a term for validation:\n");
                if (task3Helper())
                    printf("The parentheses are balanced correctly.\n");
                else
                    printf("The parentheses are not balanced correctly.\n");
                break;
            case 4:
                printf("Please enter the board dimensions:\n");
                int boardSize;
                scanf("%d", &boardSize);
                char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
                printf("Please enter the %d*%d puzzle board:\n", boardSize, boardSize);
                for (int i = 0; i < boardSize; i++)
                {
                    for (int j = 0; j < boardSize; j++)
                    {
                        scanf(" %c", &board[i][j]);
                    }
                }
                task4QueensBattle(board, MAX_BOARD_SIZE, boardSize, 0, 0);
                break;
            case 5:
                task5CrosswordGenerator();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int task1RobotPaths(int x, int y)
{
    if (x < 0 || y < 0)
        return 0;
    if (x == 0 && y == 0)
        return 1;
    return task1RobotPaths(x - 1, y) + task1RobotPaths(x, y - 1);
}

float task2HumanPyramid(int x, int y, float pyramid[][PYRAMID_SIZE], int pyramidSize, float weightLoad)
{
    if (y < 0 || x < 0)
        return 0;
    return (weightLoad * task2HumanPyramid(x, y - 1, pyramid, pyramidSize, weightLoad)) +
           (weightLoad * task2HumanPyramid(x - 1, y - 1, pyramid, pyramidSize, weightLoad)) + pyramid[y][x];
}

int task3Helper()
{
    scanf("%*c");
    int res = !task3ParenthesisValidator();
    if (!res)
        scanf("%*[^\n]");
    return res;
}

char task3ParenthesisValidator()
{
    char c;
    scanf("%c", &c);
    switch (c)
    {
    case '(':
        if (task3ParenthesisValidator() != ')')
            return 1;
        break;
    case '{':
        if (task3ParenthesisValidator() != '}')
            return 1;
        break;
    case '[':
        if (task3ParenthesisValidator() != ']')
            return 1;
        break;
    case '<':
        if (task3ParenthesisValidator() != '>')
            return 1;
        break;
    case ')':
    case '}':
    case ']':
    case '>':
        return c;
        break;
    case '\n':
        return 0;
        break;
    }
    return task3ParenthesisValidator();
}

void copyBoard(char board1[][MAX_BOARD_SIZE], char board2[][MAX_BOARD_SIZE], int boardSize, int x, int y)
{
    if (y >= boardSize || x >= boardSize)
        return;
    board2[y][x] = board1[y][x];
    if (x == 0)
        copyBoard(board1, board2, boardSize, x, y + 1);
    copyBoard(board1, board2, boardSize, x + 1, y);
}

void markBoardHorizontal(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y)
{
    if (x >= boardSize)
        return;
    if (board[y][x] != 'X')
        board[y][x] = '*';
    markBoardHorizontal(board, boardSize, x + 1, y);
}

void markBoardVertical(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y)
{
    if (y >= boardSize)
        return;
    if (board[y][x] != 'X')
        board[y][x] = '*';
    markBoardVertical(board, boardSize, x, y + 1);
}

void markDiagonals(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y)
{
    if (x > 0)
    {
        if (y > 0)
            board[y - 1][x - 1] = '*';
        if (y < boardSize - 1)
            board[y + 1][x - 1] = '*';
    }
    if (x < boardSize - 1)
    {
        if (y > 0)
            board[y - 1][x + 1] = '*';
        if (y < boardSize - 1)
            board[y + 1][x + 1] = '*';
    }
}

void markRegion(char board[][MAX_BOARD_SIZE], int boardSize, int x, int y, char region)
{
    if (x >= boardSize || y >= boardSize)
        return;
    if (board[y][x] == region)
    {
        board[y][x] = '*';
    }
    markRegion(board, boardSize, x + 1, y, region);
    if (x == 0)
        markRegion(board, boardSize, x, y + 1, region);
}

void printBoard(char board[][MAX_BOARD_SIZE], int boardSize)
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int task4QueensBattle(char board[][MAX_BOARD_SIZE], int maxBoardSize, int boardSize, int x, int y)
{
    if (x >= boardSize)
    {
        if (y == 0)
            printf("This puzzle cannot be solved.\n");
        return 0;
    }
    if (y >= boardSize)
        return 1;
    char originalBoard[maxBoardSize][maxBoardSize];
    char region;
    copyBoard(board, originalBoard, boardSize, 0, 0);
    if (board[y][x] != '*')
    {
        region = board[y][x];
        board[y][x] = 'X';
        markBoardHorizontal(board, boardSize, 0, y);
        markBoardVertical(board, boardSize, x, 0);
        markDiagonals(board, boardSize, x, y);
        markRegion(board, boardSize, 0, y, region);
        if (task4QueensBattle(board, maxBoardSize, boardSize, 0, y + 1))
        {
            if (y == 0)
                printBoard(board, boardSize);
            return 1;
        }
        else
        {
            copyBoard(originalBoard, board, boardSize, 0, 0);
            return task4QueensBattle(board, maxBoardSize, boardSize, x + 1, y);
        }
    }
    return task4QueensBattle(board, maxBoardSize, boardSize, x + 1, y);
}

void task5CrosswordGenerator()
{
    // Todo
}
