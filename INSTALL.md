# PROJECT INSTALLATION
Open a terminal and type the following command lines

		$ git clone https://github.com/mat0208/DaughterBoard_PayloadGCS.git
		$ cd DaughterBoard_PayloadGCS
	
## INSTALL Computer (GCS) side:

- Launch QtCreator. Press Ctrl-O and select payloadGCS.pro file in QtPayloadGCS folder. Launch the application. 
	
## INSTALL Daughter Board side:
	
		$ scp -rp DaughterBoard pi@raspberrypi.local:~
		$ ssh pi@raspberrypi.local
		$ ls  (this is to make sure that the folder DaughterBoard has effectively been copied)
		$ cd DaughterBoard
		$ sudo ./build.sh
	
- Answer 'Y' when you are requested if you want to reboot the Pi.
- Then a few more modifications need to be done. Connect again to the Pi through ssh and type:

		$ sudo nano /etc/rc.local

- Write "sudo ./../home/pi/DaughterBoard/run.sh" in /etc/rc.local file before the "exit 0" line, then press Ctrl-X and Y to save
- To install the RTC(realtime clock) module then follow this tutorial (https://learn.adafruit.com/adding-a-real-time-clock-to-raspberry-pi/overview) and type in the terminal: 

		$ sudo nano /lib/udev/hwclock-set 
		
and comment out these three lines:

		#if [ -e /run/systemd/system ] ; then
		# exit 0
		#fi

Add this line to etc/modules file (or your respective rtc module)

	rtc-ds1307

THen add this line to the /etc/rc.local file

	sudo /bin/bash -c "echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-1/new_device"

The system is now ready-to-use. Reboot and you will be able to begin a data login session.

- Plug in one Xbee on the computer and the other one on the Raspberry Pi.
- (Optional) Wire the Lidar to the Lidar connector as well as the Pyranometer to the Pyranometer connector. Nothings more need to be done for these sensors' set-up.
- (Optional) Plug in the OPLS USB cable in the Raspberry. On the Qt application click on "Add sensor" button and select OPLS.
- (Optional) Plug in the Wind sensor USB cable in the Raspberry. On the Qt application click on "Add sensor" button and select Wind sensor and its reference (FT205, FT742-SM or Trisonica).

Note: The order you use to plug in the sensors does not matters as long as you select the right one for the one you plugged in.
	
- On the Qt applicaton, click on "Send configuration" button when it is active (it won't be until the Pi has not reboot).

Your Daughter Board is now ready to acquire data!

## SSH over hotspot
If you can not access the RP through monitor and mouse follow these steps. In the boot partition of the RaspberryPi SD card add the following files.
 - Need to add en empty file called "ssh". There is no extension. 
 - Need to add file called "wpa_supplicant.conf" filled with: 
 
 For Raspian Jessie
 
 	network={
		ssid="YOUR_NETWORK_NAME"
		psk="YOUR_PASSWORD"
		key_mgmt=WPA-PSK
		}
		
 For Raspian Stretch
 
   	ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
 	network={
		ssid="YOUR_NETWORK_NAME"
		psk="YOUR_PASSWORD"
		key_mgmt=WPA-PSK
		}
		
Check if the process is running. Use the shell for RP and type (after reboot). 

	ps -U root |grep main
