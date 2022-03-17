/*
** EPITECH PROJECT, 2022
** My_defender
** File description:
** error_handling
*/

#ifndef ERROR_HANDLING_H_
    #define ERROR_HANDLING_H_

    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include "lib.h"

int is_a_file(char *name);
int has_correct_size(int correct_size, char *file);
int string_is_valid_nbr(char *name);
int error_handling(void);

#endif /* !ERROR_HANDLING_H_ */
