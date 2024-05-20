#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    
    open("falafel", O_RDONLY);
    perror("open");
    return 0;
}