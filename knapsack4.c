/* ID		: 2019112801
 * NAME		: woo yebin
 * OS		: linux, Ubuntu 18.04 
 * Compiler	: gcc 7.5.0
 */

// hw4-4.c
// Knapsack with two identical knapsacks
// TWO KNAPSACKS

#include	<stdio.h>
#include	<stdlib.h>

void decode(int list1, int list2, int weight, int n);
int* knapsack(int n, int weight1, int weight2, int* W, int* b);
int myPow(int x, int y);
int* knapsack_one(int n, int weight, int* W, int* b);

int main(int argc, char* argv[]){
	int *W, *b;
	int size = 0;
	W = (int*)malloc(sizeof(int));
	W[0] = 0;
	b = (int*)malloc(sizeof(int));
	b[0] = 0;
	FILE* fp;
	fp = fopen(argv[1], "r");
	while(W[size-1] != -1){
		fscanf(fp, "%d %d", W+size, b+size);
		size++;
		W = (int*)realloc(W, sizeof(int)*size);
		b = (int*)realloc(b, sizeof(int)*size);
	}
	int maxW1 = W[size-2];
	int maxW2 = b[size-2];
	size -= 2;
	int* answer = knapsack(size, maxW1, maxW2, W, b);
	decode(answer[0], answer[1], answer[2], size);
	
	free(W); free(b);
}

// Item ist is expressed as a binary number.
// digit = item number
// 0 : no item
// 1 : knapsack1's item
// 2 : knapsack2's item
void decode(int list1, int list2, int weight, int n){
	int what1[n], what2[n];
	for(int i=0; i<n; i++){
		what1[i] = list1 % 10;
		what2[i] = list2 % 10;
		list1 /= 10;
		list2 /= 10;
	}
	for(int i=0; i<n; i++){
		if(what1[i] == 1){
			printf("%d 1 ", i+1);
		}
	}
	for(int i=0; i<n; i++){
		if(what2[i] == 2){
			printf("%d 2 ", i+1);
		}
	}
	printf("%d\n", weight);
}

// knapsack function's return have
// what item is included and final maximum benefit.
// input  : n, knapsack1's volume, knapsacks2's volume, weight list, benefit list
// output : knapsack1's item list, knasack2's item list, maximum benefit

// [ns1]			[ns2's ns1]
// w-W              w		(w-W)-W2   w-W        w  
// --------------------         ------------------------      
//                 @ O 		             @        O
//                 * +		             *        +
//                 * +		             *        +
//                 @ O		             @        O
// [ns2]			[ns2's ns2]
// w-W              w		(w-W)-W2   w-W       w  
// --------------------		------------------------
//  @                O 		    @                 O
//       *           +		       *              +
//             *     +		          *           +
//                 @ O		             @        O
// [ns3]			[ns2's ns3]
// w-W              w		(w-W)-W2  w-W     w-W2        w
// --------------------		--------------------------------
//  O                @			   @        O
//       +           *		           *            +
//             +     *		           *               +
//                 O @		           @                  O

// ns(n, w) = max(ns1, ns2, ns3)
// ns1 = ns(n-1, w1)	+ ns(n-1, w2)	+ 0
// ns2 = ns(n-1, w1-W)	+ ns(n-1, w2)	+ b
// ns3 = ns(n-1, w1)	+ ns(n-1, w2-W)	+ b


int* knapsack(int n, int weight1, int weight2, int* W, int* b){
	static int arr[3];
	int ns1_list1, ns1_list2, ns1_value;
	int ns2_list1, ns2_list2, ns2_value;
	int ns3_list1, ns3_list2, ns3_value;
	if (n==0){
		arr[0] = 0; arr[1] = 0; arr[2] = 0;
		return arr;
	}
	if (weight1 == 0 && weight2 == 0){
		arr[0] = 0; arr[1] = 0; arr[2] = 0;
		return arr;
	}
	else if(weight2 == 0){
		int* arr_one = knapsack_one(n, weight1, W, b);
		arr[0] = arr_one[0];
		arr[1] = 0;
		arr[2] = arr_one[1];
		return arr;
	}
	else if(weight1 == 0){
		int* arr_one = knapsack_one(n, weight1, W, b);
		arr[0] = 0;
		arr[1] = arr_one[0];
		arr[2] = arr_one[1];
		return arr;
	}
	int* ns1 = knapsack(n-1, weight1, weight2, W, b);
	ns1_list1 = ns1[0];
	ns1_list2 = ns1[1];
	ns1_value = ns1[2];
	if(weight1-W[n-1] >= 0){
		int* ns2 = knapsack(n-1, weight1-W[n-1], weight2, W, b);
		ns2_list1 = ns2[0] + myPow(10, n-1);
		ns2_list2 = ns2[1];
		ns2_value = ns2[2]+b[n-1];
	}
	else{	ns2_value = -1;	}

	if(weight2-W[n-1] >= 0){
		int* ns3 = knapsack(n-1, weight1, weight2-W[n-1], W, b);
		ns3_list1 = ns3[0];
		ns3_list2 = ns3[1] + 2*myPow(10, n-1);
		ns3_value = ns3[2]+b[n-1];
	}
	else{	ns3_value = -1;	}
	if(ns1_value > ns2_value){
		arr[0] = ns1_list1;
		arr[1] = ns1_list2;
		arr[2] = ns1_value;
		if(ns3_value > arr[2]){
			arr[0] = ns3_list1;
			arr[1] = ns3_list2;
			arr[2] = ns3_value;
		}
	}
	else{
		arr[0] = ns2_list1;
		arr[1] = ns2_list2;
		arr[2] = ns2_value;
		if(ns3_value > arr[2]){
			arr[0] = ns3_list1;
			arr[1] = ns3_list2;
			arr[2] = ns3_value;
		}

	}

	return arr;
}

// if only one bag is empty, that can contain more.
// So caculate more based on one.
// same as code of hw4-1.c knapsack()
int* knapsack_one(int n, int weight, int* W, int* b){
	static int arr[2];
	int ns1_list, ns1_value;
	int ns2_list, ns2_value;
	if (n==0 || weight==0){
		arr[0] = 0; arr[1] = 0;
		return arr;
	}
	int* ns1 = knapsack_one(n-1, weight, W, b);
	ns1_list = ns1[0];
	ns1_value = ns1[1];
	if(weight-W[n-1] >= 0){
		int* ns2 = knapsack_one(n-1, weight-W[n-1], W, b);
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



