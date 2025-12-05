#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <limits.h>

using namespace std;

void interface(int choice);
void Menu(char* argv[]);
void Help();
void file_checker(bool* file_ECM_exist, bool* file_ECM_CONF_exist);
void files_info(bool* files_ECM_exist, bool* file_ECM_CONF_exist, char* argv[]);
void files_is_found();