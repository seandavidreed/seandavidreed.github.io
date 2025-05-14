function addDarkmodeWidget() {
	const options = {
		time: "0.2s"
	}
	new Darkmode(options).showWidget();
}
window.addEventListener('load', addDarkmodeWidget);
