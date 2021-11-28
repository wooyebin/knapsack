# knapsack problem
[explanation](https://en.m.wikipedia.org/wiki/Knapsack_problem)

## problem
1. knapsack problem
2. knapsack problem with only one item that can be devided by 2
3. knapsack problem with only one item that can be duplicated by 2
4. knapsack problem with two diffent knapsacks

## Environment
OS : Linux 18.04   
Complier : gcc 7.5.0

## how to use
<pre><code>$ ./knapsack input.txt </code></pre>

## input file format
weight1 benefit1   
weight2 benefit2   
weight3 benefit3   
...   
maximum weight -1

## Introduction
#### 1. knapsack problem
recursive function knapsack()   
> knapsack(n, weight) = max(knapsack(n-1, weight), knapsack(n-1, weight-W) + b)

> input n, weight, *W, *b
> * n : how many item
> * weight : maximum weight knapsack can get
> * *W, *b : weight and benefit list for items   

> return *arr   
> * arr[0] : what item is included (binary)   
> * arr[1] : maximum benefit

#### 2. knapsack problem with one item split
recursive function knapsack()   
> knapsack(n, weight) = max(knapsack(n-1, weight), knapsack(n-1, weight-W) + b, knapsack(n-1, weight-W/2) + b/2)

> input n, weight, *W, *b, flag
> * n : how many item
> * weight : maximum weight knapsack can get
> * *W, *b : weight and benefit list for items   
> * flag : half item is included or not

> return *arr   
> * arr[0] : what item is included (quaternary)   
> * arr[1] : maximum benefit

#### 3. knapsack problem with one duplicate item
recursive function knapsack()   
> knapsack(n, weight) = max(knapsack(n-1, weight), knapsack(n-1, weight-W) + b, knapsack(n-1, weight-W*2) + b*2)

> input n, weight, *W, *b, flag
> * n : how many item
> * weight : maximum weight knapsack can get
> * *W, *b : weight and benefit list for items   
> * flag : double item is included or not

> return *arr   
> * arr[0] : what item is included (quaternary)   
> * arr[1] : maximum benefit

#### 4. knapsack problem with two knapsacks
recursive function knapsack()   
> knapsack(n, weight1, weight2) = max(knapsack(n-1, weight1)+knapsack(n-1, weight2), knapsack(n-1, weight1-W)+knapsack(n-1, weight2)+b, knapsack(n-1, weight1)+knapsack(n-1, weight1-W)+b)

> input n, weight1, weight2, *W, *b
> * n : how many item
> * weight1 : maximum weight1 knapsack can get
> * weight2 : maximum weight2 knapsack can get
> * *W, *b : weight and benefit list for items   

> return *arr   
> * arr[0] : what item is included in knapsack1(binary)   
> * arr[1] : what item is included in knapsack2(binary)   
> * arr[2] : maximum benefit
