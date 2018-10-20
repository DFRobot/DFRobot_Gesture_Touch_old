<pre>
for raspberry, uart is for bluetooth, must disable it first. you cant use both bluetooth and uart
config on raspberry:

edit /boot/config.txt
<span style="color: red">sudo nano /boot/config.txt</span>
add <span style="color: blue">dtoverlay=pi3-disable-bt<span> at end of this file.

edit /boot/cmdline.txt
<span style="color: red">sudo nano /boot/cmdline.txt</span>
delete <span style="color: blue">console=serial0(or ttyAMA0),115200</span> or <span style="color: blue">console=serial0,115200 console=ttyAMA0,115200</span> in this file.

reboot
</pre>
