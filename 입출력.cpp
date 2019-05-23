#include <stdio.h>
int test[23][11];
int map(void);

int main(void){
    map();

for(int i=0;i<23;i++)
        {for(int j=0;j<11;j++)
            printf("%d",test[i][j]);
        }
        

return 0;


}

int map(void)
{
    char data;
    test[23][11];
    FILE *in;
    in = fopen("1.TXT", "r");
    for(int i=0;i<23;i++)
        {for(int j=0;j<11;j++){
            fscanf(in, "%c", &data);
            switch(data){
            case 35:
                test[i][j]=0;
                break;
            case 36:
                test[i][j]=2;
                break;
            case 46:
                test[i][j]=1;
                break;
            case 64:
                test[i][j]=4;
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
    
