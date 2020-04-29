#include <timers.h>
#include <button.h>
#include <callBacks.h>

extern Button *ON_button;
extern Button *open_uSwitch;

void Init_Timer3(){
	TCCR3B = 0;
	TCCR3A = 0;	
	TCNT3  = 0;					// preload timer
	TIMSK3 |= (1 << OCIE3A);	// enable timer compare interrupt
}

void Init_Timer4(){
	TCCR4B = 0;
	TCCR4A = 0;	
	TCNT4  = 0;					// preload timer 
	TIMSK4 |= (1 << OCIE4A);	// enable timer compare interrupt
}

void Init_Timer5(){
	TCCR5B = 0;
	TCCR5A = 0;	
	TCNT5  = 0;					// preload timer
}

ISR(TIMER3_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3  = 0;
	TIMSK3 = 0;
	OCR3A  = 0;
	if(ON_button->get_Status()==BSTATE_LOW){
		ON_button->set_On_Off();
		ON_button->set_Clicked(true);		
	}	
	OCR3B = 1024*3;		
	TIMSK3 |= (1 << OCIE3B);		 
}

ISR(TIMER3_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3 = 0;
	if(ON_button->get_Status()==BSTATE_HIGH){
		TCCR3B = 0;			
		TIMSK3 = 0;
		OCR3B  = 0;
		OCR3A  = 512;
		TIMSK3= (1 << OCIE3A);  
		ON_button->enableInterrupt(onButton_callback);			
	}
}

ISR(TIMER4_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT4  = 0;
	TIMSK4 = 0;
	OCR4A  = 0;	
	if(open_uSwitch->get_Status()==BSTATE_LOW){
		open_uSwitch->set_Clicked(true);
	}	
	OCR4B = 1024*3;		
	TIMSK4 |= (1 << OCIE4B);		 
}


ISR(TIMER4_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT4 = 0;
	if(open_uSwitch->get_Status()==BSTATE_HIGH){
		TCCR4B = 0;			
		TIMSK4 = 0;
		OCR4B  = 0;
		OCR4A  = 512;
		TIMSK4= (1 << OCIE4A);  	
		open_uSwitch->enableInterrupt(open_uSw_callback);		
	}
}

