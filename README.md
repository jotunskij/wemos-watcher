# wemos-watcher
Temperature and humidity watcher build on a Wemos D1 mini v2.

The WEMOS is setup as a webserver that serves json data on port 80. When a client
connects the WEMOS it reads i2c data from a temperature and humidity sensor and responds to the
clients request with the currently collected data.

I personally use this for realtime temperature and humidity watching of the attic and basement of my house.

**The following instructions apply to setup on OSX**

## To setup environment
 * Install https://www.wemos.cc/downloads
 * Install Python 2.7
 * Create the directory ```[sketchbook directory]/hardware/esp8266com```
 * Run the following terminal commands in that directory:
 * ```> git clone https://github.com/esp8266/Arduino.git esp8266```
 * ```> cd esp8266/tools```
 * ```> python get.py```
 * Clone this project to your sketchbook directory and add a ```secrets.h``` file with the following content:
```c++
namespace secrets {
  const char* ssid = "YOUR_WIFI_SSID";
  const char* password = "YOUR_WIFI_PASSWORD";
}
```


## To setup Arduino IDE
|Setting|Value|
|---|---|
|Board|WeMos D1 R2 & mini|
|CPU frequency|80MHz|
|Flash size|4M (1M..)|
|Upload speed|115200|
|Port|/dev/cu.wchusbserial1420|
|Programmer|AVRISP mkII|
|Serial monitor baud|115200|

## Install required libraries

Download both the following libraries and add to Arduino/libraries.

https://github.com/adafruit/DHT-sensor-library

https://github.com/adafruit/Adafruit_Sensor

