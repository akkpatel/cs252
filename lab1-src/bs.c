#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
	const char *s1 = "aashay and anand";
	const char *s2 = "anand";

	const char *hello = malloc(strlen(s1));
	hello = strstr(s1,"and");
	prinf("hi %s", hello);
}
