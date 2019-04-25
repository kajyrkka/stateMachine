#define DEBUG 0
/* These variables are global and FSM uses those */
unsigned int events, state, state_events;

/* 
 *  These variables are also global but our calculator application uses these
 */
float value1,value2,result;
int number;
char operand;

/* Let's implement here a null subroutine which can be used
 * in the state/event table in case there is nothing to do for certain
 * events in certain states.
 */


void null() 
{
}
void ent1()
{
  value1 = 0;
  value1 = value1*10 + number;
  #if DEBUG
  Serial.println("Siirryttiin tilaan 1=read first number");
  Serial.print("value1 =");
  Serial.println(value1);
  #endif
}
void num1()
{
  value1 = value1*10 + number;
  #if DEBUG
  Serial.println("tilassa 1=read first number");
  Serial.print("value1 =");
  Serial.println(value1);
  #endif
}
void ent2()
{
  value2 = 0;
  value2 = value2*10 + number;
  #if DEBUG
  Serial.println("Siirryttiin tilaan 3 = read second number");
  Serial.print("value2 =");
  Serial.println(value2);
  #endif
}
void num2()
{
  value2 = value2*10 + number;
  #if DEBUG
  Serial.println("tilassa 3 = read second number");
  Serial.print("value2 =");
  Serial.println(value2);
  #endif
}
void rst()
{
  #if DEBUG
  Serial.println("Initial tilassa");
  #endif
  result = 0.0;
}
void calc()
{ 
  #if DEBUG
  Serial.println("Siirrytään tilaan 0 ja exit funktiona lasketaan tulos");
  #endif
  calculateAndPrintResult();
}
void rdOp()
{ 
  #if DEBUG
  Serial.println("Siirrytään tilaan 2 = read operation");
  #endif
  //operand= operand; // operand on otettu jo talteen laskentaa varten.
}
void prEr()
{ 
  #if DEBUG
  Serial.println("Siirrytään Error tilaan");
  #endif
  Serial.println("Anna laskutoimitus oikein");
}
void prOh2()
{ 
  #if DEBUG
  Serial.println("New Line liian aikaisin");
  #endif
  Serial.println("Anna viela toinen luku");
}
void prOh1()
{ 
  #if DEBUG
  Serial.println("New Line liian aikaisin");
  #endif
  Serial.println("Anna viela laskuoperaatio");
}

void calculateAndPrintResult(void)
{
            float result = 0;
            if(operand == '+')
            {
              result = value1 + value2;
            }
            if(operand == '-')
            {
              result = value1 - value2;
            }
            if(operand == '*')
            {
              result = value1 * value2;
            }
            if(operand == '/')
            {
              result = value1 / value2;
            }
            Serial.print("Result is = ");
            Serial.println(result);
             
}



#define EVENTSX 4
#define STATESX 5
#define NUMBER_GIVEN 0x01
#define OPERAND_GIVEN 0x02
#define NOT_A_NUMBER_GIVEN 0x04
#define NEW_LINE_GIVEN 0x08

/*
 * And here we define a pointer to event hander function. In this case
 * the event handler function does not take any parameters and returns nothing.
 */
typedef void (*TPT)();
/*
 * And here we first define a state_table struct which contains 3 items. 1) active or not, 
 * 2) next state's number and 3) pointer to state event handler function.
 * And when the struct is definet we also initialize state_table struct with 
 * state and event data.
 */


struct state_table {
unsigned int active;
unsigned int next_state;
TPT action;
} state_table[EVENTSX][STATESX] = {
// States and their numbers
// Initial=0    ReadFirst=1  ReadOper=2   ReadSeco=3   ErrorSt=4   // Events
{ {1,1,ent1},   {1,1,num1},  {1,3,ent2},  {1,3,num2},  {1,4,null} }, // Number_given = 0
{ {1,4,prEr},   {1,2,rdOp},  {1,4,prEr},  {1,0,calc},  {1,4,null}  },// Operand_given = 1
{ {1,4,prEr},   {1,4,prEr},  {1,4,prEr},  {1,0,calc},  {1,4,null}  },// Not_a_number_given = 2
{ {1,0,prEr},   {1,1,prOh1}, {1,2,prOh2},  {1,0,calc},  {1,0,rst }  },// NewLine_given = 3
};

/* getmask, builds an event bit mask for a state from the FST
* enabling the dispatcher to eliminate irrelevant events
* LSB-bit in the mask is the highest priority event
*/
unsigned int getmask(unsigned int staten) {
unsigned int mask=0;
int i;
for(i = EVENTSX-1; i >= 0; i--) {
mask <<=1;
mask |= state_table[i][staten].active;
}
return mask;
}

/* geteventn, using the current state’s event mask to select
* only relevant events it then identifies the active event
* with the highest priority, returning its number
* So if there is more events registered but current state handles only
* certain events only those events are given with this function.
* Niin tama funktio maskaa ensin events muuttujasta pois kaikki
* sellaiset bitit=eventit, joita tassa tilassa ei saa esiintya.
* Ja sen jalkeen tama palauttaa eventin numeron ja nollaa sita
* vastaavan bitin events muuttujasta, jotta samaa eventtia ei kasitella
* kahteen kertaan. Jos yhtaan eventtia ei ole aktiivisena palautetaan
* ~0, joka tarkoittanee kaikki bitit ykkösinä eli suurin unsigned integer.
*/
unsigned int geteventn() {
unsigned int i, bitmask = 1;
state_events = events & getmask(state);
for(i=0; i < EVENTSX; i++) 
{
  if (state_events & bitmask) 
  {                       //mask out irrelevant events
    events &= ~bitmask;   //cancel selected event flag
    return i;
  }
  bitmask <<= 1;
}
return ~0;
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
   char code;
   unsigned int last_state, event, last_event=0;
   state = 0; //INITIAL_STATE;
   rst();
   
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
              events |= NUMBER_GIVEN;
              number = code - 48;
           }
           else if(code == 43 || code==45 || code==47 || code==42)
           {
              events |= OPERAND_GIVEN;
              operand = code;
           }
           else if(code == 10)
           {
              events |= NEW_LINE_GIVEN;
           }
           else
           {
             events |= NOT_A_NUMBER_GIVEN;
           }

          if ( (event = geteventn()) != ~0 ) 
          {
            last_event = event;
            last_state = state;
            //Serial.print("STATE ennen = ");
            //Serial.println(last_state);
            (*(state_table[event][state].action))(); // transition
                                                     // ACTION
            state = state_table[event][state].next_state;// Get next state
            //Serial.print("STATE jalkeen = ");
            //Serial.println(state);
            if(state != last_state) events = 0; // Clear event
                                                // flags
           } // if change of state

         } // end for
      } // end if
    }// end while
} // end loop

