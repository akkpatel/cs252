//
// Implement the List class
//

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted( int val )
{
	int flag = 0;
	if(_head->_value == NULL){
		printf("\n inside this thing\n");
		_head = (ListNode*)malloc(sizeof(ListNode));
		_head->_value = val;
		printf("head = %d\n", _head->_value);
		return;
	}
	if(_head->_value != NULL){
//		printf("\n i went here\n");
		ListNode *front = _head;
		if(front->_value > val){
			ListNode *temp = (ListNode*)malloc(sizeof(ListNode));
			temp->_value = val;
			temp->_next = _head;
			_head = temp;
//			printf("head = %d\n", _head->_value);
//			printf("head = %d\n", _head->_next->_value);
			return;
		}else{
			while(front->_next!=NULL){
				if(front->_next->_value > val){
					ListNode* store = (ListNode*)malloc(sizeof(ListNode));
					store->_value = val;
					store->_next = front->_next;
					front->_next = store;
					flag = 1;
					return;
				}
				front = front->_next;
			}
			if(flag == 0){
				ListNode* tStore = (ListNode*)malloc(sizeof(ListNode));
				tStore->_value = val;
				front->_next = tStore;
				tStore->_next = NULL;
			}			
		}		
	}

  // Complete procedure 
}

//
// Inserts a new element with value "val" at
// the end of the list.
//
void
List::append( int val )
{
	if(_head->_value == NULL){
//		printf("\n inside this thing\n");
		_head = (ListNode*)malloc(sizeof(ListNode));
		_head->_value = val;
//		printf("head = %d\n", _head->_value);
		return;
	}
	if(_head->_value != NULL){
		ListNode *front = _head;
		while(front->_next!=NULL){
			front = front->_next;
		}
		ListNode *store = (ListNode*)malloc(sizeof(ListNode));
		store->_value = val;
		front->_next = store;
		store->_next = NULL;
	}


  // Complete procedure 
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend( int val )
{
	if(_head->_value == NULL){
//		printf("\n inside this thing\n");
		_head = (ListNode*)malloc(sizeof(ListNode));
		_head->_value = val;
//		printf("head = %d\n", _head->_value);
		return;
	}
	if(_head->_value != NULL){
		ListNode *temp = (ListNode*)malloc(sizeof(ListNode));
		temp->_value = val;
		temp->_next = _head;
		_head = temp;
	}

  // Complete procedure 
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List:: remove( int val )
{
	if(_head->_value == NULL){
		return -1;
	}
	if(_head->_value == val){
//		printf("\n inside this thing\n");
		_head = (ListNode*)malloc(sizeof(ListNode));
		ListNode* temps = _head;
		_head = _head->_next;
		free(temps);
		return 0;
	}
	if(_head->_value != NULL){
		ListNode *front = _head;
		while(front->_next != NULL){
			if(front->_next->_value == val){
				front->_next = front->_next->_next;
				return 0;
			}
			front = front->_next;
		}
	}
return -1;
  // Complete procedure
}

// Prints The elements in the list. 
void
List::print()
{
  // Complete procedure 

	if(_head->_value == NULL){
		return;
	}
	ListNode* front = _head;
	while(front->_next != NULL){
		printf("%d\n", front->_value);
		front = front->_next;
	}
	printf("%d\n",front->_value);
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
List::lookup(int val)
{
	if(_head->_value == NULL){
		return -1;
	}
	ListNode* front = _head;
	while(front->_next != NULL){
		if(front->_value == val){
			return 0;
		}	
		front = front->_next;
	}
	if(front->_value == val){
		return 0;
	}


  // Complete procedure 
  return -1;
}

//
// List constructor
//
List::List()
{
	_head = (ListNode*)malloc(sizeof(ListNode));
	_head->_next = NULL;
	_head->_value = NULL;
  // Complete procedure 
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
{
	if(_head->_value==NULL){
		free(_head);
		return;
	}
	while(_head != NULL){
		ListNode *temp = _head;
		_head = temp->_next;
		free(temp);
	}
	free(_head);
  // Complete procedure 
}

