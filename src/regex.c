// regex.c supports [abc] ^ $ . * ?  
#include <stdio.h>
// Implement [abc](character matching) ^(beginning anchor) $(end anchor) 
// .(match single character) *(0 or more repetition) ?(0 or 1 repititions)  
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

/* recursive matching */
static int match_here(const char *p, const char *t) {
    if (*p == '\0') return 1;                              /* end of pattern */
    if (p[0] == '$' && p[1] == '\0') return *t == '\0';    /* end anchor */

/* Character matching [abc]  */
if (p[0] == '[') {

    const char *end = strchr(p, ']');
    if (!end) return 0;

    int contains = 0;
    const char *q = p + 1;

    while (q < end) {
        if (*t == *q) {
            contains = 1;
            break;
        }
        q++;
    }

    /* [abc]* repetition */
    if (end[1] == '*') {
        const char *u = t;

        while (1) {
            if (match_here(end + 2, u)) return 1;
            if (*u == '\0') break;

            int inner_contains = 0;
            const char *qq = p + 1;
            while (qq < end) {
                if (*u == *qq) {
                    inner_contains = 1;
                    break;
                }
                qq++;
            }

            if (!inner_contains) break;
            u++;
        }
        return 0;
    }

    /* [abc]?  match */
    if (end[1] == '?') {
        if (contains && match_here(end + 2, t + 1))
            return 1;
        return match_here(end + 2, t);
    }

    /* Normal single-character match */
    if (contains)
        return match_here(end + 1, t + 1);

    return 0;
}  
    
    /* lookahead * and ? */
    if (p[1] == '*') {
        const char c = p[0];
        const char *u = t;
        while (1) {
            if (match_here(p + 2, u)) return 1;           
            if (*u == '\0') break;
            if (c != '.' && *u != c) break;
            u++;
        }
        return 0;
    }

    if (p[1] == '?') {
        if (*t && (p[0] == '.' || *t == p[0]) && match_here(p + 2, t + 1))
            return 1;
        return match_here(p + 2, t);                       
    }

    /* Simple fix: if previous part matched a class ([ae]), keep matching normally */
if (p[0] != '[' && p[0] != ']' && p[0] != '*' && p[0] != '?' ) {
    if (*t && p[0] == *t)
        return match_here(p + 1, t + 1);
}
    
    /* match one char */
    if (*t && (p[0] == '.' || *t == p[0]))
        return match_here(p + 1, t + 1);

    return 0;
}

/* Read from an already-open FILE* line-by-line, apply Match(), print matches.
   Returns 0 on success, 1 on immediate error */
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
