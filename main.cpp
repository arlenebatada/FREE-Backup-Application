#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<direct.h>
#include<string>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<dirent.h>
#include "backupfunctions.h"
#include "cleanupfunctions.h"
#include"commonfunctions.h"
#include "functionsofmain.h"


int main()
{
	char cont='y';
	char folder_name[FILE_LENGTH];
	char source_path[FILE_LENGTH_WITH_PATH], destination_path[FILE_LENGTH_WITH_PATH];
	char folder_name_with_source_path[FILE_LENGTH_WITH_PATH];
	printf("\n\tWelcome to FREE Backup Application created by Arlene Batada\n\n");
	
	while(cont=='y' || cont=='Y')
	{
		system("cls");
		printf("\n\tWelcome to FREE Backup Application created by Arlene Batada\n\n");
		printf("Let's say you wish to backup folder named 'abc' from C drive (C:) into a folder named '123' which is located in D drive (D:/123).");
		printf(" Then enter folder name=abc ,  source path= C: , destination path= D:/123\n\n");
		printf("\nEnter the folder name: \n");
		gets(folder_name);
		printf("\nPlease enter the path where your source folder is located:\n");
		gets(source_path);
	  	printf("\nPlease enter the path where your destination folder \nis located (or is to be created):\n");
		gets(destination_path);
		strcpy(folder_name_with_source_path, source_path);
		strcat(folder_name_with_source_path,"/");
		strcat(folder_name_with_source_path, folder_name);
		if(!FileExists(folder_name_with_source_path))//checking if source folder exists 
		{
			printf("%s\n", folder_name_with_source_path);
			perror ("\007ERROR");
			printf("\n");
			_getch();
			continue ;
			
		}
	
		if (!FileExists(destination_path))//checking if destination path exists 
		{
			
			printf("%s\n", destination_path);
			perror ("\007ERROR");
			printf("\n");
			_getch();
			continue ;
			
		}
		
		if(!strcmp(source_path, destination_path)) //checking if source & destination are not equal
		{
			printf("\n\007Source can NOT be the destination");
			_getch();
			continue;
		}
		
		display_options_with_their_description();
		
		
		char choice=_getch();
		
		if(choice=='1')
		{
			printf("\n-----------------------PERFORMING 'EXACTLY AS IN SOURCE'------------------------");
			printf("--------------------------------------------------------------------------------\n");
			backup(folder_name, source_path, destination_path, destination_path);
			cleanup(folder_name, source_path, destination_path, destination_path);
			printf("\n\n'EXACTLY AS IN SOURCE' completed!!\001\007\n");
		}
		else if (choice=='2')
		{
			printf("\n-----------------------------PERFORMING 'BACKUP'--------------------------------");
			printf("--------------------------------------------------------------------------------\n");
			backup(folder_name, source_path, destination_path, destination_path);
			printf("\n\n'BACKUP' completed!!\001\007\n");
		}
		else
		{
			printf("\n\007Invalid choice\n");
		}
		printf("Do you wish to continue? (y/n)\n");
		cont=_getch();
		if(cont!='y' && cont!='Y' && cont!='n' && cont!='N')
		{
			printf("\nI'll take that as a NO\n");
		}
	}
	printf("\n\007Your feedback and suggestions are always welcomed at arlenebatada@ymail.com\n");
	printf("\nGood Bye! Come back soon! \001\n");
	_getch();
	return 0;
}
