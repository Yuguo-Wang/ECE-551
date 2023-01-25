#include "rand_story.h"

//function for opening a file and return it
FILE * open_temp(char * file) {
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    fprintf(stderr, "Error: Empty input file");
    exit(EXIT_FAILURE);
  }
  return f;
}

//function for replace a "_xx_" by cat in step1, and return the replaced line
char * replace_one_line(char * line, catarray_t * cat) {
  char * replace_line = NULL;
  size_t count = 0;

  //add every char into the replaced line
  while (*line != '\0') {
    if (*line != '_') {
      replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
      replace_line[count] = *line;
      line++;
      count++;
    }
    //when find the "_", find the next one and cross of it
    else {
      char * blank_left = line;
      char * blank_right = strchr(blank_left + 1, '_');

      //the "_" is not in pairs
      if (blank_right == NULL) {
        fprintf(stderr, "Error: no matching underscore");
        exit(EXIT_FAILURE);
      }

      char * old_word = strndup(blank_left, blank_right - blank_left);
      //In step1 cat is NULL
      const char * new_word = chooseWord(old_word, cat);  // cat

      while (*new_word != '\0') {
        replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
        replace_line[count] = *new_word;
        new_word++;
        count++;
      }

      line = blank_right + 1;
      free(old_word);
    }
  }
  //add '\0' at the last of the replaced line and return it
  replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
  replace_line[count] = '\0';

  printf("%s", replace_line);
  return replace_line;
}

//for step4, this function is to remove the same word, and return the fixed catarray_t cat
catarray_t * cat_unused(catarray_t * cat, char * category, const char * word) {
  if (cat == NULL || cat->n == 0) {
    fprintf(stderr, "Error: no category anymore");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < cat->n; i++) {
    if (strcmp(category, cat->arr[i].name) == 0) {
      for (size_t j = 0; j < cat->arr[i].n_words; j++) {
        if (strcmp(word, cat->arr[i].words[j]) == 0) {
          //remove this word, need free
          free(cat->arr[i].words[j]);
          for (size_t k = j; k < cat->arr[i].n_words - 1; k++) {
            cat->arr[i].words[k] = cat->arr[i].words[k + 1];
          }
          //the last place is needless, point to NULL
          cat->arr[i].words[cat->arr[i].n_words - 1] = NULL;
          cat->arr[i].n_words--;
          return cat;
        }
      }
    }
  }
  return cat;
}
//this function is to confirm whether the category is in the catarray_t cat
int check_category(char * category, catarray_t * cat) {
  for (size_t i = 0; i < cat->n; i++) {
    if (strcmp(category, cat->arr[i].name) == 0) {
      return 1;
    }
  }
  return 0;
}

//this function is to replace every "_xx_" and "_1(number)_" in one line and return the new line
char * replace_one_line_category(char * line, catarray_t * cat, bool used_permit) {
  char * replace_line = NULL;
  size_t count = 0;

  //use previous array to store the category that has been used
  char ** previous = NULL;
  size_t previous_len = 0;

  while (*line != '\0') {
    if (*line != '_') {
      replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
      replace_line[count] = *line;
      line++;
      count++;
    }
    else {
      char * blank_left = line;
      char * blank_right = strchr(blank_left + 1, '_');

      if (blank_right == NULL) {
        fprintf(stderr, "Error: no matching underscore");
        exit(EXIT_FAILURE);
      }

      char * category = strndup(blank_left + 1, blank_right - blank_left - 1);

      //in step3, the cat cannot be NULL, because we need a new word from function chooseword
      if (cat == NULL) {
        fprintf(stderr, "Error: the input of words file is invalid for step3");
        exit(EXIT_FAILURE);
      }

      if (check_category(category, cat)) {
        const char * new_word = chooseWord(category, cat);
        const char * temp = new_word;
        previous = realloc(previous, sizeof(*previous) * (previous_len + 1));
        previous[previous_len] = strdup(new_word);
        previous_len++;

        while (*new_word != '\0') {
          replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
          replace_line[count] = *new_word;
          new_word++;
          count++;
        }
        //in step 4, we use a boolean to confirm if we need to remove the overlapping word
        if (used_permit == true) {
          cat = cat_unused(cat, category, temp);
        }
      }
      //If the category is number, we need to make sure the first char is not "0", which is the rule of valid integer. And also make sure, between the "_", the inside string are all integer or vacuum(" ")
      else if (strspn(category, "0123456789") == strlen(category) &&
               strlen(category) != 0) {
        if (*category == '0') {
          fprintf(stderr, "the integer is invalid");
          exit(EXIT_FAILURE);
        }

        char * ptr;

        size_t n = strtol(category, &ptr, 10);

        //confirm that the integer cannot be more than the length of the previous array, otherwise, it is invalid.
        if (n > previous_len) {
          fprintf(stderr,
                  "Error, the integer is invalid, which is more than the previous words");
          exit(EXIT_FAILURE);
        }

        char * replace_one = previous[previous_len - n];

        previous = realloc(previous, sizeof(*previous) * (previous_len + 1));
        previous[previous_len] = strdup(replace_one);
        previous_len++;

        while (*replace_one != '\0') {
          replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
          replace_line[count] = *replace_one;
          replace_one++;
          count++;
        }
      }

      else {
        printf("%s", category);
        fprintf(stderr, "Error: there is an invalid format of '_xx_'");
        exit(EXIT_FAILURE);
      }

      line = blank_right + 1;
      free(category);
    }
  }
  //remember free the previous array after replacement
  for (size_t i = 0; i < previous_len; i++) {
    free(previous[i]);
  }

  free(previous);

  replace_line = realloc(replace_line, sizeof(*replace_line) * (count + 1));
  replace_line[count] = '\0';

  printf("%s", replace_line);
  return replace_line;
}

//this function is collecting the replaced line
void replace_all_line_category(char * file,
                               catarray_t * cat,
                               bool used_permit,
                               bool previous) {
  FILE * f = open_temp(file);
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    //difference of step1 and step3
    if (previous == false) {
      char * replace_line = replace_one_line(line, cat);
      free(replace_line);
    }
    else {
      char * replace_line = replace_one_line_category(line, cat, used_permit);
      free(replace_line);
    }
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Error: cannot close the file");
    exit(EXIT_FAILURE);
  }
}
//this function is to find the category in the file whose format is category:word
char * find_category(char * line) {
  char * colon = strchr(line, ':');
  if (colon == NULL) {
    fprintf(stderr, "Error: Wrong format of the line(find_category)");
    exit(EXIT_FAILURE);
  }
  char * category = strndup(line, colon - line);
  return category;
}

//this function is to find the word in the file whose format is category:word
char * find_word(char * line) {
  char * colon = strchr(line, ':');
  if (colon == NULL) {
    fprintf(stderr, "Error: Wrong format of the line(find_word)");
    exit(EXIT_FAILURE);
  }
  char * end = strchr(line, '\n');
  char * word = strndup(colon + 1, end - colon - 1);
  return word;
}

//store the category and word into a catarray_t struct
catarray_t * store_data(char * line, catarray_t * catarray) {
  char * category = find_category(line);
  char * word = find_word(line);

  // catagory has been added before
  for (size_t i = 0; i < catarray->n; i++) {
    if (strcmp(category, catarray->arr[i].name) == 0) {
      catarray->arr[i].words =
          realloc(catarray->arr[i].words,
                  sizeof(*catarray->arr[i].words) * (catarray->arr[i].n_words + 1));
      catarray->arr[i].words[catarray->arr[i].n_words] = word;
      catarray->arr[i].n_words++;

      free(category);  // aleady have this one
      return catarray;
    }
  }

  // no catagory existing, add it
  catarray->arr = realloc(catarray->arr, sizeof(*catarray->arr) * (catarray->n + 1));
  catarray->arr[catarray->n].name = category;
  catarray->arr[catarray->n].n_words = 1;
  catarray->arr[catarray->n].words = malloc(sizeof(*catarray->arr[catarray->n].words));
  catarray->arr[catarray->n].words[0] = word;
  catarray->n++;

  return catarray;
}

//this function is to return the answer of step2 that every category in the given file has several words
catarray_t * read_category_word(char * file) {
  FILE * f = open_temp(file);
  char * line = NULL;
  size_t sz = 0;

  catarray_t * category_words = malloc(sizeof(*category_words));
  category_words->arr = NULL;
  category_words->n = 0;
  while (getline(&line, &sz, f) >= 0) {
    category_words = store_data(line, category_words);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Error: cannot close the file");
    exit(EXIT_FAILURE);
  }
  return category_words;
}

//free the catarray_t
void free_catarray_t(catarray_t * catarray) {
  if (catarray == NULL) {
    fprintf(stderr, "Error: the catarray_t object does not exist");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < catarray->n; i++) {
    for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
      free(catarray->arr[i].words[j]);
    }
    free(catarray->arr[i].words);
    free(catarray->arr[i].name);
  }

  free(catarray->arr);
  free(catarray);
}
