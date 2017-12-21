#!/usr/bin/env python

import sys
import threading
import time
import RPi.GPIO as GPIO
import RFID.MFRC522
import RFID.Read_RC522
import ctypes

scan_data = []
rfid_data = []

# $0==>> scan_flag $1==>>rfid_flag $1==>>main_flag
global_data_flag = [0,0,0]

# 
SENSOR = 36

def get_sensor():
    # getting the sensor data
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(SENSOR,GPIO.IN,GPIO.PUD_UP)
    time.sleep(0.1)
    return GPIO.input(SENSOR)
	
def run_scanning():
    print("This is the scan function...")
    scan_function = ctypes.CDLL("./SCAN/libscan.so")
    array = ctypes.c_char*128
    data = array()
    fd = scan_function.scan_open();
    if fd < 0:
        print("the scan device cann't open")
    ret = 0
    
    while True:	
        for i in range(len(scan_data)):
            scan_data.pop();	
                    
        for i in range(2):
            ret = scan_function.scan_getdata(fd, data)          
            if ret > 0:           
                for i in range(ret):
                    scan_data.append(data[i])       
                print(scan_data)    
                break;
            if global_data_flag[2] != 0:
                break
        
        sensor1 = get_sensor()      
        if sensor1 == 0:
            if len(scan_data):
                global_data_flag[0] = 1
                global_data_flag[2] =  global_data_flag[2] + 1
                print(scan_data)
        else:
            scan_function.scan_close();
            break
            
        if (global_data_flag[0] == 1 or global_data_flag[1] == 1):
            scan_function.scan_close();
            break
        time.sleep(0.5)

def run_rfid():
    print("This is the rfid function...")
    while True:
        for i in range(len(rfid_data)):
            rfid_data.pop() 
        for i in range(2):	
            uid=RFID.Read_RC522.Read_RC522_Mul()
            time.sleep(0.1)
            if global_data_flag[2] != 0:
                break
            if uid:
                break
                
        if uid:
            global_data_flag[1] = 1
            global_data_flag[2] = global_data_flag[2] + 2
            #get the data of rfid card
            for i in range(len(uid)):
                rfid_data.append(uid[i])
                   
        print("the global_data_flag = ")
        print(global_data_flag)
              
        print("the rfid_data = ")
        print(rfid_data)
               
        if (global_data_flag[0] == 1 or global_data_flag[1] == 1):
            break;
            
        sensor2 = get_sensor()
        if sensor2 == 1: 
            break
       
        time.sleep(0.5)
        
        
        

