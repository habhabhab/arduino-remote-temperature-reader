# arduino-remote-temperature-reader
Setting up arduino with ethernet shield to remotely read the temperature in my room

## What is needed
- arduino with temperature measurement from the "official arduino starter kit" as found on amazon
- ethernet shield 2 as found on amazon as well

## What it does
Sets up a server, runs the code for reading voltages and calculating the temperature, and prints out a simple html page that can be called from any device/browser in the network.

If you want to be able to call it from outside your local network, you need to enable port-forwarding in your router. There are many tutorials out there that explain this process for many different routers. Please be aware that this might be a security risk.

### What are my future plans
I want to set up a dashboard that allows me to see all the data that was collected in the past and be displayed in a really fancy way. However, right now I am not sure as to how I will do this. The possibilities are endless, but I don't want to spend money on hardware right now.

### Sources
- for the server: basically just followed the tut on startingelectronics.org: https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/
- for the temperature measurment: followed the tut that comes with the arduino starter kid
- for the combination of the two: pure magic and mad skillz.
