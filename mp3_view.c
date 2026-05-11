#include "mp3_header.h"

void view(struct MP3 *mp3,int argc,char *argv[])
{

   if(argc!=3)
   {
      printf("To get help pass like : ./a.out --help \nUSAGE : To view please pass like: ./a.out -v mp3filename\n");
      return ;
   }
   char *ret1=strstr(argv[2],"mp3");
   if(ret1==NULL)
   {
      printf("Enter the mp3 file\nTo get help pass like : ./a.out --help\nUSAGE : To view please pass like: ./a.out -v mp3filename\n");
      return ;
   }

   int ret2=strcmp(ret1,"mp3");
   if(ret2!=0)
   {
      printf("Its not mp3 file\nUSAGE : To view please pass like: ./a.out -v mp3filename\n");
      return;
   }
   printf("------------------------SELECTED VIEW DETAILS-----------------------\n");
   printf("-------------------------------------------------------------------\n\t\tMP3 TAG READER AND EDITOR FOR ID3v2\n--------------------------------------------------------------------\n");
   mp3->org_mp3_fptr;
   
   mp3->org_mp3_fptr=fopen(argv[2],"r");
   
   if(mp3->org_mp3_fptr==NULL)
   {
    perror("ERROR");
    return;
   }
   char ch[5],ch1[]="ID3";
   fread(&ch,1,4,mp3->org_mp3_fptr);
   ch[3]='\0';
   int ret=strcmp(ch,ch1);

   if(ret!=0)
   {
    printf("its not MP3 file\n");
    perror("ERROR");
    return ;
   }
  
   rewind(mp3->org_mp3_fptr);
   
   fseek(mp3->org_mp3_fptr,10,SEEK_SET);
   

for(int j=1; j<=6;j++)
{
   // printing the tags title
   char TAG[5];
   fread(&TAG,sizeof(char),4,mp3->org_mp3_fptr);// TIT2 
   TAG[4]='\0';
   if(strcmp(TAG,"TIT2")==0)
   {
      printf("Title     :  ");
   }
   else if(strcmp(TAG,"TPE1")==0)
   {
      printf("Artist    :  ");
   }
   else if(strcmp(TAG,"TALB")==0)
   {
      printf("Album     :  ");
   }
   else if(strcmp(TAG,"TYER")==0)
   {
      printf("Year      :  ");
   }
   else if(strcmp(TAG,"TCON")==0)
   {
      printf("Music     :  ");
   }
   else if(strcmp(TAG,"COMM")==0)
   {
      printf("Comment   :  ");
   }
   
  
   // reading size no toggle indian byts typecasting is completed
   int csize;
   fread(&csize,sizeof(int),1,mp3->org_mp3_fptr);
   toggle_endianess(mp3,&csize);
   csize=csize-1;
   
   fseek(mp3->org_mp3_fptr,3,SEEK_CUR);
   print_tag_data(mp3,csize);
   
}
   fclose(mp3->org_mp3_fptr);
   printf("\n------------------------ DETAILS DISPLAYED SUCCESSFULLY -----------------------\n");
}

void print_tag_data(struct MP3 *mp3,int size)
{

   char name[size];
   fread(&name,sizeof(char),size,mp3->org_mp3_fptr);

   name[size]='\0';
   printf("%s\n",name);
   
}
