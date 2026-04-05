#include <iostream>
#include <cstdlib>          // Для использования некоторых системных функций: system(), exit()
#include <ncurses.h>        // Для реализации интерактивного меню
#include <string>
#include <fstream>
#include <unistd.h>         /////
#include <limits.h>         // Для константы максимальной длины пути
#include <iomanip>          // Для вывода информации в табличном виде

#include <wchar.h>

using namespace std;

struct columns; 

void Menu(char* argv[]);        // Главное меню программы
void interface(int choice);     // Отрисовка интерфейса главного меню программы

void Help();                    // Функция работы пункта меню "Помощь"

void Menu_for_sorting();
string choose_file_name_in();
string get_filename();
bool file_checker(string filename);       // Функция проверки существования рабочего файла программы
int file_parser(columns* array, int SIZE, string file_name);
int string_counter(string file_name);
string del_space(string str);
string inverse_del_space(string str);

int choose_field(columns* array, int SIZE);
int type_sort();
void regroup_array(int field, columns* array, int SIZE);

void swap(columns array[], int low, int high);                            // Перестановка элементов массива
int partition(columns array[], int low, int high, string pivot);          // Деление массива при выполнении сортировки
void quicksort(columns array[], int low, int high);

void file_creator(columns* array, int SIZE, int type, string file_name);                     // Вывод в файл
void interface_for_file_creator(string filename);
void add_whitespace(columns* array, string file_name);              // Добавляет к каждой строке пробелы для табличного вывода в файл
void record(columns* array, int ROWS, int COLS, string filename_out);                // Вывод сортировки по возрастанию
void reverse_record(columns* array, int ROWS, int COLS, string filename_out);                // Вывод сортировки по убыванию

void debug_print(columns* array, int SIZE);          // удалить