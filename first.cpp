#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define nn 7


int main() {
	char test[nn][nn]{ 1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,2,0,1,1,0,0,3,4,0,1,1,0,0,5,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1 };	//0:space, 1:wall, 2:box, 3:player, 4:storage, 5:full storage

	int n = 3, m = 3;	//player location
	int n2=0, m2=0, n3=0, m3=0;		//2:forward of player	3: 2blocks forward of player
	char a;
	int tmp=0, tmp2=0;
	int move = 0;
	int cnt=0;	//clear condition

		while (1) {
			printf("move : %d\n", move);
			//printf("n %d m %d n2 %d m2 %d n3 %d m3 %d\n", n, m, n2, m2, n3, m3);

			for (int i = 0; i < nn; i++) {
				for (int j = 0; j < nn; j++) {
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
				tmp2 = 1;
				test[n2][m2] = 3;
				test[n][m] = 0;
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

	printf("clear!!!");
	return 0;
}