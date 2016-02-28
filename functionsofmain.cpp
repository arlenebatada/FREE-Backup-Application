#include <stdio.h>

void display_options_with_their_description()
{
		printf("\n\nPRESS:\n\t1. for \" EXACTLY AS IN SOURCE \"\n\t2. for \" BACKUP \"\n");
		printf("\n1. EXACTLY AS IN SOURCE:\nIt'll make Destination folder exactly like the Source folder.\n");
		printf("If any file is created/edited in the Source, it'll be copied to the Destination.");
		printf("If any file is deleted from the Source, it \"WILL\" be deleted from the Destination as well.\n");
		
		printf("\n2. BACKUP:\nIf any file is created/edited in the Source, it'll be copied to the Destination.");
		printf("If any file is deleted from the Source, it'll \"NOT\" be deleted from the Destination.\n");
}
