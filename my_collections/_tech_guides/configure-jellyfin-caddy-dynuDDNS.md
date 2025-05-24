---
layout: guide
title: Configure Jellyfin, Caddy, and Dynu DDNS
date: 2025-05-21
domain: Guides
system: Ubuntu
---

# Configure Jellyfin, Caddy, and Dynu DDNS

---

Date: 2025-05-21  
OS/Distro: Ubuntu 24.04.2 LTS (Ubuntu Server)  
Resources:  
- [Jellyfin Installation](https://jellyfin.org/docs/general/installation/)
- [Caddy - Getting Started](https://caddyserver.com/docs/getting-started)
- [Caddy - Reverse Proxy](https://caddyserver.com/docs/quick-starts/reverse-proxy)
- [Caddy - HTTPS](https://caddyserver.com/docs/quick-starts/https)
- [Jellyfin - Caddy Setup](https://jellyfin.org/docs/general/post-install/networking/caddy)
- [Dynu DDNS](https://www.dynu.com/en-US/ControlPanel/AddDDNS)

---

## Install Jellyfin

For this installation, we won't be using Docker. The process is as simple as navigating to Jellyfin's [installation guide](https://jellyfin.org/docs/general/installation/), selecting your operating system, and running a few commands. I installed mine on Ubuntu Server, so this was all I needed to do.

```
curl https://repo.jellyfin.org/install-debuntu.sh | sudo bash
```

Since my server is headless, I had to access the Jellyfin Setup Wizard via a browser on a separate machine. To do this, we need to configure LAN access on the server.

- Make sure the server private IP is static. Check out this short guide: [How to Set Up a Static IP](static-ip-setup.html).
- Open Jellyfin's default port for HTTP traffic - **8096**.

    ```
    sudo ufw add allow 8096/tcp
    ```

- Open a browser on a separate machine and access your Jellyfin server with **<static-ip-address>:8096**. From here, it's straightforward to create your users and simply click through the Setup Wizard.

## Install Caddy

These commands are straight from [caddyserver.com](https://caddyserver.com/docs/getting-started), and they are all that's required to get Caddy installed! Run these on the server machine.

```
sudo apt install -y debian-keyring debian-archive-keyring apt-transport-https curl
curl -1sLf 'https://dl.cloudsmith.io/public/caddy/stable/gpg.key' | sudo gpg --dearmor -o /usr/share/keyrings/caddy-stable-archive-keyring.gpg
curl -1sLf 'https://dl.cloudsmith.io/public/caddy/stable/debian.deb.txt' | sudo tee /etc/apt/sources.list.d/caddy-stable.list
sudo apt update
sudo apt install caddy
```

---

## [Optional] Test Caddy

### Write a Configuration File

Let's create a Caddyfile. We can put it anywhere for now, so I'm putting it in my main user directory.

```
cd ~
vim Caddyfile
```

Populate the Caddyfile with a "Hello, world!" test.

```
:2015

respond "Hello, world!"
```

Start the server, and verify that it worked.

```
caddy start
curl localhost:2015
```

### Set up a Reverse Proxy

Let's modify the Caddyfile.

```
:2015 {
    respond: "Hello, world!"
}

:2080 {
    reverse_proxy :2015
}
```

Then, reload the server, and verify that it worked.

```
caddy reload
curl localhost:2080
```

### Set Up HTTPS

Modify the Caddyfile:

```
:2015 {
    respond: "Hello, world!"
}

localhost {
    reverse_proxy :2015
}
```

Reload the server, and verify.

```
caddy reload
curl -v https://localhost
```

---

## Give Caddy HTTPS Capability

```
sudo setcap cap_net_bind_service=+ep $(which caddy)
```

## Set Up DDNS

I created a free account with [Dynu DDNS](https://www.dynu.com/en-US/ControlPanel/AddDDNS), selected a domain, and pointed it at my routers public IP address. If you don't know your routers public IP, you can run the following command on any Linux machine that's connected to it.

```
curl ip.me
```

## Port Forwarding

Find your router and note the _Username_, _Password_, and _Gateway_ written on the side.

If the gateway is not written on the router, open up the terminal and run the command `route -n` to find your routers gateway. It will probably be something like _192.168.0.x_.

Open a browser and enter the IP in the address bar. Enter the Username and Password.

My router interface has a side panel where I selected _Network Setting_, then _NAT_, and then _port forwarding_. I clicked _Add New Rule_, and added these values.

```
Service Name: jellyfin
Server IP Address: <static-IP-address>
Start Port: 443
End Port: 443
Translation Start Port: 443
Translation End Port: 443
Protocol: TCP
```

## Add UFW Rule

We need to add a rule to the firewall to enable HTTPS traffic.

```
sudo ufw allow 443/tcp
```

## Rewrite the Caddyfile

If you skipped the optional section, the Caddyfile will need to be created. Simply navigate to your user directory and create it there.

```
cd ~
vim Caddyfile
```

Point the DDNS domain at the test port **2015**.

```
:2015 {
    respond "Hello, world!"
}
<your-ddns-domain> {
    reverse_proxy 127.0.0.1:2015
}
```
Reload!

```
caddy reload
```

SSL Certificates should automatically generate. In a browser, input the following: **https://<your-ddns-domain>**. *"Hello, world!"* should appear.

## Finishing Touches

We're ready to connect Caddy to Jellyfin. Edit your Caddyfile to look like this.

```
<your-ddns-domain> {
    reverse_proxy 127.0.0.1:8096
}
```

Reload!

```
caddy reload
```

Open the browser and once again input: **https://\<your-ddns-domain\>**. The Jellyfin login should appear. Huzzah!


