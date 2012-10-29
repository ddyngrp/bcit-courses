/*
 * LoginScreen.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */

package src;




/**
 * 
 */
class User{
    User() {    }
    User(String userName, String password){
        this.userName = userName;
        this.password = password;
    }
    
    private String userName;
    private String password;
    
    public void setName(String name){
        this.userName = name;
    }
    public void setPassword (String password){
        this.password = password;
    } 
    
    public String getName(){return this.userName;}
    public String getPassword(){return this.password;}    
    
    
} 
