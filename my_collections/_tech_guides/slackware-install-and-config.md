---
layout: default
title: Installing and Configuring Slackware
date: 2025-04-22
domain: Guides
system: Slackware
---

# Installing and Configuring Slackware

---

Date: 2025-04-22  
OS/Distro: Slackware 15.0  
Resources Used:  
1. [download.liveslak.org](https://download.liveslak.org)  
2. [slackware.com](http://www.slackware.com)  
3. [Slackbook - Partitioning](https://www.slackbook.org/html/installation-partitioning.html)  
4. [rufus.ie](https://rufus.ie/en/) 
5. [In Pursuit of "Slack" - Slackware UEFI Plus Grub Install](https://m.youtube.com/watch?v=OZeJd5JPQro&pp=0gcJCdgAo7VqN5tD)  
6. [Best Practise in Partitioning Slackware](https://www.linuxquestions.org/questions/slackware-14/best-practise-in-partitioning-slackware-874007/)  
7. [Reddit - Giving sudo access to /sbin](https://www.reddit.com/r/slackware/comments/tvvzdw/comment/i3djzos/?utm_source=share&utm_medium=mweb3x&utm_name=mweb3xcss&utm_term=1&utm_content=share_button)  

---

## [Optional] Testing Slackware with the Live CD

1. Navigate to [slackware.com](http://www.slackware.com) and there should be a link to Slackware Live on the index page. Currently, it is [download.liveslak.org](https://download.liveslak.org). Once there, select the United States mirror for liveslak. Currently, it is found at [us.liveslak.org](https://us.liveslak.org).
2. At the bottom of the page, select `slackware64-live-<version>.iso` to begin the download.
3. Make sure rufus is installed and ready to go. You can get it at [rufus.ie](https://rufus.ie/en/). You'll likely want the x86 version.
4. Once the iso image is downloaded, open rufus and burn it to a USB drive. 

## Installing Slackware (Following [In Pursuit of "Slack"](https://m.youtube.com/watch?v=OZeJd5JPQro&pp=0gcJCdgAo7VqN5tD) YouTube Video - *Resource 5*)

1. Navigate to [slackware.com](http://www.slackware.com), select **Get Slack**, select **mirrors**, select **Slackware ISO Images**, select the directory of the latest version of Slackware at the bottom (in my case, *slackware64-15.0-iso/*), and download *slackware64-15.0-install-dvd.iso*. 
    - Using Rufus (or *dd*), burn the ISO image to a USB drive (I'll cover this in another guide).
    - Leave the drive inserted reboot the computer.
    - Enter the BIOS setup, make sure *secure boot* is disabled, and put the flash drive at the top of the boot list.
    - Continue bootup into Slackware ISO.
2. Find disk name: `fdisk -l`. My disk is `/dev/sda 476.94 GiB`.
3. Create Partitions: `cfdisk /dev/sda`. You may need to delete partitions so that only `FREE SPACE` is left. I used this partition scheme.
    
    ```
    /dev/sda1   500M    EFI System          /boot
    /dev/sda2   4G      Linux Swap          swap
    /dev/sda3   25G     Linux Filesystem    /
    /dev/sda4   447.5G  Linux Filesystem    /home
    ```
    - The partition scheme outlined by the video was different. I took my cue from _Gerard Lally's_ comment in [Best Practise in Partitioning Slackware](https://www.linuxquestions.org/questions/slackware-14/best-practise-in-partitioning-slackware-874007/) and [Slackbook - Partitioning](https://www.slackbook.org/html/installation-partitioning.html). Both recommended separate partitions for `/` and `/home`; the latter even suggested a separate partition for `/usr/local`, but that may be explored another day.

4. Check bad blocks: `no`; select root partition: `/dev/sda3`; format /dev/sda3: `ext4`.
5. Select other partitions for /etc/fstab; `/dev/sda4: ext4`; select mountpoint for /dev/sda4: `/home`.
6. FAT or NTFS detected: select _no_ for visible in Linux.
7. Install from USB stick; package series selection: keep defaults; select prompting mode: full. _--Wait for installation to complete_
8. Skip USB boot disk creation; skip LILO and ELILO install (important concept from YouTube video).
9. Select imps2 for mouse. _I wonder if this was the right choice_
10. Load GPM: _yes_; config network: _yes_; Domain name: _localdomain_; connect via VLAN: _no_.
11. Network Manager
12. Confirm startup services: default
    - rc.atd, rc.crond, rc.fuse, rc.messagebus, rc.syslog, rc.sshd

13. No custom fonts; hardware clock local time: _US/Pacific_; default ex/vi editor: _vim_; desktop environment: _xfce_.
14. Set root password
15. <div style="color:red">DON'T REBOOT SYSTEM!</div> We haven't installed LILO or ELILO, so there is no bootloader currently. Exit setup. Unplug USB.
16. Open shell. Again, do NOT reboot or power off!
    - `mount` to find out where the system is mounted. In my case `/mnt`.
    - `chroot /mnt /bin/bash`
    - `source /etc/profile`
    - `grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=grub`
    - `grub-mkconfig -o /boot/grub/grub.cfg`
    - `mkdir -p /boot/efi/EFI/boot`
    - `cp /boot/efi/EFI/grub/grubx64.efi /boot/efi/EFI/boot/bootx64.efi`

17. Encountered error running `shutdown -r now`: `shutdown: /dev/initctl: No such file or directory`.
    - "Solved" by forcing reboot with `reboot -f`. Not ideal solution.

18. Login with root and add new user:
    - `adduser` sean
    - User ID: leave blank and hit enter
    - Initial Group: hit enter then up arrow. Add "wheel" to group list.
    - Home directory [ /home/sean ]: hit enter
    - Shell [ /bin/bash ]: hit enter
    - Expiry Date (YYYY-MM-DD): leave blank and hit enter

19. Set up `sudo`
    - `visudo` uncomment `%wheel ALL=(ALL:ALL) ALL`
    - Exit root and login to new user

20. `startx` to start xfce display manager.
21. To change how xfce comes up, open the shell and run:
    - `su` then `vim /etc/inittab`
    - change `id:3:initdefault` to `id:4:initdefault`

22. DONE!

## Further Configuration

1. Apropos wasn't working
    - Run `sudo mandb -c` to create the manual database from scratch. This solves the problem.

2. Shutdown and reboot commands not working though they are found in system binaries `/sbin`.
    - Run with root authority `visudo` and uncomment line below `hard-coded PATH instead of the user's`.

3. Missing .ssh directory in `/home/<user>.
    - Simply create it `cd ~ & mkdir .ssh & touch .ssh/known_hosts`

4. Configure slackpkg
    - Uncomment one mirror (top one) in `/etc/slackpkg/mirrors` and run `slackpkg update`. Instructions found in slackpkg man entry.

5. Figure out package management in general (slackpkg seems underpowered)
    - See [Slackware Package Management](slackware-package-management.md).

6. Find out that **/** partition is too small. Take steps to make it larger. [Here is an account](expand-root-partition.md).
7. Installed UFW (Uncomplicated Firewall). The default firewall config tool is `iptables`.
