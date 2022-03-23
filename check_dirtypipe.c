#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* str_replace(char* string, const char* substr, const char* replacement) {
	char* tok = NULL;
	char* newstr = NULL;
	char* oldstr = NULL;
	int   oldstr_len = 0;
	int   substr_len = 0;
	int   replacement_len = 0;

	newstr = strdup(string);
	substr_len = strlen(substr);
	replacement_len = strlen(replacement);

	if (substr == NULL || replacement == NULL) {
		return newstr;
	}

	while ((tok = strstr(newstr, substr))) {
		oldstr = newstr;
		oldstr_len = strlen(oldstr);
		newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));

		if (newstr == NULL) {
			free(oldstr);
			return NULL;
		}

		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replacement, replacement_len);
		memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
		memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);

		free(oldstr);
	}

	//free(string);

	return newstr;
}
int main(){
    struct utsname _uname = {};
    uname(&_uname);
    char *kversion = str_replace(str_replace(_uname.release, ".", " "), "-", " ");
    int v1, v2, v3;
    sscanf(kversion,"%d %d %d",&v1,&v2,&v3);
    printf("v1: %d | v2: %d | v3: %d\n",v1,v2,v3);
    if(
            v1 < 5 || 
            (v1 == 5 && v2 < 8) ||
            (v1 == 5 && v2 == 10 && v3 == 102) ||
            (v1 == 5 && v2 == 10 && v3 == 92) ||
            (v1 == 5 && v2 == 15 && v3 == 25) ||
            (v1 == 5 && v2 >= 16 && v3 >= 11) ||
            (v1 == 5 && v2 > 16))
    {
        printf("Not Vulnerable");
    }else
        printf("Vulnerable");
}
