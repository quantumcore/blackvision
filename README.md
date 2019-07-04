# hafaza (The Guardian Angel)

Command line Remote Access tool targeting Windows Systems.

###### Maximum number of clients is 1. 
## How to use 

#### Run server 
```
git clone https://github.com/lynxmk/hafaza.git
cd hafaza
python3 main.py
```

#### Generate Agent 
```
cd hafaza
python3 generate.py
```
##### Commands 
- [x] sendfile - Send File.
- [x] bsendfile - Send Binary file.
- [x] kill - Kill the connection.
- [x] info - View Information.
- [x] msgbox - Send Messagebox.
- [x] exec - Execute a Command on Remote Machine.
- [x] exec-file - Execute a file on the Remote Machine.
- [x] wanip - View Wan ip of remote machine.
- [x] hostname - View Remote PC Hostname.
- [x] username - View Remote PC username.
- [ ] keylog - Start keylogging.
- [ ] keydump - Dump keylog buffer.
