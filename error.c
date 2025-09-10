#include "philosophers.h"

void	err_manager(char *message, int code)
{
    printf("%s\n", message);
    exit(code);
}
