## Lab Summary
#### cache

通过这个lab，掌握了cahce的结构和原理

#### 遇到的问题

traces/trans.trace的测试用例不正确，hits少了4个，miss和 evicts多了4 个

#### 解决办法

- 实现了verbose模式
- 写了一个脚本py.py处去掉所有的I指令寻址
- 用vimdiff确定第一个出现错误的位置在188行
- 删减trans.trace,使错误在5行输入内出现
- 使用gdb断点调试，找到错误，是一个非常弱智的边界条件错误

#### 反思

- 不要依赖test case来debug，要在写代码之前就想好边界条件，出现错误要先检查逻辑
