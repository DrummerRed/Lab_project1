#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const string ECM = "ECM.csv";   // Название первого файла
const string ECM_CONF = "ECM_configuration.csv";    // Название второго файла
const int SIZE = 20;

void Menu()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0); // выключение курсора

    int switcher = 1;
    while(true)
    {    
        clear();
        interface(switcher);
        refresh();
        int ch = getch();
        if (ch == 258)
        {
            if (switcher != 4)
                switcher += 1;
            else
                switcher = 1;
        }
        if (ch == 259)
        {
            if (switcher != 1)
                switcher -= 1;
            else
                switcher = 4;
        }
        if (ch == 10)
        {
            if (switcher == 1)
            {
                Help();
            }
            if (switcher == 2)
            {
                //files_info();
            }
            if (switcher == 3)
            {
                //Menu_for_record();
            }
            if (switcher == 4)
            {
                endwin();
                system("clear");
                exit(0);
            }
        }
    }
    endwin();
}

void interface(int choice)
{
    switch(choice)
    {
        case 1:
        printw(" \t\t<< Помощь >>\n \t\tПроверка файлов\n \t\tПросмотр записей\n \t\tВыход");
        break;
        case 2:
        printw(" \t\tПомощь\n \t\t<< Проверка файлов >>\n \t\tПросмотр записей\n \t\tВыход");
        break;
        case 3:
        printw(" \t\tПомощь\n \t\tПроверка файлов\n \t\t<< Просмотр записей >>\n \t\tВыход");
        break;
        case 4:
        printw(" \t\tПомощь\n \t\tПроверка файлов\n \t\tПросмотр записей\n \t\t<< Выход >>");
        break;
    }
}

void Help()
{
    def_prog_mode();   // Сохраняем режим ncurses
    endwin();          // Временно выключаем ncurses
    system("clear");
    char str;
    string duplicate_str = "";
    FILE * file = fopen(HELP.c_str(), "r");

    if (file == NULL)
    {
        printf("Ошибка чтения файла!\n");
        exit(0);
    }
    int symb;
    while ((symb = fgetc(file)) != EOF) 
    {
        str = (char)symb;
        duplicate_str += str;
    }
    fclose(file);
    int ch = 0;
    reset_prog_mode(); // Восстанавливаем режим
    clear();
    printw("%s", duplicate_str.c_str());
    refresh();
    while((int)ch != 27)
    {
        ch = getch();
    }
}