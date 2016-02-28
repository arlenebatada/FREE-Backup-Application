#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<direct.h>
#include<string>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include"cleanupfunctions.h"
#include"constants.h"
#include"commonfunctions.h"

void cleanup(char* folder_name, char* source_path, char* destination_path, char* info_folder_path)
{
	char *slash="/", *info=".info", *meta=".meta";
	
	//2D array to store list of all files in the given directory
	char **list_of_files;
	malloc_2d_string_array(&list_of_files);
	
	
	char* folder_name_with_source_path;
	malloc_1d_array(&folder_name_with_source_path, FILE_LENGTH_WITH_PATH);
	
	char* folder_name_with_destination_path;
	malloc_1d_array(&folder_name_with_destination_path, FILE_LENGTH_WITH_PATH);
		
	char* info_folder_with_info_folder_path;
	malloc_1d_array(&info_folder_with_info_folder_path, FILE_LENGTH_WITH_PATH);
	strcpy(folder_name_with_source_path, source_path);// folder_name_with_source_path = sourcePath
	strcat(folder_name_with_source_path, slash);// folder_name_with_source_path = sourcePath/
	strcat(folder_name_with_source_path, folder_name);// folder_name_with_source_path = sourcePath/sourceFolderName
	
	strcpy(folder_name_with_destination_path, destination_path);// folder_name_with_destination_path = destinationPath
	strcat(folder_name_with_destination_path, slash);// folder_name_with_destination_path = destinationPath/
	strcat(folder_name_with_destination_path, folder_name);// folder_name_with_destination_path = destinationPath/destinationFolderName
	
	strcpy(info_folder_with_info_folder_path, info_folder_path);// info_folder_with_info_folder_path = infoFolderPath
	strcat(info_folder_with_info_folder_path, slash);// info_folder_with_info_folder_path = infoFolderPath/
	strcat(info_folder_with_info_folder_path, folder_name); // info_folder_with_info_folder_path = infoFolderPath/infoFolderName
	strcat(info_folder_with_info_folder_path, info);// info_folder_with_info_folder_path = infoFolderPath/infoFolderName.info

	//printf("%s\n", folder_name_with_source_path);
	//printf("%s\n", folder_name_with_destination_path);
	/*
	if(!FileExists(folder_name_with_source_path))//checking if source folder exists 
	{
		printf("%s\n", folder_name_with_source_path);
		perror ("\007ERROR");
		printf("\n");
		_getch();
		return ;
		
	}
	
	if (!FileExists(folder_name_with_destination_path))//checking if destination folder exists 
	{
		printf("%s\n", folder_name_with_destination_path);
		perror ("\007ERROR");
		printf("\n");
		_getch();
		return ;
		
	}
	*/
	int number_of_files=get_list_of_files_in_the_given_folder(list_of_files, folder_name_with_destination_path);
	//printf("\nNumber of files = %d", number_of_files);
	for (int i=0; i<number_of_files; i++)
	{
		char *file_name_with_destination_path;
		malloc_1d_array(&file_name_with_destination_path, FILE_LENGTH_WITH_PATH);

		char *file_name_with_source_path;
		malloc_1d_array(&file_name_with_source_path, FILE_LENGTH_WITH_PATH);
		
		char *infoORmeta_file_with_info_folder_path;
		malloc_1d_array(&infoORmeta_file_with_info_folder_path, FILE_LENGTH_WITH_PATH);
		
		strcpy(file_name_with_destination_path,folder_name_with_destination_path);// file_name_with_destination_path= destinationPath/destinationFolderName
		strcat(file_name_with_destination_path, slash);// file_name_with_destination_path= destinationPath/destinationFolderName/
		strcat(file_name_with_destination_path, list_of_files[i]);// file_name_with_destination_path= destinationPath/destinationFolderName/list_of_files[i]
		
		strcpy(file_name_with_source_path,folder_name_with_source_path);// file_name_with_source_path= sourcePath/sourceFolderName
		strcat(file_name_with_source_path, slash);// file_name_with_source_path= sourcePath/sourceFolderName/
		strcat(file_name_with_source_path, list_of_files[i]);// file_name_with_source_path= sourcePath/sourceFolderName/list_of_files[i]
		
		
		if(is_file_a_directory(file_name_with_destination_path))//if the file is a subfolder
		{
			strcpy(infoORmeta_file_with_info_folder_path,info_folder_with_info_folder_path);// info_file_with_info_file_path= infoFolderPath/infoFolderName.info
			strcat(infoORmeta_file_with_info_folder_path, slash);// info_file_with_info_file_path= infoFolderPath/infoFolderName.info/
			strcat(infoORmeta_file_with_info_folder_path, list_of_files[i]);// info_file_with_info_file_path= infoFolderPath/infoFolderName.info/list_of_files[i]
			strcat(infoORmeta_file_with_info_folder_path, info);//infoFolderPath/infoFolderName.info/list_of_files[i].info
		
			if (FileExists(file_name_with_source_path))//if the sub folder is present in the corresponding source location 
			{
				//call cleanup on it so that its subfolders & file can be assessed
				printf("%s (folder) is present in the corresponding source location\n", list_of_files[i]);
				cleanup(list_of_files[i], folder_name_with_source_path, folder_name_with_destination_path, info_folder_with_info_folder_path);
			}
			else //if the sub folder is not present in the source subfolder
			{
				//delete all its internal files
				delete_files_in_the_given_directory(file_name_with_destination_path);
				//after deleting all its internal files it, delete it
				if(FileExists(file_name_with_destination_path) && !_rmdir(file_name_with_destination_path))
				{
					printf("%s folder deleted successfully\n",file_name_with_destination_path);
				}
				//after deleting it, delete its info folder as well (if it exists)
				if(FileExists(infoORmeta_file_with_info_folder_path))
				{
					//delete all the internal files of its info folder
					delete_files_in_the_given_directory(infoORmeta_file_with_info_folder_path);		
					//after deleting all the internal files of its info folder, delete the info folder itself
					if(FileExists(infoORmeta_file_with_info_folder_path) && !_rmdir(infoORmeta_file_with_info_folder_path))
					{
						printf("%s info folder deleted successfully\n",info_folder_with_info_folder_path);
					}
					
				}
			}
		}
		else //if the file is not a subfolder, but is an internal file
		{
			strcpy(infoORmeta_file_with_info_folder_path,info_folder_with_info_folder_path);// meta_file_with_info_file_path= infoFolderPath/infoFolderName.info
			strcat(infoORmeta_file_with_info_folder_path, slash);// meta_file_with_info_file_path= infoFolderPath/infoFolderName.info/
			strcat(infoORmeta_file_with_info_folder_path, list_of_files[i]);// meta_file_with_info_file_path= infoFolderPath/infoFolderName.info/list_of_files[i]
			strcat(infoORmeta_file_with_info_folder_path, meta);//meta_file_with_info_file_path= infoFolderPath/infoFolderName.info/list_of_files[i].meta
		
			
			if (!FileExists(file_name_with_source_path))//if it is not present in the corresponding source location
			{
				//delete it
				if(FileExists(file_name_with_destination_path) && !remove(file_name_with_destination_path))
				{
					printf("%s file deleted successfully\n",file_name_with_destination_path);
				}
				//delete its corresponding meta file (if it exists)
				if(FileExists(infoORmeta_file_with_info_folder_path) && !remove(infoORmeta_file_with_info_folder_path))
				{
					printf("%s info file deleted successfully\n",infoORmeta_file_with_info_folder_path);
				}
			}
			else
			{
				printf("%s is present at the corresponding source location\n",list_of_files[i]);
			}
	
		}
		free(file_name_with_destination_path);
		free(file_name_with_source_path);
		free(infoORmeta_file_with_info_folder_path);
	}	

	free(list_of_files);
	free(folder_name_with_source_path);
	free(folder_name_with_destination_path);
	free(info_folder_with_info_folder_path);
}

void delete_files_in_the_given_directory(char* given_folder_with_its_path)
{
	char **list_of_files;
	malloc_2d_string_array(&list_of_files);
	
	int number_of_files=get_list_of_files_in_the_given_folder(list_of_files, given_folder_with_its_path);
	//printf("\nNumber of files = %d", number_of_files);
	
	for (int i=0; i<number_of_files; i++)
	{
		char *file_in_the_given_folder_with_its_path;
		malloc_1d_array(&file_in_the_given_folder_with_its_path, FILE_LENGTH_WITH_PATH);
		
		char *slash="/";
		
		strcpy(file_in_the_given_folder_with_its_path,given_folder_with_its_path);// file_in_the_given_folder_with_its_path= givenFolderPath/givenFolderName
		strcat(file_in_the_given_folder_with_its_path, slash);// file_in_the_given_folder_with_its_path= givenFolderPath/givenFolderName/
		strcat(file_in_the_given_folder_with_its_path, list_of_files[i]);// file_in_the_given_folder_with_its_path= givenFolderPath/givenFolderName/list_of_files[i]
		
		if(is_file_a_directory(file_in_the_given_folder_with_its_path))//if the file is a subfolder
		{
			//delete all the internal files of the given subfolder
			delete_files_in_the_given_directory(file_in_the_given_folder_with_its_path);
			//after deleting all its internal files, delete it			
			if(FileExists(file_in_the_given_folder_with_its_path) && !_rmdir(file_in_the_given_folder_with_its_path))
			{
				printf("%s folder deleted successfully!\n",file_in_the_given_folder_with_its_path);
			}
		}
		else //if it is not a subfolder. rather is an internal file
		{
			//delete it
			if(FileExists(file_in_the_given_folder_with_its_path) && !remove(file_in_the_given_folder_with_its_path))
			{
				printf("%s file deleted successfully!\n",file_in_the_given_folder_with_its_path);
			}
		}
		free(file_in_the_given_folder_with_its_path);
	}
	free(list_of_files);
}
