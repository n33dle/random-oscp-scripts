#!/usr/bin/python
import socket
import sys
import time

labrange = open('<filename>.txt', 'r')
for ip in labrange.readlines():
        try:#try/except/else loop
                print ip #print IP currently working on in loop
                s=socket.socket(socket.AF_INET, socket.SOCK_STREAM) #create a socket within the loop so it creates a new one if it fails
                s.settimeout(20) #set a timeout due to lab lag
                s.connect((ip, 25)) #connect to IP in list on port 25
                banner=s.recv(1024) #receive banner
                print banner # Print banner
                s.send('VRFY root' + '\r\n') #send VRFY root and cut
                result=s.recv(1024) # set result as value
                print result #print reults
                time.sleep(5) #wait 5 secs
                s.close() #close socket
                pass
        except Exception, e: #print exception
                print e