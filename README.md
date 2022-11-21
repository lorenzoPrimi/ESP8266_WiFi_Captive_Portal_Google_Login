# ESP8266 WiFi Captive Portal with Google Login

## Disclaimer
This project is for testing and educational purposes. Use it only against your own networks and devices. I don't take any responsibility for what you do with this program.

## About this project
WiFi captive portal for the NodeMCU (ESP8266 Module) with DNS spoofing. It asks the user for an email and a password for a fake Google sign in, in order to "get connected to the internet".

After the user inserts its credentials, it shows a generic connection error.

The built-in LED will blink 5 times when some credentials are posted.

<b>Warning!</b> Your saved credentials will disappear when you restart/power off the ESP8266.

<b>Note:</b> If you want to see the stored credetials go to <a>"**http**://</a>yourcurrentwebsite.com<a>/creds</a>" or "**172.0.0.1**<a>/creds</a>"

# Screenshots

<table>
  <tr>
    <th>172.0.0.1/index</th>
    <th>172.0.0.1/post</th>
    <th>172.0.0.1/creds</th>
  </tr>
  <tr>
    <td><img src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/1_index.jpg" title="Index"></td>
    <td><img src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/2_post.jpg" title="Post"></td>
    <td><img src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/3_creds.jpg" title="Creds"></td>
  </tr>
</table>

# Installation (ESP8266 Flasher - Easy way)

1. Download <a href="https://github.com/nodemcu/nodemcu-flasher"><b>ESP8266 Flasher</b></a>.

2. Download the <b><a href="https://github.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/releases/download/1.0/release.bin">release.bin</b></a> file.

3. Open the ESP8266 Flasher and select the Node MCU port

<img width="80%" src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/1_port_selection.PNG">

4. Then, go to the config tab and select the .bin file you've just downloaded.

<img width="80%" src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/2_file_selection.png">

5. Finally, go back to the first tab and press "Flash"

6. Your Node MCU is ready!

# Installation (Arduino IDE)

1. Open your <a href="https://www.arduino.cc/en/main/software">Arduino IDE</a> and go to "File -> Preferences -> Boards Manager URLs" and paste the following link:
``http://arduino.esp8266.com/stable/package_esp8266com_index.json``
2. Go to "Tools -> Board -> Boards Manager", search "esp8266" and install esp8266
3. Go to "Tools -> Board" and select you board"
4. Download and open the sketch "<a href="https://github.com/BlueArduino20/ESP8266_WiFi_Captive_Portal_2.0/blob/master/ESP8266_WiFi_Captive_Portal_2.0.ino"><b>ESP8266_WiFi_Captive_Portal_2.0.ino</b></a>"
5. You can optionally change some parameters like the SSID name and texts of the page like title, subtitle, text body...
6. Upload the code into your board.
7. You are done!

# Donate!
<img src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/bitcoin.png" title="Bitcoin" width="150">
</br></br>Send *only bitcoin* to this address:<b>bc1qd9r07nxjruvhwp2zpgf3htepq77059yzn4ck72</b>
</br></br><img src="https://raw.githubusercontent.com/lorenzoPrimi/ESP8266_WiFi_Captive_Portal_Google_Login/master/src/qr_code.png" title="Bitcoin address" width="200">

# Credits
I would like to thank <a href="https://github.com/adamff1/ESP8266_WiFi_Captive_Portal_2.0">adamff1</a> for the  basic code I used to fork this project and <a href="https://github.com/kleo/evilportals">kleo</a> for the captive portal inspiration.
