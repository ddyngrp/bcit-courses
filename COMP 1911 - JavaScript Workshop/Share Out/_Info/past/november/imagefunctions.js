	function rollover(someImageId, thisIsTheNewSrc)
	{
          if(document.images)
	  {

	  	if(document.getElementById)
	  	{
	   	 document.getElementById(someImageId).src = thisIsTheNewSrc;
   	  	}
	  	else if(document.all)
	  	{
			document.all[someImageId].src = thisIsTheNewSrc;
	  	}
	  	else if(document.layer)
	  	{

          	}
	  	else
	  	{
			document.someImageId.src = thisIsTheNewSrc
	  	}
	 }
         else
	 {
		document.write("<a href=\"htmlonly.html\">Click here</a>");
         }
	}