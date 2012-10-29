function changeLeftImage() {
	document.getElementById("ship1").src = document.getElementById("ship2").src;
}

function doubleWideRightImage() {
	document.getElementById("ship2").width = document.getElementById("ship2").width * 2;
}

function blackTextToRed() {
	document.getElementById("textID").style.color = "#FF0000";
}