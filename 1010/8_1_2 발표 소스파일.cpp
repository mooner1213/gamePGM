#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_check01(int c, int r);
void game_control(void);
void display_stone(int matrix[][20]);
int check_winner(int matrix[][20], int x, int y, int stone);
void restart_game(void);  // 다시 시작 기능 추가

int main(void)
{
    game_control();
    return 0;
}

// 커서 위치를 (x, y) 좌표로 이동시키는 함수
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 격자판을 그리는 함수
void draw_check01(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6; // ASCII 코드
    unsigned char b[12]; 
    for (i = 1; i < 12; i++)
        b[i] = 0xa0 + i;

    // 첫 번째 줄 그리기
    printf("%c%c", a, b[3]);
    for (i = 0; i < c - 1; i++)
        printf("%c%c", a, b[8]);
    printf("%c%c", a, b[4]);
    printf("\n");

    // 나머지 줄 그리기
    for (i = 0; i < r - 1; i++)
    {
        printf("%c%c", a, b[7]);
        for (j = 0; j < c - 1; j++)
            printf("%c%c", a, b[11]);
        printf("%c%c", a, b[9]);
        printf("\n");
    }

    // 마지막 줄 그리기
    printf("%c%c", a, b[6]);
    for (i = 0; i < c - 1; i++)
        printf("%c%c", a, b[10]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

// 게임 제어 함수 (오목 기능 포함, 다시 시작 기능 추가)
void game_control(void)
{
    int x = 1, y = 1, matrix[20][20] = {0};  // 캐릭터 초기 위치와 돌 저장 배열
    int turn = 0;  // 턴을 관리하는 변수 (흑돌, 백돌 교체)
    char key;
    do
    {
        gotoxy(1, 1);
        draw_check01(18, 18);  // 18x18 격자판 그리기
        gotoxy(x, y);  // 캐릭터는 한 칸씩 이동
        printf("○");  // 캐릭터 출력
        display_stone(matrix);  // 돌 출력
        gotoxy(1, 20);
        printf("방향키로 움직이고 ");
        printf("스페이스 키를 누르시오.");
        key = _getch();  // 키 입력 받기
        if (key == 27)  // ESC 키로 프로그램 종료
            exit(0);
        else if (key == 32)  // 스페이스바로 돌 놓기
        {
            if (matrix[x][y] == 0)  // 빈 자리에 돌 놓기
            {
                turn++;  // 턴 증가
                matrix[x][y] = (turn % 2 == 1) ? 1 : 2;  // 흑돌(1), 백돌(2) 번갈아 놓기
                
                // 승리 조건 확인
                if (check_winner(matrix, x, y, matrix[x][y]))
                {
                    gotoxy(1, 22);
                    if (matrix[x][y] == 1)
                        printf("흑돌 승리!\n");
                    else
                        printf("백돌 승리!\n");

                    // 다시 시작 여부 묻기
                    restart_game();
                }
            }
        }
        else if (key >= 72)  // 방향키 입력에 따른 캐릭터 이동
            move_arrow_key(key, &x, &y, 18, 18);  // 이동 처리
    } while (1);
}

// 놓인 돌을 출력하는 함수
void display_stone(int matrix[][20])
{
    int x, y;
    for (x = 1; x < 20; x++)  // 모든 칸을 확인하여 돌 출력
    {
        for (y = 1; y < 20; y++)
        {
            if (matrix[x][y] == 1)
            {
                gotoxy(x, y);  // 흑돌 위치로 커서 이동
                printf("○");  // 흑돌 출력
            }
            else if (matrix[x][y] == 2)
            {
                gotoxy(x, y);  // 백돌 위치로 커서 이동
                printf("●");  // 백돌 출력
            }
        }
    }
}

// 승리 조건 확인 함수 (가로, 세로, 대각선으로 5개의 돌 확인)
int check_winner(int matrix[][20], int x, int y, int stone)
{
    int dx[] = {1, 0, 1, 1}; // 오른쪽, 아래, 오른쪽 대각선, 왼쪽 대각선
    int dy[] = {0, 1, 1, -1};
    int i, j, count;

    // 4개의 방향을 확인 (가로, 세로, 두 대각선)
    for (i = 0; i < 4; i++)
    {
        count = 1;
        // 한쪽 방향으로 돌 확인
        for (j = 1; j < 5; j++)
        {
            int nx = x + dx[i] * j;
            int ny = y + dy[i] * j;
            if (nx < 1 || nx >= 20 || ny < 1 || ny >= 20) break;  // 경계 체크
            if (matrix[nx][ny] != stone) break;  // 같은 돌이 아니면 중단
            count++;
        }
        // 반대 방향으로 돌 확인
        for (j = 1; j < 5; j++)
        {
            int nx = x - dx[i] * j;
            int ny = y - dy[i] * j;
            if (nx < 1 || nx >= 20 || ny < 1 || ny >= 20) break;  // 경계 체크
            if (matrix[nx][ny] != stone) break;  // 같은 돌이 아니면 중단
            count++;
        }
        // 5개 이상의 돌이 연속되면 승리
        if (count >= 5) return 1;
    }
    return 0;  // 승리 조건이 아니면 0 반환
}

// 방향키 입력에 따른 캐릭터 이동을 처리하는 함수
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch (key)
    {
        case 72:  // 위쪽 방향키 입력
            *y1 = *y1 - 1;
            if (*y1 < 1) *y1 = 1;
            break;
        case 75:  // 왼쪽 방향키 입력
            *x1 = *x1 - 1;  // 1칸씩 이동
            if (*x1 < 1) *x1 = 1;
            break;
        case 77:  // 오른쪽 방향키 입력
            *x1 = *x1 + 1;  // 1칸씩 이동
            if (*x1 > x_b) *x1 = x_b;
            break;
        case 80:  // 아래쪽 방향키 입력
            *y1 = *y1 + 1;
            if (*y1 > y_b) *y1 = y_b;
            break;
        default:
            return;
    }
}

// 다시 시작 여부를 묻는 함수
void restart_game(void)
{
    char choice;
    printf("다시 시작하려면 Y를 누르세요. 종료하려면 아무 키나 누르세요.\n");
    choice = _getch();
    if (choice == 'Y' || choice == 'y')
    {
        system("cls");  // 화면 초기화
        game_control();  // 게임을 다시 시작
    }
    else
    {
        exit(0);  // 프로그램 종료
    }
}

