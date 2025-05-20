---
layout: guide
title: Find Public IP Address
date: 2025-01-11
domain: Guides
system: Ubuntu
published: false
---

# Find Public IP Address

---

Date: 2025-01-11  
OS/Distro: Ubuntu 24.04.1 LTS  
Resources Used:  
- [4 Ways to Find Server Public IP Address in Linux Terminal](https://www.tecmint.com/find-linux-server-public-ip-address/)

---

```bash
# One
$ dig +short myip.opendns.com @resolver1.opendns.com

# Four - three options
$ curl ifconfig.co
$ curl ifconfig.me
$ curl icanhazip.com
```


