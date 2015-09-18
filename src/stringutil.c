#include <stringutil.h>

void trim_str(char* str) {
	int len = strlen(str); 
	int i = len - 1; 

	while (i >=0 && (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')) {
		--i; 
	}

	str[i+1] = '\0'; 
}

bool valid_charset(char* test) {
	if (test == NULL) {
		printf("In valid_charse: NULL string received.\n"); 
		return false; 
	}
	int len = strlen(test), i = 0; 

	for (; i < len; i++) {
		if (!char_in_charset(test[i]))
			return false;
	}
	return true;
}

bool char_in_charset(char c) {
	if ('a' <= c && c <= 'z')
		return true; 

	if ('A' <= c && c <= 'Z')
		return true; 

	if ('0' <= c && c <= '9')
		return true; 

	if (c == '-' || c == '_' || c == '*' || c == '&' || c == '#')
		return true; 

	return false; 
}