#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<direct.h>
#include<string>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include"backupfunctions.h"
#include"constants.h"
#include"commonfunctions.h"

void backup(char* folder_name, char* source_path, char* destination_path, char* info_folder_path)
{ 
	//2D array to store list of all files in the given directory
	char **list_of_files;
	malloc_2d_string_array(&list_of_files);
		
	char *slash="/", *info=".info";
	
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
	
	if (!FileExists(folder_name_with_destination_path) && _mkdir(folder_name_with_destination_path)==0)//create destination directory if it does not exist 
	{
		//printf("\nDestination Directory successfully created at %s\n", folder_name_with_destination_path);
	}
	
	if(!FileExists(info_folder_with_info_folder_path) && _mkdir(info_folder_with_info_folder_path)==0)//Create info directory if it does not exist 
	{
		//printf("\ninfo Directory successfully created at %s\n", info_folder_with_info_folder_path);
	}
   	
	int number_of_files=get_list_of_files_in_the_given_folder(list_of_files, folder_name_with_source_path);
	//printf("\nNumber of files = %d", number_of_files);
		
	for (int i=0; i<number_of_files; i++)
	{
		char *file_name_with_source_path;
		malloc_1d_array(&file_name_with_source_path, FILE_LENGTH_WITH_PATH);
		
		strcpy(file_name_with_source_path,folder_name_with_source_path);// file_name_with_source_path= sourcePath/sourceFolderName
		strcat(file_name_with_source_path, slash);// file_name_with_source_path= sourcePath/sourceFolderName/
		strcat(file_name_with_source_path, list_of_files[i]);// file_name_with_source_path= sourcePath/sourceFolderName/list_of_files[i]
		
		if(is_file_a_directory(file_name_with_source_path))
		{
			free(file_name_with_source_path);
			backup(list_of_files[i], folder_name_with_source_path, folder_name_with_destination_path, info_folder_with_info_folder_path);
		}
		else
		{
			free(file_name_with_source_path);
			copy_file(list_of_files[i], source_path, destination_path, folder_name, info_folder_path);
		}
	}
	
	free(list_of_files);
	free(folder_name_with_source_path);
	free(folder_name_with_destination_path);
	free(info_folder_with_info_folder_path);
}

void copy_file(char* file_name, char* source_path, char* destination_path, char* folder_name, char* info_folder_path)
{
   	char *info=".info", *slash="/", *meta =".meta";
   	
	char*  file_name_with_destination_path;
	malloc_1d_array(&file_name_with_destination_path, FILE_LENGTH_WITH_PATH);
	
	char*  file_name_with_source_path;
	malloc_1d_array(&file_name_with_source_path, FILE_LENGTH_WITH_PATH);
	
	char*  info_folder_with_info_folder_path;
	malloc_1d_array(&info_folder_with_info_folder_path, FILE_LENGTH_WITH_PATH);
	
	char*  folder_name_with_destination_path;
	malloc_1d_array(&folder_name_with_destination_path, FILE_LENGTH_WITH_PATH);
	
	char*  meta_file_location;
	malloc_1d_array(&meta_file_location, FILE_LENGTH_WITH_PATH);   	
   	
   	strcpy(file_name_with_destination_path, destination_path); //copying destination path
   	strcat(file_name_with_destination_path, slash); //appending '/'
   	strcat(file_name_with_destination_path, folder_name);//  destinationPath/destinationFoldername
   	
	strcpy(folder_name_with_destination_path, file_name_with_destination_path); //copying destinationPath/destinationFoldername
   	
	strcat(file_name_with_destination_path, slash); // destinationPath/destinationFoldername/
   	strcat(file_name_with_destination_path, file_name); // destinationPath/destinationFoldername/destinationFilename
   	   	
   	strcpy(info_folder_with_info_folder_path, info_folder_path);//copying infoFolderPath
	strcat(info_folder_with_info_folder_path, slash);//appending '/'
	strcat(info_folder_with_info_folder_path, folder_name); // infoFolderPath/infoFolderName
	strcat(info_folder_with_info_folder_path, info);// infoFolderPath/infoFolderName.info
   	
   	strcpy(meta_file_location, info_folder_with_info_folder_path);// meta_file_location = infoFolderPath/infoFolderName.info
   	strcat(meta_file_location, slash); //meta_file_location = infoFolderPath/infoFolderName.info/
	strcat(meta_file_location, file_name); //meta_file_location = infoFolderPath/infoFolderName.info/fileName
	strcat(meta_file_location, meta); //meta_file_location = infoFolderPath/infoFolderName.info/fileName.meta
	   	
	strcpy(file_name_with_source_path, source_path); // copying source path
   	strcat(file_name_with_source_path, slash); // appending '/'
   	strcat(file_name_with_source_path, folder_name);//  sourcePath/sourceFoldername
   	strcat(file_name_with_source_path, slash); // sourcePath/sourceFoldername/
   	strcat(file_name_with_source_path, file_name);// sourcePath/sourceFoldername/sourceFilename
   	
   	  	
	if (!FileExists(file_name_with_source_path)) //Return if sourcePath/sourceFoldername/sourceFilename does not exist
   	{
   		printf("%s is invalid input path or file name\n", file_name_with_source_path);
   		return;
   	}
   	
   	
   	if (!FileExists(file_name_with_destination_path)) // If destination file does not exist
   	{
   		printf("\n%s is not available at the desination so copying it...\n\n", file_name_with_destination_path);
   		  	
   		if(!FileExists(info_folder_with_info_folder_path) && _mkdir(info_folder_with_info_folder_path)==0)//Create info directory if it does not exist 
		{
			//printf("\ninfo Directory successfully created at %s\n", info_folder_with_info_folder_path);
		}
		
		
		if (!FileExists(folder_name_with_destination_path) && _mkdir(folder_name_with_destination_path)==0)//create destination directory if it does not exist 
		{
			//printf("\nDestination Directory successfully created at %s\n", folder_name_with_destination_path);
		}
				
   		
		//backing up source file
		copy_source_file_to_the_destination(file_name, file_name_with_source_path, file_name_with_destination_path);
			
		//Gathering modified time information of the source file
		char timbuf[19];
		get_modified_time_of_the_source_file(file_name_with_source_path, timbuf);
		
		//writing modified time info of the source file to the corresponding meta file
		create_meta_file(timbuf, meta_file_location, 0);
			
   	}
	else //if destination file exists
	{
		printf("\n%s is available at the desination so checking if the source file has been updated...\n\n", file_name);
		
		//Gathering modified time information of the source file
		char timbuf[19];
		get_modified_time_of_the_source_file(file_name_with_source_path, timbuf);
		
		if(!FileExists(info_folder_with_info_folder_path)) //dest file exists but info folder does not exist
		{
			//printf("infouration folder not found. Creating infouration folder & the infouration file corresponding to the given file\n\n");
			if(_mkdir(info_folder_with_info_folder_path)==0)
			{
				//printf("infouration folder created successfully\n\n");
			}
			
			//writing modified time info of the source file to the corresponding meta file
			create_meta_file(timbuf, meta_file_location, 0);
			
			//Copying the original file
			copy_source_file_to_the_destination(file_name, file_name_with_source_path, file_name_with_destination_path);
			
		}
		else //dest file exists & info folder available
		{
			//printf("infouration folder found\n\n");
			if(!FileExists(meta_file_location)) //dest file exists + info folder BUT NOT meta file
			{
				//printf("%s not found\n\n", meta_file_location);
				
				//writing modified time info of the source file to the corresponding meta file
				create_meta_file(timbuf, meta_file_location, 0);
				
				//backup source file
				copy_source_file_to_the_destination(file_name, file_name_with_source_path, file_name_with_destination_path);
				
				
			}
			else //dest file exists + info folder + meta file
			{
				//printf("%s found\n\n", meta_file_location);
				
				char ftimbuf[19]; //to store meta data retrieved from meta file
				get_meta_info_from_the_meta_file(meta_file_location, ftimbuf);
				
				if(!strncmp(timbuf, ftimbuf, 19)) //Checking if 'modified time' recorded in the meta file & that given in the source file are same
				{
					//timbuf & ftimbuf are same
					printf("No updates found \n\n");
				}
				else //timbuf & ftimbuf are different. Means the source file has been modified
				{
					printf("%s has been modified\n\n", file_name);
					
					//backup source file
					copy_source_file_to_the_destination(file_name, file_name_with_source_path, file_name_with_destination_path);
					
					//create meta file
					create_meta_file(timbuf, meta_file_location, 1);
				}
			}
		}
		
		
		
	}
	free(file_name_with_destination_path);
   	free(file_name_with_source_path);
   	free(info_folder_with_info_folder_path);
   	free(folder_name_with_destination_path);
   	free(meta_file_location);
   	
   	
}



void create_meta_file(char* timbuf, char* meta_file_location, int choice)
{
	FILE * meta_file_pointer=fopen(meta_file_location, "wb");//meta_file_pointer points to destinationPath/destinationFoldername.info/fileName.meta
	fwrite(timbuf, sizeof(char), 19*sizeof(char), meta_file_pointer);//writing time information of the given file into the meta file
	fclose(meta_file_pointer);
	if (choice==0)
	{
		//printf("%s created successfully!\n\n", meta_file_location);	
	}
	else
	{
		//printf("%s modified successfully!\n\n", meta_file_location);	
	}
}

void get_modified_time_of_the_source_file(char* file_name_with_source_path, char* timbuf)
{
	struct stat attrib; //attrib is a stat. stat can have all the attributes of a file 
	stat (file_name_with_source_path, &attrib); // attrib now has all the attributes of the given file name
	time_t t=attrib.st_mtime; // time_t can store 'time' attribute of 'attrib' stat. st_mtime=modified time.
	struct tm* lt;//tm is a local time
	lt=localtime(&t);
	strftime(timbuf, 19*sizeof(char), "%c", lt); //timbuff size is 19. Writing local time into timbuf as array of char
	printf("%s last modified on= %s\n\n", file_name_with_source_path, timbuf);
}

void copy_source_file_to_the_destination(char* file_name, char* file_name_with_source_path, char* file_name_with_destination_path)
{
	char buf[BUFSIZ];
	size_t size;
	FILE *fp1 = fopen(file_name_with_source_path, "rb"); // fp1 points to sourcePath/sourceFoldername/sourceFilename
	FILE *fp2 = fopen(file_name_with_destination_path, "wb");// fp3 points to destinationPath/destinationFoldername/destinationFilename
						
	printf("Copying %s to %s\n\n", file_name_with_source_path, file_name_with_destination_path);
	int dot_time=0;
	while (size = fread(buf, sizeof(char), BUFSIZ, fp1)) //copying source file to destination file 
	{
		if (dot_time%100000==0)
		{
			printf(".");	//Dots to display progress to the user
		}
	   	fwrite(buf, sizeof(char), size, fp2);
	   	dot_time++;
	}
	   	printf("\n");
	   	printf("Copy Successful!\n\n", file_name, file_name_with_source_path, file_name_with_destination_path);
	fclose(fp1);
   	fclose(fp2);
}
void get_meta_info_from_the_meta_file(char* meta_file_location, char* ftimbuf)
{
	FILE * meta_file_pointer=fopen(meta_file_location, "rb");//meta_file_pointer points to destinationPath/destinationFoldername.info/fileName.meta
	fread(ftimbuf, sizeof(char), 19, meta_file_pointer);//reading from meta file & storing it into ftimbuff. size=19
	fclose(meta_file_pointer);
	//printf("Source file modification time in the meta file= %s\n\n", ftimbuf);
}
