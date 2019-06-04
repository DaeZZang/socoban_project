#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define MAX_COMMAND 10
#define MAX_RANK 100
#define STR_MAX 10
#define STAGE_NUM 5
#define MAX_LOG 1000

#define UNDO_INIT 5

#define TRUE 1
#define FALSE 0

//Print Location define

#define HELLO_PRINT_X 10
#define HELLO_PRINT_Y 2

#define STATUS_PRINT_X 0
#define STATUS_PRINT_Y (HELLO_PRINT_Y + 2)

#define MAP_PRINT_X 0
#define MAP_PRINT_Y (STATUS_PRINT_Y + 5)

#define PLAYER_PRINT_X (MAP_PRINT_X + 2 * playerX)
#define PLAYER_PRINT_Y (MAP_PRINT_Y + playerY)

#define COMMAND_PRINT_X 0
#define COMMAND_PRINT_Y (mapY + MAP_PRINT_Y + 1)

#define COMMAND_SCAN_X 10
#define COMMAND_SCAN_Y (mapY + MAP_PRINT_Y + 1)

#define DISHELP_PRINT_X 0
#define DISHELP_PRINT_Y (COMMAND_PRINT_Y + 2)

#define PROMPT_PRINT_X 0
#define PROMPT_PRINT_Y (COMMAND_PRINT_Y + 2)

#ifdef _WIN32
#include <conio.h>
#define getch() _getch()
#define getche() _getche()
#define gets(x) gets_s(x,sizeof(x))
#elif __unix__
#include <unistd.h>
#include <termio.h>
int getch(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}
int getche(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON);				 // CANONICAL 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}
#elif __linux__
#include <unistd.h>
#include <termio.h>
int getch(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}
int getche(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON);				 // CANONICAL 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}
#endif

void gotoxy(int x, int y)
{
	printf("\033[%dd\033[%dG", y, x + 1);
}
void clear(void)
{
#ifdef __unix__
	system("clear");
#elif __linux__
	printf("\033[H\033[J");
#elif _WIN32
	printf("\033[H\033[J");
#endif
}
void clearBuf(void)
{
#ifdef _WIN32
	rewind(stdin);
#elif __unix__
	fpurge(stdin);
#elif __linux__
	fpurge(stdin);
#endif
}

char name[STR_MAX];
int record[STAGE_NUM];

char logger[STAGE_NUM][MAX_LOG];

int stage;
int mapX, mapY;
int playerX, playerY;

char map[MAX][MAX];
char mapGoal[MAX][2];
int mapGoalCnt = 0;

int rankArr[MAX_RANK][STAGE_NUM + 1] = { 0 };
int rankCnt;
char nameArr[MAX_RANK][STR_MAX];

int remainUndo = UNDO_INIT;

void nameInput(void);
int mapMaker(int stage);
int checkBoxStorage(void);

void statPrint(void);
int printNewStage(int stage);
void refresh(int stage);

void goalPrinter(void);
void mapPrinter(void);
void playerFinder(void);
void goalFinder(void);

void moveplayer(int xplus, int yplus, int reload);
void movePlayerBox(int xplus, int yplus, int reload);
int move(int xplus, int yplus, int reload);
void loadMove(int repeat, int reload);

int success(int stage);

void inputRank(void);
void sort(int sortStage);
void swapRankArrAdd(int a, int b);


int main(void)
{
	FILE* save;
	FILE* rank;

	printf("Start. . . .\n");
	nameInput();
	clearBuf();
	
	for(stage = 1;stage <= STAGE_NUM;stage++)
	{
		if (!printNewStage(stage))	return 0;
		refresh(stage);

		char run = TRUE;
		char disHelp = FALSE;

		while (run)
		{
			int command;

			goalPrinter();
			gotoxy(COMMAND_SCAN_X, COMMAND_SCAN_Y);

			command = getche();
			clearBuf();

#ifdef _WIN32
			//Arrow Control
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
			if (command == 224)
			{
				command = getch();
				switch (command)
				{
				case KEY_UP:
					command = 'k';
					break;
				case KEY_LEFT:
					command = 'h';
					break;
				case KEY_RIGHT:
					command = 'l';
					break;
				case KEY_DOWN:
					command = 'j';
					break;
				}
			}
#endif

			int topNum = 0;

			char char_topNum[MAX_COMMAND] = { 0 };
			if (command == 't' || command == 'T')
			{
				//printf("%c", command);
				gets(char_topNum);
				topNum = atoi(char_topNum);

				gotoxy(COMMAND_SCAN_X, COMMAND_SCAN_Y);
				for (int i = 0; i < MAX_COMMAND; i++)	printf(" ");
			}
			
			switch (command)
			{
				//left
			case 'h':	case 'H':
				if (move(-1, 0, 0))	logger[stage - 1][record[stage - 1] - 1] = 'h';
				break;
					
				//down
			case 'j':	case 'J':
				if (move(0, 1, 0))	logger[stage - 1][record[stage - 1] - 1] = 'j';
				break;

				//up
			case 'k':	case 'K':
				if (move(0, -1, 0))	logger[stage - 1][record[stage - 1] - 1] = 'k';
				break;

				//right
			case 'l':	case 'L':
				if (move(1, 0, 0))	logger[stage - 1][record[stage - 1] - 1] = 'l';
				break;

			case 'u':	case 'U':	//undo
				if (remainUndo > 0 && record[stage - 1] > 0)
				{
					remainUndo--;
					if (!printNewStage(stage))	return 0;
					loadMove(record[stage - 1] - 1, 1);
				}
				else if(remainUndo <= 0)
				{
					refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
					printf("No more Undo Chance");
				}
				else if (record[stage - 1] <= 0)
				{
					refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
					printf("Nothing to Undo");
				}

				break;

			case 'r':	case 'R':	//replay 현재 맵을 다시시작 (움직임 횟수 유지)
				if (!printNewStage(stage))	return 0;
				break;

			case 'n':	case 'N':	//new 1번째 맵부터 다시시작 (움직임 횟수 삭제)
				for (int i = 0; i < STAGE_NUM; i++)	record[i] = 0;
				stage = 1;
				if (!printNewStage(stage))	return 0;
				break;

			case 'e':	case 'E':	//exit 게임 종료
			case 's':	case 'S':	//save 현재 상태 저장

				save = fopen("sokoban.txt", "w");

				//Line 1: name stage remainUndo
				//Line 2: Stage Records
				//Line 3~: Stage Logs

				fprintf(save, "%s %d %d\n", name, stage, remainUndo);
				for (int i = 0; i < STAGE_NUM;i++)	fprintf(save, "%d ", record[i]);
				for (int i = 0; i < STAGE_NUM; i++)
				{
					for (int j = 0; j < record[i]; j++)	fprintf(save, "%c", logger[i][j]);
					fprintf(save, "\n");
				}

				fclose(save);

				refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
				printf("Saved");

				if (command == 'e' || command == 'E')
				{
					gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y + 1);
					printf("SEE YOU %s. . . . \n", name);
					return 0;
				}
				break;

			case 'f':	case 'F':	//save파일 시점부터 게임진행

				save = fopen("sokoban.txt", "r");
				//Line 1: name stage remainUndo
				//Line 2: Stage Records
				//Line 3~: Stage Logs

				fscanf(save, "%s %d %d", name, &stage, &remainUndo);
				for (int i = 0; i < STAGE_NUM; i++)	fscanf(save, "%d", &record[i]);
				for (int i = 0; i < STAGE_NUM; i++)	fscanf(save, "%s", logger[i]);
				fclose(save);
					
				printNewStage(stage);
				loadMove(record[stage - 1], 1);

				break;

			case 'd':	case 'D':	//display help
				if (disHelp == FALSE)
				{
					disHelp = TRUE;
					refresh(stage);

					/*gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 0);	printf("%10s : 왼쪽", "h");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 1);	printf("%10s : 아래쪽", "j");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 2);	printf("%10s : 위쪽", "k");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 3);	printf("%10s : 오른쪽", "l");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 4);	printf("%10s : Undo (최대 5번)", "u");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 5);	printf("%10s : Replay 현재 맵을 처음부터 다시 시작 (움직임 횟수는 유지)", "r");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 6);	printf("%10s : New 첫번째 맵부터 다시 시작 (움직임 횟수 기록 삭제)", "n");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 7);	printf("%10s : Exit 저장 & 게임 종료", "e");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 8);	printf("%10s : Save 현재 상태 파일에 저장", "s");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 9);	printf("%10s : File Load 저장된 파일의 시점부터 다시 시작", "f");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 10);	printf("%10s : 명령 내용 보여줌", "d");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 11);	printf("%10s : 게임 순위 보여줌", "t");*/

					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 0);	printf("%10s : left", "h");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 1);	printf("%10s : down", "j");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 2);	printf("%10s : up", "k");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 3);	printf("%10s : right", "l");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 4);	printf("%10s : Undo", "u");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 5);	printf("%10s : Replay", "r");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 6);	printf("%10s : New", "n");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 7);	printf("%10s : Exit", "e");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 8);	printf("%10s : Save", "s");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 9);	printf("%10s : File Load", "f");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 10);	printf("%10s : Display Help", "d");
					gotoxy(DISHELP_PRINT_X, DISHELP_PRINT_Y + 11);	printf("%10s : Top Rank", "t");
				}
				else
				{
					disHelp = FALSE;
					refresh(stage);
				}
				break;

			case 't':	case 'T':	//top 게임 순위 보여줌
				//do something
				rankCnt = 0;
				rank = fopen("rank.txt", "r");
				if (rank == NULL)
				{
					refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
					printf("rank.txt not found");
				}
				int sum = 0;
				while (!feof(rank))
				{
					sum = 0;
					fscanf(rank, "%s", nameArr[rankCnt]);
					for (int i = 1; i <= STAGE_NUM; i++)
					{
						fscanf(rank, "%d", &rankArr[rankCnt][i]);
						sum += rankArr[rankCnt][i];
					}
					rankArr[rankCnt++][0] = sum;
					if (sum == 0)	rankCnt--;
				}

				if (0 <= topNum && topNum <= STAGE_NUM)
				{
					sort(topNum);
					refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
					for (int i = 0; i < rankCnt; i++)	printf("%3d %10s %5dpoint\n", i + 1, nameArr[i], rankArr[i][topNum]);
				}
				else
				{
					refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
					printf("STAGE unavailable");
				}

				break;

			default:
				refresh(stage);gotoxy(PROMPT_PRINT_X, PROMPT_PRINT_Y);
				printf("Command unavailable");
				break;
			}
			statPrint();

			if (success(stage))	run = FALSE;
		}
		clear();
	}
	inputRank();

	printf("SEE YOU %s. . . . \n", name);
	
	return 0;
}

void nameInput(void)
{
	printf("input name : ");
	scanf("%s", name);
	rewind(stdin);
}
int mapMaker(int stage)
{
	FILE* in = NULL;
	char tmpStr[STR_MAX] = { 0 };

	sprintf(tmpStr, "map%d.txt", stage);
	in = fopen(tmpStr, "r");

	if (in != NULL)
	{
		mapX = 0;
		mapY = 0;
		while (!feof(in))
		{
			fgets(map[mapY], MAX, in);
			if(map[mapY][strlen(map[mapY]) - 1] == '\n')	map[mapY][strlen(map[mapY]) - 1] = '\0';
			mapY++;
		}
		mapX = strlen(map[0]);
#ifdef __unix__
		mapX--;
#endif

		fclose(in);
		return 1;
	}
	else
	{
		printf("FILE LOAD FAIL! \nFILE NAME SHOuLD BE map""NUM"".txt\n");
		printf("TERMINATING PROGRAM\n");
		return 0;
	}
}

int checkBoxStorage(void)
{
	int cntBox = 0, cntStorage = 0;
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			if (map[i][j] == '$')	cntBox++;
			else if (map[i][j] == 'O')	cntStorage++;
		}
	}
	if (cntBox != cntStorage)	return 0;
	else return 1;
}
void statPrint(void)
{
	gotoxy(STATUS_PRINT_X, STATUS_PRINT_Y);
	printf("%7s: %4d", "STAGE", stage);
	gotoxy(STATUS_PRINT_X, STATUS_PRINT_Y + 1);
	printf("%7s: % 4d", "UNDO", remainUndo);
	gotoxy(STATUS_PRINT_X, STATUS_PRINT_Y + 2);
	printf("%7s: % 4d", "RECORD", record[stage - 1]);
}
int printNewStage(int stage)
{
	clear();
	if (!mapMaker(stage))	return 0;
	gotoxy(HELLO_PRINT_X, HELLO_PRINT_Y);
	printf("\tHello %s", name);
	statPrint();

	if (!checkBoxStorage())
	{
		printf("\n\nbox and goal num diff. Terminating Program\n");
		return 0;
	}

	playerFinder();
	goalFinder();
	mapPrinter();

	gotoxy(COMMAND_PRINT_X, COMMAND_PRINT_Y);
	printf("(Command) ");

	return 1;
}
void refresh(int stage)
{
	clear();
	gotoxy(HELLO_PRINT_X, HELLO_PRINT_Y);
	printf("\tHello %s", name);
	statPrint();

	mapPrinter();

	gotoxy(COMMAND_PRINT_X, COMMAND_PRINT_Y);
	printf("(Command) ");
}
void goalPrinter(void)
{
	for (int i = 0; i < mapGoalCnt; i++)
	{
		if (map[mapGoal[i][1]][mapGoal[i][0]] != '@' && map[mapGoal[i][1]][mapGoal[i][0]] != '$')
		{
			gotoxy(MAP_PRINT_X + 2 * mapGoal[i][0], MAP_PRINT_Y + mapGoal[i][1]);
			printf("O");
		}
	}
}
void mapPrinter(void)
{
	gotoxy(MAP_PRINT_X, MAP_PRINT_Y);

	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			if (map[i][j] == '.')	printf("  ");
			else printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	goalPrinter();
}
void playerFinder(void)
{
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			if (map[i][j] == '@')
			{
				playerY = i;
				playerX = j;
				return;
			}
		}
	}
}
void goalFinder(void)
{
	mapGoalCnt = 0;
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			if (map[j][i] == 'O')
			{
				mapGoal[mapGoalCnt][0] = i;
				mapGoal[mapGoalCnt][1] = j;
				mapGoalCnt++;
			}
		}
	}
}
void moveplayer(int xplus, int yplus, int reload)
{
	if (!reload)
	{
		gotoxy(PLAYER_PRINT_X, PLAYER_PRINT_Y);
		printf(" ");
	}
	
	map[playerY][playerX] = '.';
	playerX += xplus;
	playerY += yplus;

	if (!reload)
	{
		gotoxy(PLAYER_PRINT_X, PLAYER_PRINT_Y);
		printf("@");
	}

	map[playerY][playerX] = '@';

	record[stage - 1]++;
}
void movePlayerBox(int xplus, int yplus, int reload)
{
	if (!reload)
	{
		gotoxy(PLAYER_PRINT_X, PLAYER_PRINT_Y);
		printf(" ");
	}

	map[playerY][playerX] = '.';

	playerX += xplus;
	playerY += yplus;

	if (!reload)
	{
		gotoxy(PLAYER_PRINT_X, PLAYER_PRINT_Y);
		printf("@");
	}

	map[playerY][playerX] = '@';

	if (!reload)
	{
		gotoxy(PLAYER_PRINT_X + 2 * xplus, PLAYER_PRINT_Y + yplus);
		printf("$");
	}
	map[playerY + yplus][playerX + xplus] = '$';

	record[stage - 1]++;
}
int move(int xplus, int yplus, int reload)
{
	int bef_playerX = playerX, bef_playerY = playerY;

	if (playerX + xplus >= 0 && playerY + yplus >= 0 && playerX + xplus < mapX && playerY + yplus < mapY)
	{
		if (map[playerY + yplus][playerX + xplus] == '.')	moveplayer(xplus, yplus, reload);
		else if (map[playerY + yplus][playerX + xplus] == '$' && map[playerY + 2 * yplus][playerX + 2 * xplus] == '.'
			&& playerX + 2 * xplus >= 0 && playerY + 2 * yplus >= 0 && playerX + 2 * xplus < mapX && playerY + 2 * yplus < mapY)	movePlayerBox(xplus, yplus, reload);
		else if (map[playerY + yplus][playerX + xplus] == '$' && map[playerY + 2 * yplus][playerX + 2 * xplus] == 'O'
			&& playerX + 2 * xplus >= 0 && playerY + 2 * yplus >= 0 && playerX + 2 * xplus < mapX && playerY + 2 * yplus < mapY)	movePlayerBox(xplus, yplus, reload);
		else if (map[playerY + yplus][playerX + xplus] == 'O')	moveplayer(xplus, yplus, reload);
	}

	if (bef_playerX != playerX || bef_playerY != playerY)	return 1;
	else return 0;
}
void loadMove(int repeat, int reload)
{
	record[stage - 1] = 0;
	for (int i = 0; i < repeat; i++)
	{
		switch (logger[stage - 1][i])
		{
			//left
		case 'h':	case 'H':
			move(-1, 0, reload);
			break;

			//down
		case 'j':	case 'J':
			move(0, 1, reload);
			break;

			//up
		case 'k':	case 'K':
			move(0, -1, reload);
			break;

			//right
		case 'l':	case 'L':
			move(1, 0, reload);
			break;
		}
	}
	mapPrinter();
	goalPrinter();
}
int success(int stage)
{
	int cnt = 0;
	for (int i = 0; i < mapGoalCnt; i++)
	{
		if (map[mapGoal[i][1]][mapGoal[i][0]] == '$')	cnt++;
	}

	if (cnt == mapGoalCnt)	return 1;
	else return 0;
}
void inputRank(void)
{
	FILE* rank = fopen("rank.txt", "a");
	fprintf(rank, "%s ", name);

	for (int i = 0; i < STAGE_NUM; i++)	printf("%d ", record[i]);
	printf("\n");

	fclose(rank);
}
void sort(int sortStage)
{
	int maxAdd = 0;

	for (int i = 0; i < rankCnt; i++)
	{	
		maxAdd = i;
		for (int j = i; j < rankCnt; j++)
		{
			if (rankArr[maxAdd][sortStage] < rankArr[j][sortStage])	maxAdd = j;
		}
		swapRankArrAdd(i, maxAdd);
	}
}
void swapRankArrAdd(int a, int b)
{
	int temp[STAGE_NUM + 1];
	char tmpname[STR_MAX];
	
	for (int i = 0; i < STAGE_NUM + 1; i++)
	{
		temp[i] = rankArr[a][i];
		rankArr[a][i] = rankArr[b][i];
		rankArr[b][i] = temp[i];

		strcpy(tmpname, nameArr[a]);
		strcpy(nameArr[a], nameArr[b]);
		strcpy(nameArr[b], tmpname);
	}
}