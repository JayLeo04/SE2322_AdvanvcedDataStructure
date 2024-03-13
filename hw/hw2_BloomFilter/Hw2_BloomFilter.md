## Hw2 Bloom Filter

### 程序运行结果

在本次实验中获得的实验结果如下：

| (m\k) | 1    | 2    | 3    | 4    | 5    |
| ----- | ---- | ---- | ---- | ---- | ---- |
| 2     | 0.36 | 0.38 | 0.52 | 0.59 | 0.62 |
| 3     | 0.28 | 0.18 | 0.25 | 0.35 | 0.42 |
| 4     | 0.19 | 0.13 | 0.14 | 0.15 | 0.13 |
| 5     | 0.17 | 0.1  | 0.09 | 0.13 | 0.13 |

### 实验结果分析

下列图像中，蓝线表示K=1,2,3,4,5时构造的Bloom Filter的误报率，橙色线条表示理论上假阳率最低时K的取值。

实验结果与Hash函数的seed有较大相关性，当采取不同seed时，误报率有显著差异，故取10组不同seed值进行实验取平均值得到更加可信的结果。

由下列图表可知，在合理误差范围内，误报率最低的K的取值与理论计算得到的最优值接近，基本符合理论情况。

![image-20240313123015201](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240313123015201.png)

![image-20240313123023478](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240313123023478.png)

![image-20240313123027401](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240313123027401.png)

![image-20240313123031806](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240313123031806.png)