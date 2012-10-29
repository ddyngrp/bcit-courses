
import resources.ClassicsHelper;
import com.rational.test.ft.*;
import com.rational.test.ft.object.interfaces.*;
import com.rational.test.ft.object.interfaces.SAP.*;
import com.rational.test.ft.object.interfaces.WPF.*;
import com.rational.test.ft.object.interfaces.dojo.*;
import com.rational.test.ft.object.interfaces.siebel.*;
import com.rational.test.ft.object.interfaces.flex.*;
import com.rational.test.ft.script.*;
import com.rational.test.ft.value.*;
import com.rational.test.ft.vp.*;

/**
 * Description   : Functional Test Script
 * @author Administrator
 */
public class Classics extends ClassicsHelper
{
	/**
	 * Script Name   : <b>Classics</b>
	 * Generated     : <b>2008-11-14 2:01:39 AM</b>
	 * Description   : Functional Test Script
	 * Original Host : WinNT Version 5.1  Build 2600 (S)
	 * 
	 * @since  2008/11/14
	 * @author Administrator
	 */
	public void testMain(Object[] args) 
	{
		startApp("ClassicsJavaB");
		
		// Frame: ClassicsCD
		tree2().click(atPath("Composers->Haydn->Location(PLUS_MINUS)"));
		tree2().click(atPath("Composers->Haydn->Symphonies Nos. 94 & 98"));
		placeOrder().click();
		
		// Frame: Member Logon
		ok().click();
		
		// Frame: Place an Order
		cardNumberIncludeTheSpacesText().click(atPoint(43,8));
		placeAnOrder().inputChars("7777 7777 7777 7777");
		expirationDateText().click(atPoint(29,11));
		placeAnOrder().inputChars("07/09");
		placeOrder2().click();
		
		// 
		ok2().click();
		
		// Frame: ClassicsCD
		tree2().performTest(Classics_treeVP());
		jmb().click(atPath("Order"));
		jmb().click(atPath("Order->View Existing Order Status..."));
		
		// Frame: View Order Status
		ok3().click();
		
		// Frame: View Existing Orders
		orderForTrentCulpito().performTest(OrderForTrentCulpito_standardVP());
		close().click();
		
		// Frame: ClassicsCD
		tree2().click(atPath("Composers->Schubert->Location(PLUS_MINUS)"));
		tree2().click(atPath("Composers->Schubert->String Quartets Nos. 4 & 14"));
		placeOrder().click();
		
		// Frame: Member Logon
		passwordText().click(atPoint(17,6));
		memberLogon().inputChars("xxxx");
		rememberPassword().clickToState(SELECTED);
		ok().click();
		
		// Frame: Place an Order
		cardNumberIncludeTheSpacesText().click(atPoint(19,6));
		placeAnOrder().inputChars("7777 7777 7777 7777");
		expirationDateText().click(atPoint(38,10));
		placeAnOrder().inputChars("07/09");
		placeOrder2().click();
		
		// 
		ok2().click();
		
		// Frame: ClassicsCD
		classicsJava(ANY,MAY_EXIT).close();
	}
}

