---
layout: default
title: Install MakeMKV and Flash Firmware to the ASUS BW-16D1HT Optical Drive
date: 2025-04-25
domain: Guides
system: Ubuntu
---


# Install MakeMKV and Flash Firmware to the ASUS BW-16D1HT Optical Drive

---

Date: 2025-04-25  
OS/Distro: Ubuntu 24.04.2 LTS (Ubuntu Server)  
Resources Used:  
1. [makemkv forum - makemkv for Linux](https://forum.makemkv.com/forum/viewtopic.php?f=3&t=224)
2. [makemkv forum - Linux How To: Flash ASUS-BW-16D1HT](https://forum.makemkv.com/forum/viewtopic.php?t=22573)
3. [makemkv - old versions](https://www.makemkv.com/download/old/)
4. [makemkv forum - Flashing hands/does nothing.](https://forum.makemkv.com/forum/viewtopic.php?t=35901)
5. [makemkv forum - MakeMKV is free while in beta](https://forum.makemkv.com/forum/viewtopic.php?t=1053)
6. [makemkv forum - Custom firmware pack with LibreDrive patches](https://forum.makemkv.com/forum/viewtopic.php?f=19&t=19113#p71880)
7. [ffmpeg.org](https://ffmpeg.org/download.html)

## Installing MakeMKV
### Part 1 - Downloading Binary and Source Packages on Separate Computer
NOTE (2025-04-27): I ended up using makemkv version 1.17.7 since 1.18.1 did not seem to be working.
1. Download the two files found at the resource on a separate computer with a GUI.
    ```
    makemkv-bin-1.18.1.tar.gz
    makemkv-oss-1.18.1.tar.gz
    ```
2. `scp` the files to the machine running Ubuntu Server.
    ```
    scp -P <port> -i /path/to/identityfile makemkv-bin-1.18.1.tar.gz <user>@ipaddress:/home/<user>/
    scp -P <port> -i /path/to/identityfile makemkv-oss-1.18.1.tar.gz <user>@ipaddress:/home/<user>/
    ```
### Part 2 - Installing on Ubuntu Server Machine
1. In my case, the files needed to be un-Gzipped.
    ```
    gzip -d makemkv-bin-1.18.1.tar.gz
    gzip -d makemkv-oss-1.18.1.tar.gz
    ```
2. Then extracted.
    ```
    tar -xvzf makemkv-bin-1.18.1.tar
    tar -xvzf makemkv-oss-1.18.1.tar
    ```
3. Install dependencies.
    ```
    sudo apt-get install build-essential pkg-config libc6-dev libssl-dev libexpat1-dev libavcodec-dev libgl1-mesa-dev qtbase5-dev zlib1g-dev
    ```
4. As described in the guide, run the following:
    ```
    cd makemkv-oss-1.18.1
    ./configure
    make
    sudo make install
    ```
5. Next, make and install the binary file.
    ```
    cd makemkv-bin-1.18.1.tar
    make
    sudo make install
    ```
6. Verify that the install was successful.
    ```
    which makemkv   # should return /usr/bin/makemkv
    ```
7. Get the beta key and add it to a **settings.conf** file in **/root/.MakeMKV**. The Beta Key is at **Resource Link 5:** [Beta Key](https://forum.makemkv.com/forum/viewtopic.php?t=1053). The beta key updates every couple of months, or something like that, so you'll likely have to do this again. Also, the link to the beta key might change, not sure!
    ```
    sudo -i
    cd /root/.MakeMKV
    vim settings.conf
    ```
    Add `app_key = “<app_key>"` to the file. The key changes every month.

## Flash ASUS BW-16D1HT with Libredrive
This part almost made me throw my new optical drive off the balcony. Here's the steps that worked in the end. The most important resources were links 2, 3, and 4. It's not completely clear whether the problem was with the makemkv version (1.18.1) or the authority with which I was executing the commands (logged in as root or not). Executing `makemkvcon` created a **.MakeMKV** directory in my **/home** directory, and `sudo makemkvcon` created one in **/root**. The latter led to a successful rip. Below, you'll find the exact steps I took to make things work. \
1. Find and delete installed binary files for version 1.18.1. Delete all .MakeMKV directories and log files.
    ```
    which makemkv   # returns /usr/bin/makemkv
    cd /usr/bin && sudo rm makemkv makemkvcon

    # remove from user
    cd && rm -r .MakeMKV MakeMKV_log.txt

    # remove from root
    sudo -i
    rm -r .MakeMKV MakeMKV_log.txt
    ```
2. Download **makemkv-bin-1.17.7.tar.gz** and **makemkv-oss-1.17.7.tar.gz** from **Resource link 3**: [makemkv - old versions](https://www.makemkv.com/download/old/). Then, follow the first two steps as usual in [Installing MakeMKV](#installing-makemkv).
3. Make sure you're logged in as root `sudo -i`.
    - Navigate to **/root/.MakeMKV**: `cd /root/.MakeMKV`.
    - If it doesn't exist, pop a disc into the drive and run `makemkvcon info dev:/dev/sr0 --debug`. This is what I did, and of course it hung, so I hit **Ctrl-C**. Thus, my **.MakeMKV** directory was created. Perhaps there's a less stupid way to do it ¯\_(ツ)_/¯.
4. In **/root/.MakeMKV**, run the following:
    ```
    tar -tvf _private_data.tar      # this lists the compressed files without extracting
    ```
    You'll see a file like **sdf000000??.bin**. Mine was **sdf00000098.bin**.
    ```
    tar -xvf _private_data.tar sdf00000098.bin      # extract it
    ```
5. Next, we need the ASUS BW-16D1HT firmware patched with LibreDrive to liberate the drive and allow it to rip discs. On a separate computer, go to **Resource Link 5**: [makemkv forum - Custom firmware pack with LibreDrive patches](https://forum.makemkv.com/forum/viewtopic.php?f=19&t=19113#p71880), download the stuff, and get it on the Ubuntu Server machine; I used `scp` again, as in **Part 1 Step 2**.

6. Unzip, navigate to ASUS firmware, and move it to **/root/.MakeMKV**. The last step isn't strictly necessary, but I thought it more tidy.
    ```
    unzip mk-firmware-pack-20200720
    cd mk-firmware-pack-20200720/MK/ASUS/BW-16D1HT/
    cp ASUS-BW-16D1HT-3.10-WM01601-211901041014.bin /root/.MakeMKV
    ```
7. Finally, we can run the following:
    ```
    cd /root/.MakeMKV
    makemkvcon f -f sdf_00000098.bin -d /dev/sr0 rawflash -i ASUS-BW-16D1HT-3.10-WM01601-211901041014.bin
    ```
8. Done! That worked for me. Hopefully it works for you too.


## [Optional] Upgrade ffmpeg
1. The tutorial says that most Linux distributions ship with an outdated version of ffmpeg, and therefore, is it recommended to install the latest version. On a separate machine, download ffmpeg from the website: [ffmpeg.org](https://ffmpeg.org/download.html)
2. Send it over to Ubuntu Server machine.
    ```
    scp -P <port> -i /path/to/identityfile ffmpeg-7.1.1.tar.xz <user>@ipaddress:/home/<user>/
    ```
3. In my case, the file was compressed with xz, so I had to first decompress with `xz`.
    ```
    xz -d ffmpeg-7.1.1.tar.xz
    ```
4. Strangely, `tar` wouldn't work with the resulting tarball, so I had to recompress it with `gzip`.
    ```
    gzip ffmpeg-7.1.1.tar
    ```
5. Finally, tar worked.
    ```
    tar -xvzf ffmpeg-7.1.1.tar.gz
    ```
6. Build the program. I had to include the `--disable-x86asm` flag for mine to work.
    ```
    ./configure --prefix=/tmp/ffmpeg --enable-static --disable-shared --enable-pic --disable-x86asm
    ```
7. Run `make install`. This takes a while!
8. Finally, we have to configure and build makemkv-oss again.
    ```
    cd makemkv-oss-1.18.1
    PKG_CONFIG_PATH=/tmp/ffmpeg/lib/pkgconfig ./configure
    make
    sudo make install
    ```
9. Delete temporary install files.
    ```
    rm -rf /tmp/ffmpeg
    ```
10. Done!

### Note
Before doing all this, I ran `ffmpeg -version` and found I had version 6.1.1, which given the downloaded file `ffmpeg-7.1.1.tar.xz`, didn't seem like the latest version. Running `sudo apt upgrade ffmpeg` worked, but the version number didn't change. Furthermore, the version number didn't change with the whole above process of compiling from source. Either I messed something up, or I had the latest version to begin with.
