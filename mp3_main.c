#include "mp3_header.h"

#if 0
NAME : H MANJUNATHA
DATE : 01/05/2026
->The MP3 Tag Reader project metadata stored in MP3 audio files, specifically ID3 tags
->These tags contains  imporatant indormations  such as song title, artist name, album, year, genre, and comments.
->The program reads MP3 files in binary mode and extracts ID3 tag information
->User can view the tag deatails and it provides an edit feature where users can update tags like song name or artist directly within the file
->The challenge i faced in this project was implementing the edit ,function 
->Accurately locating the correct tag fields
->Handling fixed-size and variable-size data carefully improper byte alignment and pointer handling.
->o overcome this, the logic was improved by precisely locating tag positions, safely overwriting data,alignement.
Proper validation and debugging techniques were applied to ensure that only intended fields were modified without affecting the rest of the file
#endif
int main(int argc, char *argv[])
{
    /* structure variable declaration */
    struct MP3 mp3;

   int ret = validate_cla(argc,argv,&mp3);
    if(ret == VIEW)
    {
 	view(&mp3,argc,argv);
    }
    else if(ret == EDIT)
    {
    edit(&mp3,argc,argv);
    }

    return 0;
}

