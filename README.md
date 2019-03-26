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

       1. 每个客户端的数据来自两个生产者，每个生产者的数据是在各自上一次生产的消息随机加1到10，所以模拟的数据大体上是递增顺序的，但是考虑到极限情况，会有一个生产者产生的数据每次都加1，而客户端接收的是另一个增加较快的生产者的数据，所以后边仍然可能出现一个较小的数据，所以我要获得当前可能出现的最小值。
       2. 初步思路，按照数据轴模拟，每次输出1个数据或者不输出。
       3. 接下来考虑到每个客户端的数据来源于两个生产者，那么当前接收的数据如果小于等于上一次接收的数据，那么我便可以获得两个生产者当前的最小值min1。
       4. 同理，第二个客户端也是这样获得min2，那么我便可以求得二者中的最小值minn，刷新数据轴的取值，同时输出集合中小于等于minn的commit。
       5. 根据数据实时更新的特点我想到了用堆排序或者桶排序（每个桶内只放与标号相同的数据或者不放），考虑到无限数据需要控制内存和cpu，所以我想到了要维护一个优先队列。优先队列适用于客户端数量少的情况下，相对于桶排序可以大大减少空间资源浪费；桶排序适用于大量客户端的情况下，数据密度增加，使用桶排序会降低时间复杂度。
       6. 根据这个题目，我选者使用优先队列。

© 2019 GitHub, Inc.