---
layout: post
title: Building a Firefox Browser Extension - Part Two
author: Sean David Reed
date: 2025-06-17
category: Internet
---

When my browser extension is complete, it will need to highlight any dead links it finds in the page. To accomplish this, I’ve been experimenting with the [find API](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/API/find), using the word “and" to test it. I struggled to get it working at first. The following methods constitute _find_:

```
browser.find.find(
	queryPhrase,
	options
);

browser.find.highlightResults(
	options
);

browser.find.removeHighlighting();
```

I was loosely following the [Modify a web page](https://developer.mozilla.org/en-US/dacs/Mozilla/Add-ons/WebExtensions/Modify a web page) how-to guide, so my Firefox extension directory was looking like this:

```
rotten/
	background.js
	manifest.json
	rotten.js
```


I kept trying to have `background.js` call `rotten.js` (the content script that corresponds to the page in the active tab), which housed the `find()` code. Try as I might, I could never get the “ands” to highlight!

Examining the [find-across-tabs](https://github.com/mdn/webextensions-examples/tree/main/find-across-tabs) example extension, I noticed that the `find()` call was contained in the `background.js` file; moreover, it was contained within an _async_ function and prepended with _await_. I had tried using such an approach in the _content script_ `rotten.js` to no avail, but when I put everything in `background.js` it finally worked:

manifest.json

```
{
	“manifest_version”: 2,
	“name”: “rotten”,
	“version”: “1.0”,

	“permissions”: [“activeTab, “contextMenus”, “find”],

	“background”: {
		“scripts”: [“background.js”]
	}
}
```

background.js

```
async function find() {
	let result = await browser.find.find(“and”);
	browser.find.highlightResults();
}

browser.contextMenus.create({
	id: “rotten”,
	title: “Highlight rotten links”
});

browser.contextMenus.onClicked.addListener((info, tab) => {
	if (into.menuItemId === “rotten”) {
		find();
	}
});
```
