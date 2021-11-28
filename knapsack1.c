/* ID		: 2019112801
 * NAME		: woo yebin
 * OS		: linux, Ubuntu 18.04 
 * Compiler	: gcc 7.5.0
 */

// hw4-1.c
// Knapsack

#include	<stdio.h>
#include	<stdlib.h>

void decode(int list, int weight, int n);
int* knapsack(int n, int weight, int* W, int* b);
int myPow(int x, int y);

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
	int* answer = knapsack(size, maxW, W, b);
	decode(answer[0], answer[1], size);
	
	free(W); free(b);
}

// Item ist is expressed as a binary number.
// digit = item number
// 0 : no item
// 1 : whole item
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
	printf("%d\n", weight);
}

// knapsack function's return have
// what item is included and final maximum benefit.
// input  : n, knapsack's volume, weight list, benefit list
// output : item list, maximum benefit

// ns2     ns1
//  O       O
//     -    -
//        - O
// ns(n, w) = max(ns1, ns2)
// ns1 = ns(n-1, w)
// ns2 = ns(n-1, w-W)+b
int* knapsack(int n, int weight, int* W, int* b){
	static int arr[2];
	int ns1_list, ns1_value;
	int ns2_list, ns2_value;
	if (n==0 || weight==0){
		arr[0] = 0; arr[1] = 0;
		return arr;
	}
	int* ns1 = knapsack(n-1, weight, W, b);
	ns1_list = ns1[0];
	ns1_value = ns1[1];
	if(weight-W[n-1] >= 0){
		int* ns2 = knapsack(n-1, weight-W[n-1], W, b);
		ns2_list = ns2[0] + myPow(10, n-1);
		ns2_value = ns2[1]+b[n-1];
		if(ns1_value > ns2_value){
			arr[0] = ns1_list;
			arr[1] = ns1_value;
		}
		else{
			arr[0] = ns2_list;
			arr[1] = ns2_value;
		}
	}
	else{
		arr[0] = ns1_list;
		arr[1] = ns1_value;
	}
	return arr;
}

// squre number calculation for making item list
int myPow(int x, int y){
	int result = 1;
	for(int i=0; i<y; i++) result *= x;
	return result;
}



