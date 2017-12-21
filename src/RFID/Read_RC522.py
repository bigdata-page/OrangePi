#!/usr/bin/env python
# -*- coding: utf8 -*-

import RPi.GPIO as GPIO
import MFRC522
import time



# Create an object of the class MFRC522
MIFAREReader = MFRC522.MFRC522()

# Welcome message
#print "Welcome to the MFRC522 data read fun"

# 读取RFID卡的ID号，返回ID；
def Read_RC522():

    #start =time.clock()
    # Scan for cards    
    (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)

    # If a card is found
    if status == MIFAREReader.MI_OK:
        print "Card detected"
    
    # Get the UID of the card
    (status,uid) = MIFAREReader.MFRC522_Anticoll()

    # If we have the UID, continue
    if status == MIFAREReader.MI_OK:
        # Print UID
        print "Card read UID: "+str(uid[0])+","+str(uid[1])+","+str(uid[2])+","+str(uid[3])
    
        # This is the default key for authentication
        key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
        
        # Select the scanned tag
        MIFAREReader.MFRC522_SelectTag(uid)

        # Authenticate
        status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)

        # Check if authenticated
        if status == MIFAREReader.MI_OK:
            MIFAREReader.MFRC522_Read(8)
            MIFAREReader.MFRC522_StopCrypto1()

            #endtime = time.clock()-start
            #print endtime
			#return the uid
            return(uid)
        else:
            print "Authentication error"			


def Read_RC522_Mul():

    stime = time.clock()

    uid1=Read_RC522()
    print "uid1"
    uid2=Read_RC522()
    print "uid2"
    uid3=Read_RC522()
    print "uid3"
    uid4=Read_RC522()
    print "uid4"
    uid5=Read_RC522()
    print "uid5"

    etime = time.clock() - stime
    print etime
	
    if uid1==uid3 or uid1==uid5 :
        print uid1
        return uid1
    elif uid3==uid5 :
        print uid3
        return uid3		
    elif uid1!=uid3 and uid5!=uid3:
        print "id random"	



