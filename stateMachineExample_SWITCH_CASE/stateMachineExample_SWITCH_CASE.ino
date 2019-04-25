#define DEBUG_PRINT_STATE_INFO 0


enum State
{
    INITIAL_STATE,
    WAITING_NUMBER1,
    WAITING_NUMBER2,
    WAITING_SECOND_NUMBER,
};

/* events by the used. I.e. numbers and operands  */
enum Event
{
    NUMBER_GIVEN,
    OPERAND_GIVEN,
    NOT_A_NUMBER_GIVEN,
};

State state = INITIAL_STATE;
Event event;
char operand,calc,code;
int number;
float value1,value2;


void initial_state_handler()
{
  #if DEBUG_PRINT_STATE_INFO
     Serial.println("State = Initial State");
  #endif   
   value1 = 0;
   value2 = 0;
   if(event == NUMBER_GIVEN)
   {
      state = WAITING_NUMBER1;
      value1 = value1*10 + number;
   }
   else
   {
      printError();
   }
}

void waiting_number1_handler()
{
   #if DEBUG_PRINT_STATE_INFO
     Serial.println("STATE = reading value 1");
   #endif  
   if(event == NUMBER_GIVEN)
   {
      value1 = value1*10 + number;
   }
   else if(event == OPERAND_GIVEN)
   {
      state = WAITING_SECOND_NUMBER;
   }
   else
   {
      printError();
      value1 = 0;
      value2 = 0;
      state = INITIAL_STATE;
   }
}

void waiting_number2_handler()
{
   #if DEBUG_PRINT_STATE_INFO
     Serial.println("STATE = reading value 2");
   #endif  
   if(event==NUMBER_GIVEN)
   {
     value2 = value2*10+number;
   }
   else
   {
     calculateAndPrintResult();
     state = INITIAL_STATE;
   }
}

void waiting_second_number_handler()
{
   #if DEBUG_PRINT_STATE_INFO
     Serial.println("STATE = Waiting second number");
   #endif 
   calc = operand;
   if(event==NUMBER_GIVEN)
   {
      value2 = value2*10 + number;
      state = WAITING_NUMBER2;
   }
   else
   {
      printError();
      state = INITIAL_STATE;
      value1 = 0;
      value2 = 0;
   }
}

void printError(void)
{
   Serial.println("Anna laskutoimitus oikein");
}

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
           else if(code == 43 || code==45 || code==47 || code==42|| code==61)
           {
              event = OPERAND_GIVEN;
              operand = code;
           }
           else
           {
             event = NOT_A_NUMBER_GIVEN;
           }

           /*
             And here start the actual finite state machine * 
            */
           
           switch (state)
           {
             case INITIAL_STATE:
               initial_state_handler();
               break;

             case WAITING_NUMBER1:
               waiting_number1_handler();
               break;

             case WAITING_SECOND_NUMBER:
               waiting_second_number_handler();
               break;

             case WAITING_NUMBER2:
               waiting_number2_handler();
               break;

             default:
               printError();
               state = INITIAL_STATE;
          } // end switch
 
        }   // end for
      }     // end if
   }        // end while
   
}


