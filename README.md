# nodeMCU Wake On Lan Server
Hardware Wake on Lan server for those who don't have Ethernet cables plugged directly to their PCs

The motivation for this was that my PC can't impliment Wake on Lan(WoL) simply becuase I don't have an Etherner cable plugged in. Since I am RDPign to my PC whenever I needed to do work outside of home, I needed a way to turn it on only whenever needed. That way I can save some money on electricity.

To realise this I used a cheap NodeMCU programmed with the Arduino IDE. It has a simple webserver, chosen because I wasn't able send UDP packets over VPN.


To use this yourselve, simply replace the WiFi Settings and the pin configuration for your setup. Since the NodeMCU has pull-up resistors soldered on it, there is no need to add ones by yourself. Beware that only GPIO0 and GPIO2 have proper pull-up resistors.
