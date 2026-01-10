#ifndef __OBJFILE_PARSER_H__
#define __OBJFILE_PARSER_H__
typedef struct
{
	long size;
	long offset;
} sharedlib_data_t;

char **GetStrTable(void *fbuf, int len, sharedlib_data_t *text);

#endif
