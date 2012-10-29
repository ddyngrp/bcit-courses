/* 
   The purpose of the ctor_ex class and the main function that uses 
   the class, is to demonstrate:

   1) how to declare and implement a default ctor, conversion ctor and copy ctor
   2) various ways that ctors can be invoked
   3) an example of declaring and using a static member
*/

class ctor_ex
{
public:
	ctor_ex ();                 // Default ctor
	ctor_ex (int);              // Conversion ctor
	ctor_ex (int *);            // Another conversion ctor
	ctor_ex (const ctor_ex &);  // Copy ctor
   
	~ctor_ex (void);            // Destructor

private:
	int * intPtr;               // Used to point to int dynamically created in the ctor
	static int obj_count;       // This is a static member, which means there is only one such member
	                            //    for the whole class.  It is used to track how many objects 
	                            //    of the ctor_ex class have been instantiated.
	int object_no;				// Represents the object number
};


