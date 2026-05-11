#include "mp3_header.h"
void edit(struct MP3 *mp3,int argc,char *argv[])
{
    // command line arguments must be 5 otherwise gives the error message
    if(argc!=5)
    {
        printf("Enter the currect command\nTo get help pass like : ./a.out --help\n");
        return ;
    }
    // the file must be mp3 else error
    char *ret=strstr(argv[4],"mp3");
    if(ret==NULL)
    {
        printf("Enter the mp3 file\nTo get help pass like : ./a.out --help\n");
        return ;
    }
    // comparing the file name is it mp3 or not
    int ret1=strcmp(ret,"mp3");
    if(ret1!=0)
    {
        printf("its not mp3 file\nTo get help pass like : ./a.out --help\n");
        return;
    }

    printf("------------------------ SELECTED EDIT DETAILS -----------------------\n");
    char *tag;
    // tag must be match on these mp3 tags 
    if(strcmp(argv[2],"-t")==0)
    {
        tag="TIT2";
        printf("---------- Select title change option --------------- \n\n\tTITLE\t: ");
    }
    else if(strcmp(argv[2],"-a")==0)
    {
        tag="TPE1";
        printf("--------------------- Select Artist change option --------------------- \n\n\tARTIST\t: ");
    }
    else if(strcmp(argv[2],"-A")==0)
    {
        tag="TALB";
        printf("--------------------- Select ALBUM change option  ---------------------\n\n\tALBUM\t: ");
    }
    else if(strcmp(argv[2],"-y")==0)
    {
        tag="TYER";
        printf("--------------------- Select YEAR change option  ---------------------\n\n\tYEAR\t: ");
    }
    else if(strcmp(argv[2],"-m")==0)
    {
        tag="TCON";
        printf("--------------------- Select MUSIC change option  ---------------------\n\n\tMUSIC\t: ");
    }
    else if(strcmp(argv[2],"-c")==0)
    {
        tag="COMM";
        printf("--------------------- Select COMMENT change option  ---------------------\n\n\tOMMENT\t: ");
    }
    else
	{
		printf("To get help pass like : ./a.out --help\nEnter the valid command\n");
		return ;
	}
    char nname[50];
    strcpy(nname,argv[3]);// copying the name
    printf("%s\n",argv[3]);
    int size=strlen(nname)+1;// name and size
    
    // files opening 
    
    mp3->org_mp3_fptr=fopen(argv[4],"rb");// original file in read mode open
    mp3->dup_mp3_fptr=fopen("temp.mp3","wb");// temp file in write mode open
    char head[4];
    fread(&head,1,3,mp3->org_mp3_fptr);
    head[3]='\0';

    // checking is it mp3 file or not
    if(strcmp(head,"ID3")!=0)
    {
        printf("Its not mp3 file");
        return;
    }
    // reading 10 bytes of header
    char hed[11];
    rewind(mp3->org_mp3_fptr);
    fread(&hed,1,10,mp3->org_mp3_fptr);// reading 10 bytes header file
    fwrite(&hed,1,10,mp3->dup_mp3_fptr);// writing to temp file

    char TAG[5];
    char flag[4];
    for(int i=1; i<=6; i++)
    {
        fread(&TAG,1,4,mp3->org_mp3_fptr);
        TAG[4]='\0';
        fwrite(&TAG,1,4,mp3->dup_mp3_fptr);
        int ret=strcmp(tag,TAG);
        if(ret==0)
        {
            int lsize,bsize;
            fread(&lsize,sizeof(int),1,mp3->org_mp3_fptr);
            toggle_endianess(mp3,&lsize);
            bsize=size;
            toggle_endianess(mp3,&size);// new size LE to BE
            fwrite(&size,sizeof(int),1,mp3->dup_mp3_fptr);// writing the new size
            fread(&flag,1,3,mp3->org_mp3_fptr);
            fwrite(&flag,1,3,mp3->dup_mp3_fptr);
            nname[bsize]='\0';
            fwrite(&nname,sizeof(char),bsize-1,mp3->dup_mp3_fptr);// writing the new name to temp file
            flag[lsize];
            fread(&flag,sizeof(char),lsize-1,mp3->org_mp3_fptr);
        }
        else
        {
            int lsize,bsize;
            fread(&lsize,sizeof(int),1,mp3->org_mp3_fptr);
            toggle_endianess(mp3,&lsize);
            bsize=lsize;
            toggle_endianess(mp3,&bsize);
            fwrite(&bsize,sizeof(int),1,mp3->dup_mp3_fptr);
            flag[3];
            fread(&flag,sizeof(char),3,mp3->org_mp3_fptr);
            fwrite(&flag,sizeof(char),3,mp3->dup_mp3_fptr);
            char name[lsize];
            fread(&name,1,lsize-1,mp3->org_mp3_fptr);
            fwrite(&name,1,lsize-1,mp3->dup_mp3_fptr);
        }
    }
printf("\n------------------------ EDIT COMPLETED SUCCESSFULLY -----------------------\n");
    char ch;
    while(fread(&ch,sizeof(char),1,mp3->org_mp3_fptr))
    {
        fwrite(&ch,sizeof(char),1,mp3->dup_mp3_fptr);
    }

    fclose(mp3->org_mp3_fptr);
    fclose(mp3->dup_mp3_fptr);
    remove(argv[4]);// removing the  old file and rename using the library funtion
    rename("temp.mp3",argv[4]);
}

