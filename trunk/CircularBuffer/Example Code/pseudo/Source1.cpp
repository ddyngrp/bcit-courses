/*
If the start/end buffer are pointing to the same element that means the buffer is either full or empty.  I am kind of confused
on how we will implement this because both sides need access to the buffer so I guess it will be in a struct.  Just wrote kind 
of code/psuedocode to just try and understand whats going on.  I know it will probably be a lot more complicated than this.
*/
void write_buff(read or write flag, the buffer to be written too)
{	
	char buffer[1024] //just as an example no clue how big we need
	start = buffer[0]; //point to the beginning
	end = buffer[0]; //point to beginning
	char *start, *end;
	int read_index = 0,write_index = 0;

	if(write == true)
	{
		while(not end of file)
		{
			read data from the song
			if(write_index > 1023) //if it goes to the end then we go back to the beginning and start writing over old data
				write_index = 0;  //but we assume it's already been read by now.
			
			buffer[write_index] = songdata; //store in the buffer
			write_index++;
			end = buffer[write_index]; //to keep track of where the data is
			WSAsend()??
		}
		//send EOF message
	}
	else if (write == false)
	{
		while(buffer data > 0)
		{
			WaveOutWrite(buffer[read_index]);
			read_index ++;
			if(read_index > 1023)
				read_index = 0;
	
		}
	}
}