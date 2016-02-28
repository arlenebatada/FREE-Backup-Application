#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<direct.h>
#include<string>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include"commonfunctions.h"
#include"constants.h"


void malloc_2d_string_array(char*** variable_name)
{
	*variable_name = (char**)malloc(MAX_NUMBER_OF_FILES_IN_A_DIRECTORY * sizeof(char*));
	for (int i = 0; i < MAX_NUMBER_OF_FILES_IN_A_DIRECTORY; i++)
		(*variable_name)[i] = (char*)malloc((FILE_LENGTH) * sizeof(char)); 
}

void malloc_1d_array(char** variable_name, int size)
{
	if(!((*variable_name)=(char*)malloc(size*sizeof(char))))
	{
		perror("Memory allocation error :(\n\n Exiting...\n");
		exit(-1);
	}
}

int FileExists(const char *filename)
{
	if( access( filename, F_OK ) != -1 ) 
	{
    	return 1;
	} 
	else 
	{
	   return 0;
	}
}

int is_file_a_directory(char* file_name_with_path)
{
	struct stat file_stat;

    // if an error occurs, we return 0 for false
    if (stat(file_name_with_path, &file_stat) < 0) 
	{
        return 0;
    }

    // otherwise we return whatever the S_ISDIR returns
    return S_ISDIR(file_stat.st_mode);
}

int get_list_of_files_in_the_given_folder(char** list_of_files, char* folder_name_with_path)
{
	printf("\n\nInside \"%s\" \n", folder_name_with_path);
	
	char *slash="/";
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (folder_name_with_path)) != NULL) 
	{		// print all the files and directories within directory
		int i=0;
		while ((ent = readdir (dir)) != NULL) 
		{
			
			char* file_name_with_folder_name_with_path;
			malloc_1d_array(&file_name_with_folder_name_with_path, FILE_LENGTH_WITH_PATH);
			
			if(strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))//to prevent '.' & '..' folder names to be added to list_of_files
	  		 {
			  	strcpy(&list_of_files[i][0], ent->d_name);//consumed a lot of time to figure out the error
			  	
			  	strcpy(file_name_with_folder_name_with_path, folder_name_with_path);// file_name_with_folder_name_with_path = folder_name_with_path
				strcat(file_name_with_folder_name_with_path, slash);// file_name_with_folder_name_with_path = folder_name_with_path/
				strcat(file_name_with_folder_name_with_path, list_of_files[i]);//file_name_with_folder_name_with_path = folder_name_with_path/list_of_files[i]
			
			  	
		    	if(is_file_a_directory(file_name_with_folder_name_with_path))
		    	{
		    		printf ("%d. %s (folder)\n", i+1, list_of_files[i]);
		    	}
		    	else
		    	{
		    		printf ("%d. %s\n", i+1, list_of_files[i]);	
		    	}
				i++;			  	
			  }
			  free(file_name_with_folder_name_with_path);
		}
		closedir (dir);
		printf("\n");
		return i;
	} 
	else 
	{
		//could not open directory 
		perror ("ERROR");
		printf("\n");
		return -1;
	}
}
