/*
	COMP1911 Assignment 1 Example
	an external file for functions was not required in the specifications, 
	but may still be a good idea to keep the HTML pages cleaner
*/

/*
	processForm()
	loosely validates the email input from a user,
	sets a cookie if validation succeeds
*/
function processForm(){
	//obtain the value of the user input
	var text = document.getElementById("email").value;
	//if user input doesnt contain a "@" OR a "."
	if ((text.indexOf("@") == -1) || text.indexOf(".") == -1){
		//show error message
		alert("No No No, bad Email Address!");
		//reset the focus on the email entry textbox
		document.getElementById("email").focus();
		//do not forward form data to page2
		return false;
	}
	//else, the user has entered a valid email, so we should set a cookie
	else{
		//prepare a 10 minute timespan for use with the cookie
		//1000 (milliseconds) * 60 (seconds) * 10 (minutes)
		var expiryDate = new Date();
		expiryDate.setTime(expiryDate.getTime() + 10 * 60 * 1000);
		//set the cookie (YUM!)
		//setCookie(cookieName, value, expiry)
		setCookie("chocolatechip", text, expiryDate);	
	}
}

/*
	setCookie(name, value, expires, path, domain, secure)
	taken from class notes
*/
 function setCookie(name, value, expires, path, domain, secure) {
  var curCookie = name + "=" + escape(value) +
      ((expires) ? "; expires=" + expires.toGMTString() : "") +
      ((path) ? "; path=" + path : "") +
      ((domain) ? "; domain=" + domain : "") +
      ((secure) ? "; secure" : "");
		document.cookie = curCookie;
}

/*
	getCookie(name)
	taken from class notes
*/
function getCookie(name) {
  var dc = document.cookie;
  var prefix = name + "=";
  var begin = dc.indexOf("; " + prefix);
  if (begin == -1) {
    begin = dc.indexOf(prefix);
    if (begin != 0) return null;
  } else
    begin += 2;
  var end = document.cookie.indexOf(";", begin);
  if (end == -1)
    end = dc.length;
  return unescape(dc.substring(begin + prefix.length, end));
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


/***********************************************
* AnyLink Drop Down Menu- ? Dynamic Drive (www.dynamicdrive.com)
* This notice MUST stay intact for legal use
* Visit http://www.dynamicdrive.com/ for full source code
***********************************************/

//Contents for menu 1
var menu1=new Array()
menu1[0]='<a href="http://www.javascriptkit.com">JavaScript Kit</a>'
menu1[1]='<a href="http://www.freewarejava.com">Freewarejava.com</a>'
menu1[2]='<a href="http://codingforums.com">Coding Forums</a>'
menu1[3]='<a href="http://www.cssdrive.com">CSS Drive</a>'

//Contents for menu 2, and so on
var menu2=new Array()
menu2[0]='<a href="http://cnn.com">CNN</a>'
menu2[1]='<a href="http://msnbc.com">MSNBC</a>'
menu2[2]='<a href="http://news.bbc.co.uk">BBC News</a>'

//Contents for menu 3, and so on
var menu3=new Array()
menu3[0]='<a href="http://www.nfl.com">NFL</a>'
menu3[1]='<a href="http://www.nba.com">NBA</a>'
menu3[2]='<a href="http://www.defendo.com">Defendo</a>'
		
var menuwidth='165px' //default menu width
var menubgcolor='lightyellow'  //menu bgcolor
var disappeardelay=250  //menu disappear speed onMouseout (in miliseconds)
var hidemenu_onclick="yes" //hide menu when user clicks within menu?

/////No further editting needed

var ie4=document.all
var ns6=document.getElementById&&!document.all

if (ie4||ns6)
document.write('<div id="dropmenudiv" style="visibility:hidden;width:'+menuwidth+';background-color:'+menubgcolor+'" onMouseover="clearhidemenu()" onMouseout="dynamichide(event)"></div>')

function getposOffset(what, offsettype){
var totaloffset=(offsettype=="left")? what.offsetLeft : what.offsetTop;
var parentEl=what.offsetParent;
while (parentEl!=null){
totaloffset=(offsettype=="left")? totaloffset+parentEl.offsetLeft : totaloffset+parentEl.offsetTop;
parentEl=parentEl.offsetParent;
}
return totaloffset;
}


function showhide(obj, e, visible, hidden, menuwidth){
if (ie4||ns6)
dropmenuobj.style.left=dropmenuobj.style.top="-500px"
if (menuwidth!=""){
dropmenuobj.widthobj=dropmenuobj.style
dropmenuobj.widthobj.width=menuwidth
}
if (e.type=="click" && obj.visibility==hidden || e.type=="mouseover")
obj.visibility=visible
else if (e.type=="click")
obj.visibility=hidden
}

function iecompattest(){
return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
}

function clearbrowseredge(obj, whichedge){
var edgeoffset=0
if (whichedge=="rightedge"){
var windowedge=ie4 && !window.opera? iecompattest().scrollLeft+iecompattest().clientWidth-15 : window.pageXOffset+window.innerWidth-15
dropmenuobj.contentmeasure=dropmenuobj.offsetWidth
if (windowedge-dropmenuobj.x < dropmenuobj.contentmeasure)
edgeoffset=dropmenuobj.contentmeasure-obj.offsetWidth
}
else{
var topedge=ie4 && !window.opera? iecompattest().scrollTop : window.pageYOffset
var windowedge=ie4 && !window.opera? iecompattest().scrollTop+iecompattest().clientHeight-15 : window.pageYOffset+window.innerHeight-18
dropmenuobj.contentmeasure=dropmenuobj.offsetHeight
if (windowedge-dropmenuobj.y < dropmenuobj.contentmeasure){ //move up?
edgeoffset=dropmenuobj.contentmeasure+obj.offsetHeight
if ((dropmenuobj.y-topedge)<dropmenuobj.contentmeasure) //up no good either?
edgeoffset=dropmenuobj.y+obj.offsetHeight-topedge
}
}
return edgeoffset
}

function populatemenu(what){
if (ie4||ns6)
dropmenuobj.innerHTML=what.join("")
}


function dropdownmenu(obj, e, menucontents, menuwidth){
if (window.event) event.cancelBubble=true
else if (e.stopPropagation) e.stopPropagation()
clearhidemenu()
dropmenuobj=document.getElementById? document.getElementById("dropmenudiv") : dropmenudiv
populatemenu(menucontents)

if (ie4||ns6){
showhide(dropmenuobj.style, e, "visible", "hidden", menuwidth)
dropmenuobj.x=getposOffset(obj, "left")
dropmenuobj.y=getposOffset(obj, "top")
dropmenuobj.style.left=dropmenuobj.x-clearbrowseredge(obj, "rightedge")+"px"
dropmenuobj.style.top=dropmenuobj.y-clearbrowseredge(obj, "bottomedge")+obj.offsetHeight+"px"
}

return clickreturnvalue()
}

function clickreturnvalue(){
if (ie4||ns6) return false
else return true
}

function contains_ns6(a, b) {
while (b.parentNode)
if ((b = b.parentNode) == a)
return true;
return false;
}

function dynamichide(e){
if (ie4&&!dropmenuobj.contains(e.toElement))
delayhidemenu()
else if (ns6&&e.currentTarget!= e.relatedTarget&& !contains_ns6(e.currentTarget, e.relatedTarget))
delayhidemenu()
}

function hidemenu(e){
if (typeof dropmenuobj!="undefined"){
if (ie4||ns6)
dropmenuobj.style.visibility="hidden"
}
}

function delayhidemenu(){
if (ie4||ns6)
delayhide=setTimeout("hidemenu()",disappeardelay)
}

function clearhidemenu(){
if (typeof delayhide!="undefined")
clearTimeout(delayhide)
}

if (hidemenu_onclick=="yes")
document.onclick=hidemenu

// Variables for keeping track of the clipping window
var clipTop = 0;
var clipRight = 200;
var clipBottom = 200;
var clipLeft = 0;







// Function to start the scrolling
function startScrolling() {
    setTimeout("scrollDown()", 500);
}

// Function to simulate scrolling by moving the layer and the
// clipping window
function scrollDown() {
    var scrollWindow = document.getElementById('NewsLayer');

    // Check to see if we're at the bottom
    if (clipBottom != 900) {
        // If not, adjust variables for tracking the clipping window
        clipTop = clipTop + 1;
        clipBottom = clipBottom + 1;

        // Move the clipping window down and the layer up
        scrollWindow.style.clip = "rect(" + clipTop + " " + clipRight + 
                                  " " + clipBottom + " " + clipLeft + ")";
        var currentTop = parseInt(scrollWindow.style.top);
        scrollWindow.style.top = (currentTop - 1) + "px";

       // Schedule next call to scrollDown
       setTimeout("scrollDown()", 30);
    }
    else {
        // We're at the bottom, so reset the variables
        clipTop = 0;
        clipBottom = 200;

        // Move the clipping window and layers back to their 
        // original locations
        scrollWindow.style.clip = "rect(" + clipTop + " " + clipRight + 
                                  " " + clipBottom + " " + clipLeft + ")";
        scrollWindow.style.top = "200px";

        // Start the scrolling over again
        setTimeout("scrollDown()", 30);
    }
}
