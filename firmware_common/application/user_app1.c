/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */
/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
    LedOff(PURPLE);
    LedOff(WHITE);
    LedOff(BLUE);
    LedOff(CYAN);
    LedOff(ORANGE);
    LedOff(RED);
    LedOff(GREEN);
    LedOff(YELLOW);
    PWMAudioOff(BUZZER1);
    LedOn(LCD_RED); 
    LedOn(LCD_GREEN);
    LedOn(LCD_BLUE);
    PWMAudioSetFrequency(BUZZER1,200);
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_State1;
     //UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */

static void UserApp1SM_State1(void)
{
  static bool bIsChange=FALSE;
  static bool bState1=TRUE;
  static u8   au8Inputdata[20];
  static u8   au8Input[2];
  static u8   u8Datacount=0;
  static u8   u8Count;
  if(bState1)
  {  
    LedOn(PURPLE);
    LedOn(WHITE);
    LedOn(BLUE);
    LedOn(CYAN);
    LedOff(ORANGE);
    LedOff(RED);
    LedOff(GREEN);
    LedOff(YELLOW);
    DebugPrintf("Entering state 1");
    DebugLineFeed();
    LCDMessage(LINE1_START_ADDR,"STATE 1");
    LedOn(LCD_RED); 
    LedOn(LCD_BLUE);
    bState1=FALSE;
  }
    
  u8Count=DebugScanf(au8Input);
  if(u8Count>0)
  {
    au8Inputdata[u8Datacount]=au8Input[0];
    if((au8Input[0]=='\r'))
    {
      if((au8Inputdata[0]=='2')&&(u8Datacount==1))
      {
        bIsChange=TRUE; 
      }
      u8Datacount=0; 
    }
    else
    {
      u8Datacount++;
    }
  }
  //2<CR> ON DEBUG
    
    if( WasButtonPressed(BUTTON2) )
    {
      ButtonAcknowledge(BUTTON2);
      bIsChange=TRUE;
    }
    if(bIsChange)
    {
      UserApp1_StateMachine=UserApp1SM_State2;
      bState1=TRUE;
      bIsChange=FALSE;
    }
  PWMAudioOff(BUZZER1);   
}

static void UserApp1SM_State2(void)
{
  static bool bIsChange = FALSE;
  static bool bState2 = TRUE;
  static u8   au8Inputdata[20];
  static u8   au8Input[2];
  static u8   u8Datacount=0;
  static u8   u8Count;
  static u32 u32Time=0;
  u32Time++;
  
  if(bState2) 
  {
    LedOff(BLUE);
    LedOff(PURPLE);
    LedOff(WHITE);
    LedOff(CYAN);
    LedOn(GREEN);
    LedOn(YELLOW);
    LedOn(ORANGE);
    LedOn(RED);
    LedBlink(GREEN,LED_1HZ);
    LedBlink(YELLOW,LED_2HZ);
    LedBlink(ORANGE,LED_4HZ);
    LedBlink(RED,LED_8HZ);
    DebugPrintf("Entering state 2");
    DebugLineFeed();
    LCDMessage(LINE1_START_ADDR,"STATE 2");   
    LedOn(LCD_RED); 
    LedPWM(LCD_GREEN,LED_PWM_30);
    LedOff(LCD_BLUE);
    bState2=FALSE;
  }
  
  u8Count=DebugScanf(au8Input);
  if(u8Count>0)
  {
    au8Inputdata[u8Datacount]=au8Input[0];
    if((au8Input[0]=='\r'))
    {
      if((au8Inputdata[0]=='1')&&(u8Datacount==1))
      {
        bIsChange=TRUE; 
      }
      u8Datacount=0; 
    }
    else
    {
      u8Datacount++;
    }
  }//1<CR> ON DEBUG
    
  if( WasButtonPressed(BUTTON1) )
  {
    ButtonAcknowledge(BUTTON1);
    bIsChange=TRUE;
  }
  if(bIsChange)
  {
    UserApp1_StateMachine = UserApp1SM_State1;
    bState2=TRUE;
    bIsChange=FALSE;
  }
  //BUZEER RUN AT 200HZ
  
  if(u32Time==1000)
  {
    u32Time=0;
    PWMAudioOn(BUZZER1);
      
  }
  if(u32Time==100)
  {
    PWMAudioOff(BUZZER1);
  }
  //SET BUZZER
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


   
  

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{

} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
