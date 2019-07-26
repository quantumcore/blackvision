# blackvision
Buy me a Coffee : 35F5tgCydWo8LPvfT3zHVBKSVY2vCcLtAL

Command line Remote Access tool targeting Windows Systems.


###### Download Maxmind GeoIP2 Database from here ; [LINK](https://dev.maxmind.com/geoip/geoip2/geolite2/)
###### Extract the file under blackvision/
## How to use 

#### Install required modules
```
pip3 install -r requirements.txt
```
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
- [x] sendfile - Send File.
- [x] bsendfile - Send Binary file.
- [x] kill - Kill the connection.
- [x] info - View System Information (OS, RAM, Location Information, Username/Hostname, Location of Agent)
- [x] msgbox - Send Messagebox.
- [x] exec - Execute a Command on Remote Machine.
- [x] exec-file - Execute a file on the Remote Machine.
- [x] wanip - View Wan ip of remote machine.
- [x] hostname - View Remote PC Hostname.
- [x] username - View Remote PC username.
- [x] monitoroff - Turn of Monitor.
- [x] monitoron - Turn on Monitor.
- [x] cdopen - Eject CD Rom.
- [x] cdclose - Close CD Rom.
- [x] playaudio - Play Audio.
- [ ] keydump - Dump keylog buffer.

##### Termux Compatibilty
This app is compatible with Termux. Run it the same way you run it in Terminal.

#### TODO
- Fix sending file to single client.
- Fix multiple clients information saving.
- Add keylogging.
- Fix that `args[3]` does not get sent.
- Fix Broken connection problems.
