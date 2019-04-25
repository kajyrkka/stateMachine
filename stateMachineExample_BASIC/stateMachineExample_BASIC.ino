#define DEBUG 0
   
enum State
{
    INITIAL_STATE,
    WAITING_NUMBER1,
    WAITING_NUMBER2,
};



/* events by the used. I.e. numbers and operands  */
enum Event
{
    NUMBER_GIVEN,
    OPERAND_GIVEN,
    NOT_A_NUMBER_GIVEN,
};

State state = INITIAL_STATE;
char code,operand,calc;
Event event;
int number;
float value1,value2;   


void calculateAndPrintResult()
{
            float result = 0;
            if(calc == '+')
            {
              result = value1 + value2;
            }
            if(calc == '-')
            {
              result = value1 - value2;
            }
            if(calc == '*')
            {
              result = value1 * value2;
            }
            if(calc == '/')
            {
              result = value1 / value2;
            }
            Serial.print("Result is = ");
            Serial.println(result);
             
}


void setup() {
  Serial.begin(9600);
}




void loop() {

                     
    
   while(1)
   {
      
      if(Serial.available())
      {
         String line = Serial.readStringUntil('\r');

         for(int cloop = 0;cloop < line.length();cloop++)
         {
           code = line[cloop];

           if(code >47 && code<58)
           {
              event = NUMBER_GIVEN;
              number = code - 48;
           }
           else if(code == 43 || code==45 || code==47 || code==42||code==61)
           {
              event = OPERAND_GIVEN;
              operand = code;
           }
           else
           {
             event = NOT_A_NUMBER_GIVEN;
           }

           /**************************************************************
             And here start the actual implementation of activity diagram* 
            **************************************************************/

           if(state == INITIAL_STATE)
           {
               value1 = 0;
               value2 = 0;
               #if DEBUG
               Serial.println("if(state == INITIAL_STATE)");
               #endif
               if(event == NUMBER_GIVEN)
               {
                   state = WAITING_NUMBER1;
               }
               else
               {
                   Serial.println("Virhe, anna oikea laskutoimitus");
                   state = INITIAL_STATE;
               }
           }
           
           if(state == WAITING_NUMBER1)
           {               
               #if DEBUG
               Serial.println("if(state == WAITING_NUMBER1)");
               #endif
               if(event == NUMBER_GIVEN)
               {
                   value1 = value1*10 + number;
               }
               else
               {
                    #if DEBUG
                    Serial.println("Onko operand?");
                    #endif

                   if(event == OPERAND_GIVEN)
                   {
                      state = WAITING_NUMBER2;
                      calc = operand;
                   }
                   else
                   {
                      Serial.println("Virhe, anna oikea laskutoimitus");
                      state = INITIAL_STATE;
                   }
               }

           }
           else
           {
               #if DEBUG
               Serial.println("else(state == WAITING_NUMBER2)");
               #endif

               if(event == NUMBER_GIVEN)
               {
                    value2 = value2*10 + number;
               }
               else
               {
                   if(value2 == 0)
                   {
                       Serial.println("Virhe, anna oikea laskutoimitus");
                       state = INITIAL_STATE;

                   }
                   else
                   {
                       calculateAndPrintResult();
                       state = INITIAL_STATE;
                   }
               }
           }
           

            /********************************************************************
             * And here the activity diagram stuff ends and we go for next event
             * *****************************************************************/
           

        }   // end for
      }     // end if
   }        // end while

}


