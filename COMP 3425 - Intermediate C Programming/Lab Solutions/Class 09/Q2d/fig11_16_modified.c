/* Fig. 11.16: fig11_16.c
   This program reads a random access file sequentially, updates data
   already written to the file, creates new data to be placed in the
   file, and deletes data previously in the file. 
   
   Modified by Bob Langelaan         
                                                                   */
#include <stdio.h>

/* clientData structure definition */
struct clientData { 
   int acctNum;          /* account number */
   char lastName[ 15 ];  /* account last name */
   char firstName[ 10 ]; /* account first name */
   double balance;       /* account balance */
}; /* end structure clientData */

/* prototypes */
int enterChoice( void );
void textFile( FILE *readPtr );
void updateRecord( FILE *fPtr );
void newRecord( FILE *fPtr );
void deleteRecord( FILE *fPtr );

void sumRecords( FILE *fPtr ); // added by BL

int main()
{ 
   FILE *cfPtr; /* credit.dat file pointer */
   int choice;  /* user's choice */

   /* fopen opens the file; exits if file cannot be opened */
   if ( ( cfPtr = fopen( "credit.dat", "rb+" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } /* end if */
   else { 

      /* enable user to specify action */
      while ( ( choice = enterChoice() ) != 6 ) { 

         switch ( choice ) { 

            /* create text file from record file */
            case 1:
               textFile( cfPtr );
               break;

            /* update record */
            case 2:
               updateRecord( cfPtr );
               break;

            /* create record */
            case 3:
               newRecord( cfPtr );
               break;

            /* delete existing record */
            case 4:
               deleteRecord( cfPtr );
               break;

			/* sum up balances of valid records and record sum in text file */
			case 5:
				sumRecords( cfPtr );
				break;

            /* display message if user does not select valid choice */
            default:
               printf( "Incorrect choice\n" );
               break;
       
         } /* end switch */

      } /* end while */

      fclose( cfPtr ); /* fclose closes the file */
   } /* end else */
 
   return 0; /* indicates successful termination */

} /* end main */

/* create formatted text file for printing */ 
void textFile( FILE *readPtr )
{ 
   FILE *writePtr; /* accounts.txt file pointer */

   /* create clientData with default information */
   struct clientData client = { 0, "", "", 0.0 };

   /* fopen opens the file; exits if file cannot be opened */
   if ( ( writePtr = fopen( "accounts.txt", "w" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } /* end if */
   else { 
      rewind( readPtr ); /* sets pointer to beginning of file */
      fprintf( writePtr, "%-6s%-16s%-11s%10s\n", 
         "Acct", "Last Name", "First Name","Balance" );

      /* copy all records from random-access file into text file */
      while ( !feof( readPtr ) ) { 
         fread( &client, sizeof( struct clientData ), 1, readPtr );

         /* write single record to text file */
         if ( client.acctNum != 0 ) {
            fprintf( writePtr, "%-6d%-16s%-11s%10.2f\n",
               client.acctNum, client.lastName,
               client.firstName, client.balance );
         } /* end if */

      } /* end while */

      fclose( writePtr ); /* fclose closes the file */
   } /* end else */

} /* end function textFile */

/* update balance in record */
void updateRecord( FILE *fPtr )
{ 
   int account;        /* account number */
   double transaction; /* transaction amount */

   /* create clientData with no information */
   struct clientData client = { 0, "", "", 0.0 };

   /* obtain number of account to update */
   printf( "Enter account to update ( 1 - 100 ): " );
   scanf( "%d", &account );

   /* move file pointer to correct record in file */
   fseek( fPtr, ( account - 1 ) * sizeof( struct clientData ), 
      SEEK_SET );

   /* read record from file */
   fread( &client, sizeof( struct clientData ), 1, fPtr );

   /* display error if account does not exist */
   if ( client.acctNum == 0 ) {
      printf( "Acount #%d has no information.\n", account );
   } /* end if */
   else { /* update record */
      printf( "%-6d%-16s%-11s%10.2f\n\n", 
         client.acctNum, client.lastName, 
         client.firstName, client.balance );
      
      /* request transaction amount from user */ 
      printf( "Enter charge ( + ) or payment ( - ): " );
      scanf( "%lf", &transaction );
      client.balance += transaction; /* update record balance */
      
      printf( "%-6d%-16s%-11s%10.2f\n", 
         client.acctNum, client.lastName, 
         client.firstName, client.balance );
      
      /* move file pointer to correct record in file */
      fseek( fPtr, ( account - 1 ) * sizeof( struct clientData ), 
         SEEK_SET );

      /* write updated record over old record in file */
      fwrite( &client, sizeof( struct clientData ), 1, fPtr );
   } /* end else */

} /* end function updateRecord */

/* delete an existing record */
void deleteRecord( FILE *fPtr )
{ 

   struct clientData client; /* stores record read from file */
   struct clientData blankClient = { 0, "", "", 0 }; /* blank client */
   
   int accountNum; /* account number */

   /* obtain number of account to delete */
   printf( "Enter account number to delete ( 1 - 100 ): " );
   scanf( "%d", &accountNum );

   /* move file pointer to correct record in file */
   fseek( fPtr, ( accountNum - 1 ) * sizeof( struct clientData ), 
      SEEK_SET );

   /* read record from file */
   fread( &client, sizeof( struct clientData ), 1, fPtr );

   /* display error if record does not exist */
   if ( client.acctNum == 0 ) {
      printf( "Account %d does not exist.\n", accountNum );
   } /* end if */
   else { /* delete record */

      /* move file pointer to correct record in file */
      fseek( fPtr, ( accountNum - 1 ) * sizeof( struct clientData ), 
         SEEK_SET );

      /* replace existing record with blank record */
      fwrite( &blankClient, 
         sizeof( struct clientData ), 1, fPtr );
   } /* end else */

} /* end function deleteRecord */

/* create and insert record */
void newRecord( FILE *fPtr )
{ 
   /* create clientData with default information */
   struct clientData client = { 0, "", "", 0.0 };

   int accountNum; /* account number */

   /* obtain number of account to create */
   printf( "Enter new account number ( 1 - 100 ): " );
   scanf( "%d", &accountNum );

   /* move file pointer to correct record in file */
   fseek( fPtr, ( accountNum - 1 ) * sizeof( struct clientData ), 
      SEEK_SET );

   /* read record from file */
   fread( &client, sizeof( struct clientData ), 1, fPtr );

   /* display error if account already exists */
   if ( client.acctNum != 0 ) {
      printf( "Account #%d already contains information.\n",
              client.acctNum );
   } /* end if */
   else { /* create record */

      /* user enters last name, first name and balance */
      printf( "Enter lastname, firstname, balance\n? " );
      scanf( "%s%s%lf", &client.lastName, &client.firstName, 
         &client.balance );

      client.acctNum = accountNum;
      
      /* move file pointer to correct record in file */
      fseek( fPtr, ( client.acctNum - 1 ) * 
         sizeof( struct clientData ), SEEK_SET );

      /* insert record in file */
      fwrite( &client, 
         sizeof( struct clientData ), 1, fPtr );
   } /* end else */

} /* end function newRecord */

/* sum up balances of valid accounts and write sum into text file */ 
void sumRecords( FILE *readPtr )
{ 
   double sum_of_balances = 0; // variable that will contain sum of all valid balances
   FILE *writePtr; /* sum_report.txt file pointer */

   /* create clientData with default information */
   struct clientData client = { 0, "", "", 0.0 };

   /* fopen opens the file; exits if file cannot be opened */
   if ( ( writePtr = fopen( "sum_report.txt", "w" ) ) == NULL ) {
      printf( "File could not be opened.\n" );
   } /* end if */
   else { 
      rewind( readPtr ); /* sets pointer to beginning of file */
      
      /* read all records from random-access file sum balances */
      while ( !feof( readPtr ) ) { 
         fread( &client, sizeof( struct clientData ), 1, readPtr );

         /* add balance to total if valid account */
         if ( client.acctNum != 0 ) {
            sum_of_balances += client.balance;
         } /* end if */

      } /* end while */

	  fprintf (writePtr,"The sum of the balances of all of the valid accounts is: $%.2f\n",sum_of_balances);
      fclose( writePtr ); /* fclose closes the file */
   } /* end else */

} /* end function sumRecords */

/* enable user to input menu choice */
int enterChoice( void )
{ 
   int menuChoice; /* variable to store user's choice */

   /* display available options */
   printf( "\nEnter your choice\n"
      "1 - store a formatted text file of acounts called\n"
      "    \"accounts.txt\" for printing\n"
      "2 - update an account\n"
      "3 - add a new account\n"
      "4 - delete an account\n"
	  "5 - sum balances of all the accounts\n" // Added by BL
      "6 - end program\n? " );

   scanf( "%d", &menuChoice ); /* receive choice from user */

   return menuChoice;

} /* end function enterChoice */



/**************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
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