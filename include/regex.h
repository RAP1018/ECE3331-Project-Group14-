#ifndef REGEX_LITE_H
#define REGEX_LITE_H

#include <stdio.h>

/* Returns 1 if text matches pattern, else 0.
   Supported: ^ $ . * ?  (tiny per project spec) */
int Match(const char *pattern, const char *text);

/* Read from an already-open FILE* line-by-line, apply Match(), print matches.
   Returns 0 on success, 1 on error. */
int search_file(FILE *fin, const char *pattern);

#endif
