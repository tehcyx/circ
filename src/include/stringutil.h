#ifndef _STRINGUTIL_H_
#define _STRINGUTIL_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void trim_str(char* str);
bool valid_charset(char* test);
bool char_in_charset(char c);

#endif
