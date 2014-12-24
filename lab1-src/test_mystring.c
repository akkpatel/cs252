#include <assert.h>
#include <string.h>
#include <stdio.h>

char *mystrcpy(char * s1, const char * s2);
size_t mystrlen(const char *s);
char *mystrdup(const char *s1);
char *mystrcat(char * s1, const char * s2);
char *mystrstr(char * s1, const char * s2);
int mystrcmp(const char *s1, const char *s2) ;

int
main()
{
  char s1[64], *s2;

  /* TRIVIAL tests -- you should extend these or you are likely to
   * lose points in grading. */

  /* Test mystrcpy */
  mystrcpy (s1, "Hello world");
  assert(!strcmp (s1, "Hello world"));
  assert(strcmp (s1, "Hello worl"));
  assert(strcmp (s1, "Hello worldgggg"));

  mystrcpy (s1, "");
  assert(!strcmp (mystrcpy (s1, ""), ""));

  /* Trivial test for mystrcpy by Anand Patel*/
  mystrcpy(s1, "mY eMaIl is @ gMaIL.COm");
  assert(!strcmp(s1, "mY eMaIl is @ gMaIL.COm"));
  assert(strcmp(s1, "mY eMaIl is @ gMaIL.COM"));
  mystrcpy(s1, "my # = 7655676576");
  assert(!strcmp(s1, "my # = 7655676576"));

  /* Test mystrlen */
  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("Hello world") == 11);

  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("Hello world") == 11);
 
  /* Trivial test for mystrlen by Anand Patel*/
  assert (mystrlen("") == 0);
  assert (mystrlen("mY eMaIl is @ gMaIL.COm") == 23);
  assert (mystrlen("mY eMaIl is @ gMaIL.COm") - mystrlen("my # = 7655676576") + mystrlen("hi") == 8);

  /* Test strdup */
  s2 = strdup("Hello world");
  assert( !strcmp(s2, "Hello world") );
  s2[0]='Y';
  assert( !strcmp(s2, "Yello world") );
  free(s2);

  /* Trivial test for mystrdup by Anand Patel*/
  s2 = strdup("");
  assert(!strcmp(s2,""));
  s2 = strdup("mY eMaIl is @ gMaIL.COm");
  assert(!strcmp(s2, "mY eMaIl is @ gMaIL.COm"));
  free(s2);
	
  // Test mystrcat
  mystrcpy(s1, "Purdue");
  mystrcat(s1, " University");
  assert( !strcmp(s1, "Purdue University")); 

  mystrcat(s1, "");
  assert( !strcmp(s1, "Purdue University")); 

  /* Trivial test for mystrcat by Anand Patel*/
  mystrcpy(s1, " ");
  mystrcat(s1, " AnYone There !!!");
  assert( !strcmp(s1, "  AnYone There !!!"));
  
  mystrcpy(s1, "");
  mystrcat(s1, " ");	
  assert(!strcmp(s1, " "));

  // Test mystrstr
  mystrcpy(s1, "The quick brown fox jumps over the lazy dog");
  s2 = mystrstr(s1, "jumps");
  assert(!strcmp(s2, "jumps over the lazy dog")); 
  assert(mystrstr(s1, "Hello")==NULL);
  assert(mystrstr("jumps", s1)==NULL);
  s2 = mystrstr(s1, "");
  assert(s2 == s1);

  /* Trivial test for mystrstr by Anand Patel*/
  mystrcpy(s1, "CS252 starts at 1:30 P.M. on Tuesday and Thursday!");
  s2 = mystrstr(s1,"!");
  assert(!strcmp(s2, "!"));

  s2 = mystrstr(s1, ".");
  assert(!strcmp(s2, ".M. on Tuesday and Thursday!"));

//int mystrcmp(const char *s1, const char *s2) ;
 // Test strcmp
  assert(mystrcmp("abcd","dabc")<0);
  assert(mystrcmp("dab", "abcd")>0);
  assert(mystrcmp("dab", "dab")==0);
 
  /* Trivial test for mystrcmp by Anand Patel*/
  assert(mystrcmp("!@#%$", "$%#@!") < 0);
  assert(mystrcmp("TeST CaSEs", "TeST CaSEs") == 0);
 
  printf ("Seems to be OK\n");
  return 0;
}
