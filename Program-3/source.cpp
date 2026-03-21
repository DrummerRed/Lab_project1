#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const int FIELDS = 5;               // Количество полей

struct columns
{
    string column_name;
    string* ptr;
};

void Menu(char* argv[])         // Главное меню программы
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);            // выключение курсора

    // bool files_ECM_exist = false;           // Переменная для проверки существования 1-го считываемого файла
    // bool file_ECM_CONF_exist = false;       // Переменная для проверки существования 2-го считываемого файла
    
    int switcher = 1;
    while(true)
    {    
        // file_checker(&files_ECM_exist, &file_ECM_CONF_exist);
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
                // files_info(&files_ECM_exist, &file_ECM_CONF_exist, argv);
            }
            if (switcher == 3)
            {
                // Menu_for_viewing(&files_ECM_exist, &file_ECM_CONF_exist);
                Menu_for_sorting();
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

void interface(int choice)      // Отрисовка интерфейса главного меню программы
{
    switch(choice)
    {
        case 1:
        printw(" \t\t<< Помощь >>\n \t\tПроверка файлов\n \t\tНачать сортировку\n \t\tВыход");
        break;
        case 2:
        printw(" \t\tПомощь\n \t\t<< Проверка файлов >>\n \t\tНачать сортировку\n \t\tВыход");
        break;
        case 3:
        printw(" \t\tПомощь\n \t\tПроверка файлов\n \t\t<< Начать сортировку >>\n \t\tВыход");
        break;
        case 4:
        printw(" \t\tПомощь\n \t\tПроверка файлов\n \t\tНачать сортировку\n \t\t<< Выход >>");
        break;
    }
}

void Help()             // Функция работы пункта меню "Помощь"
{
    def_prog_mode();   // Сохраняем режим ncurses
    endwin();          // Временно выключаем ncurses
    system("clear");
    char str;
    string duplicate_str = "";
    FILE * file = fopen(HELP.c_str(), "r");

    if (file == NULL)
    {
        printf("Ошибка 47: Не удалось считать файл инструкций!\n");
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

void Menu_for_sorting()
{
    endwin();           // удалить
    // Меню фильтров

    // парсинг файла
    columns* array = new columns[FIELDS];
    int flag = file_parser(array, FIELDS, "Отчет_05.03.2026_19-14-19.txt");
    cout << flag << endl;
    debug_print(array, FIELDS);

    ///////////
    exit(0);             // удалить
}

int file_parser(columns* array, int SIZE, string file_name)         // Возвращает 1, если парсинг файла удался
{                                                                   // -1 если вознкикла ошибка чтения файла
    int count = string_counter(file_name);                          // Иначе 0
    if (count == -1)
        return -1;
    else
        for (int i=0; i<SIZE; i++)
            array[i].ptr = new string[count];       // Инициализируем динамические массивы

    ifstream file;
    file.open(file_name);
    if (!file.is_open())
        return 0;
    else
    {
        string str;
        for (int j=0; getline(file, str); j++)
        {   
            for (int i=0; i<SIZE; i++)
            {
                int pos = str.find("  ");
                if ((pos != -1) && (i != SIZE-1))
                {
                    string newstr ="";
                    string str2 = str;          // Дубликат
                    newstr = str.erase(pos, str.length()-pos);
                    str = str2.erase(0, pos);    
                    str = del_space(str);       // Очистка строки от передних пробелов
                    if (j == 0)
                        array[i].column_name = newstr;
                    else
                        array[i].ptr[j-1] = newstr;

                    // cout << newstr << "|" << endl;              // Отладочный принт
                }
                else if (i == SIZE-1)
                {   
                    str = inverse_del_space(str);
                    if (j == 0)
                        array[i].column_name = str;
                    else
                        array[i].ptr[j-1] = str;

                    // cout << str << "|" << endl;                 // Отладочный принт
                    // cout << "Строка окончена" << endl;          // Отладочный принт
                }
                else
                {
                    cout << "Ошибка";
                    break;
                }
            }
        }
    }
        
    file.close();
    return 1;
}

int string_counter(string file_name)        // Функция подсчета строк в файле
{                                           // Возвращает -1 при ошибке считывания файла
    int count = 0;
    string buf;

    ifstream file;
    file.open(file_name);
    if (!file.is_open())
        return -1;

    while(getline(file, buf))
        count ++;

    file.close();
    return count;
}

string del_space(string str)      // Функция очистки строки от ненужных пробелов
{
    bool flag = true;
    while (flag)
    {
        if (str[0] == ' ')
            str.erase(0, 1);

        else
            flag = false;
    }
    return str;
}

string inverse_del_space(string str)      // Функция очистки строки от ненужных пробелов и \n
{
    bool flag = true;
    int len = str.length();
    if (str[len-1] == '\n')
            str.erase(len-1, 1);

    while (flag)
    {
        len = str.length();
        if (str[len-1] == ' ')
            str.erase(len-1, 1);

        else
            flag = false;
    }
    return str;
}

void debug_print(columns* array, int SIZE)
{
    int count = 10;
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<count; j++)
        {
            cout << array[i].ptr[j] << endl;
        }
        cout << endl;
    }
}