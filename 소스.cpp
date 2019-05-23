#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

int mapx=23,mapy=11;
char test[13][25];
int map(int);
int stage=1; // stage number
int n = 8, m = 12;	//player location
int main() {
    start: // stage change
    map(stage);


	int n2=0, m2=0, n3=0, m3=0;		//2:forward of player	3: 2blocks forward of player
	char a;
	int tmp=0, tmp2=0;
	int move = 0;
	int cnt=0;	//clear condition

		while (1) {
		    printf("stage %d\n",stage);
			printf("move : %d\n", move);
			//printf("n %d m %d n2 %d m2 %d n3 %d m3 %d\n", n, m, n2, m2, n3, m3);

			for (int i = 0; i < mapy; i++) {
				for (int j = 0; j < mapx; j++) {
					switch (test[i][j]) {
					case 0:
						printf(".");
						break;
					case 1:
						printf("#");
						break;
					case 2:
						printf("$");
						cnt++;
						break;
					case 3:
						printf("@");
						break;
					case 4:
						printf("O");
						break;
					case 5:
						printf("X");
						break;
					}
				}
				printf("\n");
			}
			//printing map

			if (cnt == 0) {
				break;
			}

			a = _getch();
			switch (a) {
			case 'h':	//left
				n2 = n;
				m2 = m - 1;
				n3 = n;
				m3 = m - 2;
				break;

			case 75:	//left
				n2 = n;
				m2 = m - 1;
				n3 = n;
				m3 = m - 2;
				break;

			case 'l':	//right
				n2 = n;
				m2 = m + 1;
				n3 = n;
				m3 = m + 2;
				break;

			case 77:	//right
				n2 = n;
				m2 = m + 1;
				n3 = n;
				m3 = m + 2;
				break;

			case 'k':	//down
				n2 = n + 1;
				m2 = m;
				n3 = n + 2;
				m3 = m;
				break;

			case 80:	//down
				n2 = n + 1;
				m2 = m;
				n3 = n + 2;
				m3 = m;
				break;

			case 'j':	//up
				n2 = n - 1;
				m2 = m;
				n3 = n - 2;
				m3 = m;
				break;

			case 72:	//up
				n2 = n - 1;
				m2 = m;
				n3 = n - 2;
				m3 = m;
				break;
			}
			//move

			tmp = test[n2][m2];
			switch (tmp) {
			case 0:
				if (tmp2 == 0) {
					test[n2][m2] = 3;
					test[n][m] = 0;
				}
				else {
					test[n2][m2] = 3;
					test[n][m] = 4;
					tmp2 = 0;
				}
				n = n2;
				m = m2;
				move++;
				break;
			case 1:
				break;
			case 2:
				if (test[n3][m3] == 1 || test[n3][m3] == 2 || test[n3][m3] == 5) {
					break;
				}
				if (test[n3][m3] == 0) {
					if (tmp2 == 0) {
						test[n3][m3] = 2;
						test[n2][m2] = 3;
						test[n][m] = 0;
					}
					else {
						test[n3][m3] = 2;
						test[n2][m2] = 3;
						test[n][m] = 4;
						tmp2 = 0;
					}
				}
				if (test[n3][m3] == 4) {
					if (tmp2 == 0) {
						test[n3][m3] = 5;
						test[n2][m2] = 3;
						test[n][m] = 0;
					}
					else {
						test[n3][m3] = 5;
						test[n2][m2] = 3;
						test[n][m] = 4;
						tmp2 = 0;
					}
				}
				n = n2;
				m = m2;
				move++;
				break;
			case 4:
			    if (tmp2 == 0) {
				    test[n2][m2] = 3;
				    test[n][m] = 0;
				} else {
				    test[n2][m2] = 3;
				    test[n][m] = 4;
				}
				tmp2 = 1;
				n = n2;
				m = m2;
				move++;
				break;
			case 5:
				if (test[n3][m3] == 1 || test[n3][m3] == 2 || test[n3][m3] == 5) {
					break;
				}
				if (test[n3][m3] == 0) {
					if (tmp2 == 0) {
						test[n3][m3] = 2;
						test[n2][m2] = 3;
						test[n][m] = 0;
					}
					else {
						test[n3][m3] = 2;
						test[n2][m2] = 3;
						test[n][m] = 4;
					}
				}
				if (test[n3][m3] == 4) {
					if (tmp2 == 0) {
						test[n3][m3] = 5;
						test[n2][m2] = 3;
						test[n][m] = 0;
					}
					else {
						test[n3][m3] = 5;
						test[n2][m2] = 3;
						test[n][m] = 4;
					}
				}
				tmp2 = 1;
				n = n2;
				m = m2;
				move++;
			}
			system("cls");
			cnt = 0;
		}
    stage++;
    system("cls");
    for(int i=0;i<13;i++){
        for(int j=0; j<25; j++)
            test[i][j]=0;}// 스테이지 넘어갈 때 맵 초기화 
    if (stage==4)
        goto finish;
    goto start;
    finish:
	printf("clear!!!");
	return 0;
}

int map(int stage) // 맵 받는 함수 
{
    int mapx,mapy;
    char data;
    test[11][22];
    FILE *in;
    switch (stage){
        case 1:
        in = fopen("map1.TXT", "r");
        mapx=23,mapy=11;
        break;
        case 2:
        in = fopen("map2.TXT", "r");
        mapx=15,mapy=10;
        n=4;
        m=7;
        break;
        case 3:
        in = fopen("map3.TXT", "r");
        mapx=18,mapy=11;
        n=1,m=14;} //맵에 따른 x축 y축 크기 및 플레이어 위치  결 정 
    for(int i=0;i<mapy;i++)
        {for(int j=0;j<mapx;j++){
            fscanf(in, "%c", &data);
            switch(data){
            case 35:
                test[i][j]=1;
                break;
            case 36:
                test[i][j]=2;
                break;
            case 46:
                test[i][j]=0;
                break;
            case 64:
                test[i][j]=3;
                break;
            case 79:
                test[i][j]=4;
                break;
            case 88:
                test[i][j]=5;
                break;}
            }
        }
}
    
