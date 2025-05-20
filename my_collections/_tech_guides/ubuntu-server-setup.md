---
layout: guide
title: Ubuntu Server Setup
date: 2025-02-24
categories: Linux
system: Ubuntu
published: false
---

# Ubuntu Server Setup

---

Date: 2025-02-24  
OS/Distro: Ubuntu 24.04.2 LTS (Ubuntu Server)  
Resources Used:  
- [Connect to Wi-Fi From Command Line](https://linuxconfig.org/ubuntu-20-04-connect-to-wifi-from-command-line)  

---

1. Install Ubuntu Server from usb media
   - Wifi connection not found
   - Did not install Ubuntu Pro
   - Did not import SSH key
   - Did install openSSH as part of installation
   - Did not choose LVM
2. Connect to Wi-Fi
   - Find the name of the systems network interface: `ip a` -> _wlp1s0_
   - Create netplan configuration file if it doesn't already exist: `sudo vim /etc/netplan/50-cloud-init.yaml`
   - Add this to the yaml config file:
     
     ```
     network:
         wifis:
             wlp1s0:
                 optional: true
                 access-points:
                     "SSID":
                         password: "password"
                 dhcp4: true
     ```
   - Change permissions for _50-cloud-init.yaml_ with `sudo chmod 600 /etc/netplan/50-cloud-init.yaml`
   - Apply the changes: `sudo netplan apply`
   - Verify it worked: `ip a` -> wlp1s0: state UP
   - Can `exit` the terminal on the server machine now
3. Connect via ssh from client machine: `ssh username@server-name`

