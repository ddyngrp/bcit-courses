// File: Client.java
// Set up a Client that will send UDP packets to a server and receive packets
// from a server.

import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Client extends JFrame implements ActionListener
{
	private JTextField enter;
   private JTextArea display;

   private DatagramPacket sendPacket, receivePacket;
   private DatagramSocket socket;


   public Client()
   {
     	super( "Client" );

     	enter = new JTextField( "Type message here" );
     	enter.addActionListener( this );
     	getContentPane().add( enter, BorderLayout.NORTH );
     	display = new JTextArea();
     	getContentPane().add( new JScrollPane( display ), BorderLayout.CENTER );
      setSize( 400, 300 );
      show();

      try
      {
        	socket = new DatagramSocket();
      }
      catch( SocketException se )
      {
        	se.printStackTrace();
        	System.exit( 1 );
      }
   }

   public void waitForPackets()
   {
     	while ( true )
      {
        	try
         {
           	// set up packet
           	byte data[] = new byte[ 100 ];
           	receivePacket = new DatagramPacket( data, data.length );

           	// wait for packet
           	socket.receive( receivePacket );

           	// process packet
           	display.append( "\nPacket received:" +
              	"\nFrom host: " + receivePacket.getAddress() +
              	"\nHost port: " + receivePacket.getPort() +
              	"\nLength: " + receivePacket.getLength() +
              	"\nContaining:\n\t" +
              	new String( receivePacket.getData(), 0,
               	receivePacket.getLength() ) );

               display.setCaretPosition(display.getText().length() );
         }
         catch( IOException exception )
         {
           	display.append( exception.toString() + "\n" );
           	exception.printStackTrace();
         }
      }
   }

   public void actionPerformed( ActionEvent e )
   {
     	try
      {
        	display.append( "\nSending packet containing: " +
                        e.getActionCommand() + "\n" );

        	String s = e.getActionCommand();
        	byte data[] = s.getBytes();

        	sendPacket = new DatagramPacket( data, data.length,
	     	InetAddress.getByName("milliways.bcit.ca"), 5000 );
			socket.send( sendPacket );
        	display.append( "Packet sent\n" );
        	display.setCaretPosition(
         display.getText().length() );
     }
     catch ( IOException exception )
     {
     		display.append( exception.toString() + "\n" );
      	exception.printStackTrace();
     }
   }

   public static void main( String args[] )
   {
     	Client app = new Client();
        app.addWindowListener(
        	new WindowAdapter()
         {
           	public void windowClosing( WindowEvent e )
           	{
              	System.exit( 0 );
           	}
      	}
        );

        app.waitForPackets();
   }
}

/**************************************************************************
 * (C) Copyright 1999 by Deitel & Associates, Inc. and Prentice Hall.     *
 * All Rights Reserved.                                                   *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
