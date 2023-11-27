#include <stdio.h>
#include "edit.h"

int main(int argc, char *argv[])
{
    Music music;
    if (argc > 1)
    {
        if (checkOperation(argv) == Edit)
        {
            if (argc >= 4)
            {
                if (readandvalidate(&music, argv[4]) == success)
                {
                    editInfo(&music,argv[2],argv[3]);
                }
            }
            else
            {
                printf("\n...................................\n");
                printf("\n    please enter correct arguments \n");
                printf("\n......................................\n");
            }
        }
        else if (checkOperation(argv) == View)
        {
            if (readandvalidate(&music, argv[2]) == success)
            {
                viewInfo(&music);
            }
        }
        else if (checkOperation(argv) == Help)
        {
            printHelp();
        }
    }
    else
    {
        printf("\n........................................................\n\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE : \n");
        printf("To view use : ./a.out -v mp3filename\n");
        printf("To edit use : ./a.out -e  -t/-a/-A/-m/-y/-c mp3filename\n");
        printf("To get help use : ./a.out --help\n");
        printf("\n........................................................\n\n");
    }
}