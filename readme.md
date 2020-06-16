
Sonoff MW firmware
=================

This is a simple firmware made to control Sonoff modules via REST commands.



Features
-----------------

* Wifi connection as station.
* Connection status displayed with the green led.
* Remote control using REST commands.
* Local control using the physical button.
* Pinouts for different Sonoff models are ready to use.

Todo features

* Supprot of modules with multiple relays.


Setup
-----------------

### Pinout selection ###

The affectation of the pins may change from a model to another.

To select the right one, edit the following line in src/main.ino:

    #include "pinsRF.h"


### Settings ###

All the settings are in the file src/settings.h.

It looks like:

    // Basical Wifi station settings  
    #define WIFI_SSID                   "YOUR-SSID"  
    #define WIFI_PASSWORD               "YOU-PASSWORD"  
    #define WIFI_DEVICE_NAME            "DEVICE-NAME"  

    // Optional for static ip address, comment the following section for DCHP  
    #define WIFI_DEVICE_STATIC_IP       IPAddress(192, 168,   1, 90)  
    #define WIFI_DEVICE_STATIC_SUBNET   IPAddress(255, 255, 255,  0)  
    #define WIFI_DEVICE_STATIC_GATEWAY  IPAddress(192, 168,   1,  1)  
    #define WIFI_DEVICE_STATIC_DNS      IPAddress(192, 168,   1,  1)  

    // Port used for HTTP  
    #define WEB_SERVER_PORT             80  

Flashing
-----------------

### Connection ###

To flash your module, you need an USB to TTL 3.3v adapter like the FTDI FT232RL and 4 wires.  
Then, follow these steps :


1. The Sonoff modules are generally easy to open, do it and identity the 4 pins named GND, TX, RX and 3V3.

2. Make sure the converter uses the 3.3v level (not 5V). You can generally change it with a jumper.

3. Make the following connection between the converter and the Sonoff module :  

        GND --- GND
        TX  --- RX
        RX  --- TX
        VCC --- 3V3

4. Connect the converted to your computer via USB.

5. Entering Flash mode :  
    1. Disconnect VCC.
    2. Keep pressed the physical button of your Sonoff module.
    3. Reconnect VCC.
    4. Release the physical button.

6. Launch the flashing your module with PlatformIO.

7. Then, disconnect and reconnect VCC to comeback to the normal mode.

8. The green led will blink and stay off, your module is connected to your Wifi and is ready to use!


Usage
-----

Your Sonoff module is flashed. It starts normally and is connected to your network.

### REST API ###

The module is reachable over your local network via HTTP (No HTTPS).

GET /  
Returns the current state of your module.  
Plain text "ON" or "OFF"

POST /toggle 
Toggle the current state.  
Returns the current state.   
Plain text "ON" or "OFF"

POST /on 
Turn on the current state.  
Returns the current state.   
Plain text "ON"

POST /off
Turn off the current state.  
Returns the current state.   
Plain text "OFF" 




### Local control ###

You can toggle the state of the module using the physical button.