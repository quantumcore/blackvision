# blackvision

Command line Remote Access tool targeting Windows Systems.

###### Maximum number of clients is 1. 
## How to use 

#### Run server 
```
git clone https://github.com/lynxmk/blackvision.git
cd blackvision
python3 main.py
```

#### Generate Agent 
```
cd blackvision
python3 generate.py
```

#### Change Host/Port
Open settings.ini. And change host, port.
##### Commands 
- [x] Persistent.
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
- [ ] keydump - Dump keylog buffer.
