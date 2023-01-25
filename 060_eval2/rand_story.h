#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use
FILE * open_temp(char * file);

char * replace_one_line(char * line, catarray_t * cat);

//void replace_all_lines(char * file, catarray_t * cat);

catarray_t * store_data(char * line, catarray_t * catarray);

catarray_t * read_category_word(char * file);

void free_catarray_t(catarray_t * catarray);

int check_category(char * category, catarray_t * cat);
char * replace_one_line_category(char * line, catarray_t * cat, bool used_permit);
void replace_all_line_category(char * file,
                               catarray_t * cat,
                               bool used_permit,
                               bool previous);
catarray_t * cat_unused(catarray_t * cat, char * category, const char * word);
#endif
