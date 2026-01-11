#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <iomanip>

using namespace std;

struct cathedra_counts;
struct data_from_file;

void interface(int choice);
void Menu(char* argv[]);
void Help();
void file_checker(bool* file_ECM_exist, bool* file_ECM_CONF_exist);
void files_info(bool* files_ECM_exist, bool* file_ECM_CONF_exist, char* argv[]);
void files_is_found();
void Menu_for_viewing(bool* files_ECM_exist, bool* file_ECM_CONF_exist);
void interface_for_viewing(int choice);

void file_viewer_to_screen();               // Режим вывода данных на экран
int string_counter(string file_name);        // Функция подсчета строк в файле
bool files_warning(int counter, string filename);            // Предупреждение при ошибке чтения файла
void file_reader(data_from_file* array, int SIZE, string filename);      // Функция считывания файлов
void cathedras_counter(data_from_file* input_data, cathedra_counts* array_of_cathedras, int SIZE);        // Функция подсчета количества уникальных кафедр
void to_screen(string cathedra, data_from_file* ECM_array, data_from_file* ECM_CONF_array, int SIZE1, int SIZE2);     // Функция вывода информации на экран

void input_cathedra(data_from_file* ECM_array, data_from_file* ECM_CONF_array, int SIZE1, int SIZE2);       // Функция ввода для поиска кафедрфы
string scan_cathedra();    // Функция, считывающая номер кафедры с консоли
void clear_buffer(string* buffer);       // Функция очистки буфера
int find_esc(string mark);      // Функция проверки нажатия esc
int cathedra_symb(string cathedra);      // Функция проверки символов поля "Кафедра"
int cathedra_symb_counter(string cathedra);      // Функция проверки КОЛИЧЕСТВА символов поля Кафедра

void test_func(data_from_file* data_ECM, int SIZE);      // Удалить тестовую функцию отладки
void test_func2(cathedra_counts* data_ECM, int SIZE);       // Удалить тестовую функцию отладки