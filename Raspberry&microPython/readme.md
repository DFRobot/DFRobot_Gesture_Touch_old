for raspberry, uart is for bluetooth, must disable it first. you cant use both bluetooth and uart <br>
config on raspberry: <br>
 <br>
edit /boot/config.txt
<pre>
sudo nano /boot/config.txt
</pre>
add <span style="color: blue">dtoverlay=pi3-disable-bt<span> at end of this file. <br>
 <br>
edit /boot/cmdline.txt <br>
<pre>
sudo nano /boot/cmdline.txt
</pre>
delete 
<pre>
console=serial0(or ttyAMA0),115200
</pre>
or <br>
<pre>
console=serial0,115200 console=ttyAMA0,115200
</pre>
in this file. <br>
 <br>
reboot

----------------------------------

for micropython esp32

rx_pin = io9, tx_pin = io10
