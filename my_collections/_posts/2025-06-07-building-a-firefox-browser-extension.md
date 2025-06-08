---
layout: post
title: Building a Firefox Browser Extension - Part One
author: Sean David Reed
date: 2025-06-07
category: Internet
---

## Background
Transforming my [Programming Log](/archive.html) into this website has proven to be quite an undertaking, and I’ve thoroughly enjoyed it. The log consists of five giant markdown files, one for each year; it was a journal for all my technology projects and learning over the years. The trouble is it isn’t very searchable, and as such, I eventually stopped updating it. I built this site to solve that problem.

I mostly have everything how I want it. No doubt I will make style changes in the future, but structurally, I think things are mostly set. Unfortunately, rearranging the [programming log](/archive.html) files into new directories inevitably broke some of my links; I had to sift through many of my pages and fix them. It got me thinking about the related problem of _link rot_.

## Link Rot
_Link rot_ refers to the tendency of internet links to break as the websites to which they point go offline, change URLs, or remove a particular page or post. Anyone producing content on the Internet will feel its effects. My website will suffer link rot, and indeed it already suffers broken links, albeit by my own doing.

I began thinking about a program that would sift the outgoing links of a website and make a report of broken links and where to find them. Such a tool would be great for anyone trying to maintain a website. I decided it would be best implemented as a _browser extension_, and I’m starting with Firefox.

## First Steps
I’ll admit getting started has been tough. I’m poring over the MDN Web Docs trying to get acquainted with the structure of extensions. It seems simple at first, but it isn’t. I have mixed feelings about [MDN Web Docs](https://developer.mozilla.org/en-US/): they are excellent and incredibly thorough, but sometimes difficult to navigate.

I started with the _Browser Extensions Getting Started_ section, specifically the guides [Your first extension](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Your_first_WebExtension) and [Your second extension](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Your_second_WebExtension). The latter made things more confusing in some respects. I plan to consult the _How to_ section next, with guides like [Modify a web page](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Modify_a_web_page). I think I should be able to make more headway.
