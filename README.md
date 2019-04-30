# waterqualityusingturbiditysensor
Monitor the quality of water using turbidity sensor


Softwares installed:
1. Arduino ver. 1.8.9 for Windows

Libraries installed in Arduino:
Go to 'Tools'-> 'Manage libraries'-> type the below mentioned libraries and click install
1. Thingspeak
2. ESP8266

Connect turbidity sensor to arduino:
1. Go to Tools and select board as 'Arduino/Genuino Uno'
2. Upload the 'turbidity' code
3. After code is uploaded open Serial Monitor and Turbidity values will be displayed and if water is potable or not

Connect wifi module to thingspeak:
1. Go to Tools and select board as 'Generic ESP8266 Module'
2. Upload the 'wifi_connect' code 
3. Make sure to change to your wifi ssid, password and thingspeak API write key.
4. After code is uploaded there will be a message saying 'Connected'

If there are errors check if correct port is connected
Ex: COM8, COM6
