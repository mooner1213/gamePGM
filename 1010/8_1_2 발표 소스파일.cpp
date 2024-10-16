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
void restart_game(void);  // �ٽ� ���� ��� �߰�

int main(void)
{
    game_control();
    return 0;
}

// Ŀ�� ��ġ�� (x, y) ��ǥ�� �̵���Ű�� �Լ�
void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �������� �׸��� �Լ�
void draw_check01(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6; // ASCII �ڵ�
    unsigned char b[12]; 
    for (i = 1; i < 12; i++)
        b[i] = 0xa0 + i;

    // ù ��° �� �׸���
    printf("%c%c", a, b[3]);
    for (i = 0; i < c - 1; i++)
        printf("%c%c", a, b[8]);
    printf("%c%c", a, b[4]);
    printf("\n");

    // ������ �� �׸���
    for (i = 0; i < r - 1; i++)
    {
        printf("%c%c", a, b[7]);
        for (j = 0; j < c - 1; j++)
            printf("%c%c", a, b[11]);
        printf("%c%c", a, b[9]);
        printf("\n");
    }

    // ������ �� �׸���
    printf("%c%c", a, b[6]);
    for (i = 0; i < c - 1; i++)
        printf("%c%c", a, b[10]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

// ���� ���� �Լ� (���� ��� ����, �ٽ� ���� ��� �߰�)
void game_control(void)
{
    int x = 1, y = 1, matrix[20][20] = {0};  // ĳ���� �ʱ� ��ġ�� �� ���� �迭
    int turn = 0;  // ���� �����ϴ� ���� (�浹, �鵹 ��ü)
    char key;
    do
    {
        gotoxy(1, 1);
        draw_check01(18, 18);  // 18x18 ������ �׸���
        gotoxy(x, y);  // ĳ���ʹ� �� ĭ�� �̵�
        printf("��");  // ĳ���� ���
        display_stone(matrix);  // �� ���
        gotoxy(1, 20);
        printf("����Ű�� �����̰� ");
        printf("�����̽� Ű�� �����ÿ�.");
        key = _getch();  // Ű �Է� �ޱ�
        if (key == 27)  // ESC Ű�� ���α׷� ����
            exit(0);
        else if (key == 32)  // �����̽��ٷ� �� ����
        {
            if (matrix[x][y] == 0)  // �� �ڸ��� �� ����
            {
                turn++;  // �� ����
                matrix[x][y] = (turn % 2 == 1) ? 1 : 2;  // �浹(1), �鵹(2) ������ ����
                
                // �¸� ���� Ȯ��
                if (check_winner(matrix, x, y, matrix[x][y]))
                {
                    gotoxy(1, 22);
                    if (matrix[x][y] == 1)
                        printf("�浹 �¸�!\n");
                    else
                        printf("�鵹 �¸�!\n");

                    // �ٽ� ���� ���� ����
                    restart_game();
                }
            }
        }
        else if (key >= 72)  // ����Ű �Է¿� ���� ĳ���� �̵�
            move_arrow_key(key, &x, &y, 18, 18);  // �̵� ó��
    } while (1);
}

// ���� ���� ����ϴ� �Լ�
void display_stone(int matrix[][20])
{
    int x, y;
    for (x = 1; x < 20; x++)  // ��� ĭ�� Ȯ���Ͽ� �� ���
    {
        for (y = 1; y < 20; y++)
        {
            if (matrix[x][y] == 1)
            {
                gotoxy(x, y);  // �浹 ��ġ�� Ŀ�� �̵�
                printf("��");  // �浹 ���
            }
            else if (matrix[x][y] == 2)
            {
                gotoxy(x, y);  // �鵹 ��ġ�� Ŀ�� �̵�
                printf("��");  // �鵹 ���
            }
        }
    }
}

// �¸� ���� Ȯ�� �Լ� (����, ����, �밢������ 5���� �� Ȯ��)
int check_winner(int matrix[][20], int x, int y, int stone)
{
    int dx[] = {1, 0, 1, 1}; // ������, �Ʒ�, ������ �밢��, ���� �밢��
    int dy[] = {0, 1, 1, -1};
    int i, j, count;

    // 4���� ������ Ȯ�� (����, ����, �� �밢��)
    for (i = 0; i < 4; i++)
    {
        count = 1;
        // ���� �������� �� Ȯ��
        for (j = 1; j < 5; j++)
        {
            int nx = x + dx[i] * j;
            int ny = y + dy[i] * j;
            if (nx < 1 || nx >= 20 || ny < 1 || ny >= 20) break;  // ��� üũ
            if (matrix[nx][ny] != stone) break;  // ���� ���� �ƴϸ� �ߴ�
            count++;
        }
        // �ݴ� �������� �� Ȯ��
        for (j = 1; j < 5; j++)
        {
            int nx = x - dx[i] * j;
            int ny = y - dy[i] * j;
            if (nx < 1 || nx >= 20 || ny < 1 || ny >= 20) break;  // ��� üũ
            if (matrix[nx][ny] != stone) break;  // ���� ���� �ƴϸ� �ߴ�
            count++;
        }
        // 5�� �̻��� ���� ���ӵǸ� �¸�
        if (count >= 5) return 1;
    }
    return 0;  // �¸� ������ �ƴϸ� 0 ��ȯ
}

// ����Ű �Է¿� ���� ĳ���� �̵��� ó���ϴ� �Լ�
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
    switch (key)
    {
        case 72:  // ���� ����Ű �Է�
            *y1 = *y1 - 1;
            if (*y1 < 1) *y1 = 1;
            break;
        case 75:  // ���� ����Ű �Է�
            *x1 = *x1 - 1;  // 1ĭ�� �̵�
            if (*x1 < 1) *x1 = 1;
            break;
        case 77:  // ������ ����Ű �Է�
            *x1 = *x1 + 1;  // 1ĭ�� �̵�
            if (*x1 > x_b) *x1 = x_b;
            break;
        case 80:  // �Ʒ��� ����Ű �Է�
            *y1 = *y1 + 1;
            if (*y1 > y_b) *y1 = y_b;
            break;
        default:
            return;
    }
}

// �ٽ� ���� ���θ� ���� �Լ�
void restart_game(void)
{
    char choice;
    printf("�ٽ� �����Ϸ��� Y�� ��������. �����Ϸ��� �ƹ� Ű�� ��������.\n");
    choice = _getch();
    if (choice == 'Y' || choice == 'y')
    {
        system("cls");  // ȭ�� �ʱ�ȭ
        game_control();  // ������ �ٽ� ����
    }
    else
    {
        exit(0);  // ���α׷� ����
    }
}

