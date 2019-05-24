#include <stdio.h>
#include <string.h>
int main(void)
{
    char name[1];
    printf("Start...\n");
    printf("Input Your Name : ");
    scanf("%s",&name);
    while(strlen(name)>10)
       { printf("10자 이내로 입력하세요\n") ;
        printf("Input Your Name : ");
        scanf("%s",&name);}
    printf("Hello %s\n",name);

    return 0;
}
    
