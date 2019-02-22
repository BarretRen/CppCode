#include "../include/apue.h"
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd* getpwnam(const char* name)
{
    struct passwd* ptr;
    setpwent();
    while ((ptr = getpwent()) != NULL)
    {
        if (strcmp(name, ptr->pw_name) == 0)
            break;
    }
    endpwent();
    return ptr;
}

int main()
{
    printf("user barretr id is: %d\n", getpwnam("barretr")->pw_uid);

    return 0;
}
