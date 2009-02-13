/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package model.Model;

/**
 *
 * @author ironix
 */
public class Order {
    private static int orderNum = 0;
    private String[] cookies = {"Sugar", "Chocolate Chip", "Peanut Butter",
                               "Macadamia Nut", "Macaroon", "Cat Hair"};

    public int getOrderNum() {
        return orderNum++;
    }

    public String[] getCookies() {
        return cookies;
    }
}
