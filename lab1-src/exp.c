#include <stdio.h> 
#include<stdlib.h>

char *mystrcpy(char * s1, const char * s2)
{
  /* Complete procedure */
/*	int i = 0;
	printf("hi");
	while(s2[i] != '\0'){
		s1[i] = s2[i];
		i++;
		printf("i %d\n", i);
	}
//	printf("out i %d\n", i);	
	s1[i] = '\0';
	
	return s1;*/

	int i =0;
	for(i = 0; *(s2+i) != '\0'; i++){
		*(s1+i) = *(s2+i);
	}
	*(s1+i) = '\0';
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
  int len = mystrlen(cpy);
  if(cpy == NULL){
	return NULL;
  }
  mystrcpy(cpy,s1);
  return cpy;
}

char *mystrcat(char * s1, const char * s2)
{
	int finallen = (mystrlen(s1)+mystrlen(s2));
	int i = 0;
	int j = 0;
	char* dest = malloc((finallen));
	for(i = 0; i < finallen; i++){
		if(i < mystrlen(s1)){
			*(dest+i) = *(s1+i);
		}else{
			*(dest+i) = *(s2+j);
			j++;
		}
	
	}
	  return dest;
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
		return p;
	}

	return final;		
}

int mystrcmp(const char *s1, const char *s2) {
/*
	int i =0;
	if(mystrlen(s1)== mystrlen(s2)){
		for(i = 0; i < (mystrlen(s1)); i++){
		//	printf("hi");
			if((s1+i) == (s2+i)){

			}else{
				return 0;
			}
		}
	return 1;

	}else if(mystrlen(s1) < mystrlen(s2)){
		return -1;
	}else{
		return 0;
	}  

*/	

}
int main(){
	char* temp = "Anand hi ";
	char* hi = "";
	mystrcpy(hi, temp);
	printf("dup   %s", hi);

}