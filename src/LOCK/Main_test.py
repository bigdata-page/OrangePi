import sys
import string
import ctypes

read = "read"
open = "open"
inquire = "inquire"
fun = ctypes.CDLL("./liballfunc.so");
array = ctypes.c_int*10
data = array()
rlen = 0
nLen = len(sys.argv)

if nLen == 1:
    fun.show_function()
elif nLen == 2:
    addr = string.atoi(sys.argv[1])
    ret = fun.open_lock_all(addr)
elif nLen == 3:
    addr_begin = string.atoi(sys.argv[1])
    addr_end = string.atoi(sys.argv[2])
    ret = fun.open_lock_cycle(addr_begin, addr_end);
elif nLen == 4: 
    addr = string.atoi(sys.argv[2])
    lock = string.atoi(sys.argv[3])
    if sys.argv[1] == open:
        rlen = fun.open_lock(addr, lock, data)
        if rlen == 5:
            print("open lock successful!!!")
        else: 
            print("open lock failed!!!")
    elif sys.argv[1] == read:
        rlen = fun.read_lock_state(addr, lock, data)
        if lock != 0:      
            if rlen == 5:
                print("read lock successful!!!")
            else: 
                print("read lock failed!!!")
        else:
            if rlen == 8:
                print("read lock successful!!!")
            else: 
                print("read lock failed!!!")              
    elif sys.argv[1] == inquire:
        rlen = fun.inquire_board_address(addr, data)
        if rlen == 5:
            print("inquire_board_address successful!!!")
        else:
            print("inquire_board_address failed!!!")   
else:
    print("The parameter is error!!!");

pdata = []
for i in range(0, rlen):
    pdata.append(data[i])

print(pdata)
print(nLen)
print("The main end!!\n")



























