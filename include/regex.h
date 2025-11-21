#ifndef REGEX_LITE_H
#define REGEX_LITE_H

/* Returns 1 if text matches pattern, else 0.
   Supported: ^ $ . * ?  (tiny per project spec) */
int Match(const char *pattern, const char *text);

#endif
