#include <stdio.h>

int main(void)
{
    char str[]="#include <stdio.h>%c%cint main(void)%c{%c%cchar str[]=%c%s%c;%c%cprintf(str,10,10,10,10,9,34,str,34,10,9,10,9,10);%c%creturn 0;%c}";
    printf(str,10,10,10,10,9,34,str,34,10,9,10,9,10);
    return 0;
}