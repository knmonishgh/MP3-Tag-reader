#include "edit.h"
#include <string.h>
Status editInfo(Music *music, char *ch, char *name)
{
    if (openFiles(music) == success)
    {
        FILE *fptr_dest = fopen("sample.mp3", "wb+");
        if (fptr_dest == NULL)
        {
            perror("fopen");
            fprintf(stderr, "ERROR: Unable to open file %s\n", "sample.mp3");

            return failure;
        }
        if (checkheaderandversion(music->fptr_fname) == success)
        {
            if (readInfo(music) == success)
            {
                renametag(music, ch, name, fptr_dest);
                copytoriginal(music->fptr_fname, fptr_dest);
            }
        }
    }
}

Status renametag(Music *music, char *ch, char *name, FILE *fptr_dest)
{
    if (copyheader(music->fptr_fname, fptr_dest) == success)
    {
        switch (checkedit(ch))
        {
        case t:
            copyContent(music->fptr_fname, music->pos[m_title], fptr_dest);
            copynewcon(music->fptr_fname, name, fptr_dest);
            copyremaining(music->fptr_fname, music->Title_size, fptr_dest);
            break;
        case a:
            copyContent(music->fptr_fname, music->pos[m_album], fptr_dest);
            copynewcon(music->fptr_fname, name, fptr_dest);
            copyremaining(music->fptr_fname, music->Album_size, fptr_dest);
            break;
        case A:
            copyContent(music->fptr_fname, music->pos[m_artist], fptr_dest);
            copynewcon(music->fptr_fname, name, fptr_dest);
            copyremaining(music->fptr_fname, music->Artist_size, fptr_dest);
            break;
        case y:
            copyContent(music->fptr_fname, music->pos[m_year], fptr_dest);
            copynewcon(music->fptr_fname, name, fptr_dest);
            copyremaining(music->fptr_fname, music->Year_size, fptr_dest);
            break;
        case m:
            copyContent(music->fptr_fname, music->pos[m_genre], fptr_dest);
            copynewcon(music->fptr_fname, name, fptr_dest);
            copyremaining(music->fptr_fname, music->Genre_size, fptr_dest);
            break;
        case c:
            copyContent(music->fptr_fname, music->pos[m_comment], fptr_dest);
            copynewcon(music->fptr_fname, name, fptr_dest);
            copyremaining(music->fptr_fname, music->Com_size, fptr_dest);
            break;
        default:
            break;
        }
    }
    return success;
}

Status copyContent(FILE *fname, int pos, FILE *fptr_dest)
{
    char ch;
    for (int i = 10; i < pos; i++)
    {
        fread(&ch, 1, 1, fname);
        fwrite(&ch, 1, 1, fptr_dest);
    }
}

Status copynewcon(FILE *fname, char *name, FILE *fptr_dest)
{
    int len = strlen(name) + 1;
    char bytes[4];
    for (int i = 0; i < 4; i++)
    {
        bytes[3 - i] = ((len >> 8 * i) & 0xFF);
    }
    fwrite(bytes, 4, 1, fptr_dest);
    fseek(fname, 4, SEEK_CUR);
    char buffer[3];
    fread(buffer, 3, 1, fname);
    fwrite(buffer, 3, 1, fptr_dest);
    fwrite(name, len - 1, 1, fptr_dest);
    return success;
}

Status copyremaining(FILE *fname, int size, FILE *fptr_dest)
{
    fseek(fname, size, SEEK_CUR);
    char ch;
    while (fread(&ch, 1, 1, fname))
    {
        fwrite(&ch, 1, 1, fptr_dest);
    }
    return success;
}

Status copyheader(FILE *fname, FILE *fptr_dest)
{
    rewind(fname);
    char buffer[10];
    fread(buffer, 10, 1, fname);
    fwrite(buffer, 10, 1, fptr_dest);
    return success;
}

Status copytoriginal(FILE *fname, FILE *fptr_dest)
{
    rewind(fname);
    rewind(fptr_dest);
    char ch;
    while (fread(&ch, 1, 1, fptr_dest) > 0)
    {
        fwrite(&ch, 1, 1, fname);
    }
    fclose(fptr_dest);
    remove("sample.mp3");
    return success;
}

edittags checkedit(char *ch)
{
    if (!strcmp(ch, "-t"))
        return t;
    else if (!strcmp(ch, "-a"))
        return a;
    else if (!strcmp(ch, "-A"))
        return A;
    else if (!strcmp(ch, "-y"))
        return y;
    else if (!strcmp(ch, "-m"))
        return m;
    else if (!strcmp(ch, "-c"))
        return c;
}

