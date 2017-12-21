#!/usr/bin/env python

import sys
import threading
import mythread
import time
import string
import ctypes
import lock

def init_data():
    for i in range(len(mythread.global_data_flag)):
        mythread.global_data_flag[i] = 0
    for i in range(len(mythread.rfid_data)):
        mythread.rfid_data.pop()
    for i in range(len(mythread.scan_data)):
        mythread.scan_data.pop()
		
def main():		
    print("Starting test RFID or Scanning....") 
    init_data()  
    sensor0 = mythread.get_sensor()
    print("the sensor0 = %d " % sensor0)
    while True:
        sensor0 = mythread.get_sensor()
        init_data()
        while sensor0 == 0:	
            print("Enter the Senseor")
            init_data()	
            sensor0 = mythread.get_sensor()
            scan_thread = threading.Thread(target = mythread.run_scanning, args=())
            rfid_thread = threading.Thread(target = mythread.run_rfid, args=())

            print("The thread running...")
            scan_thread.start()
            rfid_thread.start()
            scan_thread.join()
            rfid_thread.join()
            
            sensor0 = mythread.get_sensor()
            
            if mythread.global_data_flag[2] == 0:
                print("The data is error")
                continue
            elif mythread.global_data_flag[2] == 1:
                print("the scan data is: ")
                print(mythread.scan_data)
                break
            elif mythread.global_data_flag[2] == 2:
                print("the rfid data is: ")
                print(mythread.rfid_data)
                break
            
        #print("the global_data_flag = %d " % mythread.global_data_flag[2])
        
        if mythread.global_data_flag[2] != 0:
            break;
    print("Please remove the card ...")
    print("Enter the data analysis")
    #data = data_analysis()

    print("Open the lock!!")
    data = [1, 2, 1, 4] 
    ret_data = lock.open_lock(data)
    print(ret_data)
    print("Please wait...")
    
    print("The main exit()")	
    
if __name__ == '__main__':
    while True:
        main()
        time.sleep(5)
