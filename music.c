#include <stdio.h>
#include "music.h"
#include <string.h>
#include <stdlib.h>

Operation checkOperation(char **argv)
{
    if (strcmp(argv[1], "-e") == 0)
        return Edit;
    else if (strcmp(argv[1], "-v") == 0)
        return View;
    else
        return Help;
}

void printHelp()
{
    printf("\n.............Help Menu.....................\n\n");
    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf(" 2.1. -t -> to edit song title\n");
    printf(" 2.2. -a -> to edit artist name\n");
    printf(" 2.3. -A -> to edit album name\n");
    printf(" 2.4. -y -> to edit song year\n");
    printf(" 2.5. -m -> to edit song content\n");
    printf(" 2.6. -c -> to edit song comment\n");
    printf("\n............................................\n\n");
}

Status readandvalidate(Music *music, char *arg)
{
    if (strcmp(strstr(arg, "."), ".mp3") == 0)
    {
        music->Filename = arg;
        return success;
    }
    else
    {
        printf("\n..................................\n\n");
        printf("ERROR: Mp3 File Type only\n");
        printf("\n..................................\n\n");
    }
}

Status openFiles(Music *music)
{
    music->fptr_fname = fopen(music->Filename, "rb+");
    if (music->fptr_fname == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", music->Filename);
        return failure;
    }
    return success;
}

Status checkheaderandversion(FILE *fname)
{
    char head[4];
    char ver[2];
    fread(head, 3, 1, fname);
    head[3] = '\0';
    fread(ver, 2, 1, fname);
    if (strcmp(head, "ID3") == 0 && ver[0] == 0x03 && ver[1] == 0x00)
    {
        return success;
    }
    return failure;
}

Status viewInfo(Music *music)
{
    if (openFiles(music) == success)
    {
        if (checkheaderandversion(music->fptr_fname) == success)
        {
            if (readInfo(music) == success)
            {
                printInfo(music);
            }
        }
    }
}

Status readInfo(Music *music)
{
    rewind(music->fptr_fname);
    fseek(music->fptr_fname, 10, SEEK_CUR);
    for (int i = 0; i < 6; i++)
    {
        tags t = tagreader(music->fptr_fname);
        switch (t)
        {
        case m_title:
            music->pos[m_title]=ftell(music->fptr_fname);
            tagsizereader(music->fptr_fname, &music->Title_size);
            fseek(music->fptr_fname, 3, SEEK_CUR);
            readtaginfo(music->fptr_fname, &music->Title, music->Title_size);
            break;
        case m_album:
            music->pos[m_album]=ftell(music->fptr_fname);
            tagsizereader(music->fptr_fname, &music->Album_size);
            fseek(music->fptr_fname, 3, SEEK_CUR);
            readtaginfo(music->fptr_fname, &music->album, music->Album_size);
            break;
        case m_artist:
            music->pos[m_artist]=ftell(music->fptr_fname);
            tagsizereader(music->fptr_fname, &music->Artist_size);
            fseek(music->fptr_fname, 3, SEEK_CUR);
            readtaginfo(music->fptr_fname, &music->Artist, music->Artist_size);
            break;
        case m_year:
            music->pos[m_year]=ftell(music->fptr_fname);
            tagsizereader(music->fptr_fname, &music->Year_size);
            fseek(music->fptr_fname, 3, SEEK_CUR);
            readtaginfo(music->fptr_fname, &music->Year, music->Year_size);
            break;
        case m_genre:
            music->pos[m_genre]=ftell(music->fptr_fname);
            tagsizereader(music->fptr_fname, &music->Genre_size);
            fseek(music->fptr_fname, 3, SEEK_CUR);
            readtaginfo(music->fptr_fname, &music->Genre, music->Genre_size);
            break;
        case m_comment:
            music->pos[m_comment]=ftell(music->fptr_fname);
            tagsizereader(music->fptr_fname, &music->Com_size);
            fseek(music->fptr_fname, 3, SEEK_CUR);
            readtaginfo(music->fptr_fname, &music->Comment, music->Com_size);
            break;
        default:
            break;
        }
    }
    return success;
}

Status printInfo(Music *music)
{

    printf("\n........................Selected View Details...................\n");
    printf("\n................................................................\n");
    printf("\n                MP3 TAG READER AND EDITOR FOR ID3v2          \n");
    printf("\n................................................................\n\n");
    printf("TITLE          : %s \n", music->Title);
    printf("ARTIST         : %s \n", music->Artist);
    printf("ALBUM          : %s \n", music->album);
    printf("YEAR           : %s \n", music->Year);
    printf("MUSIC          : %s \n", music->Genre);
    printf("COMMENT        : %s \n", music->Comment);
    printf("\n................................................................\n\n");
    return success;
}

tags tagreader(FILE *fname)
{
    char tag[4 + 1];
    fread(tag, 4, 1, fname);
    tag[4] = '\0';
    if (strcmp(tag, "TIT2") == 0)
        return m_title;
    else if (strcmp(tag, "TALB") == 0)
        return m_album;
    else if (strcmp(tag, "TPE1") == 0)
        return m_artist;
    else if (strcmp(tag, "TYER") == 0)
        return m_year;
    else if (strcmp(tag, "TCON") == 0)
        return m_genre;
    else if (strcmp(tag, "COMM") == 0)
        return m_comment;
}

Status tagsizereader(FILE *fname, int *size)
{
    char ch;
    *size = 0;
    for (int i = 0; i < 4; i++)
    {
        fread(&ch, 1, 1, fname);
        *size = *size << i * 8 | ch;
    }
    *size = *size - 1;
}

Status readtaginfo(FILE *fname, char **name, int size)
{
    char *buffer = malloc(size + 1);
    fread(buffer, size, 1, fname);
    buffer[size] = '\0';
    *name = malloc(size + 1);
    strcpy(*name, buffer);
    free(buffer);
}