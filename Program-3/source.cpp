#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const int FIELDS = 5;               // Количество полей

struct columns
{
    string column_name;
    string* ptr = nullptr;
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
            if (switcher != 3)
                switcher += 1;
            else
                switcher = 1;
        }
        if (ch == 259)
        {
            if (switcher != 1)
                switcher -= 1;
            else
                switcher = 3;
        }
        if (ch == 10)
        {
            if (switcher == 1)
            {
                Help();
            }
            if (switcher == 2)
            {
                Menu_for_sorting();
                // choose_file_interface();
            }
            if (switcher == 3)
            {
                endwin();
                //system("clear");///////////////////ВЕРНУТЬ
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
        printw(" \t\t<< Помощь >>\n \t\tНачать сортировку\n \t\tВыход");
        break;
        case 2:
        printw(" \t\tПомощь\n \t\t<< Начать сортировку >>\n \t\tВыход");
        break;
        case 3:
        printw(" \t\tПомощь\n \t\tНачать сортировку\n \t\t<< Выход >>");
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

void choose_file_interface()
{
    clear();
    printw("Для возврата в меню нажмите Esc\n");
    printw("-------------------------------\n\n");
    printw("Введите название файла: ");
    refresh();
    noecho();
    curs_set(1);            // включение курсора
    
    // wchar_t ch;
    int i=0;
    wint_t ch;
    wchar_t filename[256];
    string str = "";

    // Запоминаем позицию ввода
    int y, x;
    getyx(stdscr, y, x);

    while(true)
    {
        ch = getch();
        // get_wch(&ch);     НЕИСПОЛЬЗУЕМ
        if (ch == 27)
            break;

        if (ch == KEY_BACKSPACE || ch == 127) { // Backspace
            // пока без backspace
            continue;
            if (!str.empty()) {
                str.erase(str.length()-1);
                // if (ch_pred in eng)
                //     str.erase(str.length()-1);
                
                // if (ch_pred in rus)
                //   str.erase(str.length()-1);
                // Удаляем последний символ с экрана
                move(y, x + str.length());
                delch();
                delch();
                refresh();
            }
        }
        else
        {    addch(ch);
            str += char(ch);}
    }
    endwin();
    cout << str;
    curs_set(0);            // выключение курсора
    exit(0);
}

void Menu_for_sorting()
{
    // string names[FIELDS];       // Инициализируем массив названий полей      ПОКА ОТКАЖЕМСЯ
    // Меню фильтров


    // парсинг файла
    columns* array = new columns[FIELDS];
    int flag = file_parser(array, FIELDS, "Отчет_05.03.2026_19-14-19.txt");         // Считывание полей файла
    if (flag == -1)
    {
        printw("Ошибка чтения файла!");
        return;
    }
    // debug_print(array, FIELDS);

    int field = choose_field(array, FIELDS);                // Выбор поля для сортировки
    if (field == -1)
        return;

    int type = type_sort();             // выбор типа сортировки (убывание/возрастание)
    if (type == -1)
        return;

    regroup_array(field, array, FIELDS);

    debug_print(array, FIELDS);
    int len = string_counter("Отчет_05.03.2026_19-14-19.txt")-1;
    quicksort(array->ptr, 0, len-1);
    debug_print(array, FIELDS);
    cout << endl << len;
}

int file_parser(columns* array, int SIZE, string file_name)         // Возвращает 1, если парсинг файла удался
{                                                                   // -1 если вознкикла ошибка чтения файла
    int count = string_counter(file_name);                          
    if (count == -1)
        return -1;
    else
        for (int i=0; i<SIZE; i++)
            array[i].ptr = new string[count - 1];       // Инициализируем динамические массивы

    ifstream file;
    file.open(file_name);
    if (!file.is_open())
        return -1;
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
                    string newstr = "";
                    string str2 = str;          // Дубликат
                    newstr = str.erase(pos, str.length()-pos);
                    str = str2.erase(0, pos);    
                    str = del_space(str);       // Очистка строки от передних пробелов
                    if (j == 0)
                        array[i].column_name = newstr;          // Заполняем название поля
                    else
                        array[i].ptr[j-1] = newstr;             // Заполняем поле
                }
                else if (i == SIZE-1)
                {   
                    str = inverse_del_space(str);
                    if (j == 0)
                        array[i].column_name = str;             // Заполняем название поля
                    else
                        array[i].ptr[j-1] = str;                // Заполняем поле
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
    endwin();
    int count = string_counter("Отчет_05.03.2026_19-14-19.txt") - 1;
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<count; j++)
        {
            cout << array[i].ptr[j] << endl;
        }
        cout << endl;
    }
    initscr();
}

int choose_field(columns* array, int SIZE)          // Возвращает индекс выбранного элемента массива
{                                                   // либо возвращает -1 при нажатии Esc
    int index = 0;
    while(true)
    {    
        clear();
        printw("Выберите поле, по которому будет выполнена сортировка:\n\n");
        for (int i=0; i<SIZE; i++)
        {
            if (i == index)
                printw("<< %s >>\n", array[i].column_name.c_str());
            else 
                printw(" %s \n", array[i].column_name.c_str());
        }
        refresh();
        int ch = getch();
        if (ch == 258)
        {
            if (index != SIZE-1)
                index += 1;
            else
                index = 0;
        }
        if (ch == 259)
        {
            if (index != 0)
                index -= 1;
            else
                index = SIZE-1;
        }
        if (ch == 10)
            return index;

        if (ch == 27)
            return -1;
    }
}

int type_sort()                // Возвращает 0, если направление по возрастанию
{                              // 1, если по убыванию
    int reverse = 0;           // -1, если нажат Esc
    while(true)
    {    
        clear();
        printw("Выберите направление сортировки:\n\n");
        string variants[2] = {"По возрастанию", "По убыванию"};
        for (int i=0; i<2; i++)
        {
            if (i == reverse)
                printw("<< %s >>\n", variants[i].c_str());

            else 
                printw(" %s \n", variants[i].c_str());
        }
        refresh();
        int ch = getch();
        if ((ch == 258) || (ch == 259))
        {
            if (reverse == 0)
                reverse = 1;
            else
                reverse = 0;
        }
        if (ch == 10)
            return reverse;

        if (ch == 27)
            return -1;
        // reset_prog_mode();
    }
}

void regroup_array(int field, columns* array, int SIZE)            // Выполняет перестановку массива структур по выбранному полю
{
    columns temp;
    temp.column_name = array[field].column_name;
    temp.ptr = array[field].ptr;

    for(int i=field; i!=-1; i--)
    {
        if (i == 0)
        {
            array[i].column_name = temp.column_name;
            array[i].ptr = temp.ptr;
        }
        else
        {
            array[i].column_name = array[i-1].column_name;
            array[i].ptr = array[i-1].ptr;
        }
    }
}

void swap(string array[], int low, int high)                // Перестановка элементов массива
{
    string temp = array[low];
    array[low] = array[high];
    array[high] = temp;
}

int partition(string array[], int low, int high, string pivot)          // Деление массива при выполнении сортировки
{
    int i = low;
    int j = low;

    while (i <= high)
    {
        if (array[i] > pivot)
            i++;
        else 
        {
            swap(array, i, j);
            i++;
            j++;
        }
    }
    return (j - 1);
}

void quicksort(string array[], int low, int high)
{
    if (low < high)
    {
        string pivot = array[high];
        int pos = partition(array, low, high, pivot);

        quicksort(array, low, pos-1);
        quicksort(array, pos+1, high);
    }
}