/* Fig. 11.8: fig11_08.c
   Credit inquiry program */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{ 
   int request;     /* request number */
   int account;     /* account number */
   double balance;  /* account balance */
   char name[ 30 ]; /* account name */
   FILE *cfPtr;     /* clients.dat file pointer */

   /* fopen opens the file; exits program if file cannot be opened */
   if ( ( cfPtr = fopen( "clients.dat", "r" ) ) == NULL ) {
      printf( "File could not be opened\n" );
   } /* end if */
   else {
      
      /* display request options */
      printf( "Enter request\n"
         " 1 - List accounts with zero balances\n"
         " 2 - List accounts with credit balances\n"
         " 3 - List accounts with debit balances\n"
         " 4 - End of run\n? " );
      scanf( "%d", &request );

      /* process user's request */
      while ( request != 4 ) { 

         /* read account, name and balance from file */
         fscanf( cfPtr, "%d%s%lf", &account, name, &balance );

         switch ( request ) { 

            case 1:
               printf( "\nAccounts with zero balances:\n" );

               /* read file contents (until eof) */
               while ( !feof( cfPtr ) ) { 

                  if ( balance == 0 ) {
                     printf( "%-10d%-13s%7.2f\n", 
                        account, name, balance );
                  } /* end if */

                  /* read account, name and balance from file */
                  fscanf( cfPtr, "%d%s%lf", 
                     &account, name, &balance );
               } /* end while */

               break;

            case 2:
               printf( "\nAccounts with credit balances:\n" );

               /* read file contents (until eof) */
               while ( !feof( cfPtr ) ) { 

                  if ( balance < 0 ) {
                     printf( "%-10d%-13s%7.2f\n", 
                        account, name, balance );
                  } /* end if */

                  /* read account, name and balance from file */
                  fscanf( cfPtr, "%d%s%lf", 
                     &account, name, &balance );
               } /* end while */

               break;

            case 3:
               printf( "\nAccounts with debit balances:\n" );

               /* read file contents (until eof) */
               while ( !feof( cfPtr ) ) { 

                  if ( balance > 0 ) {
                     printf( "%-10d%-13s%7.2f\n", 
                        account, name, balance );
                  } /* end if */

                  /* read account, name and balance from file */
                  fscanf( cfPtr, "%d%s%lf", 
                     &account, name, &balance );
               } /* end while */

               break;           
            
         } /* end switch */ 

         rewind( cfPtr ); /* return cfPtr to beginning of file */

         printf( "\n? " );
         scanf( "%d", &request );
      } /* end while */

      printf( "End of run.\n" );
      fclose( cfPtr ); /* fclose closes the file */
   } /* end else */
 
   return 0; /* indicates successful termination */

} /* end main */



/**************************************************************************
 * (C) Copyright 1992-2007 by Deitel & Associates, Inc. and               *
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
