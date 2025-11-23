#ifndef REGEX_LITE_H
#define REGEX_LITE_H

/* Returns 1 if text matches pattern, else 0.
   Supports: ^ $ . * ?  */
int Match(const char *pattern, const char *text);

#endif
