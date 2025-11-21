// regex.c — tiny engine with ^ $ . * ?  (simple and short)
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
