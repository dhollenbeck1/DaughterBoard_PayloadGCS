# PROJECT INSTALLATION
- Open a terminal and type the following command lines:
	$ git clone https://github.com/mat0208/DaughterBoard_PayloadGCS.git
	$ unzip DaughterBoard_PayloadGCS-master.zip
	$ cd DaughterBoard_PayloadGCS-master
	
## INSTALL Computer (GCS) side:

- Launch QtCreator. Press Ctrl-O and select payloadGCS.pro file in QtPayloadGCS folder. Launch the application. 
	
## INSTALL Daughter Board side:

	$ scp -rp DaughterBoard pi@raspberrypi.local:~
	$ ssh pi@raspberrypi.local
	$ ls  (this is to make sure that the folder DaughterBoard has effectively been copied)
	$ cd DaughterBoard
	$ sudo ./build.sh
	$ sudo nano /etc/rc.local
- Write "sudo ./../home/pi/DaughterBoard/run.sh" in /etc/rc.local file before the "exit 0" line, then press Ctrl-X and Y to save
- Plug in one Xbee on the computer and the other one on the Raspberry Pi.
- (Optional) Wire the Lidar to the Lidar connector as well as the Pyranometer to the Pyranometer connector. Nothings more need to be done for these sensors' set-up.
- (Optional) Plug in the OPLS USB cable in the Raspberry. On the Qt application click on "Add sensor" button and select OPLS.
- (Optional) Plug in the Wind sensor USB cable in the Raspberry. On the Qt application click on "Add sensor" button and select Wind sensor and its reference (FT205, FT742-SM or Trisonica).
Note: The order you use to plug in the sensors does not matters as long as you select the right one for the one you plugged in.
- You now need to reboot the Pi. In the ssh terminal type:
	$ sudo reboot
	
- Click on "Send configuration" button when it is active.

Your Daughter Board is now ready to acquire data!
