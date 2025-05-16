---
layout: default
title: Set Up a Static IP Address
date: 2025-01-09
categories: Linux
system: Ubuntu
---

# Set Up a Static IP Address

---

Date: 2025-01-09  
OS/Distro: Ubuntu 24.04.1 LTS  

---

## Using the GUI

1. Open settings and navigate to Wi-Fi.
2. Locate your connection and click the _gear_ icon.
3. Select the IPv4 tab and set _IPv4 Method_ to _Manual_.
4. Populate the _Address_, _Netmask_, _Gateway_, and _DNS_ fields with the following values:
   - Address: 192.168.x.x - It's often easiest to find the current dynamic IP address  and simply make that one static. Run `$ hostname -I`. Otherwise, you can select one from the IP range: [Find Router IP Range](find-router-ip-range.md)
   - Netmask: 255.255.255.0
   - Gateway: 192.168.x.x - Find this IP by running `$ route -n`
   - DNS: 1.1.1.1, 8.8.8.8 - (I've been able to omit this before)

5. You're Done!

---

## Using the Command Line

1. `sudo apt install network-manager`
2. `nmcli -d` to identify network interface -> wlp1s0
3. Open netplan config file, `sudo vim /etc/netplan/50-cloud-init.yaml`, and make sure it says the following:

    ```
    network:
    wifis:
    wlp1s0:
    optional: true
    access-points:
    "SSID":
    password: "password"
    dhcp4: false
    addresses:
    - <static-ip-of-your-choice>/24
    routes:
    - to: default
    via: <router-internal-ip>
    nameservers:
    addresses: [8.8.8.8, 8.8.4.4]
    ```

4. `sudo netplan apply` -> this command may log you out. To log back in, `ssh username@static-ip-you-chose`
5. Done!
