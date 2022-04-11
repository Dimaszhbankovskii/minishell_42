#include "../includes/shell.h"

char *tok_buf = NULL; 	// буфер для токена
int   tok_bufsize  = 0;	// длина буфера
int   tok_bufindex = -1;// индекс в буфере

/* special token to indicate end of input */
struct token_s eof_token = 
{
	.text_len = 0,
};

void add_to_buf(char c)	// добавление символа в буфер токена
{
	tok_buf[tok_bufindex++] = c; 	// записали символ
	if(tok_bufindex >= tok_bufsize)	// проверка, что буфер не полный
	{								// перезапись данных и увеличение буфера
		char *tmp = realloc(tok_buf, tok_bufsize*2);
		if(!tmp)
		{
			errno = ENOMEM;
			return;
		}
		tok_buf = tmp;
		tok_bufsize *= 2;
	}
}

// создание структуры токена и запись текста
// str - текст токена
struct token_s *create_token(char *str)
{
	struct token_s *tok = malloc(sizeof(struct token_s));

	if(!tok)
	{
		return NULL;
	}
	memset(tok, 0, sizeof(struct token_s));
	tok->text_len = strlen(str);

	char *nstr = malloc(tok->text_len+1);

	if(!nstr)
	{
		free(tok);
		return NULL;
	}

	strcpy(nstr, str);
	tok->text = nstr;  // запись текста в токен

	return tok;
}

// очистка токена
void free_token(struct token_s *tok)
{
	if(tok->text)
	{
		free(tok->text);
	}
	free(tok);
}

struct token_s *tokenize(struct source_s *src)
{
	int  endloop = 0; // флаг конца работы

	if(!src || !src->buffer || !src->bufsize) // проверка буферов
	{
		errno = ENODATA;
		return &eof_token;
	}
	if(!tok_buf) // инициализация буфера для токена
	{
		tok_bufsize = 1024;				// размер для памяти буфера
		tok_buf = malloc(tok_bufsize);	// выделение памяти
		if(!tok_buf)	// ошибка malloc
		{
			errno = ENOMEM;
			return &eof_token;
		}
	}
	tok_bufindex     = 0; 		// индекс старта
	tok_buf[0]       = '\0';	// закрыли буфер
	char nc = next_char(src); // берем следующий символ
	if(nc == ERRCHAR || nc == EOF)
	{
		return &eof_token;	// токен EOF
	}
	do	// цикл while (конструкция do)
	{
		switch(nc) // ветвь вариантов
		{
			case ' ': // символ пробел пропускаем
			
			case '\t': // символ табуляции
				if(tok_bufindex > 0)
				{
					endloop = 1;
				}
				break;
	    
			case '\n':
				if(tok_bufindex > 0)
				{
					unget_char(src);
				}
				else
				{
					add_to_buf(nc);
				}
				endloop = 1;
				break;
	    
			default:
				add_to_buf(nc);
				break;
		}
		if(endloop)
		{
			break;
		}
	} while((nc = next_char(src)) != EOF);

	if(tok_bufindex == 0)
	{
		return &eof_token;
	}
	if(tok_bufindex >= tok_bufsize)
	{
		tok_bufindex--;
	}
	tok_buf[tok_bufindex] = '\0';
	struct token_s *tok = create_token(tok_buf);
	if(!tok)
	{
		fprintf(stderr, "error: failed to alloc buffer: %s\n",
			strerror(errno));
		return &eof_token;
	} 
	tok->src = src;
	return tok;
}