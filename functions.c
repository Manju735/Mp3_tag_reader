#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    if( argc == 1 )
    {
	printf("------------------------------------------------------------------------------\n");
	printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
	printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help pass like : ./a.out --help\n");
	printf("------------------------------------------------------------------------------\n");
	return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) )
    {
	printf("------------------------------->HELP<-----------------------------------------\n");
	printf("1. -v -> to view mp3 file contents\n");
	printf("2. -e -> to edit mp3 file contents\n");
	printf("\t\t2.1. -t -> to edit song title\n");
	printf("\t\t2.2. -a -> to edit artist name\n");
	printf("\t\t2.3. -A -> to edit album name\n");
	printf("\t\t2.4. -y -> to edit year\n");
	printf("\t\t2.5. -m -> to edit content\n");
	printf("\t\t2.6. -c -> to edit comment\n");
	printf("------------------------------------------------------------------------------\n");
	return 0; 
    }

    if(!strcmp(argv[1], "-v"))
    {
	// Do the necessary validation
	return VIEW;
    }
    else if(!strcmp(argv[1], "-e"))
    {
	// Do the necessary validation
	return EDIT;
    }
	else
	{
		printf("To get help pass like : ./a.out --help\nEnter the valid command\n");
		return 0;
	}


}


void toggle_endianess(struct MP3 *mp3, int *size)
{
	unsigned char *ch;
	// from the integer to character type casted to swap the bytes
	ch=(char *)size; // typecasting  to charater pointer to swap the byts
	int s=4;
	
	// finding the toggle endinness
	for(int i=0; i<s/2; i++)
	{
		int temp=ch[i];
		ch[i]=ch[s-i-1];
		ch[s-i-1]=temp;
	}
	*size=*(int*)ch;
}
