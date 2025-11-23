// regex.c — tiny engine with ^ $ . * ?  (simple and short)
#include <stdio.h>
#include <string.h>
#include "regex.h"

static int match_here(const char *p, const char *t);

/* Try pattern anywhere unless it starts with ^ */
int Match(const char *pattern, const char *text) {
    if (!pattern || !text) return 0;

    if (pattern[0] == '^') {
        return match_here(pattern + 1, text);
    }
    do {
        if (match_here(pattern, text)) return 1;
    } while (*text++ != '\0');
    return 0;
}

/* Core recursive matcher */
static int match_here(const char *p, const char *t) {
    if (*p == '\0') return 1;                              /* end of pattern */
    if (p[0] == '$' && p[1] == '\0') return *t == '\0';    /* end anchor */

    /* lookahead quantifiers: * and ? */
    if (p[1] == '*') {
        const char c = p[0];
        const char *u = t;
        while (1) {
            if (match_here(p + 2, u)) return 1;            /* 0 or more */
            if (*u == '\0') break;
            if (c != '.' && *u != c) break;
            u++;
        }
        return 0;
    }

    if (p[1] == '?') {
        if (*t && (p[0] == '.' || *t == p[0]) && match_here(p + 2, t + 1))
            return 1;
        return match_here(p + 2, t);                       /* zero */
    }

    /* no quantifier: match one char */
    if (*t && (p[0] == '.' || *t == p[0]))
        return match_here(p + 1, t + 1);

    return 0;
}

/* Read from an already-open FILE* line-by-line, apply Match(), print matches.
   Returns 0 on success, 1 on immediate error (e.g., fin==NULL or pattern==NULL). */
int search_file(FILE *fin, const char *pattern) {
    if (fin == NULL || pattern == NULL) return 1;

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), fin) != NULL) {
        line_number++;
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        if (Match(pattern, line)) {
            printf("%3d: %s\n", line_number, line);
        }
    }

    return 0;
}