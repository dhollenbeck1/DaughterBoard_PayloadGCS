# PROJECT INSTALLATION
	$ git clone https://github.com/mat0208/DaughterBoard_PayloadGCS.git
	$ unzip DaughterBoard_PayloadGCS-master.zip
	$ cd DaughterBoard_PayloadGCS-master
## INSTALL Daughter Board side:
	$ scp -rp DaughterBoard pi@raspberrypi.local:~
	$ ssh pi@raspberrypi.local
	$ ls    -- to make sure the folder DaughterBoard has effectively been copied
	$ cd DaughterBoard
	$ sudo ./build.sh
	$ sudo nano /etc/rc.local
write "sudo ./../home/pi/DaughterBoard/run.sh" in rc.local file before the "exit 0" line
Press Ctrl-X and Y to save
	$ sudo reboot



