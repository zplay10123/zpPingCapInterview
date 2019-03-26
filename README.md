# PingCAPinterview

the interview for PingCAP

##### 时间

###### 开始时间：北京时间 2019年3月22日，17:00       结束时间：北京时间 2019年3月26日，15:00

##### 作业要求

在GitHub上实现，截止时间前提交项目链接。

##### 题目：data_collection

###### description

A system contains multiple data sources, every data source would generate data endless.

data source would send two messages to itself streaming in order for every data

- prepare message(type == prepare), contains prepare token
- commit message(type == message), contains prepare andcommit token

###### requirement

- sort data by commit token ascending, and output them in the fastest way you can implement(this system has a real time requirement)
- add flow control for your code (data are endless, I think we need to control memory and cpu usage) 
- describe your alghorithm and implemention in README.md
- add test case (any fashion) to prove your alghorithm correctness

I have complete code relate data source, you just need to complete sort and output code in collect(), and you can add some auxiliary structures, variables and functions, but don't modify any definitions.

###### Notice: welcome any problems and feedbacks

##### 分析题目：

​        程序模拟了两个客户端一直在发送数据，而我需要对消息数据排序输出。关键点：数据无限，排序要高效，要控制内存和CPU使用量。

##### 实现思路:

    1.每个客户端的数据来自两个生产者，每个生产者的数据是在各自上一次生产的消息随机加1到10，所以模拟的数据大体上是递增顺序的，但是考虑到极限情况，会有一个生产者产生的数据每次都加1，而客户端接收的是另一个增加较快的生产者的数据，所以后边仍然可能出现一个较小的数据，所以我要获得当前可能出现的最小值。
    2.初步思路，按照数据轴模拟，数据轴每次++，每次输出符合条件的commit（最多一个）或者不输出。（肯定不能这么暴力呀！）
    3.接下来考虑到每个客户端的数据来源于两个生产者，那么当前接收的数据如果小于等于上一次接收的数据，那么我便可以获得两个生产者当前的最小值min1。
    4.同理，第二个客户端也是这样获得min2，那么我便可以求得二者中的最小值minn，刷新数据轴的取值，同时输出集合中小于等于minn的commit。
    5.根据数据实时更新的特点我想到了用堆排序或者桶排序（每个桶内只放与标号相同的数据或者不放），考虑到无限数据需要控制内存和cpu，所以我想到了要维护一个优先队列。优先队列适用于客户端数量少的情况下，相对于桶排序可以大大减少空间资源浪费；桶排序适用于大量客户端的情况下，数据密度增加，使用桶排序会降低时间复杂度。
    6.根据这个题目，我选者使用优先队列。

© 2019 GitHub, Inc.



心路历程：
               NO.1 刚刚拿到这道题目的时候，感觉这是一个实时数据流处理的问题，不可能直接一次输出最终结果。利用生产者消费者模式，生产者不停地网数据集里生产数据，消费者每隔一段时间对数据集里的所有数据进行treeset操作（不改变数据集里的原始数据），然后输出数据，随着时间的推移，数据集里的数据越多，每次treeset后的输出就越接近最终结果。
               NO.2 根据题目信息，得到排序要高效，要控制内存和CPU使用量，自己联想到可能出现负数，某一数据多次重复	出现的等问题，想到不受比较排序限制的桶排序，每次对更新后产生的数据输出时覆盖之前的输出等操作，开始写代码。
               NO.3和出题人沟通之后，发现自己理解错了题意，感觉涉及到了自己的知识盲区。开始重新思考问题。
               NO.4产生的新思路：这道题目的核心问题不是高效的排序（当然也是重要的），而是在维护顺序数据流的过程中当	前判断之后某一数据是否会出现？问题转化到现在，就是怎么预测之后某一数据是否会出现的问题，预测之后的数据肯定要通过当前已有的数据预测，我猜测可能是数据分析的相关问题（我了解一些基础的算法），查阅了一些资料，找到一个时间序列回归模型，简单的了解概念性的理论，得出一个想法：先以 token中的 ontains prepare为自变量，以commit token为因变量，拟合一个模型或函数，然后通过向函数代入后续ontains prepare，就可以预	测后续的commit token。(个人疑问，预测数据，一定准确吗？但这应该是当前的方法)。
               NO.5和出题者沟通之后，终于觉醒，自己应该从题目出发的，首先我没有着急看题目，而是开始继续学习go语言，	将所有go的基础知识看了一遍之后，便读懂了之前没有读懂、也没有重视的go语言程序。
               NO.6程序读懂了，也就知道了自己要做什么：
                          1. 每个客户端的数据来自两个生产者，每个生产者的数据是在各自上一次生产的消息随机加1到10，所以模  		拟的数据大体上是递增顺序的，但是考虑到极限情况，会有一个生产者产生的数据每次都加1，而客户端			接收的是另一个增加较快的生产者的数据，所以后边仍然可能出现一个较小的数据，所以我要获得当前			可能出现的最小值。
  	           2. 初步思路，按照数据轴模拟，每次输出1个数据或者不输出。
   	           3. 接下来考虑到每个客户端的数据来源于两个生产者，那么当前接收的数据如果小于等于上一次接收的数			据，那么我便可以获得两个生产者当前的最小值min1。
  	           4. 同理，第二个客户端也是这样获得min2，那么我便可以求得二者中的最小值minn，刷新数据轴的取值			，同时输出集合中小于等于minn的commit。
   	           5. 根据数据实时更新的特点我想到了用堆排序或者桶排序（每个桶内只放与标号相同的数据或者不放），			考虑到无限数据需要控制内存和cpu，所以我想到了要维护一个优先队列。优先队列适用于客户端数量			少的情况下，相对于桶排序可以大大减少空间资源浪费；桶排序适用于大量客户端的情况下，数据密度			增加，使用桶排序会降低时间复杂度。
   	           6. 根据这个题目，我选者使用优先队列。
                NO.7反思总结，这个小程序还是暴露了我很多问题，比如没有重视自己手里的第一手资料，凭借自己对题目的一个印象便开始了天马行空的想象......没有读懂题目便开始解决自以为的问题等等，不过这几天自己的收获也很丰富，感谢PingCAP!谢谢出题的小哥哥和hr小姐姐。
