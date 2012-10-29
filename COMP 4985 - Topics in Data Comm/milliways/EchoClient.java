//-----------------------------------------------------------
// File: EchoClient.java
// What: TCP sockets based Echo Client
// Who:  Dick Steflik (steflik@binghamton.edu
//       Prashant Sridharan (prashant@Exchange.Microsoft.com)
//-----------------------------------------------------------

import java.io.*;
import java.net.*;

public class EchoClient
{
	public static void echoclient(BufferedReader in, PrintStream out)
        throws IOException
	{
  		// make stream for reading the keyboard
  		BufferedReader kybd = new BufferedReader(new InputStreamReader(System.in));
		String line;
		while(true)
     	{
     		line="";
     		// read keyboard and write to TCP socket
     		try
     		{
        		line = kybd.readLine();
        		out.println(line);
     		}
     		catch(IOException e)
     		{
        		System.err.println(e.getMessage());
     		}
     		// read TCP socket and write to console
     		try
     		{
        		line = in.readLine();
        		System.out.println(line);
     		}
     		catch(IOException e)
     		{
     			System.err.println(e.getMessage());
         }
  		}
	}

	public static void main(String[] args )
	{
		Socket s = null;
   	try
   	{
	  		// Create a socket to communicate with "echo" on specified host
     		s = new Socket(args[0], 7000);

  			// Create streams for reading and writing lines of text from and to this socket.
  			BufferedReader in = new BufferedReader(
        	new InputStreamReader(s.getInputStream()));
  			PrintStream out = new PrintStream(s.getOutputStream());

  			// Tell the user that we've connected
  			System.out.println("Connected to " + s.getInetAddress()
            	+ ":" + s.getPort());
          echoclient(in, out);
  		}
  		catch (IOException e)
  		{
  			System.err.println(e);
  		}

  		// Always be sure the socket gets closed
  		finally
  		{
  			try
  			{
     			if(s != null)  s.close();
  			}
  			catch (IOException exc)
  			{
           	; /* terminate gracefully */}
  			}
	}
}
