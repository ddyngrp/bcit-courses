/*
 * ListBox.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */
package src;
import net.rim.device.api.ui.component.ListField;
import net.rim.device.api.ui.Graphics;
import net.rim.device.api.ui.component.ListFieldCallback;
import net.rim.device.api.ui.DrawStyle;
import net.rim.device.api.ui.*;


/**
 * 
 */
class ListBoxCallBack implements ListFieldCallback
{
   public void drawListRow(ListField list, Graphics g, int index, int y, int w)
   {
       g.drawText("Item: ", 0,y,0,w);
       //g.drawText(String.valueOf(index*111),0,y,DrawStyle.HCENTER,w);
   }
   
   public Object get(ListField listField,int index)
   {
       return null;
   }
   
   public int getPreferredWidth(ListField listField)
   {
       return Graphics.getScreenWidth();
   }
   
   public int indexOfList(ListField listField, String prefix, int start)
   {
       return listField.indexOfList(prefix,start);
   }
} 
