##Bufbomb Lab总结

---

先看下这个lab的期望：

> Students modify the run-time behavior of a binary executable by exploiting a buffer overflow bug. This lab teaches the students about the stack discipline and teaches them about the danger of writing code that is vulnerable to buffer overflow attacks.

一个是掌握栈帧结构，一个是避免写易受攻击的代码。


这个实验有5个部分，前两个level都比较简单，就是直接覆盖掉ret或者上层栈帧的args即可。

###Level 2: Firecracker

这一关需要给一个全局变量赋值为cookie，并返回到指定位置。但是经过检查，buffer溢出是覆盖不到global variable的位置的。所以需要将代码写到buffer中，并覆盖ret使其跳转到这段代码的起始位置。

对应的assembly code

```
mov cookie地址, %eax
mov %eax, global地址
push 返回函数地址
ret
```
用gcc和objdump得到机器码

```
gcc -m32 -c bang.S
objdump -d bang.o > bang.d
```
并将对应的机器码写入到buffer中，从起始位开始写，因为buffer的起始位是低位，执行的时候也是从低位执行到高位。

这里遇到了一个问题并且卡了很久，我发现没法找到机器码(buffer)的起始位置。一开始以为是通过间接的方式得到地址，然而一直没有找到表达式。后来发现直接在gdb中找到存储地址的寄存器，并打出来即可。

###Level 3: Dynamite
这一关要求在返回`test()`时恢复被污染的state。这里搞清楚什么算是被污染，返回test，`%esp`会指向(ret+4)的位置，`%ebp`需要指向test栈帧的`%ebp`。这里可以看出`%ebp`是没办法直接恢复的，因为`%ebp`在覆盖缓冲区时，值已经被覆盖了，所以重点是找到`%ebp`的值。通过画出`test()`过程调用的栈计算出`%ebp`的位置，然后思路还是和level 2一样，在buffer中写入对`%ebp`赋值的操作即可。

###Level 4: Nitroglycerin
这一关需要在Nitro模式下运行，条件和任务与level 3 一样。但是buffer有512 byte那么大，并且`getbufn`会在分配栈空间时先随机分配一些空间，使得`%ebp`的地址不是订制，其浮动范围是 ±240。同时Nitro要求输入5次相同的字符串，全部通过才行(因为栈的空间分配是随机的，减少因为运气因素)

这样的话就不能直接覆盖ret一个确定的地址(因为我们无法确定地址)来指向缓冲区的起始地址来执行机器码。但是观察可以知道，栈随机分配至多480 bytes，而缓冲区有512 bytes。
如果我们的代码写在480~512 byte这个区间，这样就可以
- 不超出当前栈帧，不污染上层栈帧
- 保证能够执行到这些代码

剩下的就是在这之前全部用`90(nop)`来填满buffer即可, 即nop sled。