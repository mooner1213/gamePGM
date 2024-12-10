# Game Programming

## 1. 커서위치 제어

- goto 함수를 이용합니다.

```
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y);

int main(void){
      gotoxy(2,4);
      printf("Hello");
      gotoxy(40, 20);
      printf("Hello");
      return 0;
}
void gotoxy(int x, int y){
      COORD Pos = {x - 1, y - 1};
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

## 2. 화면 지우기

```
#include <stdio.h>
#include <stdlib.h>

int main(void){
        char ch;
        printf("문자를 입력하고 Enter>");
        scanf("%c", &ch);
        system("cls");
        printf("입력된 문자 %c\n", ch);
        return 0;
}
```

## 3. 키보드 입력 값의 아스키코드 출력

```
#include <stdio.h>
#include <conio.h>

int main(void){
        int chr;
        do{
                chr=getch();
                if (chr==0 || chr == 0xe0){
                        chr=getch();
                        printf("확장키 code=%d\n", chr);
                        }
                else
                printf("아스키 code=%d\n", chr);
        }while(1);
        return 0;
}
```

## 4. 방향키로 이동

```
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define X_MAX 79 //가로(열)방향의 최대값
#define Y_MAX 24 //세로(행)방향의 최대값

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);

void gotoxy(int x, int y);

int main(void){
	char key;
	int x=10, y=5;
	do {
		gotoxy(x, y);
		printf("P");
		key=getch();
		move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
		system("cls"); //화면 비우기 
	}while(key!=27);
	
	return 0;
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
	switch(key) {
		case 72: //위쪽(상) 방향의 화살표 키 입력
				*y1=*y1-1;
				if (*y1<1) *y1=1; //y좌표의 최소값
				break;
		case 75: //왼쪽(좌) 방향의 화살표 키 입력
				*x1=*x1-1;
				if (*x1<1) *x1=1; //x좌표의 최소값
				break;
		case 77: //오른쪽(우) 방향의 화살표 키 입력
				*x1=*x1+1;
				if (*x1>x_b) *x1=x_b; //x좌표의 최대값
				break;
		case 80: //아래쪽(하) 방향의 화살표 키 입력
				*y1=*y1+1;
				if (*y1>y_b) *y1=y_b; //y좌표의 최대값
				break;
		default:
				return;
	}
}

void gotoxy(int x, int y) {
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```

## 5. 사각형 만들기

![image](https://github.com/user-attachments/assets/491c43b0-e6ea-42f2-98cc-a788c6c30ab5)


![image](https://github.com/user-attachments/assets/be5ae5d8-59b4-43bc-89c3-5b78b4a4b451)

```
#include <stdio.h>

void draw_square(int size);

int main(void) {
	int n;
	
	printf("정사각형 그리기\n\n");
	printf("정사각형의 길이(최대 37)를\n");
	printf("입력하고 Enter>");
	scanf("%d", &n);
	draw_square(n);
	
	return 0;
}

void draw_square(int size) {
	int i, j;
	unsigned char a=0xa6;
	unsigned char b[7];
	
	for(i=1;i<7;i++) b[i]=0xa0+i;
	printf("%c%c",a, b[3]);
	for(i=0;i<size;i++) printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);
	printf("\n");
	for(i=0;i<size;i++) {
		printf("%c%c", a, b[2]);
		for(j=0;j<size;j++) printf(" ");
		printf("%c%c",a, b[2]);
		printf("\n");
	}
	printf("%c%c", a, b[6]);
	for(i=0;i<size;i++) printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");
}
```

## 6. 메뉴 만들기

```
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu_display(void);

void hamburger(void);

void spaghetti(void);

void press_any_key(void);

int main(void) {
	int c;
	while((c=menu_display()) != 3) {
		switch(c) {
			case 1 : hamburger();
					break;
			case 2 : spaghetti();
					break;
			default : break;
		}
	}
	
	return 0;
}

int menu_display(void) {
	int select;
	system("cls");
	printf("간식 만들기\n\n");
	printf("1. 햄버거 \n");
	printf("2. 스파게티\n");
	printf("3. 프로그램 종료\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void hamburger(void) {
	system("cls");
	printf("햄버거 만드는 방법\n");
	printf("나도 모르지롱\n");
	press_any_key();
}

void spaghetti(void) {
	system("cls");
	printf("스파게티 만드는 방법\n");
	printf("면 불리고 소스 넣고 데치면 끝\n");
	press_any_key();
}

void press_any_key(void) {
	printf("\n\n");
	printf("아무키나 누르면 메인 메뉴로...");
	getch();
}
```

+ 더많은 메뉴 만들기

```
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu_display(void);
int sub_menu_display01(void); //햄버거에 대한 서브 메뉴 출력과 번호 입력
int sub_menu_display02(void); //스파게티에 대한 서브 메뉴 출력과 번호 입력
void sub_main01(void); //햄버거에 대한 서브 메뉴 제어
void sub_main02(void); //스파게티에 대한 서브 메뉴 제어
void chicken_burger(void);
void cheese_burger(void);
void tomato_spaghetti(void);
void cream_spaghetti(void);
void press_any_key(void); //아무키나 누르면 이전 메뉴로

int main(void) {
	int c;
	while((c=menu_display())!=3) {
		switch(c) {
			case 1 : sub_main01();
					break;
			case 2 : sub_main02();
					break;
			default : break;
		}
	}
	return 0;
}

int menu_display(void) {
	int select;
	system("cls");
	
	printf("간식 만들기\n\n");
	printf("1. 햄버거 \n");
	printf("2. 스파게티\n");
	printf("3. 프로그램 종료\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void sub_main01(void) {
	int c;
	while((c=sub_menu_display01())!= 3) {
		switch(c) {
			case 1 : chicken_burger();
					break;
			case 2 : cheese_burger();
					break;
			default : break;
		}
	}
}

int sub_menu_display01(void) {
	int select;
	system("cls");
	
	printf("햄버거 만들기\n\n");
	printf("1. 치킨버거\n");
	printf("2. 치즈버거\n");
	printf("3. 메인 메뉴로 이동\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void chicken_burger(void) {
	system("cls");
	printf("치킨버거 만드는 방법\n");
	printf("치킨을 먹고 햄버거를 먹는다.\n");
	press_any_key();
}

void cheese_burger(void) {
	system("cls");
	printf("치즈버거 만드는 방법\n");
	printf("치즈를 먹고 햄버거를 먹는다.\n");
	press_any_key();
}

void sub_main02(void) {
	int c;
	while((c=sub_menu_display02())!= 3) {
		switch(c) {
			case 1 : tomato_spaghetti();
					break;
			case 2 : cream_spaghetti();
					break;
			default : break;
		}
	}
}

int sub_menu_display02(void) {
	int select;
	system("cls");
	
	printf("스파게티 만들기\n\n");
	printf("1. 토마토 스파게티 \n");
	printf("2. 크림 스파게티 \n");
	printf("3. 메인 메뉴로 이동\n\n");
	printf("메뉴번호 입력>");
	select=getch()-48;
	
	return select;
}

void tomato_spaghetti(void) {
	system("cls");
	printf("토마토 스파게티 만드는 방법\n");
	printf("면이랑 토마토 소스랑 섞어 먹는다.\n");
	press_any_key();
}

void cream_spaghetti(void) {
	system("cls");
	printf("크림 스파게티 만드는 방법\n");
	printf("면이랑 우유랑 치즈랑 섞어 먹는다.\n리조또가 더 맛있다.\n");
	press_any_key();
}
void press_any_key(void) {
	printf("\n\n");
	printf("아무키나 누르면 이전 메뉴로...");
	getch();
}
```

## 7. 주사위 난수 생성

```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	int i;
	srand(time(NULL));
	for(i=1;i<=10;i++) printf("%2d:%d\n",i, rand()%6+1);
	
	return 0;
}
```
