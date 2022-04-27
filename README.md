Overview
---------------
 Watcher is a monitoring program that monitors your files in directory as specified in directory parameter.

Quick Start
---------------
```shell
Usage: ./watcher --watcher[-server , -client] 127.0.0.1 dirname
--help     display help
--watcher-server     watcher as server.
--watcher-client     watcher as client.

Param
dirname		specify the directory which contains your desire files to monitor.
```
Compile watcher
---------------

```shell
mkdir build
cd build
cmake .. ; make 
```
the above commands will compile watcher base on your platform and generate an executable file name 'watcher' , currently watcher only support Linux, BSD and MacOS.

note: you may delete the build directory that follow this project.

Try this to get watcher running.
---------------------------------
```shell
 ./watcher --watcher-server 127.0.0.1 path_to_directory # start watcher as server
```
watcher start as server running on port 8989 and ready to watch all events
happening in your specified directory such as file deleted,modified , file accessed etc.

```shell
 ./watcher --watcher-client 127.0.0.1			#start watcher as client
```
watcher as client and ready to log events send by the server if connected.




