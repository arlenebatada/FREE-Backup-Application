#include "constants.h"
#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

void malloc_2d_string_array(char*** variable_name);
void malloc_1d_array(char** variable_name, int size);
int FileExists(const char *filename);
int is_file_a_directory(char* file_name_with_path);
int get_list_of_files_in_the_given_folder(char** list_of_files, char* folder_name_with_path);


#endif
