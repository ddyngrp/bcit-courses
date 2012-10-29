var timer = null;
var targetURL;

function dispHandle(obj) {
	if (obj.style.display == "none") {
		obj.style.display = "";
	}
	else {
		obj.style.display = "none";
	}
}

function timerControl() {
	if(timer == null){
		timer = setInterval('moveImage()', '1000');
	}
}

function moveImage() {
	var movingImage = document.getElementById("lion");
	
	movingImage.style.top  = parseInt(movingImage.style.top) - 1;
	movingImage.style.left = parseInt(movingImage.style.left) + 1;
}

function openWindow(targetURL) {
	newWindow = window.open(targetURL,targetURL,"scrollbars=no,menubar=no,status=no,toolbar=no,titlebar=no,width=100,height=500");
}	