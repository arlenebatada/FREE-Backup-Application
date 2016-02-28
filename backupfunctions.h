#include "constants.h"

#ifndef BACKUPFUNCTIONS_H
#define BACKUPFUNCTIONS_H

void backup(char* folder_name, char* source_path, char* destination_path, char* config_folder_path);
void copy_file(char* file_name, char* source_path, char* destination_path, char* folder_name, char* config_folder_path);
void create_meta_file(char* timbuf, char* meta_file_location, int choice);
void get_modified_time_of_the_source_file(char* file_name_with_source_path, char* timbuf);
void copy_source_file_to_the_destination(char* file_name, char* file_name_with_source_path, char* file_name_with_destination_path);
void get_meta_info_from_the_meta_file(char* meta_file_location, char* ftimbuf);

#endif
