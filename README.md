# pcap-test

## Compile Output
```
13:47:13: Running steps for project pcap-test...
13:47:13: Configuration unchanged, skipping qmake step.
13:47:13: Starting: "/usr/bin/make" -j2
g++ -c -pipe -g -std=gnu++1z -Wall -Wextra -fPIC -DQT_QML_DEBUG -I../pcap-test -I. -I../Qt/6.1.2/gcc_64/mkspecs/linux-g++ -o main.o ../pcap-test/main.cpp
g++  -o pcap-test main.o   -lpcap   
13:47:13: The process "/usr/bin/make" exited normally.
13:47:13: Elapsed time: 00:00.
```

## Application Output
```
=========* [90 BYTES PACKET CAPTURED] *=========
------------* 1. ETH.SRC & ETH.DST *------------
eth.src: 00:0c:29:4a:ec:68
eth.dst: 00:50:56:ed:d0:d1
-------------* 2. IP.SRC & IP.DST *-------------
ip.src: 10.10.10.5
ip.dst: 10.10.10.5
-----------* 3. PORT.SRC & PORT.DST *-----------
port.src: 37655
port.dst: 123
---------* 4. HEXA PAYLOAD (8 BYTES) *----------
0x93 0x17 0x00 0x7b 0x00 0x38 0xc9 0xdb 
================================================
90 bytes captured

=========* [90 BYTES PACKET CAPTURED] *=========
------------* 1. ETH.SRC & ETH.DST *------------
eth.src: 00:50:56:ed:d0:d1
eth.dst: 00:0c:29:4a:ec:68
-------------* 2. IP.SRC & IP.DST *-------------
ip.src: 91.189.89.198
ip.dst: 91.189.89.198
-----------* 3. PORT.SRC & PORT.DST *-----------
port.src: 123
port.dst: 37655
---------* 4. HEXA PAYLOAD (8 BYTES) *----------
0x00 0x7b 0x93 0x17 0x00 0x38 0x1a 0xdc 
================================================
100 bytes captured

=========* [100 BYTES PACKET CAPTURED] *=========
------------* 1. ETH.SRC & ETH.DST *------------
eth.src: 00:0c:29:4a:ec:68
eth.dst: 00:50:56:ed:d0:d1
-------------* 2. IP.SRC & IP.DST *-------------
ip.src: 10.10.10.5
ip.dst: 10.10.10.5
-----------* 3. PORT.SRC & PORT.DST *-----------
port.src: 49455
port.dst: 53
---------* 4. HEXA PAYLOAD (8 BYTES) *----------
0xc1 0x2f 0x00 0x35 0x00 0x42 0x28 0x6e 
================================================
161 bytes captured

=========* [161 BYTES PACKET CAPTURED] *=========
------------* 1. ETH.SRC & ETH.DST *------------
eth.src: 00:50:56:ed:d0:d1
eth.dst: 00:0c:29:4a:ec:68
-------------* 2. IP.SRC & IP.DST *-------------
ip.src: 10.10.10.2
ip.dst: 10.10.10.2
-----------* 3. PORT.SRC & PORT.DST *-----------
port.src: 53
port.dst: 49455
---------* 4. HEXA PAYLOAD (8 BYTES) *----------
0x00 0x35 0xc1 0x2f 0x00 0x7f 0x52 0x46 
================================================
100 bytes captured

=========* [100 BYTES PACKET CAPTURED] *=========
------------* 1. ETH.SRC & ETH.DST *------------
eth.src: 00:0c:29:4a:ec:68
eth.dst: 00:50:56:ed:d0:d1
-------------* 2. IP.SRC & IP.DST *-------------
ip.src: 10.10.10.5
ip.dst: 10.10.10.5
-----------* 3. PORT.SRC & PORT.DST *-----------
port.src: 41078
port.dst: 53
---------* 4. HEXA PAYLOAD (8 BYTES) *----------
0xa0 0x76 0x00 0x35 0x00 0x42 0x28 0x6e 
================================================
161 bytes captured
```
