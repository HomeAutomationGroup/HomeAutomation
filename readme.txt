Instructions for running the Home Automation using RedBear Duo

Installing Arduino IDE:
	-https://www.arduino.cc/en/Guide/Windows
Instructions for selecting RedBear Duo Board Package:
	-https://github.com/redbear/Duo/blob/master/docs/arduino_board_package_installation_guide.md

1. We have developed the server on the Arduino IDE platform for Windows.
	We have used a static IP router with SSID: 'DDmini' with an IP Address in range of 192.168.0.100 to 192.168.0.199 and default gateway address 192.168.0.254 and it is not encrypted.

2. For the breadboard connection we have used 5 different colored LEDs viz. Red, Blue, Green, Yellow and White which are connected to the pins D0, D1, D2, D7 and D5 respectively.

3. On the client application there are respective switches for each LED and as well as a switch for Random LED which randomly toggles at diffrent frequencies(0.1-1.2 sec) for remaining on and (0.2-0.9 sec) for off.

4. Client connects to server when the view is loaded.Server ip used to connect in the client code is from TPLink DHCP client list and on port 27014.

5. Disconnect button on client application is to disconnect from the server.

6. Procedure to run: 
	a. Start the web server(Webwifiservernoencryption.ino) through Arduino IDE which is connected to RedBear Duo on the breadboard. From the Tools menu of the Arduino IDE, select the RedBear Duo (Native USB Port), check whether the Port is enabled on which the RedBear Duo is connected and select the Programmer as Duo FW Uploader. 
	b. Once server code has been uploaded and open the serial monitor which displays the server IP address along with the SSID.
	c. Connect from the client application through iOS application (HAClient) with the IP address that is displayed on the Serial Monitor. 