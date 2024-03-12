### Skip list

* Linked List

  * search: O(n)

  * update: O(1)(after search)

* Sorted List

  * search: O(log n)

  * update: O(n)

Combine the two structure became a **skip list**

* maintain a sorted linked list
* add short cuts

#### Skip List by two

 ![image-20240228211422138](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240228211422138.png)

1. started in top level, go to successor if successor<=target
2. if successor in level > target, go to down level

#### Analysis

​	**size** is linear: $n+n/2+n/4+…+n/2^n < 2n$ 

​	**search** is O(log n): we will do 1 step in almost every level and the sum of level is log n

#### Skip List by randomization

​	**How to efficiently insert and delete in a skip list?**

​		**Randomization**

* every element in the bottom level at the beginning
* every element will be in the next or no higher level with 50% possibility

#### Analysis

​	**expected size** is linear: just same as the former but in a probabilistic view

​	**length** is O(log n)

* vertical steps: log n ,because we just need to go up log n times for the 50% possibility
* horizontal steps:  E[horizontal steps in level $Ei$] = E[same level numbers between former higher number]= 1  so with log n levels the result is log n