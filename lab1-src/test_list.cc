
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"

int a[] = {45, 23, 78, 12, 100, 1, 100, 34, 90, 78 };

int test[] = {50, 15, 10, 8, 23, 24, 76, 67};

int
main( int argc, char ** argv )
{
  List l;
  List testing;
  int i;
  int j;
  int nelements = sizeof( a )/ sizeof( int );
  int total = sizeof(test)/sizeof(int);
  for ( i = 0; i < nelements; i++ ) {
    l.insertSorted( a[ i ] );
  }
  
  for(j = 0; j < total; j++){
	testing.insertSorted( test[ j ]);
  }

  printf("List after sorting...\n");

  l.print();

  printf("\n List after sorting new test cases....\n");
  testing.print();

  // Make sure that list is sorted
  ListNode *n = l._head;
  while ( n && n->_next ) {
    assert( n->_value <= n->_next->_value );
    n = n->_next;
  }
  
  ListNode *t = testing._head;
  while( t && t->_next){
	assert( t->_value <= t->_next->_value );
	t = t->_next;
  }

  // remove elements from the list
  assert( l.remove( 34 ) == 0 );
  assert( l.remove( 34 ) == -1 );
  assert( l.remove( 95 ) == -1 );
  assert( l.remove( 100 ) == 0 );
  assert( l.remove( 100 ) == 0 );
  assert( l.remove( 100 ) == -1 );

  // remove elements from the testing list
  assert( testing.remove( 10 ) == 0);
  assert( testing.remove( 50 ) == 0);
  assert( testing.remove( 2 ) == -1);

  // Make sure that the other elements are still there
  assert ( l.lookup( 45) == 0 );
  assert ( l.lookup( 23) == 0 );
  assert ( l.lookup( 78) == 0 );
  assert ( l.lookup( 1) == 0 );
  assert ( l.lookup( 90) == 0 );
  assert ( l.lookup( 34) == -1 );
  assert ( l.lookup( 100) == -1 );
  assert ( l.lookup( 95) == -1 );
  assert ( l.lookup( 2) == -1 );
  assert ( l.lookup( 12) == 0 );
  
  // Make sure that the other elements are still there
  assert( testing.lookup( 86 ) == -1);
  assert( testing.lookup( 2 ) == -1);
  assert( testing.lookup( 8 ) == 0);
  assert( testing.lookup( 3 ) == -1);

  printf(">>> test_listd!\n");
  exit( 0 );
}
