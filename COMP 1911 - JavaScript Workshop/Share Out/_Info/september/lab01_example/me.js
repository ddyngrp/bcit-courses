/*
	COMP1911
	LAB01 Example
*/

/*
	determine if they are using Windows Exploder or not
*/
if (navigator.appName != "Microsoft Internet Explorer") {
	document.write("Why don't you use internet explorer?<br />");
}

/*
	changeSource(elementID, newSrc)
	swaps the image source of
	elementID
	with the image described at
	newSrc
*/
function changeSource(elementID, newSrc) {
	document.getElementById(elementID).src=newSrc;
}	

/*
	doubleWidth(elementID)
	doubles the width of the given element
*/
function doubleWidth(elementID) {
	document.getElementById(elementID).width = 2 * document.getElementById(elementID).width;
}

/*
	makeRed(elementID) 
	alters the color of the given element to red - oooh scary!
*/
function makeRed(elementID) {
		document.getElementById(elementID).style.color="red";
}
	