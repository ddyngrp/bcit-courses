
import resources.OrderTotalHelper;
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
public class OrderTotal extends OrderTotalHelper
{
	/**
	 * Script Name   : <b>OrderTotal</b>
	 * Generated     : <b>2008-11-14 3:26:57 AM</b>
	 * Description   : Functional Test Script
	 * Original Host : WinNT Version 5.1  Build 2600 (S)
	 * 
	 * @since  2008/11/14
	 * @author Administrator
	 */
	public void testMain(Object[] args) 
	{
		startApp("ClassicsJavaA");
		
		// Frame: ClassicsCD
		tree2().doubleClick(atPath("Composers->Schubert"));
		tree2().click(atPath("Composers->Schubert->String Quartets Nos. 4 & 14"));
		placeOrder().click();
		
		// Frame: Member Logon
		ok().click();
		
		// Frame: Place an Order
		cardNumberIncludeTheSpacesText().click(atPoint(33,14));
		placeAnOrder().inputChars("1234567890");
		expirationDateText().click(atPoint(30,11));
		placeAnOrder().inputChars("09/09");
		// Data Driven Code inserted on 2008-11-14
		itemText().setText(dpString("Composer"));
		_1899Text().setText(dpString("Item"));
		quantityText().setText(dpString("Quantity"));
		cardNumberIncludeTheSpacesText().setText(dpString("CardNum"));
		creditCombo().setText(dpString("CardType"));
		expirationDateText().setText(dpString("ExpDate"));
		nameText().setText(dpString("Name"));
		streetText().setText(dpString("Street"));
		cityStateZipText().setText(dpString("CityStateZip"));
		phoneText().setText(dpString("Phone"));
		_1999().performTest(_1999_textVP());
		placeOrder2().click();
		
		// 
		ok2().click();
		
		// Frame: ClassicsCD
		classicsJava(ANY,MAY_EXIT).close();
	}
}

