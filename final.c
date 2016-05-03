//Erin Flynn, Brynna Conway and Leah Plofchan Final Project
#include <stdio.h>
#include <string.h> 
#include "gfx5.h"
#define MAXLENGTH 50

void draw_calendar(int w, int h);
int check_month(int month);
int check_day(int day, int month, int year);
int check_year(int year);

typedef struct Event
{
  int year;
  int month;
  int day;
  char title[MAXLENGTH];
  char location[MAXLENGTH];
  char start_time[10];
  char end_time[10];
}Event;
    
int main() { 
  
    char garbage1[5];    
    Event event1;
    int w,h;
    char c1,c2;
    
   
  /*printf("\nWhich year would you like? Please input the year as the corresponding number with four digits.\n"); 
    scanf("%d", &event1.year); 
    while (check_year(event1.year)==1){ //check to make sure a valid year is input 
        printf("ERROR! Please enter a valid year.\n");
        scanf("%d", &event1.year);
        check_year(event1.year);
    }
    
    printf("\nWhich month would you like? Please input the month as the corresponding number.\n"); 
    scanf("%d", &event1.month); 
    while (check_month(event1.month)==1){ //check to make sure a valid month is input 
        printf("ERROR! Please enter a valid month.\n");
        scanf("%d", &event1.month);
        check_month(event1.month);
    }

    
    printf("\nWhich day would you like? Please input the day as a number.\n"); 
    scanf("%d", &event1.day); 
    while (check_day(event1.day,event1.month, event1.year)==1){
        printf("Error! Please enter a valid day.\n");
        scanf("%d",&event1.day);
        check_day(event1.day,event1.month, event1.year);
    }
    
    printf("\nPlease enter the title of the event.\n"); 
    fgets(garbage1,5,stdin);//store the return value in an array
    fgets(event1.title,MAXLENGTH,stdin); //get the title input from user
    puts(event1.title); //needs to be deleted later, used to check right now 
   
    printf("\nPlease enter the location of the event.\n");
    fgets(event1.location,MAXLENGTH,stdin);
    puts(event1.location); //needs to be deleted later, used to check right now 
    
    printf("\nPlease enter the start time of the event, using am or pm to denote morning or afternoon.\n");
    fgets(event1.start_time,10,stdin);
    
    printf("\nPlease enter the end time of the event, using am or pm to denote morning or afternoon.\n");
    fgets(event1.end_time,10,stdin);

    
    *///find the width and height of the screen the program is running on
    w=gfx_screenwidth();
    h=gfx_screenheight();
    
    gfx_open(w/2,h/2,"Choose type of Event");
     while(c1!='p'){
         gfx_fill_rectangle(50,200,60,20);
        
   
        if (gfx_event_waiting){
            c1=gfx_wait();
        }
    
    
    }//end while loop
    
    gfx_open(w,h,"Calendar");
    
    while(c2!='q'){
    	draw_calendar(w,h);
   
        if (gfx_event_waiting){
            c2=gfx_wait();
        }
    
    
    }//end while loop
    
    switch (event1.month) {
        case 1: 
            break; 
        case 2: 
            break;
        case 3: 
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
    }
    
    return 0; 
}  //end main
   

int check_year(int year) { 
    if (year < 1000 || year > 9999) 
        return 1; 
    else 
        return 0; 
} 

//this function checks to see if the user has entered a correct month value 
//NOTE WE STILL NEED TO ACCOUNT FOR FEB
int check_month (int month){
    if (month<1 || month>12)
        return 1;
    else 
        return 0;
}     

int check_day(int day, int month, int year) {
    if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) {
            if (day<1 || day>31)
                return 1;
    }

    else if (month==4 || month==6 || month==9 || month==11) {
        if (day<1 || day>30)
            return 1;
    }

    else if (month == 2) { //to account for leap years
        if (year%4 == 0 && (day < 1 || day > 29))
            return 1; 
        else if (day < 1 || day > 28) 
            return 1; 
    }

    return 0;
}

void draw_calendar(int w, int h){
    gfx_rectangle(100,100,1100,600);
    gfx_line(1000/7,100,1000/7,500);
    //gfx_line(200,100,w-200,h-100);
    


} 
