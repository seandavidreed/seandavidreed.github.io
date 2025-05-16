---
layout: default
title: Create SSH Alias on Windows
domain: Guides
system: Windows
published: false
---

# Create an SSH Alias on Windows

---

Date: 2025-02-26  
OS/Distro: Windows 11 Pro  
Resources Used:  
- [Guide to Creating an ssh Alias on Windows](https://www.linsnotes.com/posts/guide-to-creating-an-ssh-alias-on-windows/)

---

1. Create a config file in `C:\Users\%USERNAME%\.ssh\` via Powershell.
	```
    C:\Users\%USERNAME%\.ssh> New-Item config
    ```
2. In File Explorer, navigate to and open the new file, and populate it with the following:
	```
    Host <server>
    	Hostname <static-ip>
        User <username>
        Port <port>
        IdentityFile C:\path\to\your\private\key
    ```
    - Note: the path to the private key should be in the `.ssh` directory.
3. Done!
