#include<stdio.h>
#include"types.h"

#define possize 6

typedef struct music 
{
    char *Filename;
    FILE *fptr_fname;
    
    char *Title;
    int Title_size;

    char *album;
    int Album_size;

    char *Artist;
    int Artist_size;

    char *Year;
    int Year_size;

    char *Genre;
    int Genre_size;

    char *Comment;
    int Com_size;

    int pos[possize];

}Music;

/*check operation type*/
Operation checkOperation(char **argv);

/*function to print*/
void printHelp();

/*To view all the info*/
Status viewInfo(Music *music);

/*to validate the file mp3 or not*/
Status readandvalidate(Music *music,char *argv);

/*To open files*/
Status openFiles(Music *music);

/*To check header and version */
Status checkheaderandversion(FILE *fname);

/*To readInfo*/
Status readInfo(Music *music);

/*to read tag*/
tags tagreader(FILE *fname);

/*To read tag size*/
Status tagsizereader(FILE *fname,int *size);

/*To read tag details*/
Status readtaginfo(FILE *fname,char **name,int size);

/*to print the information*/
Status printInfo(Music *music);