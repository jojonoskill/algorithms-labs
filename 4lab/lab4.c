#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.h>
#include <math.h>


#define RADIUS_VALUE 35
#define SMALL_OFFSET_VALUE 20
#define BIG_OFFSET_VALUE 40
#define OFFSET_X_VALUE 16
#define OFFSET_Y_VALUE 16
#define DTX_VALUE 5



float** randm(int n) {
    srand(2121);
    float** arr = (float**)malloc(n * sizeof(float*));
    for(int i = 0; i < n; i++){
        arr[i] = (float*)malloc(n * sizeof(float));
        for(int j = 0; j < n; j++){
            arr[i][j] = ((float)rand() / (float)RAND_MAX) * 2.0;
        }
    }

    return arr;
}




float** multiplyMatrixAndRound(float coefficient, float** matrix, int n) { //or mulmr
    float** result = (float**)malloc(n * sizeof(float*));
    for(int i = 0; i < n; i++){
        result[i] = (float*)malloc(n * sizeof(float));
        for(int j = 0; j < n; j++){
            result[i][j] = floorf(matrix[i][j] * coefficient);
        }
    }

    return result;
}

char** symbolArray(int N){
    char** array = malloc(N * sizeof(char*));
    for(int i = 0; i < N; i++) {
        array[i] = malloc(3 * sizeof(char));
        sprintf(array[i], "%d", i+1);
    }
    return array;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int show)
{
    WNDCLASS windClass;
    windClass.style = CS_HREDRAW | CS_VREDRAW;
    windClass.lpfnWndProc = WndProc;
    windClass.cbClsExtra = 0;
    windClass.cbWndExtra = 0;
    windClass.hInstance = hInstance;
    windClass.hIcon = 0;
    windClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1 );
    windClass.lpszMenuName = 0;
    windClass.lpszClassName = L"Lab 4";

    if (!RegisterClass(&windClass)) return 0;

    HWND hWnd = CreateWindow(L"Lab 4",
                             L"Lab 4. Khvyts Maksim",
                             WS_OVERLAPPEDWINDOW,
                             100, 100, 1400, 1000,
                             NULL, NULL, hInstance, NULL
    );
    if(!hWnd) return 0;

    ShowWindow(hWnd, show);
    MSG lpMsg;
    int b;

    while ((b = GetMessage(&lpMsg, hWnd, 0, 0)) != 0)
    {
        if (b == -1)
            return lpMsg.wParam;
        else {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    }
    return(lpMsg.wParam);
}


void arrow(float fi, int px, int py, HDC context)
{
    fi = 3.1416 * (180.0 - fi) / 180.0;
    int leftX, leftY, rightX, rightY;
    leftX = px + 15 * cos(fi + 0.3);
    rightX = px + 15 * cos(fi - 0.3);
    leftY = py + 15 * sin(fi + 0.3);
    rightY = py + 15 * sin(fi - 0.3);
    MoveToEx(context, leftX, leftY, NULL);
    LineTo(context, px, py);
    LineTo(context, rightX, rightY);
}

void releaseMemory(float** matrix, int N) {
    if (matrix == NULL) return ;

    for (int i = 0; i < N; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
            matrix[i] = NULL;
        }
    }

    free(matrix);
    matrix = NULL;
}

void drawArrowWithSize(int startX, int startY, int endX, int endY, int arrowSize, HDC context) {
    float angleRad = atan2f((endY - startY), (endX - startX));
    float pointX = endX - arrowSize * cosf(angleRad);
    float pointY = endY - arrowSize * sinf(angleRad);
    arrow(angleRad, pointX, pointY, context);
}
int isArrayRegular(int size, int* array) {
    for (int i = 0; i < size; i++) {
        if (array[0] != array[i]) return 0;
    } return 1;
}

float** createSymmetricMatrix(float** mat, int N) {
    float** result = (float**)malloc(N * sizeof(float*));
    if (result != NULL) {
        for (int i = 0; i < N; i++) {
            result[i] = (float*)malloc(N * sizeof(float));
            if (result[i] != NULL) {
                for (int j = 0; j < N; j++) {
                    if (mat[i][j] == 1 || mat[j][i] == 1) {
                        result[i][j] = 1;
                    } else {
                        result[i][j] = 0;
                    }
                }
            } else {
                // Обробка помилки при виділенні пам'яті для рядка матриці
                // Можна додати код для звільнення пам'яті, виділеної для попередніх рядків матриці
                // та повернути NULL або індикатор помилки
            }
        }
    } else {
        // Обробка помилки при виділенні пам'яті для матриці
        // Можна повернути NULL або індикатор помилки
    }
    return result;
}

void printModifiedMatrix(int size, float** matrix) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("%.0f ", matrix[row][col]);
        }
        printf("\n");
    }
}

void displayModifiedIntArray(int size, int* array){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printRegularityStatus(int isRegular, int* array){
    if(isRegular == 0){
        printf("Graph is not regular.\n");
    } else if(isRegular == 1){
        printf("Graph is regular.\n Power of regularity is: %d\n", array[1]);
    }
}

void calculateArrayX(int size, int* arr) {
    float step = size / 5.0;
    int ceilStep = ceilf(step);
    int offset = 500;

    for (int i = 0; i < ceilStep + 1; i++)
        *(arr + i) = 100 + 100 * i + offset;

    for (int i = ceilStep + 1; i < ceilStep * 2 + 1; i++)
        *(arr + i) = *(arr + i - 1);

    for (int i = ceilStep * 2 + 1; i < ceilStep * 3 + 1; i++)
        *(arr + i) = *(arr + i - 1) - 100;

    for (int i = ceilStep * 3 + 1; i < fmin(ceilStep * 4, size); i++)
        *(arr + i) = *arr;
}

void calculateArrayY(int size, int* arr) {
    float step = size / 5.0;
    int ceilStep = ceilf(step);

    const int LENGTH = 100;

    for (int i = 0; i < ceilStep + 1; i++) {
        *(arr + i) = LENGTH;
    }

    for (int i = ceilStep + 1; i < ceilStep * 2 + 1; i++) {
        *(arr + i) = *(arr + i - 1) + LENGTH;
    }

    for (int i = ceilStep * 2 + 1; i < ceilStep * 3 + 1; i++) {
        *(arr + i) = *(arr + i - 1);
    }

    for (int i = ceilStep * 3 + 1; i < fmin(ceilStep * 4, size); i++) {
        *(arr + i) = *(arr + i - 1) - LENGTH;
    }
}
// подивитись
void drawUndirectedEllipses(int index, int j, int* xCoordinates, int* yCoordinates, HDC context, int edgeCeil) {
    int direction = (index + 1) / edgeCeil + 1;

    if (direction % 2 == 0) {
        if (direction > edgeCeil) {
            Ellipse(context, xCoordinates[index] - BIG_OFFSET_VALUE, yCoordinates[index] - SMALL_OFFSET_VALUE,
                    xCoordinates[index], yCoordinates[index] + SMALL_OFFSET_VALUE);
        } else {
            Ellipse(context, xCoordinates[index] + BIG_OFFSET_VALUE, yCoordinates[index] - SMALL_OFFSET_VALUE,
                    xCoordinates[index], yCoordinates[index] + SMALL_OFFSET_VALUE);
        }
    } else {
        if (direction >= edgeCeil) {
            Ellipse(context, xCoordinates[index] - SMALL_OFFSET_VALUE, yCoordinates[index] + BIG_OFFSET_VALUE,
                    xCoordinates[index] + SMALL_OFFSET_VALUE, yCoordinates[index]);
        } else {
            Ellipse(context, xCoordinates[index] - SMALL_OFFSET_VALUE, yCoordinates[index] - BIG_OFFSET_VALUE,
                    xCoordinates[index] + SMALL_OFFSET_VALUE, yCoordinates[index]);
        }
    }
}

void drawUndirectedConnection(int index1, int index2, int* xCoords, int* yCoords, HDC context, int edgeCeil){
    if(xCoords[index1] == xCoords[index2]){
        MoveToEx(context, xCoords[index1], yCoords[index1], NULL);
        LineTo(context, xCoords[index2]+RADIUS_VALUE, yCoords[index1]-(yCoords[index1]-yCoords[index2])/2);
        MoveToEx(context, xCoords[index2]+RADIUS_VALUE, yCoords[index1]-(yCoords[index1]-yCoords[index2])/2, NULL);
        LineTo(context, xCoords[index2], yCoords[index2]);
    } else{
        MoveToEx(context, xCoords[index1], yCoords[index1], NULL);
        LineTo(context, xCoords[index2]+(xCoords[index1]-xCoords[index2])/2, yCoords[index1]-RADIUS_VALUE);
        MoveToEx(context, xCoords[index2]+(xCoords[index1]-xCoords[index2])/2, yCoords[index1]-RADIUS_VALUE, NULL);
        LineTo(context, xCoords[index2], yCoords[index2]);
    }
}

void drawUndirectedCommonLines(int index1, int index2, HDC context, int* xCoordinates, int* yCoordinates){
    MoveToEx(context, xCoordinates[index1], yCoordinates[index1], NULL);
    LineTo(context, xCoordinates[index2], yCoordinates[index2]);
}

void drawUndirectedGraph(HWND window, HDC context, const int vertices, char** names, int* xCoords, int* yCoords, float** adjacency) {
    int ceilEdges = (int)ceil((float)vertices / 4.0);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    SelectObject(context, pen);

    printf("Undirected adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (adjacency[j][i] == 1 || adjacency[i][j] == 1) {
                printf("1");
            }
            else {
                printf("%.0f ", adjacency[i][j]);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (adjacency[i][j] == 1) {
                if (i == j) {
                    drawUndirectedEllipses(i, j, xCoords, yCoords, context, ceilEdges);
                }
                else if (((abs(i - j) >= 2 && abs(i - j) <= ceilEdges) || abs(i - j) >= 3 * ceilEdges) && (xCoords[i] == xCoords[j] || yCoords[i] == yCoords[j])) {
                    drawUndirectedConnection(i, j, xCoords, yCoords, context, ceilEdges);
                }
                else {
                    drawUndirectedCommonLines(i, j, context, xCoords, yCoords);
                }
            }
        }
    }
    HPEN boldPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    SelectObject(context, boldPen);
    for (int i = 0; i < vertices; i++) {
        Ellipse(context, xCoords[i] - OFFSET_X_VALUE, yCoords[i] - OFFSET_Y_VALUE, xCoords[i] + OFFSET_X_VALUE, yCoords[i] + OFFSET_Y_VALUE);
        TextOut(context, xCoords[i] - DTX_VALUE, yCoords[i] - OFFSET_Y_VALUE / 2, names[i], 2);
    }
}



void changeCommonLines(int a, int b, HDC dc, int x[], int y[], int dX, float** M){
    if(a > b && M[b][a] == 1){
        MoveToEx(dc, x[a], y[a], NULL);
        LineTo(dc, (x[a]+x[b])/2, (y[a]+y[b])/2+10);
        MoveToEx(dc, (x[a]+x[b])/2, (y[a]+y[b])/2+10, NULL);
        LineTo(dc, x[b], y[b]);
        drawArrowWithSize((x[a]+x[b])/2, (y[a]+y[b])/2+10, x[b], y[b], dX, dc);
    } else if(y[a] == y[b]){
        MoveToEx(dc, x[a], y[a], NULL);
        LineTo(dc, (x[a]+x[b])/2+10, (y[a]+y[b])/2);
        MoveToEx(dc, (x[a]+x[b])/2+10, (y[a]+y[b])/2, NULL);
        LineTo(dc, x[b], y[b]);
        drawArrowWithSize((x[a]+x[b])/2+10, (y[a]+y[b])/2, x[b], y[b], dX, dc);
    } else{
        MoveToEx(dc, x[a], y[a], NULL);
        LineTo(dc, x[b], y[b]);
        drawArrowWithSize(x[a], y[a], x[b], y[b], dX, dc);
    }
}


void drawObscureEllipses(int a, int b, HDC dc, int x[], int y[], int dX, int adgeCeil) {
    if (a == b) {
        int dir = (int)ceil ((a + 1) / (float)adgeCeil);
        if (dir % 2 == 0) {
            if (dir > ceil) {
                Ellipse(dc, x[a] - 100, y[a] - 50, x[a], y[a] + 50);
                drawArrowWithSize(x[a] - 25, y[a] + 75, x[b], y[b], dX, dc);
            }
            else {
                Ellipse(dc, x[a] + 100, y[a] - 50, x[a], y[a] + 50);
                drawArrowWithSize(x[a] + 25, y[a] - 75, x[b], y[b], dX, dc);
            }
        }
        else {
            if (dir >= ceil) {
                Ellipse(dc, x[a] - 50, y[a] + 100, x[a] + 50, y[a]);
                drawArrowWithSize(x[a] + 75, y[a] + 75, x[b], y[b], dX, dc);
            }
            else {
                Ellipse(dc, x[a] - 50, y[a] - 100, x[a] + 50, y[a]);
                drawArrowWithSize(x[a] - 75, y[a] - 75, x[b], y[b], dX, dc);
            }
        }
    }
}

void obscureLines(int a, int b, HDC dc, int x[], int y[], int dX){
    if(x[a] == x[b]){
        if(a > b){
            MoveToEx(dc, x[a], y[a], NULL);
            LineTo(dc, x[b]+100, y[a]-(y[a]-y[b])/2);
            MoveToEx(dc, x[b]+100, y[a]-(y[a]-y[b])/2, NULL);
            LineTo(dc, x[b], y[b]);
            drawArrowWithSize(x[b]+100, y[a]-(y[a]-y[b])/2, x[b], y[b], dX, dc);
        } else{
            MoveToEx(dc, x[a], y[a], NULL);
            LineTo(dc, x[b]-100, y[a]-(y[a]-y[b])/2);
            MoveToEx(dc, x[b]-100, y[a]-(y[a]-y[b])/2, NULL);
            LineTo(dc, x[b], y[b]);
            drawArrowWithSize(x[b]-100, y[a]-(y[a]-y[b])/2, x[b], y[b], dX, dc);
        }
    } else{
        if(a > b){
            MoveToEx(dc, x[a], y[a], NULL);
            LineTo(dc, x[b]+(x[a]-x[b])/2, y[a]+100);
            MoveToEx(dc, x[b]+(x[a]-x[b])/2, y[a]+100, NULL);
            LineTo(dc, x[b], y[b]);
            drawArrowWithSize(x[b]+(x[a]-x[b])/2, y[a]+100, x[b], y[b], dX, dc);
        } else{
            MoveToEx(dc, x[a], y[a], NULL);
            LineTo(dc, x[b]+(x[a]-x[b])/2, y[a]-100);
            MoveToEx(dc, x[b]+(x[a]-x[b])/2, y[a]-100, NULL);
            LineTo(dc, x[b], y[b]);
            drawArrowWithSize(x[b]+(x[a]-x[b])/2, y[a]-100, x[b], y[b], dX, dc);
        }
    }
}

void modifyGraph(HWND window, HDC context, int vertices, int xCords[], int yCords[], char** labels, float** matrix){
    int ceilEdges = ceil(vertices / 4.0);

    printf("Adjacency matrix:\n");
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            printf("%.0f ", matrix[i][j]);
        }
        printf("\n");
    }

    int totalLines = 0;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            if(matrix[i][j] == 1){
                totalLines++;
                drawObscureEllipses(i, j, context, xCords, yCords, OFFSET_X_VALUE, ceilEdges);
                if(((abs(i-j) >=2 && abs(i-j) <= ceilEdges) || abs(i-j) >= 3*ceilEdges) && (xCords[i] == xCords[j] || yCords[i] == yCords[j])){
                    obscureLines(i, j, context, xCords, yCords, OFFSET_X_VALUE);
                }
                else if(i != j){
                    changeCommonLines(i, j, context, xCords, yCords, OFFSET_X_VALUE, matrix);
                }
            }
        }
    }

    printf("Number of all lines: %d\n", totalLines);

    HPEN thickPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN thinPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(context, thickPen);
    for(int i = 0; i < vertices; i++){
        Ellipse(context, xCords[i] - OFFSET_X_VALUE, yCords[i] - OFFSET_Y_VALUE, xCords[i] + OFFSET_X_VALUE, yCords[i] + OFFSET_Y_VALUE);
        TextOut(context, xCords[i] - DTX_VALUE, yCords[i] - OFFSET_Y_VALUE / 2, labels[i], 2);
    }
}

int* calculateVertexPowers(int vertexCount, float** adjacencyMatrix) {
    int* powers = malloc(vertexCount * sizeof(int));

    for(int i = 0; i < vertexCount; i++) {
        powers[i] = 0;
        for(int j = 0; j < vertexCount; j++) {
            if(adjacencyMatrix[i][j] == 1.0) {
                powers[i]++;
            }
        }
    }

    return powers;
}


int* calculateOutDegrees(int vertexCount, float** adjacencyMatrix) {
    int* outDegrees = (int*) malloc(vertexCount * sizeof(int));

    for (int i = 0; i < vertexCount; i++) {
        int count = 0;
        for (int j = 0; j < vertexCount; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                count++;
            }
        }
        outDegrees[i] = count;
    }

    return outDegrees;
}

int* calculateInDegrees(int vertexCount, float** adjacencyMatrix) {
    int* inDegrees = (int*) malloc(vertexCount * sizeof(int));

    for (int i = 0; i < vertexCount; i++) {
        inDegrees[i] = 0;
    }

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                inDegrees[j]++;
            }
        }
    }

    return inDegrees;
}

int* classifyVertices(int vertexCount, int* degrees) {
    int* classifications = (int*) malloc(vertexCount * sizeof(int));

    for (int i = 0; i < vertexCount; i++) {
        if (degrees[i] == 0) {
            classifications[i] = 0; // Isolated vertex
        } else if (degrees[i] == 1) {
            classifications[i] = 1; // Pendant vertex
        } else {
            classifications[i] = 2; // Regular vertex
        }
    }

    return classifications;
}

void drawIsolatedPendantVertices(HWND hWnd, HDC context, int N, int xCoordinates[], int yCoordinates[], char** vertexNames, int* classifications) {
    HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN yellowPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

    for (int i = 0; i < N; i++) {
        HPEN pen;

        if (classifications[i] == 0) {
            pen = redPen; // Isolated vertex
        } else if (classifications[i] == 1) {
            pen = yellowPen; // Pendant vertex
        } else {
            continue; // Skip regular vertices
        }

        SelectObject(context, pen);
        Ellipse(context, xCoordinates[i] - OFFSET_X_VALUE, yCoordinates[i] - OFFSET_Y_VALUE, xCoordinates[i] + OFFSET_X_VALUE, yCoordinates[i] + OFFSET_Y_VALUE);
        TextOut(context, xCoordinates[i] - DTX_VALUE, yCoordinates[i] - OFFSET_Y_VALUE / 2, vertexNames[i], 2);
    }
}

float** multiplyMatrices(float** mat1, float** mat2, int N) {
    float** result = (float**)malloc(N * sizeof(float*));

    for (int i = 0; i < N; i++) {
        result[i] = (float*)malloc(N * sizeof(float));
        memset(result[i], 0, N * sizeof(float)); // Initialize the row to 0

        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

float** powerMatrix(float** matrix, int N, int power) {
    float** result = (float**)malloc(N * sizeof(float*));

    for (int i = 0; i < N; i++) {
        result[i] = (float*)malloc(N * sizeof(float));
        memcpy(result[i], matrix[i], N * sizeof(float));
    }

    for (int p = 1; p < power; p++) {
        float** temp = (float**)malloc(N * sizeof(float*));

        for (int i = 0; i < N; i++) {
            temp[i] = (float*)malloc(N * sizeof(float));
            memset(temp[i], 0, N * sizeof(float));
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    temp[i][j] += result[i][k] * matrix[k][j];
                }
            }
        }

        for (int i = 0; i < N; i++) {
            free(result[i]);
        }
        free(result);

        result = temp;
    }

    return result;
}

float** transposeMatrix(float** matrix, int rows, int columns) {
    float** result = (float**)malloc(columns * sizeof(float*));
    for (int i = 0; i < columns; i++) {
        result[i] = (float*)malloc(rows * sizeof(float));
        for (int j = 0; j < rows; j++) {
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}

float** performElementwiseMultiplication(float** matrix1, float** matrix2, int size) {
    float** result = (float**)malloc(size * sizeof(float*));

    for (int i = 0; i < size; i++) {
        result[i] = (float*)malloc(size * sizeof(float));
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }

    return result;
}

void printIsolatedPendantVertices(int numVertices, int* vertexArray) {
    printf("\nIsolated Vertices:\n");
    for (int i = 0; i < numVertices; i++) {
        if (vertexArray[i] == 0) {
            printf("%d  ", i + 1);
        }
    }
    printf("\n\nPendant Vertices:\n");
    for (int i = 0; i < numVertices; i++) {
        if (vertexArray[i] == 1) {
            printf("%d  ", i + 1);
        }
    }
}

void findPathsTwo(float** adjacencyMatrix, int numVertices) {
    printf("Paths:\n");

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                for (int k = 0; k < numVertices; k++) {
                    if (adjacencyMatrix[j][k] == 1) {
                        printf("%d -> %d -> %d\n", i + 1, j + 1, k + 1);
                    }
                }
            }
        }
    }
}

void findPathsThree(float** adjacencyMatrix, int numVertices) {
    printf("Paths:\n");

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            for (int k = 0; k < numVertices; k++) {
                for (int m = 0; m < numVertices; m++) {
                    if (adjacencyMatrix[i][j] == 1 && adjacencyMatrix[j][k] == 1 && adjacencyMatrix[k][m] == 1) {
                        printf("%d -> %d -> %d -> %d\n", i + 1, j + 1, k + 1, m + 1);
                    }
                }
            }
        }
    }
}

float** calculateReachabilityMatrix(float** adjacencyMatrix, int numVertices) {
    float** reachabilityMatrix = (float**)malloc(numVertices * sizeof(float*));

    for (int i = 0; i < numVertices; i++) {
        reachabilityMatrix[i] = (float*)malloc(numVertices * sizeof(float));
        for (int j = 0; j < numVertices; j++) {
            reachabilityMatrix[i][j] = (adjacencyMatrix[i][j] > 0 || i == j) ? 1 : 0;
        }
    }

    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                reachabilityMatrix[i][j] = reachabilityMatrix[i][j] || (reachabilityMatrix[i][k] && reachabilityMatrix[k][j]);
            }
        }
    }

    return reachabilityMatrix;
}

float** calculateStronglyConnectedMatrix(float** adjacencyMatrix, int numVertices) {
    float** transposedMatrix = transposeMatrix(adjacencyMatrix, numVertices, numVertices);
    float** resultMatrix = performElementwiseMultiplication(adjacencyMatrix, transposedMatrix, numVertices);

    releaseMemory(transposedMatrix, numVertices);

    return resultMatrix;
}

void depthFirstSearch(int vertex, float** adjacencyMatrix, int* visited, int numVertices) {
    visited[vertex] = 1;
    printf("%d ", vertex + 1);

    for (int i = 0; i < numVertices; i++) {
        if (adjacencyMatrix[vertex][i] != 0 && !visited[i]) {
            depthFirstSearch(i, adjacencyMatrix, visited, numVertices);
        }
    }
}

void depthSecondSearch(float** adjacencyMatrix, int numVertices, int startVertex, int* visited, int* componentLabels, int component) {
    visited[startVertex] = 1;
    componentLabels[startVertex] = component;

    for (int i = 0; i < numVertices; i++) {
        if (adjacencyMatrix[startVertex][i] != 0 && !visited[i]) {
            depthSecondSearch(adjacencyMatrix, numVertices, i, visited, componentLabels, component);
        }
    }
}

void printCustomConnectedComponents(float** adjacencyMatrix, int numVertices) {
    int* visited = (int*)calloc(numVertices, sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            printf("Connected Component: ");
            depthFirstSearch(i, adjacencyMatrix, visited, numVertices);
            printf("\n");
        }
    }

    free(visited);
}

float** getCustomCondensedGraph(float** adjacencyMatrix, int N, int* componentCount) {
    int* visited = (int*)calloc(N, sizeof(int));
    int* componentLabels = (int*)malloc(N * sizeof(int));
    int component = 0;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            component++;
            depthSecondSearch(adjacencyMatrix, N, i, visited, componentLabels, component);
        }
    }

    int numComponents = component;
    float** condensedGraph = (float**)malloc(numComponents * sizeof(float*));
    float* condensedGraphData = (float*)calloc(numComponents * numComponents, sizeof(float));

    for (int i = 0; i < N; i++) {
        int componentLabel = componentLabels[i];
        for (int j = i + 1; j < N; j++) {
            if (adjacencyMatrix[i][j] != 0 && componentLabel != componentLabels[j]) {
                condensedGraphData[(componentLabel - 1) * numComponents + componentLabels[j] - 1] = 1.0;
                condensedGraphData[(componentLabels[j] - 1) * numComponents + componentLabel - 1] = 1.0;  // If adjacency matrix is symmetric
            }
        }
    }

    for (int i = 0; i < numComponents; i++) {
        condensedGraph[i] = condensedGraphData + i * numComponents;
    }

    free(visited);
    free(componentLabels);

    *componentCount = numComponents;
    return condensedGraph;
}






















void mainFunc(int option, HWND hWnd, HDC context) {
    const int N = 12;
    int xCordinate[N], yCordinate[N];
    int components = 0;
    int flag;

    calculateArrayX(N, xCordinate);
    calculateArrayY(N, yCordinate);

    char** nn = symbolArray(N);
    float** T = randm(N);
    float** A = multiplyMatrixAndRound(0.66, T, N); // Fill our matrix

    switch (option) {
        case 1:
            modifyGraph(hWnd, context, N, xCordinate, yCordinate, nn, A);
            break;
        case 2:
            drawUndirectedGraph(hWnd, context, N, nn, xCordinate, yCordinate, A);
            break;
        case 3: {
            float** symA = createSymmetricMatrix(A, N);
            int* outgoingDeg = calculateOutDegrees(N, A);
            int* incomingDeg = classifyVertices(N, A);
            int* undirectedPower = calculateVertexPowers(N, symA);

            printf("Directed graph:\n");
            printModifiedMatrix(N, A);
            printf("Half degree of incoming according to the above matrix:\n");
            displayModifiedIntArray(N, incomingDeg);
            printf("Half degree of outcoming according to the above matrix:\n");
            displayModifiedIntArray(N, outgoingDeg);
            printf("\n");
            printf("Undirected graph:\n");
            printModifiedMatrix(N, symA);
            printf("Power of vertices in the undirected graph according to the above matrix:\n");
            displayModifiedIntArray(N, undirectedPower);

            free(outgoingDeg);
            free(incomingDeg);
            free(undirectedPower);
            releaseMemory(symA, N);
            break;
        }
        case 4: {
            float** symA = createSymmetricMatrix(A, N);
            int* outgoingDeg = calculateOutDegrees(N, A);
            int* incomingDeg = classifyVertices(N, A);
            int* undirectedPower = calculateVertexPowers(N, symA);

            printf("Is the undirected graph regular? ");
            flag = isArrayRegular(N, undirectedPower);
            printRegularityStatus(flag, undirectedPower);
            printf("Is the directed graph regular for incoming vertices? ");
            flag = isArrayRegular(N, incomingDeg);
            printRegularityStatus(flag, incomingDeg);
            printf("Is the directed graph regular for outgoing vertices? ");
            flag = isArrayRegular(N, outgoingDeg);
            printRegularityStatus(flag, outgoingDeg);

            free(outgoingDeg);
            free(incomingDeg);
            free(undirectedPower);
            releaseMemory(symA, N);
            break;
        }
        case 5: {
            int* undirectedPower = calculateVertexPowers(N, createSymmetricMatrix(A, N));
            int* IsolatedPendant = classifyVertices(N, undirectedPower);

            drawUndirectedGraph(hWnd, context, N, nn, xCordinate, yCordinate, A);
            drawIsolatedPendantVertices(hWnd, context, N, xCordinate, yCordinate, nn, IsolatedPendant);
            printIsolatedPendantVertices(N, IsolatedPendant);

            free(undirectedPower);
            free(IsolatedPendant);
            break;
        }
        case 6: {
            float** A2 = multiplyMatrixAndRound(0.71, T, N);
            float** A2Power2 = powerMatrix(A2, N, 2);
            float** A2Power3 = powerMatrix(A2, N, 3);
            printf("(A2)^2:\n");
            printModifiedMatrix(N, A2Power2);
            printf("(A2)^3:\n");
            printModifiedMatrix(N, A2Power3);
            findPathsTwo(A2, N);
            findPathsThree(A2, N);

            float** symA2 = createSymmetricMatrix(A2, N);
            int* outgoingDeg = calculateOutDegrees(N, A2);
            int* incomingDeg = classifyVertices(N, A2);
            int* undirectedPower = calculateVertexPowers(N, symA2);


            modifyGraph(hWnd, context, N, xCordinate, yCordinate, nn, A2);
            printf("Half degree of incoming according to the above matrix:\n");
            displayModifiedIntArray(N, incomingDeg);
            printf("Half degree of outcoming according to the above matrix:\n");
            displayModifiedIntArray(N, outgoingDeg);
            printf("\n");
            printf("Undirected graph:\n");
            printModifiedMatrix(N, symA2);
            printf("Power of vertices in the undirected graph according to the above matrix:\n");
            displayModifiedIntArray(N, undirectedPower);


            float** reachabilityMatrix = calculateReachabilityMatrix(A2, N);
            printf("Reachability matrix:\n");
            printModifiedMatrix(N, reachabilityMatrix);

            float** strongConMat = calculateStronglyConnectedMatrix(reachabilityMatrix, N);

            printf("Strongly connected matrix:\n");
            printModifiedMatrix(N, strongConMat);

            printf("\n");
            printCustomConnectedComponents(A2, N);

            free(outgoingDeg);
            free(incomingDeg);
            free(undirectedPower);
            releaseMemory(symA2, N);
            releaseMemory(A2Power2, N);
            releaseMemory(A2Power3, N);
            releaseMemory(reachabilityMatrix, N);
            releaseMemory(strongConMat, N);
            releaseMemory(A2, N);
            break;
        }
        case 11: {
            float** A2 = multiplyMatrixAndRound(0.71, T, N);
            float** condensate = getCustomCondensedGraph(A2, N, &components);

            printCustomConnectedComponents(A2, N);

            modifyGraph(hWnd, context, components, xCordinate, yCordinate, nn, condensate);

            releaseMemory(A2, N);
            releaseMemory(condensate, components);
            break;
        }
        default:
            break;
    }

    free(nn);
    releaseMemory(T, N);
    releaseMemory(A, N);
}







void windowUpdate(HWND hWnd, HDC context, PAINTSTRUCT ps, int option){
    InvalidateRect(hWnd, NULL, TRUE);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    UpdateWindow(hWnd);
    system("cls");
    context = BeginPaint(hWnd, &ps);
    FillRect(context, &ps.rcPaint, hBrush);
    mainFunc(option, hWnd, context);
    EndPaint(hWnd, &ps);
}

//attribute

HWND btnDrawDirect;
HWND btnDrawUnd;
HWND btnPower;
HWND btnRegCheck;
HWND btnFindIsolated;
HWND btnDraw2;
HWND btnWays;
HWND btnReachable;
HWND btnStronglyConnectedMat;
HWND btnComponent;
HWND btnCondensate;







LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC context;
    PAINTSTRUCT ps;
    switch(message){
        case WM_CREATE:

            btnDrawDirect = CreateWindow("BUTTON",
                                            "Draw directed graph",
                                            WS_VISIBLE | WS_CHILD | WS_BORDER,
                                            20, 20, 150, 30,
                                            hWnd, (HMENU) 1, NULL, NULL);
            btnDrawUnd = CreateWindow("BUTTON",
                                         "Draw undirected graph",
                                         WS_VISIBLE | WS_CHILD | WS_BORDER,
                                         20, 50, 150, 30,
                                         hWnd, (HMENU) 2, NULL, NULL);
            btnPower = CreateWindow("BUTTON",
                                       "Power graph",
                                       WS_VISIBLE | WS_CHILD | WS_BORDER,
                                       20, 80, 150, 30,
                                       hWnd, (HMENU) 3, NULL, NULL);
            btnRegCheck = CreateWindow("BUTTON",
                                          "Check for regular graph",
                                          WS_VISIBLE | WS_CHILD | WS_BORDER,
                                          20, 110, 180, 30,
                                          hWnd, (HMENU) 4, NULL, NULL);
            btnFindIsolated = CreateWindow("BUTTON",
                                              "Show isolated and pendant",
                                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                                              20, 140, 200, 30,
                                              hWnd, (HMENU) 5, NULL, NULL);
            btnDraw2 = CreateWindow("BUTTON",
                                       "Draw modified graph",
                                       WS_VISIBLE | WS_CHILD | WS_BORDER,
                                       20, 170, 200, 30,
                                       hWnd, (HMENU) 6, NULL, NULL);
            btnCondensate = CreateWindow("BUTTON",
                                           "Condensate graph",
                                           WS_VISIBLE | WS_CHILD | WS_BORDER,
                                           20, 200, 200, 30,
                                           hWnd, (HMENU) 11, NULL, NULL);
            break;
        case WM_COMMAND:

            switch(LOWORD(wParam)){
                case 1:
                    windowUpdate(hWnd, context, ps, 1);
                    break;
                case 2:
                    windowUpdate(hWnd, context, ps, 2);
                    break;
                case 3:
                    windowUpdate(hWnd, context, ps, 3);
                    break;
                case 4:
                    windowUpdate(hWnd, context, ps, 4);
                    break;
                case 5:
                    windowUpdate(hWnd, context, ps, 5);
                    break;
                case 6:
                    windowUpdate(hWnd, context, ps, 6);
                    break;
                case 7:
                    windowUpdate(hWnd, context, ps, 7);
                    break;
                case 8:
                    windowUpdate(hWnd, context, ps, 8);
                    break;
                case 9:
                    windowUpdate(hWnd, context, ps, 9);
                    break;
                case 10:
                    windowUpdate(hWnd, context, ps, 10);
                    break;
                case 11:
                    windowUpdate(hWnd, context, ps, 11);
                    break;
            }
            break;
        case WM_PAINT:
            UpdateWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}