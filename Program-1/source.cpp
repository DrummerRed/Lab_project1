#include "header.h"

const string HELP = "help.txt";                     // Название файла для вкладки "Помощь"
const string ECM = "ECM.csv";                       // Название первого файла (файл ЭВМ)
const string ECM_CONF = "ECM_configuration.csv";    // Название второго файла (файл конфигураций)
const int SIZE = 20;                                // Размер массивов (для строк)
const int NUMB_SIZE = 6;                            // Размер массива (для ввода числа)

void Menu()                     // Функция вывода меню программы
{
    initscr();                  // Инициализация экрана из библиотеки ncurses
    cbreak();                   // Отключение буферизации для экрана ncurses
    noecho();                   // Отключение отображения вводимых символов (ncurses)
    keypad(stdscr, TRUE);       // Включение обработки специальных клавиш (ncurses)
    curs_set(0);                // Выключение курсора (ncurses)

    bool stop = false;
    int switcher = 1;
    while(stop == false)
    {    
        clear();                // Очистка экрана ncurses
        interface(switcher);    // Функция отрисовки главного меню программы
        refresh();              // Отрисовка экрана ncurses 
        int ch = getch();
        if (ch == 258)
        {
            if (switcher != 5)
                switcher += 1;
            else
                switcher = 1;
        }
        if (ch == 259)
        {
            if (switcher != 1)
                switcher -= 1;
            else
                switcher = 5;
        }
        if (ch == 10)
        {
            if (switcher == 1)
                Help();

            if (switcher == 2)
                files_info();

            if (switcher == 3)
                Menu_for_cleaning();

            if (switcher == 4)
                Menu_for_record();

            if (switcher == 5)
            {
                endwin();               // Завершение работы экрана в режиме ncurses
                system("clear");        // Функция очистки терминала
                stop = true;            // Завершение работы программы
            }
        }
    }
}

void interface(int choice)      // Функция отрисовки пользовательского интерфейса меню
{
    switch(choice)
    {
        case 1:
        printw(" \t\t<< Помощь >>\n \t\tИнформация о файлах\n \t\tОчистить файлы\n \t\tНачать запись\n \t\tВыход");
        break;
        case 2:
        printw(" \t\tПомощь\n \t\t<< Информация о файлах >>\n \t\tОчистить файлы\n \t\tНачать запись\n \t\tВыход");
        break;
        case 3:
        printw(" \t\tПомощь\n \t\tИнформация о файлах\n \t\t<< Очистить файлы >>\n \t\tНачать запись\n \t\tВыход");
        break;
        case 4:
        printw(" \t\tПомощь\n \t\tИнформация о файлах\n \t\tОчистить файлы\n \t\t<< Начать запись >>\n \t\tВыход");
        break;
        case 5:
        printw(" \t\tПомощь\n \t\tИнформация о файлах\n \t\tОчистить файлы\n \t\tНачать запись\n \t\t<< Выход >>");
        break;
    }
}

void Menu_for_record()          // Функция работы подпункта меню "Начать запись"
{
    bool stop = false;
    int switcher = 1;
    while(stop == false)
    {    
        clear();                            // Очистка экрана ncurses
        interface_for_record(switcher);     
        refresh();                          // Отрисовка изменений на экране ncurses
        int ch = getch();
        if (ch == 258)
        {
            if (switcher == 2)
                switcher = 1;
            else
                switcher = 2;
        }
        if (ch == 259)
        {
            if (switcher == 1)
                switcher = 2;
            else
                switcher = 1;
        }
        if (ch == 10)
        {
            if (switcher == 1)
                record_1();
            if (switcher == 2)
                record_2();
        }
        if (ch == 27)
            stop = true;
    }
}

void interface_for_record(int choice)             // Функция отрисовки пользовательского интерфеса для пункта меню "Начать запись"
{
    printw("Чтобы вернуться в меню нажмите Esc \n");
    printw("---------------------------------- \n\n");
    printw("Выберите файл для записи:\n\n");
    switch(choice)
    {
        case 1:
        printw("<< %s >>\n%s\n", "Файл ЭВМ", "Файл конфигураций"); 
        printw("\n\nОписание:\n");
        printw("Файл ЭВМ содержит информацию о марке ЭВМ, заводском номере и номере кафедры.\n");
        break;
        case 2:
        printw("%s\n<< %s >>\n", "Файл ЭВМ", "Файл конфигураций");
        printw("\n\nОписание:\n");
        printw("Файл конфигураций содержит информацию о количестве терминалов и количестве внешних запоминающих устройств ЭВМ.\n");
        break;
    }
}

void Help()                         // Функция работы пункта меню "Помощь"
{
    def_prog_mode();                // Сохраняем режим ncurses
    endwin();                       // Временно выключаем ncurses
    system("clear");                // Очистка экрана терминала
    char str;
    string duplicate_str = "";
    FILE * file = fopen(HELP.c_str(), "r");

    if (file == NULL)
    {
        printf("Ошибка чтения файла!\n");
        exit(0);
    }
    int symb;
    while ((symb = fgetc(file)) != EOF)         // Посимвольно считываем файл
    {
        str = (char)symb;
        duplicate_str += str;
    }
    fclose(file);
    reset_prog_mode();              // Восстанавливаем режим ncurses
    clear();
    printw("%s", duplicate_str.c_str());
    refresh();
    int ch = 0;
    while((int)ch != 27)
    {
        ch = getch();
    }
}

void file_creater()                 // Функция для создания и проверки существования рабочих файлов программы
{
FILE * file_1 = fopen(ECM.c_str(), "r");
    if (file_1 == NULL)
    {
        FILE * new_file_1 = fopen(ECM.c_str(), "w");
        fprintf(new_file_1, "Марка ЭВМ,Заводской номер,Номер кафедры\n");
        fclose(new_file_1);
    }
    else
        fclose(file_1);

FILE * file_2 = fopen(ECM_CONF.c_str(), "r");
    if (file_2 == NULL)
    {
        FILE * new_file_2 = fopen(ECM_CONF.c_str(), "w");
        fprintf(new_file_2, "Марка ЭВМ,Количество терминалов,Количество внешних запоминающих устройств\n");
        fclose(new_file_2);
    }
    else
        fclose(file_2);
}

void files_info()               // Функция работы подпункта меню "информация о файлах"
{
    clear();
    printw("Информация о файлах\n======================================\n\n");
    char absolute_path[PATH_MAX];
    if (realpath(ECM.c_str(), absolute_path))           // realpath() преобразовывает относительный путь в абсолютный
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
    refresh();

    int ch = 0;
    while((int)ch != 27)
    {
        ch = getch();
    }
}

void record_1()                         // Функция записи первого файла (файл ЭВМ)
{
    FILE * file_ECM = fopen(ECM.c_str(), "a");
    if (file_ECM == NULL)
    {
        printf("Ошибка открытия файла");
        endwin();
        exit(0);                        // Завершение работы при возникновении ошибки
    }

    clear();
    printw("Чтобы вернуться нажмите Esc \n\n");
    printw("Для продолжения нажмите Enter ...");
    while(true)
    {
    bool inner_STOP = false;
    int ch = 0;
    while(inner_STOP == false)
    {
        ch = getch();
        if ((int)ch == 27)
        {   
            fclose(file_ECM);
            return;                 // Досрочное завершение функции
        }
        if ((int)ch == 10)
            inner_STOP = true;   
    }

    def_prog_mode();                // Сохраняем режим ncurses
    endwin();                       // Временно выключаем ncurses
    system("clear");

    string mark = "";       // Создаем переменные, считываем их с консоли при помощи функции choose_1 и записываем в файл
    string serial_number = "";
    string cathedra = ""; 
    choose_1(&mark, &serial_number, &cathedra);
    serial_number = upper_symb(serial_number);       // Преобразовываем буквы нижнего регистра в верхний
    
    mark.erase(mark.find('\n'), 1);         // Используем метод erase() для удаления символа переноса
    if (mark == "")                         // Отсутствие записи в случае принудительного выхода (Esc + enter)
        {
        reset_prog_mode();
        refresh();
        system("clear");
        break;
        }
    serial_number.erase(serial_number.find('\n'), 1);
    if (serial_number == "")                // Проверка на принудительный выход (Esc + enter)
        {
        reset_prog_mode();
        refresh();
        system("clear");
        fprintf(file_ECM, "%s,%s,%s\n", mark.c_str(), "=", "=");        // Запись значений в файл
        break;
        }
    cathedra.erase(cathedra.find('\n'), 1);
    if (cathedra == "")                     // Проверка на принудительный выход (Esc + enter)
        {
        reset_prog_mode();
        refresh();
        system("clear");
        fprintf(file_ECM, "%s,%s,%s\n", mark.c_str(), serial_number.c_str(), "=");
        break;
        }
    fprintf(file_ECM, "%s,%s,%s\n", mark.c_str(), serial_number.c_str(), cathedra.c_str());     // Запись значений в файл

    system("clear");
    reset_prog_mode();          // Восстанавливаем режим ncurses
    refresh();
    }
    system("clear");
    fclose(file_ECM);
}

void choose_1(string* mark_ptr, string* serial_number_ptr, string* cathedra_ptr)        // Считывание информации для файла ЭВМ
{
    printf("(Для принудительного выхода зажмите сочетание клавиш \"Esc\"+\"Enter\")");
    printf("\n");
    printf("-------------------------------------------------------------------\n\n");
    printf("Введите:\n\n");
    string mark = scan_mark();      // Считываем марку ЭВМ при помощи соответствующей функции
    printf("\n");
    if (mark == "\n")
        {
        *mark_ptr = "\n";
        *serial_number_ptr = "\n";
        *cathedra_ptr = "\n";
        return;                     // Досрочное завершение функции
        }

    string serial_number = scan_serial_number();        // Считываем серийный номер
    printf("\n");
    if (serial_number == "\n")
        {
        *mark_ptr = mark;
        *serial_number_ptr = "\n";
        *cathedra_ptr = "\n";
        return;
        }

    string cathedra = scan_cathedra();      // Считываем номер кафедры
    printf("\n");
    if (cathedra == "\n")
        {
        *mark_ptr = mark;
        *serial_number_ptr = serial_number;
        *cathedra_ptr = "\n";
        return;
        }

    // Записываем параметры для вывода в файл:
    *mark_ptr = mark;
    *serial_number_ptr = serial_number;
    *cathedra_ptr = cathedra;
}

void record_2()           // Функция записи второго файла (файл конфигураций)
{
    FILE * file_ECM_CONF = fopen(ECM_CONF.c_str(), "a");
    if (file_ECM_CONF == NULL)
    {
        printf("Ошибка открытия файла");
        endwin();
        exit(0);
    }

    clear();
    printw("Чтобы вернуться нажмите Esc \n\n");
    printw("Для продолжения нажмите Enter ...");
    while(true)
    {
    bool inner_STOP = false;
    int ch = 0;
    while(inner_STOP == false)
    {
        ch = getch();
        if ((int)ch == 27)
        {   
            fclose(file_ECM_CONF);
            return;
        }
        if ((int)ch == 10)
            inner_STOP = true;   
    }

    def_prog_mode();   // Сохраняем режим ncurses
    endwin();          // Временно выключаем ncurses
    system("clear");   // Очищаем экран

    string mark = "";       // Создаем переменные, считываем их с консоли при помощи функции choose_2 и записываем в файл
    string terminals = "";
    string storage_device = "";
    choose_2(&mark, &terminals, &storage_device);

    mark.erase(mark.find('\n'), 1);         // Используем метод erase() для удаления символа переноса
    if (mark == "")                         // Отсутствие записи в случае принудительного выхода (Esc + enter)
        {
        reset_prog_mode();
        refresh();
        system("clear");
        break;
        }
    terminals.erase(terminals.find('\n'), 1);
    if (terminals == "")                    // Проверка на принудительный выход (Esc + enter)
        {
        reset_prog_mode();
        refresh();
        system("clear");
        fprintf(file_ECM_CONF, "%s,%s,%s\n", mark.c_str(), "=", "=");
        break;
        }
    storage_device.erase(storage_device.find('\n'), 1);
    if (storage_device == "")               // Проверка на принудительный выход (Esc + enter)
        {
        reset_prog_mode();
        refresh();
        system("clear");
        fprintf(file_ECM_CONF, "%s,%s,%s\n", mark.c_str(), terminals.c_str(), "=");
        break;
        }
    fprintf(file_ECM_CONF, "%s,%s,%s\n", mark.c_str(), terminals.c_str(), storage_device.c_str());

    system("clear");
    reset_prog_mode();      // Восстанавливаем режим ncurses
    refresh();
    }
    system("clear");
    fclose(file_ECM_CONF);
}

void choose_2(string* mark_ptr, string* terminals_ptr, string* storage_device_ptr)          // Считывание информации для файла конфигураций
{
    printf("(Для принудительного выхода зажмите сочетание клавиш \"Esc\"+\"Enter\")");
    printf("\n");
    printf("-------------------------------------------------------------------\n\n");
    printf("Введите:\n\n");   
    string mark = scan_mark();      // Считываем марку ЭВМ функцией scan_mark
    printf("\n");
    if (mark == "\n")
        {
        *mark_ptr = "\n";
        *terminals_ptr = "\n";
        *storage_device_ptr = "\n";
        return;
        }

    string terminals = scan_terminals();    // Считываем количество терминалов функцией scan_terminals
    printf("\n");
    if (terminals == "\n")
        {
        *mark_ptr = mark;
        *terminals_ptr = "\n";
        *storage_device_ptr = "\n";
        return;
        }

    string storage_device = scan_storage_device();      // Считываем количество ВЗУ функцией scan_storage_device
    printf("\n");
    if (storage_device == "\n")
        {
        *mark_ptr = mark;
        *terminals_ptr = terminals;
        *storage_device_ptr = "\n";
        return;
        }

    // записываем параметры для вывода в файл:
    *mark_ptr = mark;
    *terminals_ptr = terminals;
    *storage_device_ptr = storage_device;
}

int mark_symb(string mark)      // Функция проверки символов поля "Марка ЭВМ"
{                               // Возвращает 1, если введены корректные символы. Иначе 0
    string eng_high = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string eng_low = "abcdefghijklmnopqrstuvwxyz";
    string numbers = "0123456789-. ";
    int invalid_symb = 1; 
    mark += "\n";

    for (int i=0; (mark[i] != '\n'); i++)
    {
        if ((eng_high.find(mark[i]) == -1) &&
            (eng_low.find(mark[i]) == -1) &&
            (numbers.find(mark[i]) == -1))
            {
                invalid_symb = 0;
                break;
            }
    }
    return invalid_symb;
}

string scan_mark()    // Функция, считывающая марку ЭВМ с консоли 
{                                                            
    while(true)                                                 
        {                                                    
        bool error_flag = false; 
        string checker = "";
        char local_mark[SIZE] = "";
        int i = 0;
        printf("Марка ЭВМ: ");
        while((local_mark[i] = getchar()) != '\n')
            {
            checker+=local_mark;
            i++;
            if (i == SIZE-1)            // Очищаем буфер при превышении допустимого количества введенных символов
                {
                    error_flag = true;
                    clear_buffer(&checker);         // При очистке записываем символы из буфера в переменную checker
                    break;
                }
            }

        if (find_esc(checker) == 0)         // Проверка на принудительный выход по Esc
            {
            return "\n";
            }

        if (mark_symb(local_mark) == 0)      // Проверка на корректность символов
            {
            printf("Ошибка ввода! Недопустимые символы!\nНазвание может содержать только буквы латинского алфавита, а также цифры и символы \"-.\"!\n");
            continue;
            }

        if (error_flag == true)         // Проверка на максимальную длину строки
            {
            printf("Ошибка ввода! Название не может быть больше %d символов!\n", SIZE-2);    
            continue;
            }

        if ((local_mark[0] == '\n') || (local_mark[0] == ' '))      // Проверка на пустую строку
            {
            printf("Ошибка ввода! Введена пустая строка!\n");
            continue;
            }
        else
            return local_mark;
        }
}

int serial_number_symb(string serial_number)      // Функция проверки символов поля "Заводской номер"
{                                                 // Возвращает 1, если введены корректные символы. Иначе 0
    string eng_high = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string eng_low = "abcdefghijklmnopqrstuvwxyz";
    string numbers = "0123456789"; 
    int invalid_symb = 1; 
    serial_number += "\n";
    if ((serial_number == "=\n") || (serial_number == "=\n\n"))       //проверка на ввод отсутствующей информации
        return invalid_symb;

    for (int i=0; (serial_number[i] != '\n'); i++)
    {
        if ((eng_high.find(serial_number[i]) == -1) &&
            (eng_low.find(serial_number[i]) == -1) &&
            (numbers.find(serial_number[i]) == -1))
            {
                invalid_symb = 0;
                break;
            }
    }
    return invalid_symb;
}

string scan_serial_number()    // Функция, считывающая заводской номер с консоли
{                                                            
    while(true)                                                 
        {                                                    
        bool error_flag = false; 
        string checker = "";
        char serial_number[SIZE] = "";
        int i = 0;
        printf("Заводской номер: ");
        while((serial_number[i] = getchar()) != '\n')
            {
            checker+=serial_number;
            i++;
            if (i == SIZE-1)        // Очищаем буфер при превышении допустимого количества введенных символов
                {
                    error_flag = true;
                    clear_buffer(&checker);       // При очистке записываем символы из буфера в переменную checker
                    break;
                }
            }

        if (find_esc(checker) == 0)     // Проверка на принудительный выход по Esc
            {
            return "\n";
            }
        if (serial_number_symb(serial_number) == 0)     // Проверка на корректность символов
            {
            printf("Ошибка ввода! Недопустимые символы!\nНомер может содержать только цифры и буквы латинского алфавита!\n");
            continue;
            }
        if (error_flag == true)         // Проверка на максимальную длину строки
            {
            printf("Ошибка ввода! Номер не может содержать больше %d символов!\n", SIZE-2);    
            continue;
            }
        if ((serial_number[0] == '\n') || (serial_number[0] == ' '))      // Проверка на пустую строку
            {
            printf("Ошибка ввода! Введена пустая строка!\n");
            continue;
            }
        else
            return serial_number;
        }
}

int cathedra_symb(string cathedra)      // Функция проверки символов поля "Кафедра"
{                                       // Возвращает 1, если введены корректные символы. Иначе 0
    string rus_high = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧЩЭЮЯ";
    string numbers = "0123456789";
    int invalid_symb = 1; 
    cathedra += "\n";
    if ((cathedra == "=\n") || (cathedra == "=\n\n"))       // Проверка на ввод отсутствующей информации
    {
        return invalid_symb;
    }

    for (int i=0; (cathedra[i] != '\n'); i++)
    {
        if ((rus_high.find(cathedra[i]) == -1) &&
            (numbers.find(cathedra[i]) == -1))
            {
                invalid_symb = 0;
                break;
            }
    }
    return invalid_symb;
}

int cathedra_symb_counter(string cathedra)      // Функция проверки КОЛИЧЕСТВА символов поля Кафедра
{                                               // Возвращает 1, если введены корректные символы. Иначе 0
    string rus_high = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧЩЭЮЯ";
    string numbers = "0123456789";
    int invalid_symb = 1; 
    cathedra += "\n";
    if ((cathedra == "=\n") || (cathedra == "=\n\n"))       // Проверка на ввод отсутствующей информации
        return invalid_symb;
    int numb_counter = 0;
    int symb_counter = 0;
    for (int i=0; (cathedra[i] != '\n'); i++)
    {
        if (rus_high.find(cathedra[i]) != -1)
        {
            symb_counter++;
        }
        else if (numbers.find(cathedra[i]) != -1)
        {
            numb_counter++;
        }
    }
    if ((numb_counter > 3) || (symb_counter > 6))
        invalid_symb = 0;
    return invalid_symb;
}

string scan_cathedra()    // Функция, считывающая номер кафедры с консоли
{                                                            
    while(true)                                                 
        {                                                     
        string checker = "";
        char cathedra[SIZE] = "";
        int i = 0;
        printf("Номер кафедры: ");
        while((cathedra[i] = getchar()) != '\n')
        {
            checker+=cathedra;
            i++;
            if (i == SIZE-1)        // Очищаем буфер при превышении допустимого количества введенных символов
            {
                clear_buffer(&checker);         // При очистке записываем символы из буфера в переменную checker
                break;
            }
        }

        if (find_esc(checker) == 0)         // Проверка на принудительный выход по Esc
        {
            return "\n";
        }
        if (cathedra_symb(cathedra) == 0)       //Проверка на корректность символов
        {
            printf("Ошибка ввода! Недопустимые символы!\nНомер может содержать только цифры и заглавные буквы русского алфавита!\n");
            continue;
        }
        if (cathedra_symb_counter(cathedra) == 0)       // Проверка на максимальное количество символов
        {
            printf("Ошибка ввода! Номер не может содержать больше 3 численных и 3 буквенных символов!\n");    
            continue;
        }
        if ((cathedra[0] == '\n') || (cathedra[0] == ' '))      //проверка на пустую строку
        {
            printf("Ошибка ввода! Введена пустая строка!\n");
            continue;
        }
        else
            return cathedra;
        }
}

int terminals_and_storage_device_symb(string str)    // Функция проверки символов поля "количество терминалов" или "количество внешних устройств"
{                                                    // Возвращает 1, если введены корректные символы. Иначе 0
    string numbers = "0123456789";
    int invalid_symb = 1; 
    str += "\n";
    if ((str == "=\n") || (str == "=\n\n"))       // Проверка на ввод отсутствующей информации
    {
        return invalid_symb;
    }

    for (int i=0; (str[i] != '\n'); i++)
    {
        if (numbers.find(str[i]) == -1)
        {
            invalid_symb = 0;
            break;
        }
    }
    return invalid_symb;
}

string scan_terminals()     // Функция, считывающая количество терминалов с консоли
{                                                            
    while(true)                                                 
        {                                                    
        bool error_flag = false; 
        string checker = "";
        char terminals[NUMB_SIZE] = "";  
        int i = 0;
        printf("Количество терминалов: ");
        while((terminals[i] = getchar()) != '\n')
            {
            checker+=terminals;
            i++;
            if (i == NUMB_SIZE-1)        // Очищаем буфер при превышении допустимого количества введенных символов
                {
                    error_flag = true;
                    clear_buffer(&checker);         // При очистке записываем символы из буфера в переменную checker
                    break;
                }
            }

        if (find_esc(checker) == 0)         // Проверка на принудительный выход по Esc
            {
            return "\n";
            }
        if (terminals_and_storage_device_symb(terminals) == 0)       // Проверка на корректность символов
            {
            printf("Ошибка ввода! Недопустимые символы! Введите целое число!\n");
            continue;
            }
        if (error_flag == true)         // Проверка на максимальную длину строки
            {
            printf("Ошибка ввода! Поле не может содержать больше %d символов!\n", NUMB_SIZE-2);    
            continue;
            }
        if ((terminals[0] == '\n') || (terminals[0] == ' '))      // Проверка на пустую строку
            {
            printf("Ошибка ввода! Введена пустая строка!\n");
            continue;
            }
        else
            return terminals;
        }
}

string scan_storage_device()        // Функция, считывающая количество ВЗУ с консоли
{                                                            
    while(true)                                                 
        {                                                    
        bool error_flag = false; 
        string checker = "";
        char storage_device[NUMB_SIZE] = "";  
        int i = 0;
        printf("Количество внешних запоминающих устройств: ");
        while((storage_device[i] = getchar()) != '\n')
            {
            checker+=storage_device;
            i++;
            if (i == NUMB_SIZE-1)        // Очищаем буфер при превышении допустимого количества введенных символов
                {
                    error_flag = true;
                    clear_buffer(&checker);         // При очистке записываем символы из буфера в переменную checker
                    break;
                }
            }

        if (find_esc(checker) == 0)         // Проверка на принудительный выход по Esc
            {
            return "\n";
            }
        if (terminals_and_storage_device_symb(storage_device) == 0)       // Проверка на корректность символов
            {
            printf("Ошибка ввода! Недопустимые символы! Введите целое число!\n");
            continue;
            }
        if (error_flag == true)         // Проверка на максимальную длину строки
            {
            printf("Ошибка ввода! Поле не может содержать больше %d символов!\n", NUMB_SIZE-2);    
            continue;
            }
        if ((storage_device[0] == '\n') || (storage_device[0] == ' '))      // Проверка на пустую строку
            {
            printf("Ошибка ввода! Введена пустая строка!\n");
            continue;
            }
        else
            return storage_device;
        }
}

void Menu_for_cleaning()        // Меню для выбора файла, который желаем очистить
{
    bool stop = false;
    int switcher = 1;
    while(stop == false)
    {    
        clear();
        interface_for_cleaning(switcher);
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
        {                                   // Вызываем предупреждение об очистке файла:
            if (switcher == 1)
            {
                Menu_are_you_sure_cleaning(ECM.c_str());        // Для файла ЭВМ
            }
            if (switcher == 2)
            {
                Menu_are_you_sure_cleaning(ECM_CONF.c_str());   // Для файла конфигураций
            }
            if (switcher == 3)
            {
                Menu_are_you_sure_cleaning(ECM.c_str(), ECM_CONF.c_str());      // Для обоих файлов
            }
        }
        if (ch == 27)
            stop = true;
    }
}

void interface_for_cleaning(int choice)     // Интерфейс выбора очищаемого файла
{
    printw("Чтобы вернуться в меню нажмите Esc \n");
    printw("---------------------------------- \n\n");
    printw("Выберите файлы для очистки:\n\n");
    switch(choice)
    {
        case 1:
        printw("<< Файл ЭВМ (%s) >>\nФайл конфигураций (%s)\nОчистить все файлы\n", ECM.c_str(), ECM_CONF.c_str());
        break;
        case 2:
        printw("Файл ЭВМ (%s)\n<< Файл конфигураций (%s) >>\nОчистить все файлы\n", ECM.c_str(), ECM_CONF.c_str());
        break;
        case 3:
        printw("Файл ЭВМ (%s)\nФайл конфигураций (%s)\n<< Очистить все файлы >>\n", ECM.c_str(), ECM_CONF.c_str());
        break;
    }
}

void Menu_are_you_sure_cleaning(string file_1, string file_2)       // Функция предупреждения об очистке файла
{
    bool stop = false;
    int switcher = 1;
    while(stop == false)
    {    
        clear();
        are_you_sure_interface(switcher, file_1.c_str(), file_2.c_str());       // Выводим интерфейс предупреждения
        refresh();
        int ch = getch();
        if (ch == 258)
        {
            if (switcher == 2)
                switcher = 1;
            else
                switcher = 2;
        }
        if (ch == 259)
        {
            if (switcher == 1)
                switcher = 2;
            else
                switcher = 1;
        }
        if (ch == 10)
        {
            if (switcher == 1)
            {   
                if ((file_1 == ECM) && (file_2 == ""))      // Очистка только файла ЭВМ
                {
                    file_ECM_cleaning();                    // Перезаписываем (очищаем) файл ЭВМ
                    printw("Файл успешно очищен."); 
                    refresh();
                    sleep(2);
                    break;
                }
                else if ((file_1 == ECM_CONF) && (file_2 == ""))    // Очистка только файла конфигураций
                {
                    file_ECM_CONF_cleaning();               // Перезаписываем (очищаем) файл конфигураций
                    printw("Файл успешно очищен."); 
                    refresh();
                    sleep(2);
                    break;
                }
                else if (file_2 != "")      // Если в аргументах введены 2 файла, то очищаем оба файла
                {
                    file_ECM_cleaning();                    // Очищаем оба файла
                    file_ECM_CONF_cleaning();
                    printw("Файлы успешно очищены.");
                    refresh();
                    sleep(2);
                    break;
                }
            }
            if (switcher == 2)
                stop = true;
        }
    }
}

void are_you_sure_interface(int choice, string file_1, string file_2)       // Интерфейс предупреждения об очистке
{
    if (file_2 == "")
    {
        printw("Вы уверены? Содержимое файла %s будет удалено!\n\n", file_1.c_str());
    }
    else
        printw("Вы уверены? Содержимое файлов %s и %s будет удалено!\n\n", file_1.c_str(), file_2.c_str());
    switch(choice)
    {
        case 1:
        printw("<< Да >>\nОтмена\n\n");
        break;
        case 2:
        printw("Да\n<< Отмена >>\n\n");
        break;
    }
}

void file_ECM_cleaning()    // Функция для очистки первого файла (файла ЭВМ)
{
    FILE * new_file_1 = fopen(ECM.c_str(), "w");
    fprintf(new_file_1, "Марка ЭВМ,Заводской номер,Номер кафедры\n");
    fclose(new_file_1);
}

void file_ECM_CONF_cleaning()   // Функция для очистки второго файла (файл конфигураций)
{
    FILE * new_file_2 = fopen(ECM_CONF.c_str(), "w");
    fprintf(new_file_2, "Марка ЭВМ,Количество терминалов,Количество внешних запоминающих устройств\n");
    fclose(new_file_2);
}

string upper_symb(string str)       // Функция для преобразования строчных букв в заглавные 
{
    string eng_low = "abcdefghijklmnopqrstuvwxyz";

    for (int i=0; i<str.length(); i++)
    {
        if (eng_low.find(str[i])!=-1)
        {
            char ch = str[i];
            str[i] = toupper((unsigned char)ch);
        }
    }
    return str;
}

void clear_buffer(string* buffer)       // Функция очистки буфера
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) 
    {
        if (buffer != nullptr)      // Проверка передаваемого параметра
            *buffer += (char)c;     // Записываем символы из буфера в параметр buffer
    }
}

int find_esc(string mark)      // Функция проверки нажатия esc
{                              // Возвращает 0, если esc найден. Иначе 1
    int invalid_symb = 1; 
    mark += "\n";
    for (int i=0; (mark[i] != '\n'); i++)
    {
        if (mark[i] == 27)
            {
                invalid_symb = 0;
                break;
            }
    }
    return invalid_symb;
}