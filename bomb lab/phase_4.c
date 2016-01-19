int edx = 14, esi = 0, eax = 0, ecx = 0, Param1 = 1;
int func(void) {
    if (edx > esi) {
        eax = (edx - esi) / 2;
    } else {
        eax = (edx - esi + 1) / 2;
    }
    ecx = eax + esi;
    if (ecx == Param1) {
        eax = 0;
    } else if (ecx < Param1) {
        eax = 0;
        esi = 1 + ecx;
        func();
    } else {
        edx = ecx - 1;
        func();
        eax *= 2;
    }
}

