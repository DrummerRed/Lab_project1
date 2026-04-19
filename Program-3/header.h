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
string choose_file_name_in222();            //2 версия
string input_file(bool* flag_Esc);
//string get_filename();
bool file_checker(string filename);       // Функция проверки существования рабочего файла программы
int file_parser(columns* array, int SIZE, string file_name);
int string_counter(string file_name);
void convert_to_numb(columns* array, int len);
void convert_to_str(columns* array, int len, int SIZE);
string del_space(string str);
string inverse_del_space(string str);
string choose_file_name_out();

string choose_file_name_out222();
string scan_file_name();    // Функция, считывающая марку ЭВМ с консоли
string scan_file_name_222();
void clear_buffer(string* buffer);       // Функция очистки буфера
int find_esc(string mark);
int symb(string cathedra);

int choose_field(columns* array, int SIZE);
int type_sort();
void regroup_array(int field, columns* array, int SIZE);

void swap(columns array[], int low, int high);                            // Перестановка элементов массива
int partition_str(columns array[], int low, int high, string pivot);          // Деление массива при выполнении сортировки
int partition_int(columns array[], int low, int high, int pivot);          // Деление целочисл массива при выполнении сортировки
void quicksort(columns array[], int low, int high);

void file_creator(columns* array, int SIZE, int type, string field_name, string file_name);                     // Вывод в файл
void interface_for_file_creator(string filename);
void add_whitespace(columns* array, string file_name);              // Добавляет к каждой строке пробелы для табличного вывода в файл
bool cathedra_checker(string cathedra);
void record(columns* array, int ROWS, int COLS, string field_name, string filename_out);                // Вывод сортировки по возрастанию
void reverse_record(columns* array, int ROWS, int COLS, string field_name, string filename_out);                // Вывод сортировки по убыванию

void free_memory(columns* array, int SIZE);

void debug_print(columns* array, int SIZE);          // удалить