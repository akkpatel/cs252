#include <stdlib.h>
#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>

/*
template <class Type>
Type newswap(Type* a, Type* b, int size)
{
Type* temp = (Type*)malloc(size);
temp = b;
b = a;
a = temp;
}
*/

void* swap(char* temp, char* store, char* store2, int elementSize){
	int k;
	for(k = 0; k < elementSize; k++){
		temp[k] = store[k];
	}
//	printf("temp %s\n", temp);
	for(k = 0; k < elementSize; k++){
		store[k] = store2[k];
	}
//	printf("store %s\n", store);
	for(k = 0; k < elementSize; k++){
		store2[k] = temp[k];
	}
//	printf("store2 %s\n", store2);
}

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
  // Add your code here. Use any sorting algorithm you want.

	int i;
	int j;
	char* temp = (char*)malloc(elementSize);
	for(i = 0; i < n; i++){
		for(j = 0; j<n-1; j++){
			if(ascending==0 && compFunc((char*)array+((j)*elementSize), (char*)array+((j+1)*elementSize)) <= 0){
//				printf("ascending==0\n");
//				if(compFunc((char*)array+((j)*elementSize), (char*)array+((j+1)*elementSize)) <= 0){
//					printf("func <= 0\n");
					swap(temp, (char*)array+((j)*elementSize), (char*)array+((j+1)*elementSize), elementSize);
					
//				}
			}
			if(ascending!=0 && compFunc((char*)array+((j)*elementSize), (char*)array+((j+1)*elementSize)) >= 0){
//				printf("descending\n");
//				if(compFunc((char*)array+((j)*elementSize), (char*)array+((j+1)*elementSize)) >= 0){
//					printf("inside func\n");
					swap(temp, (char*)array+((j)*elementSize), (char*)array+((j+1)*elementSize), elementSize);
//				}
			}
		}
	}
	free(temp);
}

