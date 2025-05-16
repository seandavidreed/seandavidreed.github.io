---
layout: default
title: Setup SSH Key Access
date: 2025-01-12
domain: Guides
system: Ubuntu
published: false
---

# Setup SSH Key Access

---
 
Date: 2025-01-12  
OS/Distro: Ubuntu 24.04.1 LTS  
Resources Used:  
- [How to Setup Passwordless SSH Login | Linuxize](https://linuxize.com/post/how-to-setup-passwordless-ssh-login/)
- [Alternative to ssh-copy-id on windows - Super User](https://superuser.com/a/1815968)

---

## Client Side

1. Check for existing SSH keys. If they exist, try using them instead, or back them up and generate new ones. If keys are overwritten, other SSH connections could be disrupted.
   
   ```bash
   $ ls -al ~/.ssh/id_*.pub
   ```

2. Generate a 4096-bit key pair. Simply hit enter for "file in which to save" and passphrase (leaving it blank).
   Linux:
   
   ```bash
   $ ssh-keygen -t rsa -b 4096 -C "email@domain.com"
   ```
   
   Windows:
   
   ```powershell
   C:\> ssh-keygen -t rsa -b 4096 -C "email@domain.com"
   ```

3. Copy the _public_ key (with the .pub extension) from the client to the server. You will be prompted to enter your password.
   Linux:
   
   ```bash
   $ ssh-copy-id remote_username@server_ip_address
   ```
   
   Windows (solution found on superuser.com):
   
   ```powershell
   C:\> type %USERPROFILE%\.ssh\id_rsa.pub | ssh user@host "cat >> .ssh/authorized_keys"
   ```

4. Verify that you can SSH into your server without a password.
   Linux:
   
   ```bash
   $ ssh remote_username@server_ip_address
   ```
   
   Windows:
   
   ```powershell
   C:\> ssh remote_username@server_ip_address
   ```

## Disable Password Authentication - Server Side

Disabling Password Authentication will require any machine that wants to access the server to have the private key. This will provide better security than Username and Password access.

5. Open the `sshd_config` file.
   
   ```bash
   $ sudo vim /etc/ssh/sshd_config
   ```

6. Modify the fields _PasswordAuthentication_, _ChallengeResponseAuthentication_, and _UsePAM_.
   
   ```bash
   PasswordAuthentication no
   ChallengeResponseAuthentication no
   UsePAM no
   ```
   
   - In my case, I couldn't find _ChallengeResponseAuthentication_ even after running `/ChallengeResponseAuthentication` in Vim. Adjusting the other fields seemed to do the trick though. Needs further investigation.

7. Restart the SSH service.
   
   ```bash
   Sudo systemctl restart ssh
   ```
   
   - If the above command doesn't work, try the commands in [Change SSH Default Port](/change-ssh-default-port.md) at _Steps 6 and 7_.

8. [Optional] Verify that you cannot SSH into the server by trying to establish a connection from a machine without the private key.
9. Done!
