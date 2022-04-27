Introduction
---------------
 Watcher is a monitoring program that monitors your file/directory as specified in dir parameter.

Quick Start
---------------

Compile watcher

mkdir build
cd build
cmake .. ; make 

the above commands will compile watcher base on your platform and generate an executable file name 'watcher' , currently watcher only support Linux, BSD and MacOS.

Try this to get watcher running.

```shell
#syntax : ./watcher --watcher-server 127.0.0.1 path_to_directory # start watcher as server
# watcher start as the server and ready to watch all events
# happening in your specified directory such as file deleted,modified , file accessed etc.

./watcher --watcher-server 127.0.0.1 mydir # connect watcher to the server on the other end


```shellend



./watcher --watcher-client 127.0.0.1  # the starts watcher as client and ready to log events send by thee server if connected.

