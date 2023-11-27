#include<stdio.h>
#include"music.h"


/*edit file info*/
Status editInfo(Music *music,char *ch,char *name);

Status renametag(Music *music,char *ch,char *name,FILE *fptr_dest);

Status copyheader(FILE *fname,FILE *fptr_dest);

edittags checkedit(char *ch);

Status copyContent(FILE *fname,int pos,FILE *fptr_dest);

Status copynewcon(FILE *fname,char *name,FILE *fptr_dest);

Status copyremaining(FILE *fname,int size,FILE *fptr_dest);

Status copytoriginal(FILE *fname,FILE *fptr_dest);