---
layout: default
title: Write a Powershell Script to Simplify SCP Transfer Syntax
date: 2025-02-27
domain: Guides
system: Windows
---

# Write a Powershell Script to Simplify SCP Transfer Syntax

---

Date: 2025-02-27  
OS/Distro: Windows 11 Pro  
Resources Used:  
- [How to Create and Run Your First Powershell Script File - Windows 10](https://www.windowscentral.com/how-create-and-run-your-first-powershell-script-file-windows-10)  
- [Powershell Command-Line Arguments](https://shellgeek.com/powershell-command-line-arguments/)  
- [Customizing Your Powershell Profile](https://www.howtogeek.com/50236/customizing-your-powershell-profile/)  

---

1. Problem: the syntax for running scp in powershell is burdensome. Here's what it looks like for me:
    
    ```
    PS C:\> scp -i C:\path\to\key\file -P <port> username@<static-ip-or-ddns-domain>:/path/to/destination/directory
    ```

2. In powershell, run the following command. I did so after `cd .\Documents\`. Name your script whatever you like.

    ```
    PS C:\> New-Item scp-transfer.ps1
    ```

3. Navigate to the file in File Explorer and open it with Notepad. Add the content below. The `param` enclosure defines command line arguments for us; that way, when we run `scp-transfer.ps1 filename.ext`, _filename_ will be stored in `$source`.
    
    ```
    param(
        [string]$source
    )

    scp -i C:\path\to\key\file -P <port> $source username@<static-ip-or-ddns-domain>:/path/to/destination/directory
    ```

4. To make this script operational, we need to set the execution policy. Open Powershell with _Run as Administrator_, which can be done by right-clicking Powershell from the start menu. Run the following command. When it asks if your sure, enter `'Y'.
    
    ```
    PS C:\> Set-ExecutionPolicy RemoteSigned
    ```

5. Now you can easily transfer a file to your server with a much shorter command.
    
    ```
    PS C:\> scp-transfer.ps1 filename.ext
    ```

6. Find a directory where your scripts will live. Here's a recommendation: `C:\Users\User\powershell_scripts\`
7. Let's make a Powershell profile if one doesn't already exist. Run `Test-Path $profile`. If it returns false, we have to create one with the following.

    ```
    New-Item -path $profile -type file -force
    ```

8. Navigate to and open the newly created file.
    
    ```
    cd C:\Users\Admin\Documents\WindowsPowerShell\
    notepad Microsoft.PowerShell_profile.ps1
    ```

9. Add the text below - an alias for our powershell script and Clear-Host.
    
    ```
    new-item alias:scp-transfer -value C:\Users\User\powershell_scripts\scp-transfer.ps1
    Clear-Host
    ```

9. Done! Now you can run `scp-transfer filename.ext` without worrying about the absolute path to the script.
