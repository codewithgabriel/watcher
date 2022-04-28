Overview
---------------
 Watcher is a system security program that keep eyes on your protected files located inside the directory specified in the `path_to_dir` parameter. Watcher can report to a remote network/system or local network/system all events and activies performed on this files in many cases, one good case is of cyber attacks or security breach. Current version of watcher support Unix-base and Unix-like Operating systems, Linux, MacOS and BSD to mention, efforts is ongoing for MS-DOS or Window support.
 
 
Quick Start
---------------
```shell
Usage: ./watcher --watcher[-server , -client] 127.0.0.1 path_to_dir
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


With the right permission on watcher, watcher can do the following.
 
  watcher will report which devices on the system is accessed, by which user and time.
 ```shell
 ./watcher --watcher-server 127.0.0.1 /dev 
 ```

watcher keep eyes on processes in the /proc/process_id to report process activities.
 ```shell
 ./watcher --watcher-server 127.0.0.1 /proc/1
 ```
 
watcher reports user's activities in the user /home directory
 ```shell
 ./watcher --watcher-server 127.0.0.1 /home/root
 ```
 watcher reports which configuration files are modified in the /etc
  ```shell
 ./watcher --watcher-server 127.0.0.1 /etc
 ```
 
 watcher reports which process read/write to  /tmp directory
  ```shell
 ./watcher --watcher-server 127.0.0.1 /tmp
 ```

watch over all file system locate in the /sys/fs/dir

  ```shell
 ./watcher --watcher-server 127.0.0.1 /sys/fs/ext4
 ```





