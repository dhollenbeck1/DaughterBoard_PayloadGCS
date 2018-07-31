# PROJECT INSTALLATION
	$ git clone https://github.com/mat0208/DaughterBoard_PayloadGCS.git
	$ unzip DaughterBoard_PayloadGCS-master.zip
	$ cd DaughterBoard_PayloadGCS-master
	
## INSTALL Computer (GCS) side:

	- Launch QtCreator. Press Ctrl-O and select payloadGCS.pro file in QtPayloadGCS folder. Launch the application. 
	

## INSTALL Daughter Board side:

	$ scp -rp DaughterBoard pi@raspberrypi.local:~
	$ ssh pi@raspberrypi.local
	- to make sure the folder DaughterBoard has effectively been copied

	$ ls  
	$ cd DaughterBoard
	$ sudo ./build.sh
	$ sudo nano /etc/rc.local
write "sudo ./../home/pi/DaughterBoard/run.sh" in /etc/rc.local file before the "exit 0" line, then press Ctrl-X and Y to save

	$ sudo reboot
Your Daughter Board is ready to acquire data



