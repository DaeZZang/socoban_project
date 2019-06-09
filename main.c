#include <stdio.h>
//#include <windows.h>
#include <stdlib.h>
#include <termio.h>
#include <string.h>
#include <unistd.h>

int mapx=23,mapy=11;
char test[13][25];
int stage=1; // stage number
int n = 0, m = 0;	//player location
char name[11] = {0};
//char utest[5][13][25];
//char unm[5][5];
int asdf=-1;
int ucnt=5;
//int undo(void);
char key_list[5] = {0};
int tmp2 = 0;
int undo_cnt = 5;
int map_record[10][25][25];
int move = 0;
int box_cnt = 0, storage_cnt = 0;
int move_stg1, move_stg2, move_stg3, move_stg4, move_stg5;



int map(int);
int getch(void);
int name_recieve(void);
void save(int);
int load();
//void saverank();
int show_ranking(int);
int ranking_save(void);
void map_check(void);
int rank_stg1(void);
int rank_stg2(void);
int rank_stg3(void);
int rank_stg4(void);
int rank_stg5(void);
void display_help(void);


int main() {
	

	name_recieve();
	start: // stage change
    map(stage);
	for(int x = 0; x <= 5; x++) {	
			for(int i = 0;i < mapy;i++) {
			        for(int j = 0;j < mapx;j++){
					map_record[x][i][j] = test[i][j];
					
					
				}
			}
		}

	int asd=0;
	int n2=0, m2=0, n3=0, m3=0;		//2:forward of player	3: 2blocks forward of player
	char a;
	int tmp=0;
	int cnt=0;	//clear condition
	int stopper;
	int tmp2_r[10] = {0};
		map_check();
		while (1) {
		nothing:
			system("clear");
			printf("Hello %s\n", name);
		   printf("stage %d\n",stage);
			printf("move : %d\n", move);
			//printf("n %d m %d n2 %d m2 %d n3 %d m3 %d\n", n, m, n2, m2, n3, m3);
			printf("undo available : %d\n", undo_cnt);

			for (int i = 0; i < mapy; i++) {
				for (int j = 0; j < mapx; j++) {
					switch (test[i][j]) {
					case 0:
						printf(" ");
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
						n = i;
						m = j;
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


			a = getch();
			switch (a) {
            case 'u'://undo ddddddddddd
		if (undo_cnt == 0) {
		    	goto nothing;
		} else {
		move++;
		tmp2 = tmp2_r[1];
		for(int b = 0; b < 5; b++) {
			tmp2_r[b] = tmp2_r[b+1];
		}

		for(int i = 0;i < mapy;i++) {
		        for(int j = 0;j < mapx;j++){
				test[i][j] = map_record[1][i][j];
			}
		}
		for(int x = 0; x <= 5; x++) {	
			for(int i = 0;i < mapy;i++) {
			        for(int j = 0;j < mapx;j++){
					map_record[x][i][j] = map_record[x+1][i][j];
					
					
				}
			}
		}
		undo_cnt--;
		goto nothing;
                	}
		break;
            case 'r'://çöàç¸ê´ù½ã½ãàû
                    map(stage);
                    n2=0, m2=0, n3=0, m3=0, tmp2 = 0;
		    for(int x = 0; x <= 5; x++) {	
			for(int i = 0;i < mapy;i++) {
			        for(int j = 0;j < mapx;j++){
					map_record[x][i][j] = test[i][j];
				}
			}
		    }

		    undo_cnt = 5;
                    continue;
                break;
            case 'n'://´ù½ã½ãàû
                    stage=1;
                    map(stage);
                    n2=0, m2=0, n3=0, m3=0, tmp2 = 0;
		    for(int x = 0; x <= 5; x++) {	
			for(int i = 0;i < mapy;i++) {
			        for(int j = 0;j < mapx;j++){
					map_record[x][i][j] = test[i][j];
				}
			}
		    }

		    undo_cnt = 5;
                    move=0;
                    continue;
                break;
            case 'e'://á¾·á ddddddddddd
                save(move);
		printf("System is shutting down...\n");
		sleep(1);
		printf("(3)...\n");
		sleep(1);
		printf("(2)...\n");
		sleep(1);
		printf("(1)...\n");
		sleep(1);
              //  saverank();
                return 0;
                break;
            case 's'://¼¼àìºê ddddddddddd
                save(move);
            //    saverank();
	    	continue;
                break;
            case 'f'://·îµå ddddddddddd
                load();
                n2=0, m2=0, n3=0, m3=0;
                asd=1;
		continue;
                break;
            case 'd'://¸í·é³»¿ë ddddddddddd
	    	display_help();
		stopper = getch();
		continue;
                break;
            case 't'://¼øà§ ddddddddddd
	    	//system("clear");
		//show_ranking(6);
		stopper = getchar();
                	if (stopper == '\n') {
				system("clear");
				show_ranking(6);
				stopper = getch();
			}
			if (stopper == '1') {
				stopper = getch();
				system("clear");
				show_ranking(1);
				stopper = getch();
			}
			if (stopper == '2') {
				stopper = getch();
				system("clear");
				show_ranking(2);
				stopper = getch();
			}
			if (stopper == '3') {
				stopper = getch();
				system("clear");
				show_ranking(3);
				stopper = getch();
			}
			if (stopper == '4') {
				stopper = getch();
				system("clear");
				show_ranking(4);
				stopper = getch();
			}
			if (stopper == '5') {
				stopper = getch();
				system("clear");
				show_ranking(5);
				stopper = getch();
			}
			continue;
			break;
			case 'h':	//left
				n2 = n;
				m2 = m - 1;
				n3 = n;
				m3 = m - 2;
				move++;
				break;



			case 'l':	//right
				n2 = n;
				m2 = m + 1;
				n3 = n;
				m3 = m + 2;
				move++;
				break;



			case 'j':	//down
				n2 = n + 1;
				m2 = m;
				n3 = n + 2;
				m3 = m;
				move++;
				break;



			case 'k':	//up
				n2 = n - 1;
				m2 = m;
				n3 = n - 2;
				m3 = m;
				move++;
				break;

			case '8':
				if (stage>1) {
					tmp2 = 0;
					stage--;
				}
				goto start;
				break;

			case '9' :
				if (stage<5) {
					tmp2 = 0;
					stage++;
				}
				goto start;
				break;
			

			default :
				goto nothing;
				break;
			}
			//move
            //if(asd==1){}else{
                    asd=0;
			//if (undo_cnt < 5) {
			//	undo_cnt++;
			//}
			for (int a = 5; a >= 0; a--) {
				tmp2_r[a] = tmp2_r[a-1];
			}
			tmp2_r[0] = tmp2; 
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

			//}
		}
		cnt = 0;
			
		for(int x = 5; x >= 0; x--) {	
			for(int i = 0;i < mapy;i++) {
			        for(int j = 0;j < mapx;j++){
					if (x == 0) {
						map_record[x][i][j] = test[i][j];
					} else {
						map_record[x][i][j] = map_record[x-1][i][j];
					}
					
				}
			}
		}
		}
	switch (stage) {
		case 1:
			move_stg1 = move;
			rank_stg1();
			break;
		case 2:
			move_stg2 = move - move_stg1;
			rank_stg2();
			break;
		case 3:
			move_stg3 = move - move_stg1 - move_stg2;
			rank_stg3();
			break;

		case 4:
			move_stg4 = move - move_stg1 - move_stg2 - move_stg3;
			rank_stg4();
			break;

		case 5:
			move_stg4 = move - move_stg1 - move_stg2 - move_stg3 - move_stg4;
			rank_stg5();
			break;
	}
    stage++;
    system("clear");
    for(int i=0;i<13;i++){
        for(int j=0; j<25; j++)
            test[i][j]=0;}// ½ºÅ×ÀÌÁö ³Ñ¾î°¥ ¶§ ¸Ê ÃÊ±âÈ­
    if (stage < 6)
        goto start;

	printf("clear! Congratulations!!!!!\n");
    	ranking_save();
	show_ranking(6);
	printf("Press any key\n");
	stopper = getch();
	return 0;
}



int map(int stage) 
{
    char data;
     FILE *in;
    switch (stage){
		case 1:
        	in = fopen("map1.TXT", "r");
			mapx=24,mapy=11;
			break;
			
     	case 2:
        	in = fopen("map2.TXT", "r");
        	mapx=16,mapy=10;
        	break;

      case 3:
        	in = fopen("map3.TXT", "r");
        	mapx=19,mapy=11;
        	break;

		case 4:

			in = fopen("map4.TXT", "r");
        		mapx=24,mapy=13;
        		break;

		case 5:

 			in = fopen("map5.TXT", "r");
        		mapx=19,mapy=13;
        		break;
	}
    for(int i = 0;i < mapy;i++) {
        for(int j = 0;j < mapx;j++){
            fscanf(in, "%c", &data);
            switch(data){
            case 35:
                test[i][j]=1;
                break;

            case 36:
                test[i][j]=2;
		box_cnt++;
                break;

            case 46:
                test[i][j]=0;
                break;

            case 64:
                test[i][j]=3;
				n = i;
				m = j;
                break;

            case 79:
                test[i][j]=4;
		storage_cnt++;
                break;

            case 88:
                test[i][j]=5;
		box_cnt++;
		storage_cnt++;
                break;
			}
		}
   }
}

void map_check(void) {
	if (box_cnt != storage_cnt) {
		system("clear");
		printf("Your map file is cracked. Please check your map file.\n");
		sleep(1);
		abort();
	}	
	return;
}
/*
void saverank(){
FILE *fp;
fp=fopen("ranking.txt","a");
fclose(fp);
fp=fopen("ranking.txt","r");
fscanf(fp,"%d %d");


}*/

int load(){
FILE *fp;
int mo;
fp = fopen("sokoban.txt","r");
int aa,bb;
fscanf(fp,"%d %d %d %d %d %s",&stage,&move,&m,&n, &undo_cnt, name);

    switch (stage){
		case 1:
			mapx=24,mapy=11;
			break;

     	case 2:
        	mapx=16,mapy=10;
        	break;

      case 3:
        	mapx=19,mapy=11;
        	break;

		case 4:
			mapx = 24, mapy = 13;
			break;

		case 5:
			mapx = 19, mapy = 13;
 			break;
	}

    for(int i = 0;i < mapy;i++) {
        for(int j = 0;j < mapx;j++){
            fscanf(fp,"%c ",&test[i][j]);
		}
   }

for(int x = 0; x < 10; x++) {
	for(int i = 0; i < mapy; i++) {
		for(int j = 0; j < mapx; j++) {
			fscanf(fp,"%c ", &map_record[x][i][j]);
		}
	}
}

   //m=aa;
   //n=bb;  
fclose(fp);

return 0;	
}

void save(int a){
FILE * fp;
fp = fopen("sokoban.txt","w");
fprintf(fp,"%d %d %d %d %d %s",stage, move,m,n, undo_cnt, name);

for(int i = 0;i < mapy;i++) {
        for(int j = 0;j < mapx;j++){
            fprintf(fp,"%c ",test[i][j]);
		}
		fprintf(fp," ");
   }

for(int x = 0; x < 10; x++) {
	for(int i = 0; i < mapy; i++) {
		for(int j = 0; j < mapx; j++) {
			fprintf(fp, "%c ", map_record[x][i][j]);
		}
		fprintf(fp, " ");
	}
}
fclose(fp);
}


int getch(void) {
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}


int name_recieve(void) {
	printf("Start...\n");
	printf("Input Your Name : ");
	scanf("%s", name);
	while (strlen(name) > 10) {
		printf("Set Your Name Within 10 Alphabets!\n");
		printf("Input Your Name : ");
		scanf("%s", name);
	}
	system("clear");
	return 0;
}



int ranking_save(void) {
	int r_score, line = 0, tmp = 0;
	char c, r_name[11];
	FILE *rank_f, *rank_n, *rank_l;
	rank_n = fopen("./ranking/ranking_n.txt", "w");
	rank_f = fopen("./ranking/ranking.txt", "r");
	rank_l = fopen("./ranking/ranking.txt", "r");

	while ((c = getc(rank_l)) != EOF) {
		if (c == '\n')
			line ++;
	}
	fclose(rank_l);

	for(int r = 1; r <= line; r++) {
		fscanf(rank_f, "%s %d", r_name, &r_score);
		if (r_score < move) {
			fprintf(rank_n, "%s %d\n", r_name, r_score);
			tmp = r_score;
		} else {
			if (tmp <= move && move < r_score) {
				fprintf(rank_n, "%s %d\n", name, move);
				fprintf(rank_n, "%s %d\n", r_name, r_score);
				tmp = r_score;
			} else {
				fprintf(rank_n, "%s %d\n", r_name, r_score);
				tmp = r_score;
			}
		}
		if (r == line && tmp < move) {
			fprintf(rank_n, "%s %d\n", name, move);
		}
	}
	if (tmp == 0) {
		fprintf(rank_n, "%s %d\n", name, move);
	}
	fclose(rank_f);
	fclose(rank_n);
	
	system("rm ./ranking/ranking.txt");
	system("mv ./ranking/ranking_n.txt ./ranking/ranking.txt");
	return 0;
}




int show_ranking(int n) {
	int rank_num = 5;
	char c;
	char r_name[11];
	int r_score; 
	char temp[10];
	int line = 0, count = 1;
	FILE *rank_f, *rank_ft;

	switch (n) {
		case 6:
			rank_f = fopen("./ranking/ranking.txt", "r");
			rank_ft = fopen("./ranking/ranking.txt", "r");
			printf("RANKING : total\n");
			while((c = getc(rank_ft)) != EOF) {
				if (c=='\n') {
					line++;
				}
			}
			if (line < 5)
				rank_num = line;
			for(int i = 0; i < rank_num; i++) {
				printf("%2d. ", count);
				fscanf(rank_f, "%s %d", r_name, &r_score);	
				printf("%-10s       ---------------- %10d\n", r_name, r_score);
				count++;
			}
			break;
		case 1 :
			rank_f = fopen("./ranking/ranking_stg1.txt", "r");
			rank_ft = fopen("./ranking/ranking_stg1.txt", "r");
			printf("RANKING : stage 1\n");
			while((c = getc(rank_ft)) != EOF) {
				if (c=='\n') {
					line++;
				}
			}
			if (line < 5)
				rank_num = line;

			for(int i = 0; i < rank_num; i++) {
				printf("%2d. ", count);
				fscanf(rank_f, "%s %d", r_name, &r_score);	
				printf("%-10s       ---------------- %10d\n", r_name, r_score);
				count++;
			}
			break;
		case 2:
			rank_f = fopen("./ranking/ranking_stg2.txt", "r");
			rank_ft = fopen("./ranking/ranking_stg2.txt", "r");
			printf("RANKING : stage 2\n");
			while((c = getc(rank_ft)) != EOF) {
				if (c=='\n') {
					line++;
				}
			}
			if (line < 5)
				rank_num = line;

			for(int i = 0; i < rank_num; i++) {
				printf("%2d. ", count);
				fscanf(rank_f, "%s %d", r_name, &r_score);	
				printf("%-10s       ---------------- %10d\n", r_name, r_score);
				count++;
			}
			break;
		case 3:
			rank_f = fopen("./ranking/ranking_stg3.txt", "r");
			rank_ft = fopen("./ranking/ranking_stg3.txt", "r");
			printf("RANKING : stage 3\n");
			while((c = getc(rank_ft)) != EOF) {
				if (c=='\n') {
					line++;
				}
			}
			if (line < 5)
				rank_num = line;

			for(int i = 0; i < rank_num; i++) {
				printf("%2d. ", count);
				fscanf(rank_f, "%s %d", r_name, &r_score);	
				printf("%-10s       ---------------- %10d\n", r_name, r_score);
				count++;
			}
			break;
		case 4:
			rank_f = fopen("./ranking/ranking_stg4.txt", "r");
			rank_ft = fopen("./ranking/ranking_stg4.txt", "r");
			printf("RANKING : stage 4\n");
			while((c = getc(rank_ft)) != EOF) {
				if (c=='\n') {
					line++;
				}
			}
			if (line < 5)
				rank_num = line;

			for(int i = 0; i < rank_num; i++) {
				printf("%2d. ", count);
				fscanf(rank_f, "%s %d", r_name, &r_score);	
				printf("%-10s       ---------------- %10d\n", r_name, r_score);
				count++;
			}
			break;
		case 5:
			rank_f = fopen("./ranking/ranking_stg5.txt", "r");
			rank_ft = fopen("./ranking/ranking_stg5.txt", "r");
			printf("RANKING : stage 5\n");
			while((c = getc(rank_ft)) != EOF) {
				if (c=='\n') {
					line++;
				}
			}
			if (line < 5)
				rank_num = line;

			for(int i = 0; i < rank_num; i++) {
				printf("%2d. ", count);
				fscanf(rank_f, "%s %d", r_name, &r_score);	
				printf("%-10s       ---------------- %10d\n", r_name, r_score);
				count++;
			}
			break;
	}


	

	fclose(rank_f);
	return 0;
}


int rank_stg1(void) {
	int r_score, line = 0, tmp = 0;
	char c, r_name[11];
	FILE *rank_f1, *rank_n1, *rank_l1;
	rank_n1 = fopen("./ranking/ranking_stg1_n.txt", "w");
	rank_f1 = fopen("./ranking/ranking_stg1.txt", "r");
	rank_l1 = fopen("./ranking/ranking_stg1.txt", "r");

	while ((c = getc(rank_l1)) != EOF) {
		if (c == '\n')
			line ++;
	}
	fclose(rank_l1);

	for(int r = 1; r <= line; r++) {
		fscanf(rank_f1, "%s %d", r_name, &r_score);
		if (r_score < move_stg1) {
			fprintf(rank_n1, "%s %d\n", r_name, r_score);
			tmp = r_score;
		} else {
			if (tmp <= move_stg1 && move_stg1 < r_score) {
				fprintf(rank_n1, "%s %d\n", name, move_stg1);
				fprintf(rank_n1, "%s %d\n", r_name, r_score);
				tmp = r_score;
			} else {
				fprintf(rank_n1, "%s %d\n", r_name, r_score);
				tmp = r_score;
			}
		}
		if (r == line && tmp < move_stg1) {
			fprintf(rank_n1, "%s %d\n", name, move_stg1);
		}
	}
	if (tmp == 0) {
		fprintf(rank_n1, "%s %d\n", name, move_stg1);
	}
	fclose(rank_f1);
	fclose(rank_n1);
	
	system("rm ./ranking/ranking_stg1.txt");
	system("mv ./ranking/ranking_stg1_n.txt ./ranking/ranking_stg1.txt");
	return 0;
}



int rank_stg2(void) {
	int r_score, line = 0, tmp = 0;
	char c, r_name[11];
	FILE *rank_f2, *rank_n2, *rank_l2;
	rank_n2 = fopen("./ranking/ranking_stg2_n.txt", "w");
	rank_f2 = fopen("./ranking/ranking_stg2.txt", "r");
	rank_l2 = fopen("./ranking/ranking_stg2.txt", "r");

	while ((c = getc(rank_l2)) != EOF) {
		if (c == '\n')
			line ++;
	}
	fclose(rank_l2);

	for(int r = 1; r <= line; r++) {
		fscanf(rank_f2, "%s %d", r_name, &r_score);
		if (r_score < move_stg2) {
			fprintf(rank_n2, "%s %d\n", r_name, r_score);
			tmp = r_score;
		} else {
			if (tmp <= move_stg2 && move_stg2 < r_score) {
				fprintf(rank_n2, "%s %d\n", name, move_stg2);
				fprintf(rank_n2, "%s %d\n", r_name, r_score);
				tmp = r_score;
			} else {
				fprintf(rank_n2, "%s %d\n", r_name, r_score);
				tmp = r_score;
			}
		}
		if (r == line && tmp < move_stg2) {
			fprintf(rank_n2, "%s %d\n", name, move_stg2);
		}
	}
	if (tmp == 0) {
		fprintf(rank_n2, "%s %d\n", name, move_stg2);
	}
	fclose(rank_f2);
	fclose(rank_n2);
	
	system("rm ./ranking/ranking_stg2.txt");
	system("mv ./ranking/ranking_stg2_n.txt ./ranking/ranking_stg2.txt");
	return 0;
}



int rank_stg3(void) {
	int r_score, line = 0, tmp = 0;
	char c, r_name[11];
	FILE *rank_f3, *rank_n3, *rank_l3;
	rank_n3 = fopen("./ranking/ranking_stg3_n.txt", "w");
	rank_f3 = fopen("./ranking/ranking_stg3.txt", "r");
	rank_l3 = fopen("./ranking/ranking_stg3.txt", "r");

	while ((c = getc(rank_l3)) != EOF) {
		if (c == '\n')
			line ++;
	}
	fclose(rank_l3);

	for(int r = 1; r <= line; r++) {
		fscanf(rank_f3, "%s %d", r_name, &r_score);
		if (r_score < move_stg3) {
			fprintf(rank_n3, "%s %d\n", r_name, r_score);
			tmp = r_score;
		} else {
			if (tmp <= move_stg3 && move_stg3 < r_score) {
				fprintf(rank_n3, "%s %d\n", name, move_stg3);
				fprintf(rank_n3, "%s %d\n", r_name, r_score);
				tmp = r_score;
			} else {
				fprintf(rank_n3, "%s %d\n", r_name, r_score);
				tmp = r_score;
			}
		}
		if (r == line && tmp < move_stg3) {
			fprintf(rank_n3, "%s %d\n", name, move_stg3);
		}
	}
	if (tmp == 0) {
		fprintf(rank_n3, "%s %d\n", name, move_stg3);
	}
	fclose(rank_f3);
	fclose(rank_n3);
	
	system("rm ./ranking/ranking_stg3.txt");
	system("mv ./ranking/ranking_stg3_n.txt ./ranking/ranking_stg3.txt");
	return 0;
}



int rank_stg4(void) {
	int r_score, line = 0, tmp = 0;
	char c, r_name[11];
	FILE *rank_f4, *rank_n4, *rank_l4;
	rank_n4 = fopen("./ranking/ranking_stg4_n.txt", "w");
	rank_f4 = fopen("./ranking/ranking_stg4.txt", "r");
	rank_l4 = fopen("./ranking/ranking_stg4.txt", "r");

	while ((c = getc(rank_l4)) != EOF) {
		if (c == '\n')
			line ++;
	}
	fclose(rank_l4);

	for(int r = 1; r <= line; r++) {
		fscanf(rank_f4, "%s %d", r_name, &r_score);
		if (r_score < move_stg4) {
			fprintf(rank_n4, "%s %d\n", r_name, r_score);
			tmp = r_score;
		} else {
			if (tmp <= move_stg4 && move_stg4 < r_score) {
				fprintf(rank_n4, "%s %d\n", name, move_stg4);
				fprintf(rank_n4, "%s %d\n", r_name, r_score);
				tmp = r_score;
			} else {
				fprintf(rank_n4, "%s %d\n", r_name, r_score);
				tmp = r_score;
			}
		}
		if (r == line && tmp < move_stg4) {
			fprintf(rank_n4, "%s %d\n", name, move_stg4);
		}
	}
	if (tmp == 0) {
		fprintf(rank_n4, "%s %d\n", name, move_stg4);
	}
	fclose(rank_f4);
	fclose(rank_n4);
	
	system("rm ./ranking/ranking_stg4.txt");
	system("mv ./ranking/ranking_stg4_n.txt ./ranking/ranking_stg4.txt");
	return 0;
}



int rank_stg5(void) {
	int r_score, line = 0, tmp = 0;
	char c, r_name[11];
	FILE *rank_f5, *rank_n5, *rank_l5;
	rank_n5 = fopen("./ranking/ranking_stg5_n.txt", "w");
	rank_f5 = fopen("./ranking/ranking_stg5.txt", "r");
	rank_l5 = fopen("./ranking/ranking_stg5.txt", "r");

	while ((c = getc(rank_l5)) != EOF) {
		if (c == '\n')
			line ++;
	}
	fclose(rank_l5);

	for(int r = 1; r <= line; r++) {
		fscanf(rank_f5, "%s %d", r_name, &r_score);
		if (r_score < move_stg5) {
			fprintf(rank_n5, "%s %d\n", r_name, r_score);
			tmp = r_score;
		} else {
			if (tmp <= move_stg5 && move_stg5 < r_score) {
				fprintf(rank_n5, "%s %d\n", name, move_stg5);
				fprintf(rank_n5, "%s %d\n", r_name, r_score);
				tmp = r_score;
			} else {
				fprintf(rank_n5, "%s %d\n", r_name, r_score);
				tmp = r_score;
			}
		}
		if (r == line && tmp < move_stg5) {
			fprintf(rank_n5, "%s %d\n", name, move_stg5);
		}
	}
	if (tmp == 0) {
		fprintf(rank_n5, "%s %d\n", name, move_stg5);
	}
	fclose(rank_f5);
	fclose(rank_n5);
	
	system("rm ./ranking/ranking_stg5.txt");
	system("mv ./ranking/ranking_stg5_n.txt ./ranking/ranking_stg5.txt");
	return 0;
}

void display_help(void) {
	system("clear");
	printf("<Manual>\nh : left, j : down, k : up, l : right\nu : undo\nr : replay\nn : new\ne : exit\ns : save\nf : file load\nd : display help\nt : top\n\n\n");
	return;
}
