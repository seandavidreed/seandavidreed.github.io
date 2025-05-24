---
layout: post
title: From Plex to Jellyfin
author: Sean David Reed
date: 2025-05-23
categories: Linux Ubuntu Servers Jellyfin
---

On April 29th, Plex increased the prices of its Plex pass subscription plans an d moved some key features behind that paywall. After that date, a Plex pass would be required to play video content remotely. The change was announced well in advance, and given I've been running a Plex media server since the start of this year, I knew I would have to do something about it: either cough up \\$120 dollars for the lifetime Plex pass before it jumped to \\$250, or switch to Jellyfin.

I chose Jellyfin. I'm a proponent of FOSS (Free and Open Source Software), so I knew I would eventually ditch the commercial confines of Plex for Jellyfin, especially since Plex seems to be signaling a move toward some of the practices of the dominant streaming services. The whole point of spinning up a media server was to remove the middlemen between me and my content, and to return to *owning* things again. I think of the controversial article put out by the World Economic Forum, [Welcome to 2030. I own nothing, have no privacy, and life has never been better](https://web.archive.org/web/20161125135500/https://www.weforum.org/agenda/2016/11/shopping-i-can-t-really-remember-what-that-is)

Okay, let me cool it with the melodrama. Plex users are still in control of the content on their servers, the platform provided is top-notch, and the software satisfies a very valid use case. I'm simply no longer in the target market.

Stuffy philsophical views aside, installing Jellyfin provided an opportunity to learn a few more technical skills. Its configuration is a bit more fussy than that of Plex. I used [Dynu DDNS](https://www.dynu.com/en-US/DynamicDNS) to make my router findable under a static domain, [Caddy](https://caddyserver.com/) to spin up a reverse proxy for managing incoming traffic and enforcing HTTPS, and, of course, [Jellyfin](https://jellyfin.org/) to organize and serve my content: I elected not to run Jellyfin in a docker container, but that may change in the future.

I wrote a guide of the whole install and configuration process. Looking back on it, it really is quite simple. However, I still had some difficulties. There were some key things I didn't know, and worse, I didn't know that I didn't know them. For instance, when first configuring the reverse proxy, I was trying to point my DDNS domain to the static IP of my server machine, *192.x.x.x*, instead of the IP for localhost, *127.0.0.1*. That silly error was one of several that dragged out the process.

Next time I configure a server in this way, i.e. with a reverse proxy, it will be much easier. [Here's the guide I wrote](/tech_guides/configure-jellyfin-caddy-dynuDDNS.html).
