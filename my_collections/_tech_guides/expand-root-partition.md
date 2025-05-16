---
layout: default
title: Expand Your Root Partition
date: 2025-05-04
domain: Guides
system: Slackware
---

# Expand Your Root Partition

---

Date: 2025-05-04  
OS/Distro: Slackware 15.0  
Resources Used (External):  
- [Download the Ubuntu iso image](https://ubuntu.com/tutorials/try-ubuntu-before-you-install#1-getting-started)

Relevant Documents (Internal):  
- [Slackware Install and Config](slackware-install-and-config.md)

---

## The Problem
Currently, my disk is partitioned according to the scheme below:

```
/dev/sda1   500M    EFI System          /boot
/dev/sda2   4G      Linux swap          swap
/dev/sda3   25G     Linux filesystem    /
/dev/sda4   447.5G  Linux filesystem    /home
```

Since it was the first time I manually partitioned my disk for a Linux system, I tried to find the best practices online. Several people claimed that the size of **/** is often in the range of 15G to 30G. I chose 25G, allocating the remainder to **/home**. While attempting to install *GHC* (Glasgow Haskell Compiler), a 4G dependency that *pandoc* requires, my **/** partition maxed out. I went on Reddit to ask about the size of my **/** partition, and several people confirmed that it was much too small. One commentor said I should boot from a live usb and use *gparted* to reduce the size **/home** from the left and increase the size of **/** from the right. That's the solution I implemented.

## The Solution
1. [Download the the Ubuntu iso image](https://ubuntu.com/tutorials/try-ubuntu-before-you-install#1-getting-started)
2. Burn it to an available USB drive.
3. Insert the USB drive and run `lsblk` in the terminal. Determine the name of your device; in my case it is **/dev/sdb**.
4.  Navigate to the destination directory of your Ubuntu iso image download (probably **~/Downloads**). Run the following *dd* command.

    ```
    $ sudo dd if=ubuntu-24.04.2-desktop-amd64.iso of=/dev/sdb bs=4M status=progress
    ```

5. Reboot the computer and as it starts up, press whatever key interrupts the process to enter the BIOS settings. In my case, it is **Enter** followed by **F1**.
6. In the BIOS settings, reorder the boot priority list and put the USB drive at the top. Exit the BIOS settings and continue with bootup.
7. Open *gparted* and select the **/home** partition. In my case, it's **/dev/sda4**. Reduce the size of **/home** from the left side by your required amount, and increase **/** from the right by that same amount. Here's how the changes were indicated in *gparted*.

    ```
    Move /dev/sda4 to the right and shrink it from 447.45 GiB to 422.45 GiB
    Grow /dev/sda3 from 25.00 GiB to 50.00 GiB
    ```

8. Apply changes and wait for them to complete; it may take some time.
9. Reboot the system and remove the USB drive.
10. Enter the BIOS settings and reorder the boot priority so that your original settings are in place.
11. Done! My new partitions are as follows.

    ```
    /dev/sda1   500M    EFI System          /boot
    /dev/sda2   4G      Linux swap          swap
    /dev/sda3   50G     Linux filesystem    /
    /dev/sda4   422.5G  Linux filesystem    /home
    ```
