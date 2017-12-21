import sys
import string
import ctypes

set_init = [0]

def int_to_func(num):
    if num == 1:
        return "open"
    elif num == 2:
        return "read"
    elif num == 3:
        return "inquire"
    elif num == 4:
        return "check"
    else: 
        print("the data is error")
		
def open_lock(data):
    
    #the parameter
    func = int_to_func(data[0])
    addr = data[1]
    lock = data[2]
    nLen = data[3]
    
    print("The open lock start...")
    read = "read"
    open = "open"
    inquire = "inquire"
    array = ctypes.c_int*10
    ret_data = array()
    fun = ctypes.CDLL("./liblock.so")
    if set_init[0] == 0:
        fun.init_setup()
        set_init[0] = 1
    rlen = [0]
    pdata = []
    
    print("The nLen = %d" % nLen)   

    if nLen == 1:
        fun.show_function()
    elif nLen == 2:
        ret = fun.open_lock_all(addr)
    elif nLen == 3:
        addr_end = lock
        ret = fun.open_lock_cycle(addr, addr_end);
    elif nLen == 4: 
        if func == open:
            rlen[0] = fun.open_lock(addr, lock, ret_data)
            if rlen[0] == 5:
                print("open lock successful!!!")
            else: 
                print("open lock failed!!!")
        elif func == read:
            rlen[0] = fun.read_lock_state(addr, lock, ret_data)
            if lock != 0:      
                if rlen[0] == 5:
                    print("read lock successful!!!")
                else: 
                    print("read lock failed!!!")
            else:
                if rlen[0] == 8:
                    print("read lock successful!!!")
                else: 
                    print("read lock failed!!!")              
        elif func == inquire:
            rlen[0] = fun.inquire_board_address(addr, ret_data)
            if rlen[0] == 5:
                print("inquire_board_address successful!!!")
            else:
                print("inquire_board_address failed!!!")   
    else:
        print("The parameter is error!!!");

   
    for i in range(rlen[0]):
        pdata.append(ret_data[i])
    print(pdata)
    print(rlen[0])
    print("The lock end!!\n")
    return pdata
    



























