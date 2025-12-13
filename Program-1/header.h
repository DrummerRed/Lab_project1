#include <iostream>
#include <cstdlib>          // Для использования некоторых системных функций: system(), exit()
#include <ncurses.h>        // Для реализации интерактивного меню
#include <string>
#include <unistd.h>         // Для использования задержки по времени sleep()
#include <limits.h>         // Содержит системные константы 

using namespace std;

void file_creater();                    // Функция для создания и проверки существования рабочих файлов программы
void Menu();                            // Функция вывода меню программы
void interface(int choice);             // Функция отрисовки пользовательского интерфейса меню

void Help();                            // Функция работы пункта меню "Помощь"
void files_info();                      // Функция работы подпункта меню "Информация о файлах"

void Menu_for_record();                 // Функция работы подпункта меню "Начать запись"
void interface_for_record(int choice);  // Функция отрисовки пользовательского интерфеса для пункта меню "Начать запись"
void record_1();                        // Функция записи первого файла (файл ЭВМ)
void record_2();                        // Функция записи второго файла (файл конфигураций)
void choose_1(string* mark_ptr, string* serial_number_ptr, string* cathedra_ptr);       // Считывание информации для файла ЭВМ
void choose_2(string* mark_ptr, string* terminals_ptr, string* storage_device_ptr);     // Считывание информации для файла конфигураций
int mark_symb(string mark);             // Функция проверки символов поля "Марка ЭВМ"
string scan_mark();                     // Функция, считывающая марку ЭВМ с консоли
int serial_number_symb(string serial_number);       // Функция проверки символов поля "Заводской номер"
string scan_serial_number();            // Функция, считывающая заводской номер с консоли
int cathedra_symb(string cathedra);     // Функция проверки символов поля "Кафедра"
int cathedra_symb_counter(string cathedra);      // Функция проверки КОЛИЧЕСТВА символов поля Кафедра
string scan_cathedra();                 // Функция, считывающая номер кафедры с консоли    
int terminals_and_storage_device_symb(string str);      // Функция проверки символов поля "количество терминалов" или "количество внешних устройств"
string scan_terminals();                // Функция, считывающая количество терминалов с консоли
string scan_storage_device();           // Функция, считывающая количество ВЗУ с консоли
string upper_symb(string str);          // Функция для преобразования строчных букв в заглавные
void clear_buffer(string* buffer);      // Функция очистки буфера
int find_esc(string mark);              // Функция проверки нажатия esc

void Menu_for_cleaning();               // Меню для выбора файла, который желаем очистить
void interface_for_cleaning(int choice);            // Интерфейс выбора очищаемого файла
void Menu_are_you_sure_cleaning(string file_1, string file_2 = "");         // Функция предупреждения об очистке файла
void are_you_sure_interface(int choice, string file_1, string file_2);      // Интерфейс предупреждения об очистке
void file_ECM_cleaning();               // Функция для очистки первого файла (файла ЭВМ)
void file_ECM_CONF_cleaning();          // Функция для очистки второго файла (файл конфигураций)