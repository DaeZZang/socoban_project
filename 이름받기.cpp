#include <stdio.h>
#include <string.h>
int main(void)
{
    char name[1];
    printf("Start...\n");
    printf("Input Your Name : ");
    scanf("%s",&name);
    while(strlen(name)>10)
       { printf("10�� �̳��� �Է��ϼ���\n") ;
        printf("Input Your Name : ");
        scanf("%s",&name);}
    printf("Hello %s\n",name);

    return 0;
}
    
