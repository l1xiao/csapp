...
input = {1, 2, 3, 4, 5, 6};
f(x) = 7 - x;
n = {6, 5, 4, 3, 2, 1}
esi = 0;
eax = 0;
while (true) {
    if (eax != 0) {
        while (ecx != eax) {
            rdx = *(rdx + 8);
            eax++;
        }
    } else {
        ecx = *(rsp + rsi);

    }
    // when input[i] == 1
    while (true) {
        ecx = *(rsp + rsi);
        if (exc > 1) break;
        edx = 0x6032d0;
        *(rsp + rsi*2 + 32) = rdx;// set node into nodes[];
        rsi += 4;
        if (rsi == 24) {
            flag = true;
            break;
        }
    }
    if (flag) {
        break;
    }
    eax = 1;
    edx = 0x6932d0;
}

rbx = 0x20 + rsp; // &num[0]
rax = 0x28 + rsx; // &num[1]
rsi = 0x50 + rsp; // &num[5]
rcx = rbx; // rcx = & num[0]
while (true) {
    rdx = *rax; // num[1] num[2]
    *(rcx + 8) = rdx; // num[1] = num[1]
    rax = rax + 8; // 1 [2] 3 4 5
    if (rsi == rax) {
       break;
    }
    rcx = rdx; // num[1]
}
ebp = 5;
do {
    rax = *(rbx + 8);
    eax = *rax;
    if ( *rbx >= eax) {
        rbx = *($rbx + 8);
    } else {
        bomb();
    }
} while (ebp = ebp - 1 != 0)
