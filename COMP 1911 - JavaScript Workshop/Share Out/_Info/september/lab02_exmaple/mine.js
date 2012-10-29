/*
	COMP1911 lab02 example
*/

var timerId = null;
/*
	startTimer() intitates the 'animation'
*/
function startTimer(){
	if(timerId == null){
		//1000 millisecond interval = 1 second
		timerId = setInterval('moveImage()', '1000');
	}
}

/*
	moveImage() relocates the lion image up and to the right 1 pixel
*/
function moveImage(){
	var lionImage = document.getElementById("lion");
	lionImage.style.left = parseInt(lionImage.style.left) + 1;
	lionImage.style.top  = parseInt(lionImage.style.top) - 1;
}
/*
	newWindow() opens a new window with correct URL and window size etc
*/
function newWindow(){
	myWindow = window.open(
						"http://www.defendo.com", 
						"mine",
						"scrollbars=no,menubar=no,toolbar=no,titlebar=no,width=100,height=500");

	myWindow.location="http://www.defendo.com";
}	