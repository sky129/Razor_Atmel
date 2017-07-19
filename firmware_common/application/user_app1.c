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
 LCDClearChars(LINE1_START_ADDR,19);
 LCDMessage(LINE1_START_ADDR+1,"0");
 LCDMessage(LINE1_START_ADDR+3,"0");
 LCDMessage(LINE1_START_ADDR+6,"0");
 LCDMessage(LINE1_START_ADDR+8,"0");
 LCDMessage(LINE1_START_ADDR+11,"0");
 LCDMessage(LINE1_START_ADDR+13,"0");
 LCDMessage(LINE1_START_ADDR+16,"0");
 LCDMessage(LINE1_START_ADDR+18,"0");
 LCDMessage(LINE2_START_ADDR+18,"0");
 LCDMessage(LINE2_START_ADDR+17,"0");
 LCDMessage(LINE2_START_ADDR+16,"0");
 LCDMessage(LINE2_START_ADDR+15,"0");
 LCDMessage(LINE2_START_ADDR+14,"0");
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
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
  static u32 u32TimePoint=0;
  static u8 i=0;
  static u8 au8Wan[]={0};
  static u8 au8Qian[]={0};
  static u8 au8Bai[]={0};
  static u8 au8Shi[]={0};
  static u8 au8Ge[]={0};
  static u8 au8Bit[16]= {18,18,16,16,13,13,11,11,8,8,6,6,3,3,1,1};
  
  au8Wan[0]=u32TimePoint/10000;
  au8Qian[0]=u32TimePoint%10000/1000;
  au8Bai[0]=u32TimePoint%1000/100;
  au8Shi[0]=u32TimePoint%100/10;
  au8Ge[0]=u32TimePoint%10;

  LedCommandType aeDemolist[]=
	{
	  {RED,1000,TRUE,LED_PWM_100},
	  {RED,10000,FALSE,LED_PWM_0},
	  {ORANGE,2000,TRUE,LED_PWM_100},
	  {ORANGE,11000,FALSE,LED_PWM_0},
	  {YELLOW,3000,TRUE,LED_PWM_100},
	  {YELLOW,12000,FALSE,LED_PWM_0},
	  {GREEN,4000,TRUE,LED_PWM_100},
	  {GREEN,13000,FALSE,LED_PWM_0},
	  {CYAN,5000,TRUE,LED_PWM_100},
	  {CYAN,14000,FALSE,LED_PWM_0},
	  {BLUE,6000,TRUE,LED_PWM_100},
	  {BLUE,15000,FALSE,LED_PWM_0},
	  {PURPLE,7000,TRUE,LED_PWM_100},
	  {PURPLE,16000,FALSE,LED_PWM_0},
	  {WHITE,8000,TRUE,LED_PWM_100},
	  {WHITE,17000,FALSE,LED_PWM_0},
	};
   
	u32TimePoint++;
	if(u32TimePoint == 20000)
	{
	  u32TimePoint=0;
	}
	
	if(u32TimePoint%1000==0)
	{
		LCDMessage(LINE2_START_ADDR+14,au8Wan);
		LCDMessage(LINE2_START_ADDR+15,au8Qian);
		LCDMessage(LINE2_START_ADDR+16,au8Bai);
		LCDMessage(LINE2_START_ADDR+17,au8Shi);
		LCDMessage(LINE2_START_ADDR+18,au8Ge);
		
		for(i=0;i<16;i++)
		{
			if(u32TimePoint==aeDemolist[i].u32Time)
			{
			  LedPWM(aeDemolist[i].eLed,aeDemolist[i].eCurrentRate);
			  
			  if(aeDemolist[i].bOn==TRUE)
			  {
				LCDMessage(LINE1_START_ADDR+au8Bit[i],"1");
			  }
			  else
			  {
				LCDMessage(LINE1_START_ADDR+au8Bit[i],"0");
			  }
			}
			
			
		}
	}
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
