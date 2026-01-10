#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const string ECM = "ECM.csv";   // Название первого файла
const string ECM_CONF = "ECM_configuration.csv";    // Название второго файла
const int SIZE = 20;

struct cathedra_counts
{
    string cathedra;
    int count = 0;
};

struct data_from_file
{
    string mark;
    string field_1;             // serial_number (Файл эвм) или terminals (Файл конфигураций)
    string field_2;             // cathedra (файл эвм) или storage_device (Файл конфигураций)
};

void Menu(char* argv[])
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);            // выключение курсора

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
                Menu_for_viewing(&files_ECM_exist, &file_ECM_CONF_exist);
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
            printw("Добавьте требуемые файлы (%s, %s) в директорию:\t%s\n\n", ECM.c_str(), ECM_CONF.c_str(), dir_name.c_str());
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
            printw("Добавьте требуемый файл в директорию:\t%s\n\n", dir_name.c_str());
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
            printw("Добавьте требуемый файл в директорию:\t%s\n\n", dir_name.c_str());
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

void Menu_for_viewing(bool* files_ECM_exist, bool* file_ECM_CONF_exist)         // Меню просмотра файлов
{
    if ((*files_ECM_exist == false) || (*file_ECM_CONF_exist == false))
        while(true)
        {    
            clear();
            interface_for_viewing(3);
            refresh();
            int ch = getch();
            if (ch == 27)
                break;
        }
    else
    {    
        int switcher = 1;
        while(true)
        {    
            clear();
            interface_for_viewing(switcher);
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
                    file_viewer_to_screen();
                }
                if (switcher == 2)
                {
                    //record_2();
                }
            }
            if (ch == 27)
                break;
        }
    }
}

void interface_for_viewing(int choice)
{
    printw("Чтобы вернуться в меню нажмите Esc \n");
    printw("---------------------------------- \n\n");
    switch(choice)
    {
        case 1:
        printw("Выберите:\n\n");
        printw("<< %s >>\n%s\n", "Поиск записей", "Экспорт в файл"); 
        printw("\n\nОписание:\n");
        printw("Поиск информации по запросу.\n");
        break;
        case 2:
        printw("Выберите:\n\n");
        printw("%s\n<< %s >>\n", "Поиск записей", "Экспорт в файл");
        printw("\n\nОписание:\n");
        printw("Запись всей информации в файл.\n");
        break;
        case 3:
        printw("Внимание! Просмотр информации недоступен!\n");
        printw("Некоторые считываемые файлы не были обнаружены.\n");
        printw("Для исправления ошибки и получения большей информации перейдите в раздел \"Проверка файлов\".");
        break;
    }
}

void file_viewer_to_screen()            // Режим вывода данных на экран
{
    clear();
    int counter1 = string_counter(ECM);
    bool flag_ECM_file = files_warning(counter1, ECM);       // Для проверки корректности чтения файла ЭВМ
    int counter2 = string_counter(ECM_CONF);
    bool flag_ECM_CONF_file = files_warning(counter2, ECM_CONF);       // Для проверки корректности чтения файла ЭВМ
    if (flag_ECM_file || flag_ECM_CONF_file)
        return;                 // Завершение работы функции при ошибки считывания файлов

    const int COUNT_ECM = counter1 - 1;
    data_from_file data_ECM[COUNT_ECM];      // Массив для записи всех полей файла ЭВМ       // Надо бы поменять название
    file_reader(data_ECM, COUNT_ECM, ECM);

    //test_func(data_ECM, COUNT_ECM);             // Тестовая функция для отладки

    const int COUNT_ECM_CONF = counter2 - 1;
    data_from_file data_ECM_CONF[COUNT_ECM_CONF];
    file_reader(data_ECM_CONF, COUNT_ECM_CONF, ECM_CONF);

    //test_func(data_ECM_CONF, COUNT_ECM_CONF);             // Тестовая функция для отладки

    //cathedra_counts array_of_cathedras[COUNT_ECM];      // Массив для определения количества машин на каждой кафедре P.S. мб он даже не понадобится
                                                        // Сделаем его в режиме вывода в файл. Здесь можно обойтись без него! 

    
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

bool files_warning(int counter, string filename)            // Предупреждение при ошибке чтения файла
{                                                           // Возвращает true, если есть ошибки чтения файла. Иначе false
    if (counter == -1)
    {
        printw("Ошибка чтения файла %s!", filename.c_str());
        refresh();
        sleep(3);
        return true;
    }
    else if (counter == 1 || counter == 0)
    {
        printw("Файл %s пуст! Информация не доступна", filename.c_str());
        refresh();
        sleep(3);
        return true;
    }
    else
        return false;
}

void file_reader(data_from_file* array, int SIZE, string filename)      // Функция считывания файлов
{                                                       // При считывании повторных записей возвращает пустую строку 
    string line;                                        
    int len;
    string mark, field_1, field_2;
    ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        for (int i=-1; getline(file, line); i++)
        {
            bool repeat_flag = false;
            if (i == -1)
                continue;                                       // пропуск первой строки
            else
            {   
                string copy_line_1 = line;
                int position_1 = line.find(",");
                mark = line.erase(position_1);                  // Выразили марку
                line = copy_line_1.erase(0, position_1 + 1);
                int position_2 = line.find(",");
                string copy_line_2 = line;
                field_1 = line.erase(position_2);         // Выразили серийный номер
                field_2 = copy_line_2.erase(0, position_2 + 1);       // Выразили номер кафедры

                if ((i > 0) && (filename == ECM))
                {
                    for (int j=0; j<i; j++)                     // Проверка на повторные записи в файле
                    {
                        if ((array[j].mark == mark) &&                   
                            (array[j].field_1 == field_1) &&         // Нет смысла проверять только на серийный номер
                            (array[j].field_2 == field_2))                     // потому что: 1) во время записи человек мог посмотреть не на ту строку и ошибочно записать данные
                        {                                                           // при этом перезаписав данные мы точно не сможем узнать, были они перезаписаны верно или ошибочно (перезаписали вместо правильной)            
                            repeat_flag = true;                                     // проще позвонить на кафедру и уточнив информацию отредактировать файл 
                            break;                                                  // 2) вероятность одинакового серийника на разных марках хоть и мала, но возможна
                        }
                    }
                }
                else if ((i > 0) && (filename == ECM_CONF))
                {
                    for (int j=0; j<i; j++)                     // Проверка на повторные записи в файле
                    {
                        if (array[j].mark == mark)                                    
                        {
                            if (field_1 != "=")
                                array[j].field_1 = field_1;
                            if ((field_2 != "=") && (field_2 != "=\n"))
                                array[j].field_2 = field_2;
                            
                            repeat_flag = true;                                     
                            break;                                                  
                        }
                    }
                }
                if (!repeat_flag)
                {
                    array[i].mark = mark;
                    array[i].field_1 = field_1;
                    array[i].field_2 = field_2;
                }
            }
        }
    }
    file.close();
}

void test_func(data_from_file* data_ECM, int SIZE)
{
    endwin();
    for (int i = 0; i<SIZE; i++)
    {
        // cout << data_ECM[i].mark << "\t" << data_ECM[i].serial_number << "\t" << data_ECM[i].cathedra << endl;
        printf("%s\t%s\t%s\n", data_ECM[i].mark.c_str(), data_ECM[i].field_1.c_str(), data_ECM[i].field_2.c_str());
    }
    sleep(100);
}

int cathedras_counter(data_from_file* input_data, cathedra_counts* array_of_cathedras, int SIZE)        // Функция подсчета количества уникальных кафедр
{
    int counter = 0;
    for (int i=0; i<SIZE; i++)
    {
        string cathedra = input_data[i].field_2;
        if (i == 0)
        {
            array_of_cathedras[i].cathedra = cathedra;
            array_of_cathedras[i].count = 1;
        }
        else
        {
            for (int j=0; j<i; j++)
            {
                // Нужно сравнивать текущую ячейку входящих данных с предыдущими ячейками для проверки повторений кафедры 
                // вопрос - с ячейками какого массива сравнивать.
                // Как будто бы легче сравнивать с ячейками запиСЫВАЕМОГО массива array_of_cathedras
                // мол сразу зашел, сверил, прибавил

                // да надо сверять также, как при записи строк из первого файла
            }
        }
    }
    return 1;
}