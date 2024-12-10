# GameProGramming

## 트럼프 카드 표시하기
![image](https://github.com/user-attachments/assets/85e86f96-9982-4625-86fe-973db5cfaaec)
```
struct trump {
    char order;	//카드의 우선순위 
    char shape[3];	//카드 모양(2 byte크기의 완성형 기호)
    char number;	//카드의 숫자(또는 문자)
};
```
![image](https://github.com/user-attachments/assets/51c8c3db-8f05-4071-8580-1c9b4d369c45)
```
void make_card(trump m_card[]) {
    int i, j;
    char shape[4][3] = {"♠","◆", "♥","♣"};

    for (i = 0; i < 4; i++) {

        for (j = i * 13; j < i * 13 + 13; j++) {
            m_card[j].order = i;   
            strcpy(m_card[j].shape, shape[i]);  
            m_card[j].number = j % 13 + 1;  

            switch (m_card[j].number) {
            case 1:
                m_card[j].number = 'A';
                break;
            case 11:
                m_card[j].number = 'J';
                break;
            case 12:
                m_card[j].number = 'Q';
                break;
            case 13:
                m_card[j].number = 'K';
                break;
            }
        }
    }
}
```
- 생성된 카드 출력 하기

![image](https://github.com/user-attachments/assets/11634219-cbed-4a9f-bbc3-76b134bb8478)

```
void display_card(trump m_card[]) {
    
    int i, count = 0;

    for (i = 0; i < 52; i++) {
        printf("%s", m_card[i].shape);

        if (10 < m_card[i].number)
        	printf("%-2c ", m_card[i].number);
        else
            printf("%-2d ", m_card[i].number);
        count++;

        if (i % 13 + 1 == 13) {
            printf("\n");
            count = 0;
        }
    }
}
```
```
#include <stdio.h>
#include <string.h>

struct trump {
    char order;
    char shape[3];
    char number;
};

typedef struct trump trump;

void make_card(trump m_card[]);
void display_card(trump m_card[]);

int main() {
    trump card[52];
    make_card(card);
    display_card(card);
    return 0;
}
```
- 카드 섞기(1)
![image](https://github.com/user-attachments/assets/71b1f8df-9ba6-4f92-9b97-5ca93470e160)

```
void shuffle_card(trump m_card[]){
	int rnd;
	trump temp;
	srand(time(NULL)); //난수의 초기화
	 
	for(int i=0; i<52; i++){
		rnd = rand()%52;
		temp = m_card[rnd];
		m_card[rnd] = m_card[i];
		m_card[i] = temp;
	}
}
```
- 카드 섞기(2)
![image](https://github.com/user-attachments/assets/d4776ff0-f9e5-4c0b-9c43-ee895e391c8a)
```
void shuffle_card(trump m_card[]){
	int rnd;
	trump temp;
	srand(time(NULL)); //난수의 초기화
	 
	for(int i=0; i<52; i++){
		
		do{
			rnd = rand()%52;
		}while(rnd==i);
		
		temp = m_card[rnd];
		m_card[rnd] = m_card[i];
		m_card[i] = temp;
	}
}
```
