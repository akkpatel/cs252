#include <sys/types.h>
#include <stdlib.h>


/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */

char *mystrcpy(char * s1, const char * s2)
{
  /* Complete procedure */
  while(*s1++ = *s2++){
  ;
  }
  *s1 = '\0';
  return s1;
}

size_t mystrlen(const char *s)
{
  /* Complete procedure */
  size_t len;
    for (len = 0; *s != '\0'; s++,len++){
	}
    return len;
}

char *mystrdup(const char *s1)
{
  /* Complete procedure */
  char* cpy = malloc(mystrlen(s1)+1);
  if(cpy == NULL){
	return NULL;
  }
  mystrcpy(cpy,s1);
  return cpy;
}

char *mystrcat(char * s1, const char * s2)
{
  /* Complete procedure */
/*	int finallen = (mystrlen(s1)+mystrlen(s2));
	int i = 0;
	int j = 0;
	char* dest = malloc((finallen));
	for(i = 0; i < finallen; i++){
		if(i < mystrlen(s1)){
			dest[i] = s1[i];
		}else{
			dest[i] = s2[j];
			j++;
		}
	
	}
	dest[i] = '\0';
	  return dest;
*/
	int len = mystrlen(s1);
	int i;
	int j = 0;
	for(i = len; s2[j] != '\0'; i++){
		s1[i] = s2[j];
		j++;
	}
	s1[i] = '\0';
	
	return s1;
}

char *mystrstr(char * s1, const char * s2)
{
  /* Complete procedure */
	int len = mystrlen(s2);
	char *p = "\0";
	char* final;
	int i =0;
	int j = 0;
	int start = -1;
	if(mystrlen(s2)==0){
		return s1;
	}
	for(i = 0; i < mystrlen(s1); i++){
		if(*(s1+i)==*(s2+j)){
			j++;
			if(j==len){
			  start = i - len;
			  break;
			}
		}else{
			j = 0;
		}
	}
	int sizes = mystrlen(s1)-start;
	final = (char*)malloc(sizes);
	int k = 0;
	if(start != -1){
		for(i = start+1; i < mystrlen(s1); i++){
			*(final+k) = *(s1+i);
			k++;
		}
	}else{
		return NULL;
	}

	return final;	 



}

int mystrcmp(const char *s1, const char *s2) {
  /* Complete procedure */
	while(1){
		if(*s1 != *s2){
			return *s1 - *s2;
		}
		if(*s1 == '\0' && *s2=='\0'){
			return 0;
		}
		s1++;
		s2++;
		
	}
}

