#ifndef SCANNER_H
#define SCANNER_Hl

struct token_s
{
	struct s_source *src;       /* source of input */
	int    text_len;            /* length of token text */
	char   *text;               /* token text */
};

/* the special EOF token, which indicates the end of input */
extern struct token_s eof_token;
struct token_s *tokenize(struct s_source *src);
void free_token(struct token_s *tok);

#endif 