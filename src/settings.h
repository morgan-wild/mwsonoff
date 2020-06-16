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
