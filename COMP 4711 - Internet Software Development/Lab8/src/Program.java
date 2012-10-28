/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
/**
 *
 * @author A00702683
 */
public class Program implements Comparable {

    public Program()
    {
        title = "Not Given";
        desc = "not Given";
        startDate = new Date();
        endDate = new Date();
    }

    public Date getStartDate()
    {
        return startDate;
    }
    
    public void setStartDate(String startDate)
    {
        DateFormat indf = new SimpleDateFormat("yyyyMMddkkmmss");
        
        try {
            this.startDate = indf.parse(startDate);
        } catch (ParseException ex) {
            //do nothing
        }
    }
    
    public Date getEndDate()
    {
        return endDate;
    }
    
    public void setEndDate(String endDate)
    {
        DateFormat indf = new SimpleDateFormat("yyyyMMddkkmmss");
        
        try {
            this.endDate = indf.parse(endDate);
        } catch (ParseException ex) {
            //do nothing
        }
    }

    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    private String title;
    private String desc;

    private Date startDate;
    private Date endDate;

    public int compareTo(Object o) {
        Program prog = (Program)o;       
        return startDate.compareTo(prog.getStartDate());
    }

    public void print()
    {
        DateFormat outdf = new SimpleDateFormat("EEE, MMMMM d 'at' hh:mm a");

        System.out.println("Title: " + this.title);
        
        if(this.desc != null)
            System.out.println("Desc: " + this.desc);
        else
            System.out.println("Desc: None given.");

        System.out.println("Start Time: " + outdf.format(startDate));
        System.out.println("End Time: " + outdf.format(endDate));
        System.out.println();
    }

}
