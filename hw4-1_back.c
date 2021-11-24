/* ID		: 2019112801
 * NAME		: woo yebin
 * OS		: linux, Ubuntu 18.04 
 * Compiler	: gcc 7.5.0
 */

// hw4-1.c
// Knapsack problem

#include	<stdio.h>
#include	<stdlib.h>

void decode(int list, int weight, int n);
int knapsack(int n, int weight, int* W, int* b);
int myPow(int x, int y);
int list=0;

int main(int argc, char* argv[]){
	int *W, *b;
	int size = 0;
	W = (int*)malloc(sizeof(int));
	W[0] = 0;
	b = (int*)malloc(sizeof(int));
	b[0] = 0;
	FILE* fp;
	fp = fopen(argv[1], "r");
	while(b[size-1] != -1){
		fscanf(fp, "%d %d", W+size, b+size);
		size++;
		W = (int*)realloc(W, sizeof(int)*size);
		b = (int*)realloc(b, sizeof(int)*size);
	}
	int maxW = W[--size];

	int answer = knapsack(size, maxW, W, b);
	decode(list, answer, size);
	
	free(W); free(b);
}

void decode(int list, int weight, int n){
	int what[n];
	for(int i=0; i<n; i++){
		what[i] = list % 10;
		list /= 10;
	}
	for(int i=0; i<n; i++){
		if(what[i] == 1){
			printf("%d ", i+1);
		}
	}
	printf("%d\n", list);
	printf("%d\n", weight);
}

int knapsack(int n, int weight, int* W, int* b){
	int arr;
	int mylist = list;
	if (n==0 || weight==0){
		list = 0; arr = 0;
		return arr;
	}
	int ns1 = knapsack(n-1, weight, W, b);
	if(weight-W[n-1] >= 0){
		int ns2 = knapsack(n-1, weight-W[n-1], W, b)+b[n-1];
		if(ns1 > ns2){
			list = mylist;
			arr = ns1;
		}
		else{
			list = mylist + myPow(10, n-1);
			arr = ns2;
		}
	}
	else{
		list = mylist;
		arr = ns1;
	}
	return arr;
}

int myPow(int x, int y){
	int result = 1;
	for(int i=0; i<y; i++) result *= x;
	return result;
}



