<style>
.main-header {
    color: cyan;
    font-family: Chalkduster;
}
</style>

<h3 style="color:lightgreen;">2025-05-04</h3>

OS/Distro: Slackware 15.0

Resources Used: \
[Download the the Ubuntu iso image](https://ubuntu.com/tutorials/try-ubuntu-before-you-install#1-getting-started)

Relevant Documents: \
[Slackware Install and Config](slackware-install-and-config.md)

<h1 class="main-header">The Problem</h1>
Currently, my disk is partitioned according to the scheme below:

```
/dev/sda1   500M    EFI System          /boot
/dev/sda2   4G      Linux swap          swap
/dev/sda3   25G     Linux filesystem    /
/dev/sda4   447.5G  Linux filesystem    /home
```

Since it was the first time I manually partitioned my disk for a Linux system, I tried to find the best practices online. Several people claimed that the size of **/** is often in the range of 15G to 30G. I chose 25G, allocating the remainder to **/home**. While attempting to install *GHC* (Glasgow Haskell Compiler), a 4G dependency that *pandoc* requires, my **/** partition maxed out. I went on Reddit to ask about the size of my **/** partition, and several people confirmed that it was much too small. One commentor said I should boot from a live usb and use *gparted* to reduce the size **/home** from the left and increase the size of **/** from the right. That's the solution I implemented.

<h1 class="main-header">The Solution</h1>
1. [Download the the Ubuntu iso image](https://ubuntu.com/tutorials/try-ubuntu-before-you-install#1-getting-started)
2. Burn it to an available USB drive.
    1. Insert the USB drive and run `lsblk` in the terminal. Determine the name of your device; in my case it is **/dev/sdb**.
    2. Navigate to the destination directory of your Ubuntu iso image download (probably **~/Downloads**). Run the following *dd* command.

    ```
    $ sudo dd if=ubuntu-24.04.2-desktop-amd64.iso of=/dev/sdb bs=4M status=progress
    ```

3. Reboot the computer and as it starts up, press whatever key interrupts the process to enter the BIOS settings. In my case, it is **Enter** followed by **F1**.
4. In the BIOS settings, reorder the boot priority list and put the USB drive at the top. Exit the BIOS settings and continue with bootup.
5. Open *gparted* and select the **/home** partition. In my case, it's **/dev/sda4**. Reduce the size of **/home** from the left side by your required amount, and increase **/** from the right by that same amount. Here's how the changes were indicated in *gparted*.

```
Move /dev/sda4 to the right and shrink it from 447.45 GiB to 422.45 GiB
Grow /dev/sda3 from 25.00 GiB to 50.00 GiB
```

6. Apply changes and wait for them to complete; it may take some time.
7. Reboot the system and remove the USB drive.
8. Enter the BIOS settings and reorder the boot priority so that your original settings are in place.
9. Done! My new partitions are as follows.

```
/dev/sda1   500M    EFI System          /boot
/dev/sda2   4G      Linux swap          swap
/dev/sda3   50G     Linux filesystem    /
/dev/sda4   422.5G  Linux filesystem    /home
```


