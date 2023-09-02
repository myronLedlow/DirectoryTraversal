#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/*

        Compile/Exec Instructions
        -------------------------

        To compile:
                gcc -o dir_trav dir_traversal.c

        To run:

                ./dir_trav <directory name>

*/

/* declare function prototypes */

typedef int func(char *var);

/* declare functions with function pointers to their respective prototypes */
int usr_func(char *var, func *f);

int usr_func(char *var, func *f)
{

        return f(var);
}

int displ_1(char *var);

int displ_1(char *var)
{

        printf("\n%s\n", var);
        printf("\n");
        return 0;
}

int trav(char *dirname)
{

        DIR *parentDir;
        struct dirent *dirent;
        char fullname[BUFSIZ];

        /* open directory if there's one there */
        if ((parentDir = opendir(dirname)) == NULL)
        {
                return (-1);
        }

        /* read directory while any left to read */
        while ((dirent = readdir(parentDir)) != NULL)
        {
                if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
                        continue;

                /* If directory */
                if (dirent->d_type == DT_DIR)
                {

                        /* copy dir name, call display function, build path, traverse directory */

                        strcpy(fullname, dirname);
                        usr_func(dirent->d_name, displ_1);
                        strcat(fullname, "/");
                        strcat(fullname, dirent->d_name);
                        trav(fullname);
                }

                else
                {
                        usr_func(dirent->d_name, displ_1);
                }
        }

        closedir(parentDir);

        return 0;
}

int main(int argc, char **argv)
{
        int trav_val;
        /* If only one argument, exit */
        if (argc < 2)
        {
                printf("Usage: %s <dirname>\n", argv[0]);
                exit(-1);
        }

        if ((trav_val = trav(argv[1])) == -1)
        {
                printf("\n%s\n", "Error opening directory...");
        }
        return 0;
}
