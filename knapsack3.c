/* ID		: 2019112801
 * NAME		: woo yebin
 * OS		: linux, Ubuntu 18.04 
 * Compiler	: gcc 7.5.0
 */

// hw4-3.c
// Knapsack with one duplicate item
// ONLY ONE item can be added TWICE

#include	<stdio.h>
#include	<stdlib.h>

void decode(int list, int weight, int n);
int* knapsack(int n, int weight, int* W, int* b, int flag);
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
	int* answer = knapsack(size, maxW, W, b, 0);
	decode(answer[0], answer[1], size);
	
	free(W); free(b);
}

// Item list is expressed as a quaternary number.
// digit = item number
// 0 : no item
// 1 : whole item
// 2 : double item
void decode(int list, int weight, int n){
	int list_int = (int)list;
	int what[n];
	for(int i=0; i<n; i++){
		what[i] = list_int % 10;
		list_int /= 10;
	}
	for(int i=0; i<n; i++){
		if(what[i] == 1){
			printf("%d ", i+1);
		}
		else if(what[i] == 2){
			printf("%dx2 ", i+1);
		}
	}
	printf("%d\n", weight);

}

// knapsack function's return have
// what item is included and final maximum benefit.
// input  : n, knapsack's volume, weight list, benefit list, flag
//	+ flag : double item is included or not
// output : item list, maximum benefit

// w-W*2   w-W      w
// --------------------
// ns3     ns2     ns1
//  O       O       O
//     *      *     *
//          *    *  * 
//               *  O
// ns(n, w) = max(ns1, ns2, ns3)
// ns1 = ns(n-1, w)	+ 0
// ns2 = ns(n-1, w-W)	+ b
// ns3 = ns(n-1, w-W*2)	+ b*2

int* knapsack(int n, int weight, int* W, int* b, int flag){
	static int arr[2];
	int ns1_list, ns1_value;
	int ns2_list, ns2_value;
	int ns3_list, ns3_value;
	if (n==0 || weight==0){
		arr[0] = 0; arr[1] = 0;
		return arr;
	}
	if(flag == 1){
		int* ns1 = knapsack(n-1, weight, W, b, 1);
		ns1_list = ns1[0];
		ns1_value = ns1[1];
		if(weight-W[n-1] >= 0){
			int* ns2 = knapsack(n-1, weight-W[n-1], W, b, 1);
			ns2_list = ns2[0] + myPow(10, n-1);
			ns2_value = ns2[1] + b[n-1];
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
	}
	else{
		int* ns1 = knapsack(n-1, weight, W, b, 0);
		ns1_list = ns1[0];
		ns1_value = ns1[1];
		
		
		if(weight-W[n-1]*2 >= 0){
			int* ns2 = knapsack(n-1, weight-W[n-1], W, b, 0);
			ns2_list = ns2[0] + myPow(10, n-1);
			ns2_value = ns2[1] + b[n-1];
			int* ns3 = knapsack(n-1, weight-W[n-1]*2, W, b, 1);
			ns3_list = ns3[0] + 2*myPow(10, n-1);
			ns3_value = ns3[1] + b[n-1]*2;
			if(ns1_value > ns2_value){
				arr[0] = ns1_list;
				arr[1] = ns1_value;
				if(ns3_value > arr[1]){
					arr[0] = ns3_list;
					arr[1] = ns3_value;
				}
			}
			else{
				arr[0] = ns2_list;
				arr[1] = ns2_value;
				if(ns3_value > arr[1]){
					arr[0] = ns3_list;
					arr[1] = ns3_value;
				}
			}
		}
		else if(weight-W[n-1] >= 0){
			int* ns2 = knapsack(n-1, weight-W[n-1], W, b, 0);
			ns2_list = ns2[0] + myPow(10, n-1);
			ns2_value = ns2[1] + b[n-1];

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
	}
	return arr;
}

// squre number calculation for making item list
int myPow(int x, int y){
	int result = 1;
	for(int i=0; i<y; i++) result *= x;
	return result;
}



