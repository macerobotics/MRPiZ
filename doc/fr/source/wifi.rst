====
Wifi
====


Default Configuration
*********************


Connecting to a wifi rooter
***************************


Contents of **/etc/network/interfaces**::

   auto lo
   iface lo inet loopback
   
   allow-hotplug eth0
   iface eth0 inet dhcp
   
   allow-hotplug wlan0
   iface wlan0 inet manual
       wpa-roam /etc/wpa_supplicant/wpa_supplicant.conf
       post-up ifdown eth0
   iface default inet dhcp

Contents of **/etc/wpa_supplicant/wpa_supplicant.conf**::

   ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
   update_config=1
   
   network={
       ssid="YOUR_SSID_HERE"
       psk="YOUR_SECRET_PASSPHRASE_HERE"
       id_str="SOME_DESCRIPTIVE_NAME"
   }
