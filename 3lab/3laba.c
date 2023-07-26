#include <windows.h>
#include "math.h"
#include "stdio.h"
//21-15
const int n1 = 2;
const int n2 = 1;
const int n3 = 1; //10+1 = 11 - число вершин
const int n4 = 5; // 5 - трикутник
const int vertices = n3 + 10;
#define IDC_BUTTON 1
#define IDC_BUTTON2 2
int state = 0;

double **randm(int n){
    double **matrix;
    matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }

    srand(2115);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = (double)rand() / RAND_MAX * 2.0;
        }
    }
    return matrix;
}

double **mulmr(double coef, double **matrix) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            matrix[i][j] *= coef;
            matrix[i][j] = matrix[i][j] < 1 ? 0 : 1;
        }
    }
    return matrix;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[]  = "My Window Class";
    const char WINDOW_NAME[] = "Lab number3 by Kostiantyn Matiushenko IM-21";
    WNDCLASSEX wc = {0};
    wc.cbSize        = sizeof(wc);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // завантажений курсор
    wc.lpszClassName = CLASS_NAME;
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            WINDOW_NAME,
            WS_OVERLAPPEDWINDOW,
            100, 100, 1000, 700,
            NULL, NULL, hInstance, NULL
    );
    if (hwnd == NULL) {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

void arrow(double fi, double px,double py, HDC hdc){
    int lx,ly,rx,ry;
    lx = px+15*cos(fi+0.3);
    rx = px+15*cos(fi-0.3);
    ly = py+15*sin(fi+0.3);
    ry = py+15*sin(fi-0.3);
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

double **symmetricMatrix(double **matrix) {
    double **symmetrical = (double **) malloc(vertices * sizeof(double *));
    for (int i = 0; i < vertices; ++i) {
        symmetrical[i] = (double *) malloc(vertices * sizeof(double));
    }
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            symmetrical[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (symmetrical[i][j] != symmetrical[j][i]) {
                symmetrical[i][j] = 1;
                symmetrical[j][i] = 1;
            }
        }
    }
    return symmetrical;
}

void freeMatrix(double **matrix) {
    for (int i = 0; i < vertices; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void drawArc(int startX, int startY, int finalX, int finalY, int radiusOfVertex, HDC hdc, int t) {
    int top_left[2] = {};
    int bottom_right[2] = {};
    double circleCenter[2] = {};
    double newlineangle;
    if(startX < finalX && startY < finalY){
        top_left[0] = startX;
        top_left[1] = startY-(finalY-startY);
        bottom_right[0] = finalX+(finalX-startX);
        bottom_right[1] = finalY;
        circleCenter[0] = finalX;
        circleCenter[1] = startY;
        newlineangle = M_PI;
    }
    else if(startX < finalX && startY > finalY){
        top_left[0] = finalX;
        top_left[1] = startY;
        bottom_right[0] = startX+(startX-finalX);
        bottom_right[1] = finalY+(finalY- startY);
        newlineangle = M_PI_2;
    }
     else if(startX>finalX && startY>finalY){
        top_left[0] = finalX;
        top_left[1] = startY;
        bottom_right[0] = startX+(startX-finalX);
        bottom_right[1] = finalY+(finalY- startY);
        newlineangle = -M_PI_2;
    }
    else if(startX>finalX && startY<finalY){
        top_left[0] = finalX;
        top_left[1] = startY;
        bottom_right[0] = startX+(startX-finalX);
        bottom_right[1] = finalY+(finalY- startY);
        newlineangle = -M_PI_2;
    }
    else if(startX == finalX && startY == finalY) {
        top_left[0] = startX;
        top_left[1] = startY;
        bottom_right[0] = startX + 40;
        bottom_right[1] = startY + 40;

    }
    else{
        top_left[0] = startX;
        top_left[1] = startY-40;
        bottom_right[0] = finalX;
        bottom_right[1] = finalY+40;
        if(finalX>startX){
            newlineangle = M_PI-M_PI_4;
        }
        else{
            newlineangle = -M_PI_4;
        }

    }
    if(t == 0){
        //не зовсім зрозумів як нормально стрілочки зробити, але що є те є
        arrow(newlineangle, finalX + radiusOfVertex * cos(newlineangle), finalY + radiusOfVertex * sin(newlineangle), hdc);
    }
    Arc(hdc, top_left[0],top_left[1],bottom_right[0],bottom_right[1],startX,startY,finalX,finalY);
}

void drawDirectedGraph(int nx[], int ny[], int radiusOfVertex, HDC hdc, HPEN BPen, HPEN KPen, double **matrix){
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            MoveToEx(hdc, nx[i], ny[i], NULL);
            if((matrix[i][j] == 1 && i < 6 && j < 6 && abs(i-j)>1)){
                drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 0);
            }
            else if(((matrix[i][j] == 1 && i < 9 && j < 9 && i >= 5 && j >= 5 && abs(i-j)>1))){
                drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 0);
            }
            else if((matrix[i][j] == 1 && i < 11 && j < 11 && i >= 8 && j >= 8 && abs(i-j)>1) ||
            ((matrix[i][j] == 1 && i == 0 && j < 11 && j >= 8 && abs(i-j)>1) ||
            (matrix[i][j] == 1 && j == 0 && i < 11 && i >= 8 && abs(i-j)>1))){
                drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 0);
            }
            else if ((j >= i && matrix[i][j] == 1) || (j <= i && matrix[i][j] == 1 && matrix[j][i] == 0)){
                if (i == j) {
                    drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 0);
                }else{
                    LineTo(hdc, nx[j], ny[j]);
                    double line_angle = atan2(ny[i] - ny[j], nx[i] - nx[j]);
                    arrow(line_angle, nx[j] + radiusOfVertex * cos(line_angle),
                          ny[j] + radiusOfVertex * sin(line_angle), hdc);
                }
            }
            else if (j < i && matrix[i][j] == 1 && matrix[j][i] == 1) {
                drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 0);
            }
        }
    }
}
void drawUndirectedGraph(int nx[], int ny[], double **matrix, HPEN KPen, HPEN GPen, HDC hdc, int radiusOfVertex) {
    for (int i = 0; i < vertices; ++i) {

        for (int j = 0; j < vertices; ++j) {
            if (i > j) continue;
            MoveToEx(hdc, nx[i], ny[i], NULL);
            if (matrix[i][j] == 1) {
                if(i < 6 && j < 6 && abs(i-j)>1){
                    drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 1);
                }
                else if(i < 9 && j < 9 && i >= 5 && j >= 5 && abs(i-j)>1){
                    drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 1);
                }
                else if((i < 11 && j < 11 && i >= 8 && j >= 8 && abs(i-j)>1) ||
                        (i == 0 && j < 11 && j >= 8 && abs(i-j)>1)){
                    drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 1);
                }
                else if(i == j){
                    drawArc(nx[i], ny[i], nx[j], ny[j], radiusOfVertex, hdc, 1);
                }
                else{LineTo(hdc, nx[j], ny[j]);}
            }
        }
    }

}
void displayMatrix(double **matrix) {
    for(int i = 0;i<vertices;i++){
        for (int j = 0; j < vertices; j++) {
            printf("%.0f ", matrix[i][j]);
        }
        printf("\n");
    }
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    HDC hdc; // контекст
    PAINTSTRUCT ps; // екземпляр структури
    HWND Button_directed;
    HWND Button_undirected;
    switch (msg) {
        case WM_CREATE: {
            Button_directed = CreateWindow(
                    (LPCSTR) "BUTTON",
                    (LPCSTR) "Directed",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    700,
                    30,
                    160,
                    50,
                    hwnd,
                    (HMENU) IDC_BUTTON,
                    (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);
            Button_undirected = CreateWindow(
                    (LPCSTR) "BUTTON",
                    (LPCSTR) "Undirected",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    700,
                    100,
                    160,
                    50,
                    hwnd,
                    (HMENU) IDC_BUTTON2,
                    (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);
            return 0;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {

                case IDC_BUTTON:
                    state = 0;
                    InvalidateRect(hwnd, NULL, FALSE);
                    break;

                case IDC_BUTTON2:
                    state = 1;
                    InvalidateRect(hwnd, NULL, FALSE);
                    break;
            }
        }
        case WM_PAINT :
            hdc=BeginPaint(hwnd, &ps);
            char *nn[] = {"1", "2", "3", "4", "5","6", "7","8","9","10","11"};

            int nx[] = {100,200,300,400,500,600, 510,440,350,260,190,};
            int ny[] = {500,500,500, 500, 500, 500, 357,244,100,244,357,};
            int rad = 16;
            int dtx  = rad/2.5;

            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN NoPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
            SelectObject(hdc, NoPen);
            Rectangle(hdc, 0, 0, 1000, 1000);
            SelectObject(hdc, KPen);

            double **matrix = randm(vertices);
            double coefficient = 1.0 - 0.02 * n3 - 0.005 * n4 - 0.25;
            matrix = mulmr(coefficient, matrix);
            double **symetric_matrix = symmetricMatrix(matrix);
            printf("directed matrix : \n");
            displayMatrix(matrix);
            printf("\nundirected matrix : \n");
            displayMatrix(symetric_matrix);

            SelectObject(hdc, KPen);

            state == 0?
            drawDirectedGraph(nx, ny, rad, hdc, BPen, KPen, matrix):
            drawUndirectedGraph(nx,ny,symetric_matrix,KPen,BPen,hdc,rad);

            SelectObject(hdc, BPen);
            for(int i=0;i<sizeof(nx)/sizeof (int);i++){
                Ellipse(hdc, nx[i]-rad,ny[i]-rad,nx[i]+rad,ny[i]+rad);
                TextOut(hdc, nx[i]-dtx,ny[i]-rad/2, nn[i],2);
            }

            freeMatrix(matrix);
            freeMatrix(symetric_matrix);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
