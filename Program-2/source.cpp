#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const string ECM = "ECM.csv";   // Название первого файла
const string ECM_CONF = "ECM_configuration.csv";    // Название второго файла
const int SIZE = 20;

void Menu(char* argv[])
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0); // выключение курсора

    bool files_ECM_exist = false;           // Переменная для проверки существования 1-го считываемого файла
    bool file_ECM_CONF_exist = false;   // Переменная для проверки существования 2-го считываемого файла
    file_checker(&files_ECM_exist, &file_ECM_CONF_exist);
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
                files_info(&files_ECM_exist, &file_ECM_CONF_exist, argv);
            }
            if (switcher == 3)
            {
                //Menu_for_record();
            }
            if (switcher == 4)
            {
                endwin();
                //system("clear");
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
    reset_prog_mode(); // Восстанавливаем режим
    clear();
    printw("%s", duplicate_str.c_str());
    refresh();
    int ch = 0;
    while((int)ch != 27)
    {
        ch = getch();
    }
}

void file_checker(bool* file_ECM_exist, bool* file_ECM_CONF_exist)       // Функция проверки файлов
{
    FILE * file_ECM = fopen(ECM.c_str(), "r");
    if (file_ECM == NULL)
        *file_ECM_exist = false;
    else
    {
        *file_ECM_exist = true;
        fclose(file_ECM);
    }

    FILE * file_ECM_CONF = fopen(ECM_CONF.c_str(), "r");
    if (file_ECM_CONF == NULL)
        *file_ECM_CONF_exist = false;
    else
    {
        *file_ECM_CONF_exist = true;
        fclose(file_ECM_CONF);
    }
}

void files_info(bool* files_ECM_exist, bool* file_ECM_CONF_exist, char* argv[])
{
    clear();
    printw("Информация о файлах\n======================================\n\n");
    char absolute_path[PATH_MAX];
    bool error_flag = false;
    string dir_name = "";
    if (realpath(argv[0], absolute_path))
        {
            try
            {
                string str = argv[0];
                str.erase(0, 1);
                dir_name = absolute_path;
                dir_name.erase(dir_name.find(str), (str.length()));
            }
            catch(const exception& ex)
            {
                error_flag = true;  // Отлавливаем исключение
            }
        }
        else 
            error_flag = true;      //Ошибка чтения названия скомпелированного файла

    if ((*files_ECM_exist == false) && (*file_ECM_CONF_exist == false))
    {
        if (error_flag)
        {
            printw("Внимание! Файлы с информацией отсутствуют!\n");
            printw("Добавьте требуемые файлы (%s, %s) в папку с программой\n", ECM.c_str(), ECM_CONF.c_str());
        } 
        else
        {       
            printw("Внимание! Файлы с информацией отсутствуют!\n");
            printw("Добавьте требуемые файлы (%s, %s) в директорию:\n%s\n\n", ECM.c_str(), ECM_CONF.c_str(), dir_name.c_str());
            printw("После добавления перезапустите программу.");
        }
    }
    else if ((*files_ECM_exist == false) && (*file_ECM_CONF_exist == true))
    {
        if (error_flag)
            printw("Внимание! Файл ЭВМ (%s) отсутствует!\nДобавьте требуемый файл в папку с программой", ECM.c_str());
        else
        {       
            printw("Внимание! Файл ЭВМ (%s) отсутствует!\n", ECM.c_str());
            printw("Добавьте требуемый файл в директорию:\n%s\n\n", dir_name.c_str());
            printw("После добавления перезапустите программу.");
        }
    }
    else if ((*files_ECM_exist == true) && (*file_ECM_CONF_exist == false))
    {
        if (error_flag)
            printw("Внимание! Файл конфигураций (%s) отсутствует!\nДобавьте требуемый файл в папку с программой", ECM_CONF.c_str());
        else
        {       
            printw("Внимание! Файл конфигураций (%s) отсутствует!\n", ECM_CONF.c_str());
            printw("Добавьте требуемый файл в директорию:\n%s\n\n", dir_name.c_str());
            printw("После добавления перезапустите программу.");
        }
    }
    else
        files_is_found();

    int ch = 0;
    while((int)ch != 27)
    {
        ch = getch();
    }
}

void files_is_found()
{
    printw("Все рабочие файлы были успешно загружены.\n\n");
    char absolute_path[PATH_MAX];
    if (realpath(ECM.c_str(), absolute_path))
        {
        printw("%s\n", ECM.c_str());
        printw("Описание:\t\tФайл ЭВМ. Хранит информацию о марке ЭВМ, заводском номере и номере кафедры.\n");
        printw("Путь до файла:\t\t");
        printw("%s\n\n", absolute_path);
        }
    else
        printw("Ошибка чтения файла %s !\n\n", ECM.c_str());

    if (realpath(ECM_CONF.c_str(), absolute_path))
        {
        printw("%s\n", ECM_CONF.c_str());
        printw("Описание:\t\tФайл конфигураций. Хранит информацию о марке ЭВМ, количестве терминалов и количестве внешних запоминающих устройств.\n");
        printw("Путь до файла:\t\t");
        printw("%s\n", absolute_path);
        }
    else
        printw("Ошибка чтения файла %s !\n", ECM_CONF.c_str());
}