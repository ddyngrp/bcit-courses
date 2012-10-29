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

class ListBoxCallBack implements ListFieldCallback
{
   private MediaController mc;
   public ListBoxCallBack(MediaController mc){
        this.mc = mc;
   }
   public void drawListRow(ListField list, Graphics g, int index, int y, int w)
   {
        String name;
        mc.fake();
        for(MediaNode node = this.mc.iterator(); node != null; node = node.next(), y++) {
            name = node.item().format();
            g.drawText(name,0,y,0,w);
        }
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
   
   public MediaController getMC(){
       return this.mc;
   }
} 
