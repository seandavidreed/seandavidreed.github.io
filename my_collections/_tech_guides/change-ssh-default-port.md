---
layout: guide
title: Change SSH Default Port
date: 2025-01-11
categories: Linux
system: Ubuntu
---

# Change SSH Default Port

---

Date: 2025-01-11  
OS/Distro: Ubuntu 24.04.1 LTS  
Resources Used:  
- [How to Change the SSH Port in Linux - Linuxize](https://linuxize.com/post/how-to-change-ssh-port-in-linux/)
- [sshd - SSH default port not changing (Ubuntu 22.10 and later) - Ask Ubuntu](https://askubuntu.com/a/1534466)

---

1. Port numbers 1 - 1024 are reserved for system services, so they're best left alone. Choose any port number >1024.

2. Allow the port through the firewall.
   
   ```bash
   $ sudo ufw allow <port>/tcp
   ```

3. Add the port to the ssh config file.
   
   ```bash
   $ sudo vim /etc/ssh/sshd_config
   ```
   
   In Vim, type `/Port 22`, which should find the same commented out. Below it, add your port number:
   
   ```
   #Port 22
   Port 1492       # Added by seandavidreed
   #AddressFamily any
   #ListenAddress 0.0.0.0
   #ListenAddress ::
   ```

4. Restart ssh.
   
   ```bash
   $ sudo systemctl restart sshd
   ```

5. Check that the port has been changed.
   
   ```bash
   $ sudo systemctl status ssh
   ```

## Troubleshooting a problem on Ubuntu 24.04.1 LTS

6. On Ubuntu 24.04.1 LTS, I had trouble getting the default port to actually change using steps 4 and 5. Consulting an answer on Ask Ubuntu (shared above), I got the default port to change.
   
   ```bash
   $ sudo systemctl daemon-reload
   $ sudo systemctl restart ssh.socket
   $ sudo systemctl restart ssh.service
   ```

7. Check that it worked.
   
   ```bash
   $ sudo systemctl status ssh
   ```
   
   
