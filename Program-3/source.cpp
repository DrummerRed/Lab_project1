#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const int FIELDS = 5;               // Количество полей
const int NO_DATA = 99999;

struct columns
{
    string column_name;
    string* ptr = nullptr;
    int* i_ptr = nullptr;
    int field_length = 0;       ////////
};

void Menu(char* argv[])         // Главное меню программы
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);            // выключение курсора

    int switcher = 1;
    while(true)
    {    
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
            }
            if (switcher == 3)
            {
                endwin();
                // system("clear");
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

string choose_file_name_in()                            // Обработка имени входного файла
{                                                       // Возвращает имя файла при корректном вводе
    string str;                                         // Либо пустую строку при выходе из режима

    clear();
    printw("Для возврата в меню нажмите Esc\n");
    printw("-------------------------------\n\n");
    refresh();
    noecho();
    curs_set(1);            // включение курсора
    
    bool file_exist = false;
    while(!file_exist)
    {
        printw("Введите название файла: ");
        refresh();

        bool flag_Esc = false;
        str = input_file(&flag_Esc);
        file_exist = file_checker(str);

        if (flag_Esc == true)
            break;

        else if ((flag_Esc == false) && (file_exist == false))
        {
            printw("\nФайл с таким названием отсутствует\n\n");
            refresh();
            continue;
        }
    }

    endwin();
    curs_set(0);            // выключение курсора
    return str;
}

string input_file(bool* flag_Esc)                   // Ввод названия файла с клавиатуры
{                                                   // Возвращает имя файла при корректном вводе
    wint_t ch;                                      // Либо пустую строку при нажатии Esc
    wchar_t filename[256];
    string str = "";

    while(true)
    {
        ch = getch();
        if (ch == 27)
        {
            str = "";
            *flag_Esc = true;
            break;
        }

        else if (ch == KEY_BACKSPACE || ch == 127) // Backspace
            continue;

        else if (ch == 10)
            break;

        else
        {   
            addch(ch);
            str += char(ch);
        }
    }
    return str;
}

bool file_checker(string file_name)       // Функция проверки существования рабочего файла программы
{                                         // Возвращает false, если файл с таким именем отсутствует
    ifstream file;                        // И true, если файл был найден
    file.open(file_name);
    if (!file.is_open())
        return false;
    else
    {
        file.close();
        return true;
    }
}

void Menu_for_sorting()
{
    string file_name = choose_file_name_in();
    if (file_name == "")
        return;                                             // Выход по Esc

    columns* array = new columns[FIELDS];
    int flag = file_parser(array, FIELDS, file_name);       // Считывание полей файла
    if (flag == -1)
    {
        printw("Ошибка чтения файла!");
        return;
    }

    int len = string_counter(file_name)-1;
    convert_to_numb(array, len);

    int field = choose_field(array, FIELDS);                // Выбор поля для сортировки
    if (field == -1)
        return;                                             // Выход по Esc

    int type = type_sort();                                 // выбор типа сортировки (убывание/возрастание)
    if (type == -1)
        return;                                             // Выход по Esc

    regroup_array(field, array, FIELDS);

    quicksort(array, 0, len-1);
    convert_to_str(array, len, FIELDS);

    file_creator(array, FIELDS, type, file_name);

    free_memory(array, FIELDS);
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
                    string str2 = str;                          // Дубликат
                    newstr = str.erase(pos, str.length()-pos);
                    str = str2.erase(0, pos);    
                    str = del_space(str);                       // Очистка строки от передних пробелов
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

void convert_to_numb(columns* array, int len)
{
    for(int i=2; i<4; i++)
    {
        array[i].i_ptr = new int[len];
        for(int j=0; j<len; j++)
        {
            string str = array[i].ptr[j];
            if (str == "Нет данных")
                array[i].i_ptr[j] = NO_DATA;
            else
            {
                try
                {
                    int number = stoi(str);
                    array[i].i_ptr[j] = number;
                }
                catch(exception& e)
                {
                    array[i].i_ptr[j] = NO_DATA;
                    printf("Предупреждение! Элемент поля %s на %d строке вызывает некорректную обработку элемента!\n",
                           array[i].column_name.c_str(), j+2);
                }
            }
        }
    }
}

void convert_to_str(columns* array, int len, int SIZE)
{
    for(int i=0; i<SIZE; i++)
    {
        if (array[i].i_ptr == nullptr)
            continue;
        else
        {
            for(int j=0; j<len; j++)
            {
                if (array[i].i_ptr[j] == NO_DATA)
                    array[i].ptr[j] = "Нет данных";
                else
                    array[i].ptr[j] = to_string(array[i].i_ptr[j]);
            }
            delete[] array[i].i_ptr;
            array[i].i_ptr = nullptr;
        }
    }
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

void file_creator(columns* array, int SIZE, int type, string file_name) // Вывод в файл         // Добавить направление и ввод файла
{
    int count = string_counter(file_name);          
    string filename_out = choose_file_name_out();         // Убрать хардкод
    if (filename_out == "")
        return;                                 // Выход по Esc

    add_whitespace(array, file_name);                              // "Причесываем" поля к для табличной записи (добавление пробелов)
    if (type == 0)
        record(array, count, SIZE, filename_out);
    else
        reverse_record(array, count, SIZE, filename_out);

    interface_for_file_creator(filename_out);
}

string choose_file_name_out()                           // Обработка имени выходного файла
{                                                       // Возвращает имя файла при корректном вводе
    string str;                                         // Либо пустую строку при выходе из режима

    clear();
    printw("Для возврата в меню нажмите Esc\n");
    printw("-------------------------------\n\n");
    refresh();
    noecho();
    curs_set(1);            // включение курсора
    
    string elem = ".txt\n";
    bool elem_exist = false;
    bool flag_Esc = false;
    while(!elem_exist)
    {
        printw("Введите название файла: ");
        refresh();

        str = input_file(&flag_Esc);
        str += "\n";

        if (flag_Esc == true)
            break;

        else if ((flag_Esc == false) && (str.find(elem) == -1))
        {
            printw("\nНазвание файла должно содержать расширение .txt\n\n");
            refresh();
            continue;
        }

        else if (str.find(elem) != -1)
            elem_exist = true;
    }
    if (elem_exist == true)
        str.erase(str.find("\n"));

    endwin();
    curs_set(0);            // выключение курсора
    return str;
}

// string output_file()
// {
//     string str;

// }

void record(columns* array, int ROWS, int COLS, string filename_out)                // Вывод сортировки по возрастанию
{
    ofstream file;
    file.open(filename_out);
    for(int i=-1; i<ROWS-1; i++)             
    {
        for(int j=0; j<COLS; j++)
        {
            if (i == -1)
                file << array[j].column_name;
            else
            {
                int count = 27;
                file << setw(count) << left << array[j].ptr[i];
            }
        }
        file << endl;
    }
    file.close();
}

void reverse_record(columns* array, int ROWS, int COLS, string filename_out)                // Вывод сортировки по убыванию
{
    ofstream file;
    file.open(filename_out);
    for(int i=ROWS-1; i>-1; i--)             
    {
        for(int j=0; j<COLS; j++)
        {
            if (i == ROWS-1)
                file << array[j].column_name;
            else
            {
                int count = 27;
                file << setw(count) << left << array[j].ptr[i];
            }
        }
        file << endl;
    }
    file.close();
}

void add_whitespace(columns* array, string file_name)              // Добавляет к каждой строке пробелы для табличного вывода в файл
{         
    for(int i=0; i<FIELDS; i++)
    {
        string name;
        name = array[i].column_name;
        if (name == "Марка ЭВМ")
            array[i].column_name = "Марка ЭВМ                  ";
        else if (name == "Заводской номер")
            array[i].column_name = "Заводской номер            ";
        else if (name == "Кол-во терминалов")
            array[i].column_name = "Кол-во терминалов          ";
        else if (name == "Кол-во ВЗУ")
            array[i].column_name = "Кол-во ВЗУ                 ";
        else 
            array[i].column_name = "Кафедра                    ";
    }

    int count = string_counter(file_name);            
    for(int i=0; i<FIELDS; i++)
    {
        for(int j=0; j< count-1; j++)
        {
            string str = array[i].ptr[j];
            if (str == "Нет данных")
                array[i].ptr[j] = "Нет данных                 ";
        }
    }
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
    temp.i_ptr = array[field].i_ptr;

    for(int i=field; i!=-1; i--)
    {
        if (i == 0)
        {
            array[i].column_name = temp.column_name;
            array[i].ptr = temp.ptr;
            array[i].i_ptr = temp.i_ptr;
        }
        else
        {
            array[i].column_name = array[i-1].column_name;
            array[i].ptr = array[i-1].ptr;
            array[i].i_ptr = array[i-1].i_ptr;
        }
    }
}

void swap(columns array[], int low, int high)                // Перестановка элементов массива
{
    for(int i=0; i<FIELDS; i++)
    {
        if (array[i].i_ptr == nullptr)
        {
            string temp = array[i].ptr[low];
            array[i].ptr[low] = array[i].ptr[high];
            array[i].ptr[high] = temp;
        }
        else
        {
            int temp = array[i].i_ptr[low];
            array[i].i_ptr[low] = array[i].i_ptr[high];
            array[i].i_ptr[high] = temp;
        }
    }
}

int partition_str(columns array[], int low, int high, string pivot)          // Деление массива строк при выполнении сортировки
{
    int i = low;
    int j = low;

    while (i <= high)
    {
        if (array[0].ptr[i] > pivot)
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

int partition_int(columns array[], int low, int high, int pivot)          // Деление целочисл массива при выполнении сортировки
{
    int i = low;
    int j = low;

    while (i <= high)
    {
        if (array[0].i_ptr[i] > pivot)
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

void quicksort(columns array[], int low, int high)
{
    if (low < high)
    {
        int pos = 0;
        if (array[0].i_ptr == nullptr)
        {
            string pivot = array[0].ptr[high];
            pos = partition_str(array, low, high, pivot);
        }
        else
        {
            int pivot = array[0].i_ptr[high];
            pos = partition_int(array, low, high, pivot);
        }

        quicksort(array, low, pos-1);
        quicksort(array, pos+1, high);
    }
}

void free_memory(columns* array, int SIZE)
{
    for(int i=0; i<SIZE; i++)
    {
        delete[] array[i].ptr;
        array[i].ptr = nullptr;
    }
}

void interface_for_file_creator(string filename)        // Интерфейс записи файла
{
    clear();
    printw("Данные были успешно записаны в файл\n\n");

    char absolute_path[PATH_MAX];
    string dir_name = "";
    if (realpath(filename.c_str(), absolute_path))       // Преобразует относительный путь в абсолютный
    {
        printw("Имя файла:\t%s\n", filename.c_str());
        printw("Путь до файла:\t%s", absolute_path);
    }
    else 
        printw("Ошибка! Файл не был загружен!\n");

    printw("\n\n\n\nДля продолжения нажмите Enter...");
    int ch = 0;
    while((int)ch != 10)
    {
        ch = getch();
    }
}