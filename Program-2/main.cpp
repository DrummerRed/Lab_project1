#include "header.h"

int main(int argc, char* argv[])
{
    //setlocale(LC_ALL, "Rus");
    // setenv("LANG", "ru_RU.UTF-8", 1);
    // setenv("LC_CTYPE", "ru_RU.UTF-8", 1);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    Menu(argv);

    return 0;
}
