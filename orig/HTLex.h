
#ifndef HTLEX_H
#define HTLEX_H

#include "HTUtils.h"

#ifdef SHORT_NAMES
#define lex_verb lex_verbose
#endif /*SHORT_NAMES*/

typedef enum
{
    LEX_NONE,        /* Internally used	*/
    LEX_EOF,         /* End of file		*/
    LEX_REC_SEP,     /* Record separator	*/
    LEX_FIELD_SEP,   /* Field separator	*/
    LEX_ITEM_SEP,    /* List item separator	*/
    LEX_OPEN_PAREN,  /* Group start tag	*/
    LEX_CLOSE_PAREN, /* Group end tag	*/
    LEX_AT_SIGN,     /* Address qualifier	*/
    LEX_ALPH_STR,    /* Alphanumeric string	*/
    LEX_TMPL_STR,    /* Template string	*/
    LEX_CLOSE_BRACE  /* End of prot.def.	*/
} LexItem;

extern char lex_buffer[]; /* Read lexical string		*/
extern int lex_line;      /* Line number in source file	*/

PUBLIC LexItem lex PARAMS((FILE * fp));

PUBLIC void unlex PARAMS((LexItem lex_item));

PUBLIC char *lex_verbose PARAMS((LexItem lex_item));

#endif /* not HTLEX_H */