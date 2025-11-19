#include "header.h"

int main()
{
    //setlocale(LC_ALL, "Rus");
    setenv("LANG", "ru_RU.UTF-8", 1);
    setenv("LC_CTYPE", "ru_RU.UTF-8", 1);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    file_creater();
    Menu();

    //system("clear");
    return 0;
}
