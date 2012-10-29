function changeColor(theObject, theColor)
{
	if(document.getElementById)
	{
	 document.getElementById(theObject.id).style.color = theColor;
	 theObject.style.fontSize = "50px";
	}
	else if(document.all)
	{

	}
	else if(document.layers)
	{

	}
}