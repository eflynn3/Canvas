#include <stdio.h>
#include <string.h>
#include <math.h> 
#include "gfx5.h"
#include <unistd.h> 
#define HEIGHT 740 // height of graphics window
#define WIDTH 1200 // width of graphics window
#define XVAL 10 // starting x location of square on the color palette of the tool bar
#define YVAL 500 // starting x location of square on the color palette of the tool bar
#define SQUARE 25 // size of each square on the color palette of the tool bar

// function prototypes
int checktool(int x, int y); 
int spraypaint(int *tool, int *checked, char *c);
int markertool(int *tool, int *checked, char *c);
int drag(int *tool, int *checked, char *c);
int penciltool(int *tool, int *checked, char *c);
int erasertool(int *tool, int *checked, char *c);
int drawcolortools(int x1, int y1, int w, int h,int colors[][3]);
int checkcolors(int, int);
void draw_toolbarsection(); 
void check_box(int x, int y,int size);
void draw_pencil(int x,int y, int pencil[][3]);
void draw_spraycan(int, int y, int spraycan[][3]);
void draw_marker(int,int,int [][3]);
void draw_eraser(int,int,int [][3]);
void draw_rectangle(int x,int y);
void draw_clear(int x, int y); 

// begin main function
int main(){
    char c;
    int colors[10][3]={ // array of the 10 colors displayed on the paint tool bar, each location contains the RGB color values of the respective color
        {0,0,0},//black
        {128,128,128},//gray
        {0,0,255},//blue
        {255,0,0},//red
        {0,255,0},//green
        {255,255,0},//yellow
        {255,128,0},//orange
        {0,255,255},//light blue
        {127,0,255},//pink
        {255,0,255}//purple 
    };
    int pencil[13][3]={ //array used for the drawing of the pencil icon on the paint tool bar
        {0,0,0},//black
        {206,179,151},//A
        {222,198,175},//B
        {255,229,204},//C
        {255,255,102},//D
        {255,233,28},//E
        {239,217,20},//F
        {239,239,239},//G
        {216,216,215},//H
        {188,188,188},//I
        {255,204,229},//J
        {236,125,177},//K
        {209,79,140}//L
        };
    int spraycan[3][3]={ //array used for drawing the spray can icon on the paint tool bar
        {0,0,0},//black
        {255,255,255},//white
        {127,0,255}//purple
    };
    int marker[7][3]={ // array used for drawing the marker icon on the paint tool bar
        {129,195,63},//left green
        {169,232,76},//middle green
        {98,151,45},//right green
        {224,224,224},//light gray
        {255,255,255},//white
        {192,192,192},//gray
        {0,0,0}//black
    };
    int eraser[5][3]={ // array used for drawing the eraser icon of the paint tool bar
        {210,157,157},//front edge
        {202,122,122},//side edge
        {255,204,204},//light pink
        {255,153,153},//darker pink
        {206,126,126}//darkest pink
    };

    int x, y, tool=0, checked, checkcount=0, toolcount =0; // initialization of variables
    
    gfx_open(WIDTH,HEIGHT,"Welcome to Canvas!"); // open the graphics window
    gfx_clear_color(255,255,255); // make window initially all white
    gfx_clear();
    draw_toolbarsection(); // draw the tool bar on the left side of the graphics window
    drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // function that will draw the color palette on the bottom of the tool bar on the graphics window
    draw_pencil(30,60,pencil); // draws the pencil icon on the tool bar
    draw_spraycan(30,150,spraycan); // draws the spray can icon on the tool bar
    draw_marker(100,60,marker); // draws the marker icon on the tool bar
    draw_eraser(90,140,eraser); // draws the eraser icon on the tool bar
    draw_rectangle(22,200); // draws the rectangle icon on the tool bar
    draw_clear(78, 195); // draws the clear icon on the tool bar that will clear any previously drawn drawings
    gfx_text(35,590, "You are using: ");
    gfx_cleararea(31,601,88,88);
    gfx_rectangle(30,600,90,90);
    int begin=0;
    char p;

    // begin main while loop
    while(c!='q'){  
		while (begin==0) {
		    while (c!=1){
		        c=gfx_wait(); // waits for user interaction
		        if (c=='q'){ //checks to see if the user tries to exit
		        	return 0;
		        }
		    }
		 	x=gfx_xpos(); //get the x and y position 
		  	y=gfx_ypos();
		  	if (toolcount == 0) {
		      tool = checktool(x, y); // calls checktool() function to find which icon tool was clicked by the user
		      begin=1; //change begin so that the while loop will exit 
		  	}
		    if (checkcount == 0) {
		        checked = checkcolors(x, y); // calls checkcolors() function to find which color was chosen by the user
		        begin=1; //chang begin so that the while loop will exit 
		        
		    }
  		 } 
            switch(checked){ // assigns corresponding color that user chose based on returned value from the checkcolors() function
                    case 1: // black is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*0,YVAL,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[0][0], colors[0][1], colors [0][2]); // changes color
                        checkcount = 1;  // increment checkcount
                       	p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                        
                    case 2: // grey is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*1,YVAL,SQUARE);// draws check box on color to indicate the chosen color
                        gfx_color(colors[1][0], colors[1][1], colors [1][2]); // changes color
                        checkcount = 1; // increment checkcount
                      	p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        
                        break;
                    case 3: // dark blue is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*2,YVAL,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[2][0], colors[2][1], colors [2][2]); // changes color
                        checkcount = 1; // increment checkcount
 						p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 4: // red is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*3,YVAL,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[3][0], colors[3][1], colors [3][2]); // changes color 
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 5: // green is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*4,YVAL,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[4][0], colors[4][1], colors [4][2]); // changes color
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 6: // yellow is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*0,YVAL+30,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[5][0], colors[5][1], colors [5][2]); // changes color
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 7: // orange is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*1,YVAL+30,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[6][0], colors[6][1], colors [6][2]); // changes color
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 8: // light blue is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*2,YVAL+30,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[7][0], colors[7][1], colors [7][2]); // changes color
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 9: // purple is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*3,YVAL+30,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[8][0], colors[8][1], colors [8][2]); // changes color
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                    case 10: // pink is chosen
                        drawcolortools(XVAL,YVAL,SQUARE,SQUARE,colors); // redraws color palette
                        check_box(XVAL+30*4,YVAL+30,SQUARE); // draws check box on color to indicate the chosen color
                        gfx_color(colors[9][0], colors[9][1], colors [9][2]); // changes color
                        checkcount = 1; // increment checkcount
                        p=gfx_wait(); //check for click again
                       	x=gfx_xpos(); //get x and y position of the click 
                       	y=gfx_ypos();
                       	if (p==1){ //if there is a click 
                       		tool=checktool(x,y); //find out if it was on a tool 
                       	}
                        break;
                }//end switch 
            switch(tool){ // go into respective drawing tools function based on user's click
                case 1:  // pencil tool
                    toolcount = 1; // increment toolcount 
                    gfx_cleararea(31,601,88,88); // makes white box on the bottom of the tool bar
                    draw_pencil(55,660,pencil); // draw pencil icon in white box to indicate current tool
                    gfx_color(colors[checked-1][0], colors[checked-1][1], colors[checked-1][2]); // changes color back to selected color
                    penciltool(&tool, &checked, &c); // enter penciltool() function to allow user to draw with pencil
                    if (c == 'q') // allow user to quit program
                        return 0; 
                    break;
                case 2:  // spray paint tool
                    toolcount = 1; // increment toolcount 
                    gfx_cleararea(31,601,88,88); // makes white box on the bottom of the tool bar
                    draw_spraycan(70,675,spraycan); // draw spray can icon in white box to indicate current tool
                    gfx_color(colors[checked-1][0], colors[checked-1][1], colors[checked-1][2]); // changes color back to selected color
                    spraypaint(&tool, &checked, &c); // enter spraypaint() function to allow user to spray paint the canvas
                    if (c == 'q') // allow user to quit program
                        return 0; 
                    break;
                case 3:  // marker tool
                    toolcount = 1; // increment toolcount 
                    gfx_cleararea(31,601,88,88); // makes white box on the bottom of the tool bar
                    draw_marker(65,660,marker); // draw marker icon in white box to indicate current tool
                    gfx_color(colors[checked-1][0], colors[checked-1][1], colors[checked-1][2]); // changes color back to selected color
                    markertool(&tool, &checked, &c); // enter markertool() function to allow user to draw with marker
                    if (c == 'q') // allow user to quit program
                        return 0; 
                    break; 
                case 4: // draw rectangle tool
                    toolcount = 1;    // increment toolcount
                    gfx_cleararea(31,601,88,88); // makes white box on the bottom of the tool bar
                    draw_rectangle(55,660); // draw rectangle icon in white box to indicate current tool
                    gfx_color(colors[checked-1][0], colors[checked-1][1], colors[checked-1][2]); // changes color back to selected color            
                    drag(&tool, &checked, &c); // enter drag() function to allow user to draw rectangles and resize them
                    if (c == 'q') // allow user to quit program
                        return 0; 
                    break;
                case 5: // eraser tool
                    toolcount = 1; // increment toolcount 
                    gfx_cleararea(31,601,88,88); // makes white box on the bottom of the tool bar
                    draw_eraser(55,650,eraser); // draw eraser icon in white box to indicate current tool
                    erasertool(&tool, &checked, &c); // enter erasertool() function to allow user to erase drawings and change size of eraser
                    if (c == 'q') // allow user to quit program
                        return 0; 
                    break;
                case 6: // clear canvas tool
                    gfx_cleararea(161, 0, WIDTH - 161, HEIGHT);
                    gfx_cleararea(31,601,88,88); // makes white box on the bottom of the tool bar
                    draw_clear(38,650); // draw clear icon in white box to indicate current tool
                    toolcount = 0; 
                    checkcount = 0; 
                    begin=0;
                    break;
            }//end switch
        c=gfx_wait(); //check for event 
    }  
	
    return 0; 
}

// function that wil draw the tool bar on the left side of the graphics window
void draw_toolbarsection(){
        
    gfx_color(192,192,192); // set color to gray
    gfx_fill_rectangle(0,0,160,HEIGHT); //draw gray rectangle that will be the toolbar 
    gfx_color(0,0,0); // set color to black for the right border line
    gfx_line(160,0,160,HEIGHT); //draw line for the edge of the toolbar 
    
return;
}

// function that will recognize, based on location of user click, which color on the tool bar was chosen. 
// function will return corresponding checked value that will direct the program through the switch statement in the main function
int checkcolors(int x, int y){
    int checked;
        if ((x>=XVAL+30*0 && x<=XVAL+30*0+SQUARE) && (y>=YVAL && y<=YVAL+SQUARE)){ // location of black color box
            checked=1;//black
            }
        else if ((x>=XVAL+30*1 && x<=XVAL+30*1+SQUARE) && (y>=YVAL && y<=YVAL+SQUARE)){ // location of grey color box
            checked=2;//grey
            }
        else if ((x>=XVAL+30*2 && x<=XVAL+30*2+SQUARE) && (y>=YVAL && y<=YVAL+SQUARE)){ // location of blue color box
            checked=3;//blue
            }
        else if ((x>=XVAL+30*3 && x<=XVAL+30*3+SQUARE) && (y>=YVAL && y<=YVAL+SQUARE)){ // location of red color box
            checked=4; //red 
            }
        else if ((x>=XVAL+30*4 && x<=XVAL+30*4+SQUARE) && (y>=YVAL && y<=YVAL+SQUARE)){ // location of green color box
            checked=5;//green
            }
        else if ((x>=XVAL+30*0 && x<=XVAL+30*0+SQUARE) && (y>=YVAL+30 && y<=YVAL+30+SQUARE)){ // location of yellow color box
            checked=6;//yellow
            }
        else if ((x>=XVAL+30*1 && x<=XVAL+30*1+SQUARE) && (y>=YVAL+30 && y<=YVAL+30+SQUARE)){ // location of orange color box
            checked=7;//orange
            }
        else if ((x>=XVAL+30*2 && x<=XVAL+30*2+SQUARE) && (y>=YVAL+30 && y<=YVAL+30+SQUARE)){ // location of light blue color box
            checked=8;//light blue
            }
        else if ((x>=XVAL+30*3 && x<=XVAL+30*3+SQUARE) && (y>=YVAL+30 && y<=YVAL+30+SQUARE)){ // location of pink color box
            checked=9;//pink
            }
        else if ((x>=XVAL+30*4 && x<=XVAL+30*4+SQUARE) && (y>=YVAL+30 && y<=YVAL+30+SQUARE)){ // location of purple color box
            checked=10;//purple
            }
    return checked;
}

// function that will recognize, based on location of user click, which tool on the tool bar was chosen
// function will return corresponding tool value that will direct the program throught the switch statement in the main function
int checktool(int x, int y) { 

    int tool; 
    if ((x>30 && x<74) && (y>16 && y<60)){ // location of pencil icon
            tool=1; //pencil
        }
    else if ((x>30 && x<50) && (y>94 && y<150)){ // location of spray paint icon
        tool=2; // spray paint
        }
    else if ((x>100 && x<114) && (y>16 && y<70)){ // location of marker tool icon
        tool=3; // marker
        }
    else if ((x>22 && x<55) && (y>170 && y<200)){ // location of rectangle icon
        tool=4; // draw rectangle
        }
    else if ((x>90 && x<132) && (y>110 && y<170)){ // location of eraser icon
        tool=5; // eraser
        }
    else if ((x>78 && x<153) && (y>177 && y<195)){ // location of clear canvas button
        tool=6; // clear
        }
    else { // otherwise, return 0 value of tool so no tool is selected
        tool = 0;
    }
    return tool; 
}

// function that will allow the user to use the spray paint on the canvas
int spraypaint(int *tool, int *checked, char *c) { 

    int i, r = 0, xclick, yclick, x1, y1, xc, yc, loop = 1, event, check = 0, x, y, t, color; 
    double theta = 0;
    char cc = '2';  
    
    while (loop) {
        r = 0;
        theta = 0; 
        if (event = gfx_event_waiting()) { // waits for user input
            cc = gfx_wait();
            if (cc == 'q')  { // allows the user to quit from program
                *c = 'q'; 
                return; 
            }
            if (cc == 1 || cc == 3) { // checks if user clicked
                if(event == 3) // mouse button push down
                    check = 1; // set check value so that program will enter if statement below
                else if (event==4) // mouse button release
                    check=0; // will stop the spray paint from displaying on screen
            }
            if (check) { 
                x1 = gfx_xpos(); // find x position
                y1 = gfx_ypos(); // find y position
                xc = x1; 
                yc = y1;
                if (gfx_xpos() > 162) // restricts spray paint from only appearing on the canvas (nothing will appear on the tool bar section of the graphics window)
                    for (r = 0; r < 10; r= r + 2) {  // for loop that will create spray paint look 
                        for (theta = 0; theta < 2*M_PI; theta = theta + (M_PI/6)) { 
                            x1 = xc + (r * cos(theta)); 
                            y1 = yc + (r * sin(theta));
                            gfx_point(x1, y1); 
                        }    
                    }
                else { // if user clicked inside the toolbar, this will allow another tool or color to be chosen
                    while (gfx_xpos() < 162) {
                        cc = gfx_wait();
                        x = gfx_xpos(); 
                        y = gfx_ypos();
                        if (cc == 1) { // recognized user click
                            t = checktool(x, y); // check if a tool was chosen
                            color = checkcolors(x, y); // check if a color was chosen
                            if (t != 0) {
                                *tool = t; // assign t value from checktool() to the address of tool
                                return;
                            }
                            if (color != 0) {
                                *checked = color; // assign color value from checkcolors() to the address of checked
                                return;  
                            }
                        }
                        if (cc == 'q') { // allows user to quit the program
                            *c = 'q'; 
                            return; 
                        }
                    }
                } 
            }
            
        }
    }

return 0; 
}
// function that will allow the user to draw a rectangle on the canvas, user will be able to change size of the rectangle
int drag(int *tool, int *checked, char *c){ 
    int i, r = 0, xclick = 200, yclick, xclick1, yclick1, loop = 1, event, check = 0, x, xchange, ychange, y, t, color, xcorner, ycorner;  
    double theta = 0;
    char cc = '2';  
    int width, height, ytop, xtop; 

    start: 
    // display instructions on how to operate the rectangle tool 
    gfx_text(10, 320, "To change the size of");
    gfx_text(10, 332, "the rectangle, click");
    gfx_text(10, 344,"the bottom left corner of");
    gfx_text(10, 356, "the rectangle and drag.");
    gfx_text(10, 368, "When you are finished"); 
    gfx_text(10, 380, "changing size, press s");  
    check = 0;
    width = 75; 
    height=50; 
    wait: 
    cc=gfx_wait(); 
    while (cc!= 1) {
        cc=gfx_wait();
        if (cc == 'q') { // allows user to quit the program
            *c = 'q'; 
            return;
        }
    }
    // find x and y locations of the user click so that the rectangle will be drawn whereever the user clicks (as long as it is not clicked on the tool bar section)
    xtop = gfx_xpos();
    ytop = gfx_ypos();
    xcorner = xtop; 
    ycorner = ytop + height; 
    if (xtop > 162) // draws the rectangle on the canvas
        gfx_rectangle(xtop, ytop, width, height); 
    else { // if the user clicked inside the tool bar, this will check if a new tool or different color was chosen
        t = checktool(xtop, ytop); // check if a tool was chosen
        color = checkcolors(xtop, ytop);  // check if a color was chosen
        if (t != 0) {
            *tool = t; // assign t value from checktool() to the address of tool
            gfx_color(192, 192, 192);  // sets color to grey
            gfx_fill_rectangle(9, 310, 150, 100); // redraws over the rectangle tool instructions so it does not appear while other tools are chosen
            return;
        }
        if (color != 0) {
            *checked = color; // assign color value from checkcolor() to the address of checked
            return;  
        }
        goto wait; // returns to earlier part of function to allow user to click and draw another rectangle on the canvas
    }
 

    while (loop) {
        event = gfx_event_waiting();
        if (event) {
            cc = gfx_wait();
            if (cc== 'q') { // allows the user to quit
                *c = 'q';
                return;
            }
            if (cc == 1 || cc == 3) {
                xclick1 = gfx_xpos(); 
                yclick1 = gfx_ypos(); 
                if(event == 3) { // user mouse button press
                    if (xclick1 < xcorner + 10 && xclick1 > xcorner - 10 && yclick1 < ycorner +10 && yclick1 > ycorner - 10) // if the user clicks the bottom letter corner of the rectangle, assign value to check to allow user to change size
                        check = 1;
                    else 
                        goto start; // since user didn't click the bottom left corner, restarts the checking process to either draw another rectangle or to check if user clicked inside the tool bar
                }
                else if (event==4) // mouse button release
                    check=0;
            }
        }
            while (check) { 
                cc = gfx_wait(); 
                while (xclick > 162) { // if the click was outside of the tool bar
                    xclick = gfx_xpos(); 
                    yclick = gfx_ypos();
                    xchange = xclick - xclick1; 
                    ychange = yclick - yclick1; 
                    if (xclick < xtop) // changes width of the rectangle
                        xchange = -1*width;
                    if (yclick < ytop) // changes height of the rectangle
                        ychange = -1*height;
                    if (xchange < -3*width || ychange < -3*height) // restricts the user to changing the size of the rectangle so that you must drag the bottom corner down and not up
                        goto skip; // will skip through clearing of the rectangle
                    // clears each line of the rectangle to create moving rectangle so that only the final size of the changed rectangle will appear
                    gfx_cleararea(xtop, ytop, width +1, 1);
                    gfx_cleararea(xtop, ytop + height, width +1, 1);
                    gfx_cleararea(xtop, ytop, 1, height+1);
                    gfx_cleararea(xtop + width, ytop, 1, height+1);
                    width = 75 + xchange; 
                    height = 50 + ychange; 
                    gfx_rectangle(xtop, ytop, width, height); 
                    skip:  
                    cc = gfx_wait();
                    if (cc=='s') // once the user presses the 's' key, the function will stop checking for movement to change the size of the currently selected rectangle
                        goto start;
                    xclick = gfx_xpos(); 
                    yclick = gfx_ypos();
                }
                cc = gfx_wait(); 
                if (cc == 1) { // checks to see if the user clicked a new tool or color
                    t = checktool(xclick, yclick); // checks for new tool
                    color = checkcolors(xclick, yclick); // checks for new color
                    if (t != 0) {
                        *tool = t; // assign t value from checktool() to the address of tool
                        gfx_color(192, 192, 192); // set grey color
                        gfx_fill_rectangle(9, 310, 150, 100); // draws over the instructions of the rectangle function so that they will not appear for the new tool function
                        return;
                    }
                    if (color != 0) {
                        *checked = color; // assigns color value from checkcolors() to the address of checked
                        return;  
                    }
                }
                if (cc == 'q') { // allows user to quit
                    *c = 'q';
                    return; 
                }
            }
                
        }

return 0; 
}

// function that will allow the user to draw on the canvas with a marker
int markertool(int *tool, int *checked, char *c){
    int w=600;
    int h=700;
    int xpos, ypos;
    char cc;
    int check = 0, event, loop=1, x, y, t, color;

    while (loop) {
        if (event = gfx_event_waiting()) { // checks for user input
            cc = gfx_wait();
            if (cc == 'q') { // allows user to quit program
                *c = 'q';
                return;
            }
            if (cc == 1 || cc == 3) // if user input is detected
                if(event == 3) // mouse button press
                    check = 1; // change check value to have program enter if statement to use marker tool
                else if (event==4) // mouse button release
                    check=0; // change check value so that marker tool is not going while user has not clicked
            if (check) {
                if (gfx_xpos() > 162) // checks that user clicked outside of the tool bar
                    gfx_fill_circle(gfx_xpos(), gfx_ypos(), 5); // will continuously draw a circle of radius 5 to create marker effect
                else { 
                    while (gfx_xpos() < 162) { // user clicked inside of the tool bar
                        cc = gfx_wait();
                        x = gfx_xpos(); // finds position of user click
                        y = gfx_ypos();
                        if (cc == 1) { 
                            t = checktool(x, y); // checks for new tool
                            color = checkcolors(x, y); // checks for new color
                            if (t != 0) {
                                *tool = t; // assign t value from checktool() to the address of tool
                                return;
                            }
                            if (color != 0) {
                                *checked = color; // assigns color value from checkcolors() to the address of checjed
                                return;  
                            }
                        }
                        if (cc == 'q') { // allows the user to quit
                            *c = 'q'; 
                            return;
                        }
                    }
                }
            }
        }
    }
    
return 0;
}

// function that will allow the user to erase on the canval
int erasertool(int *tool, int *checked, char *c){
    int w=600;
    int h=700;
    int size = 15; // default size of the eraser in case the user does not choose a size in the tool bar
    int xpos, ypos;
    char cc;
    int check = 0, event, loop=1, x, y, xclick, yclick, t, color;
    
    // displays the size options of the erase inside of the tool bar
    gfx_color(0,0,0);
    gfx_text(10, 320, "Choose eraser size:");
    gfx_text(10, 350, "Small"); 
    gfx_text(10, 380, "Medium"); 
    gfx_text(10, 410, "Large");       
    gfx_color(255,255,255);

    cc = gfx_wait(); 
    xclick = gfx_xpos(); // finds position of the user click
    yclick = gfx_ypos(); 
    while (cc != 1 ) { 
        cc = gfx_wait();
        xclick = gfx_xpos(); 
        yclick = gfx_ypos(); 
        if (cc == 'q') { // allows the user to quit
            *c = 'q'; 
            return;
        }
    }
    sizechange: 
    if (xclick >= 8 && xclick <= 80 && yclick >= 340 && yclick <= 365) { // user clicked on the small size option
        size = 5;
    }
    if (xclick >= 8 && xclick <= 80 && yclick >= 370 && yclick <= 395) // user clicked on the medium size option
        size = 15; 
    if (xclick >= 8 && xclick <= 80 && yclick >= 400 && yclick <= 425) // user clicked on the large size option
        size = 25;  
 
    usleep(500000); 
    gfx_color(192, 192, 192); // set color to grey
    gfx_fill_rectangle(8, 305, 130, 108); // will draw over the size change options of the eraser (the user can only change the size of the eraser once)
    gfx_color(255, 255, 255); // resets color back to white for the eraser funciton

    while (loop) {
        if (event = gfx_event_waiting()) {
            cc = gfx_wait();
            if (cc == 'q') {  // allows the user to quit
                *c = 'q'; 
                return; 
            } 
            if (cc == 1 || cc == 3) 
                if(event == 3) // mouse button press
                    check = 1; // changes check value to allow program to enter if statement to use eraser
                else if (event==4) // mouse button release
                    check=0;
            if (check) {
                if (gfx_xpos() > 161+size)  // user clicked outside of the tool bar
                    gfx_fill_circle(gfx_xpos(), gfx_ypos(), size); // continuously draws white circles corresponding to location of cursor, size is dependent on user choice from above
                else {
                    while (gfx_xpos() < 162 +size) { // user clicked inside of the tool bar
                        cc = gfx_wait();
                        x = gfx_xpos(); // finds position of user click
                        y = gfx_ypos();
                        if (cc == 1) {
                            t = checktool(x, y); // checks for new tool
                            color = checkcolors(x, y);  // checks for new color
                            if (t != 0) {
                                *tool = t; // assign t value from checktool() to the address of tool
                                return;
                            }
                            if (color != 0) {
                                *checked = color; // assign color value from checkcolors() to the address of checked
                                return;  
                            }
                        }
                        if (cc == 'q') { // allows the user to quit
                            *c = 'q'; 
                            return; 
                        }
                    }
                }
            }
        }
    }
return 0;
}

// function that will allow the user to use the pencil on the canvas
int penciltool(int *tool, int *checked, char *c) {
    int w=600;
    int h=700;
    int xpos, ypos;
    char cc;
    int check = 0, event, loop=1, x, y, t, color;

    while (loop) {
        if (event = gfx_event_waiting()) {
            cc = gfx_wait();
            if (cc == 'q')  { // allows the user to quit
                *c = 'q'; 
                return;
            }
            if (cc == 1 || cc == 3) 
                if(event == 3) // mouse button press
                    check = 1; // changes the check value to allow the program to enter the following if statement to draw the pencil
                else if (event==4) // mouse button release
                    check=0;
            if (check) {
                if (gfx_xpos() > 162) // user clicked outside of the tool bar
                    gfx_fill_circle(gfx_xpos(), gfx_ypos(), 2); // continuously draws small circle of chosen color to create pencil drawing effect
                else {
                    while (gfx_xpos() < 162) { // user clicked inside of the tool bar
                        cc = gfx_wait();
                        x = gfx_xpos(); // finds position of the user click
                        y = gfx_ypos();
                        if (cc == 1) {
                            t = checktool(x, y); // checks for new tool
                            color = checkcolors(x, y); // checks for new color
                            if (t != 0) {
                                *tool = t; // assign t value from checktool() to the address of tool
                                return;
                            }
                            if (color != 0) {
                                *checked = color; // assigns color value from checkcolors() to the address of checked
                                return;  
                            }
                        }
                        if (cc == 'q') { // allows the user to quit
                            *c = 'q'; 
                            return; 
                        }
                    }
                }
            }
        }
    }
return 0;
}

// function that will draw the color palette on the bottom of the tool bar on the graphics window
int drawcolortools(int x1, int y1, int w, int h, int colors [][3]) { 
    
    gfx_color(colors[0][0],colors[0][1],colors[0][2]); //black (calling the RGB values from the array initialized in the main function)
    gfx_text(x1,y1-10,"Pick Your Color");
    gfx_fill_rectangle(x1,y1,w,h); // draws black box
    gfx_color(colors[1][0],colors[1][1],colors[1][2]); //gray (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+30,y1,w,h); // draws gray box
    gfx_color(colors[2][0],colors[2][1],colors[2][2]); //blue (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+60,y1,w,h); // draws blue box
    gfx_color(colors[3][0],colors[3][1],colors[3][2]); //red (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+90,y1,w,h); // draws red box
    gfx_color(colors[4][0],colors[4][1],colors[4][2]); //green (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+120,y1,w,h); // draws green box
    //Start new line 
    gfx_color(colors[5][0],colors[5][1],colors[5][2]); //yellow (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1,y1+30,w,h); // draws yellow box
    gfx_color(colors[6][0],colors[6][1],colors[6][2]); //orange (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+30,y1+30,w,h); // draws orange box
    gfx_color(colors[7][0],colors[7][1],colors[7][2]); //light blue (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+60,y1+30,w,h); // draws light blue box
    gfx_color(colors[8][0],colors[8][1],colors[8][2]); //purple (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+90,y1+30,w,h); // draws purple box
    gfx_color(colors[9][0],colors[9][1],colors[9][2]); //pink (calling the RGB values from the array initialized in the main function)
    gfx_fill_rectangle(x1+120,y1+30,w,h); // draws pink box

    return 0; 
} 

// function that will draw a check mark inside of the color box that is chosen on the color palette of the tool bar
void check_box(int x, int y,int size){
    gfx_color(255,255,255); // set color to white for the check mark
    gfx_line(x+size/6,y+size/2,x+size/3,y+3*size/4);
    gfx_line(x+size/6+1,y+size/2,x+size/3+1,y+3*size/4);
    gfx_line(x+size/3,y+3*size/4,x+4*size/5,y+size/7);
    gfx_line(x+size/3,y+3*size/4,x+4*size/5+1,y+size/7);
}

// function that will draw the pencil icon on the tool bar
void draw_pencil(int x,int y, int pencil[][3]){
    int n=4;
    gfx_color(pencil[0][0],pencil[0][1],pencil[0][2]);
    gfx_fill_rectangle(x,y,n,n);
    gfx_color(pencil[3][0],pencil[3][1],pencil[3][2]);
    gfx_fill_rectangle(x,y-1*n,n,n);
    gfx_fill_rectangle(x,y-2*n,n,n);
    gfx_color(pencil[1][0],pencil[1][1],pencil[1][2]);  
    gfx_fill_rectangle(x+1*n,y,n,n);
    gfx_fill_rectangle(x+2*n,y,n,n);
    gfx_color(pencil[2][0],pencil[2][1],pencil[2][2]);
    gfx_fill_rectangle(x+1*n,y-1*n,n,n);
    gfx_color(pencil[4][0],pencil[4][1],pencil[4][2]);  
    gfx_fill_rectangle(x,y-3*n,n,n);
    gfx_fill_rectangle(x+1*n,y-3*n,n,n);
    gfx_fill_rectangle(x+1*n,y-4*n,n,n);
    gfx_fill_rectangle(x+2*n,y-4*n,n,n);
    gfx_fill_rectangle(x+2*n,y-5*n,n,n);
    gfx_fill_rectangle(x+3*n,y-5*n,n,n);
    gfx_fill_rectangle(x+3*n,y-6*n,n,n);
    gfx_fill_rectangle(x+4*n,y-6*n,n,n);
    gfx_fill_rectangle(x+4*n,y-7*n,n,n);
    gfx_fill_rectangle(x+5*n,y-7*n,n,n);
    gfx_color(pencil[5][0],pencil[5][1],pencil[5][2]);  
    gfx_fill_rectangle(x+1*n,y-2*n,n,n);
    gfx_fill_rectangle(x+2*n,y-1*n,n,n);
    gfx_fill_rectangle(x+2*n,y-2*n,n,n);
    gfx_fill_rectangle(x+2*n,y-3*n,n,n);
    gfx_fill_rectangle(x+3*n,y-2*n,n,n);
    gfx_fill_rectangle(x+3*n,y-3*n,n,n);
    gfx_fill_rectangle(x+3*n,y-4*n,n,n);
    gfx_fill_rectangle(x+4*n,y-3*n,n,n);
    gfx_fill_rectangle(x+4*n,y-4*n,n,n);
    gfx_fill_rectangle(x+4*n,y-5*n,n,n);
    gfx_fill_rectangle(x+5*n,y-4*n,n,n);
    gfx_fill_rectangle(x+5*n,y-5*n,n,n);
    gfx_fill_rectangle(x+5*n,y-6*n,n,n);
    gfx_fill_rectangle(x+6*n,y-5*n,n,n);
    gfx_fill_rectangle(x+6*n,y-6*n,n,n);
    gfx_color(pencil[6][0],pencil[6][1],pencil[6][2]);  
    gfx_fill_rectangle(x+3*n,y,4,n);
    gfx_fill_rectangle(x+4*n,y-1*n,n,n);
    gfx_fill_rectangle(x+3*n,y-1*n,n,n);
    gfx_fill_rectangle(x+4*n,y-2*n,n,n);
    gfx_fill_rectangle(x+5*n,y-2*n,n,n);
    gfx_fill_rectangle(x+5*n,y-3*n,n,n);
    gfx_fill_rectangle(x+6*n,y-3*n,n,n);
    gfx_fill_rectangle(x+6*n,y-4*n,n,n);
    gfx_fill_rectangle(x+7*n,y-4*n,n,n);
    gfx_fill_rectangle(x+7*n,y-5*n,n,n);
    gfx_color(pencil[7][0],pencil[7][1],pencil[7][2]);  
    gfx_fill_rectangle(x+5*n,y-8*n,n,n);
    gfx_fill_rectangle(x+6*n,y-8*n,n,n);
    gfx_fill_rectangle(x+6*n,y-9*n,n,n);
    gfx_fill_rectangle(x+7*n,y-9*n,n,n);
    gfx_color(pencil[8][0],pencil[8][1],pencil[8][2]);  
    gfx_fill_rectangle(x+6*n,y-7*n,n,n);
    gfx_fill_rectangle(x+7*n,y-7*n,n,n);
    gfx_fill_rectangle(x+8*n,y-7*n,n,n);
    gfx_fill_rectangle(x+7*n,y-8*n,n,n);
    gfx_fill_rectangle(x+8*n,y-8*n,n,n);
    gfx_color(pencil[9][0],pencil[9][1],pencil[9][2]);  
    gfx_fill_rectangle(x+8*n,y-5*n,n,n);
    gfx_fill_rectangle(x+8*n,y-6*n,n,n);
    gfx_fill_rectangle(x+9*n,y-7*n,n,n);
    gfx_fill_rectangle(x+9*n,y-6*n,n,n);
    gfx_color(pencil[10][0],pencil[10][1],pencil[10][2]);   
    gfx_fill_rectangle(x+8*n,y-10*n,n,n);
    gfx_fill_rectangle(x+7*n,y-10*n,n,n);
    gfx_color(pencil[11][0],pencil[11][1],pencil[11][2]);   
    gfx_fill_rectangle(x+8*n,y-9*n,n,n);
    gfx_fill_rectangle(x+9*n,y-9*n,n,n);
    gfx_fill_rectangle(x+9*n,y-8*n,n,n);
    gfx_color(pencil[12][0],pencil[12][1],pencil[12][2]);   
    gfx_fill_rectangle(x+10*n,y-7*n,n,n);
    gfx_fill_rectangle(x+10*n,y-8*n,n,n);
    

return ;
}

// function that will draw the spray can icon on the tool bar
void draw_spraycan(int x, int y, int spraycan[][3]){
    int n=4;
    gfx_color(spraycan[0][0],spraycan[0][1],spraycan[0][2]);
    gfx_fill_rectangle(x,y-9*n,4,9*n);
    gfx_fill_rectangle(x+1*n,y-9*n,5*n,n);
    gfx_fill_rectangle(x+1*n,y-1*n,5*n,n);
    gfx_fill_rectangle(x+5*n,y-9*n,n,9*n);      
    gfx_fill_rectangle(x+5*n,y-7*n,n,n);    
    gfx_fill_rectangle(x+4*n,y-7*n,n,n);
    gfx_fill_rectangle(x+3*n,y-7*n,n,n);
    gfx_fill_rectangle(x+3*n,y-6*n,n,n);
    gfx_fill_rectangle(x+3*n,y-5*n,n,n);
    gfx_fill_rectangle(x+3*n,y-4*n,n,n);
    gfx_fill_rectangle(x+3*n,y-3*n,n,n);
    gfx_fill_rectangle(x+4*n,y-3*n,n,n);
    gfx_fill_rectangle(x+1*n,y-10*n,n,n);
    gfx_fill_rectangle(x+4*n,y-10*n,n,n);
    gfx_fill_rectangle(x+2*n,y-11*n,n,n);
    gfx_fill_rectangle(x+3*n,y-11*n,n,n);
    gfx_fill_rectangle(x+3*n,y-12*n,n,n);
    gfx_fill_rectangle(x+2*n,y-12*n,n,n);
    gfx_color(spraycan[1][0],spraycan[1][1],spraycan[1][2]);
    gfx_fill_rectangle(x+1*n,y-8*n,n,n);
    gfx_fill_rectangle(x+2*n,y-8*n,n,n);
    gfx_fill_rectangle(x+3*n,y-8*n,n,n);
    gfx_fill_rectangle(x+4*n,y-8*n,n,n);
    gfx_fill_rectangle(x+1*n,y-7*n,n,n);
    gfx_fill_rectangle(x+2*n,y-7*n,n,n);
    gfx_fill_rectangle(x+1*n,y-6*n,n,n);
    gfx_fill_rectangle(x+2*n,y-6*n,n,n);
    gfx_fill_rectangle(x+1*n,y-5*n,n,n);
    gfx_fill_rectangle(x+2*n,y-5*n,n,n);
    gfx_fill_rectangle(x+1*n,y-4*n,n,n);
    gfx_fill_rectangle(x+2*n,y-4*n,n,n);
    gfx_fill_rectangle(x+1*n,y-3*n,n,n);
    gfx_fill_rectangle(x+2*n,y-3*n,n,n);
    gfx_fill_rectangle(x+1*n,y-2*n,n,n);
    gfx_fill_rectangle(x+2*n,y-2*n,n,n);
    gfx_fill_rectangle(x+3*n,y-2*n,n,n);
    gfx_fill_rectangle(x+4*n,y-2*n,n,n);
    gfx_fill_rectangle(x+2*n,y-10*n,n,n);
    gfx_fill_rectangle(x+3*n,y-10*n,n,n);
    gfx_color(spraycan[2][0],spraycan[2][1],spraycan[2][2]);
    gfx_fill_rectangle(x+4*n,y-4*n,n,n);
    gfx_fill_rectangle(x+4*n,y-5*n,n,n);
    gfx_fill_rectangle(x+4*n,y-6*n,n,n);
    gfx_fill_rectangle(x-1*n,y-12*n,n,n);
    gfx_fill_rectangle(x-3*n,y-11*n,n,n);
    gfx_fill_rectangle(x-3*n,y-13*n,n,n);
    gfx_fill_rectangle(x-5*n,y-14*n,n,n);
    gfx_fill_rectangle(x-5*n,y-12*n,n,n);
    gfx_fill_rectangle(x-5*n,y-10*n,n,n);
    
return;
}

// function that will draw the marker icon on the tool bar
void draw_marker(int x,int y,int marker[][3]){
    int n=2;
    gfx_color(marker[6][0],marker[6][1],marker[6][2]);
    gfx_fill_rectangle(x,y-21*n,n,21*n);
    gfx_fill_rectangle(x+7*n,y-21*n,n,21*n);
    gfx_fill_rectangle(x,y,8*n,n);
    gfx_fill_rectangle(x,y-2*n,7*n,n);
    gfx_fill_rectangle(x,y-6*n,7*n,n);
    gfx_fill_rectangle(x,y-16*n,7*n,n);
    gfx_fill_rectangle(x,y-20*n,7*n,n);
    gfx_fill_rectangle(x+1*n,y-22*n,6*n,n);
    gfx_fill_rectangle(x+2*n,y+2*n,4*n,n);
    gfx_fill_rectangle(x+5*n,y+3*n,n,3*n);
    gfx_fill_rectangle(x+2*n,y+3*n,n,n);
    gfx_fill_rectangle(x+3*n,y+4*n,n,n);
    gfx_fill_rectangle(x+4*n,y+5*n,n,n);
    gfx_fill_rectangle(x+1*n,y+1*n,n,n);
    gfx_fill_rectangle(x+6*n,y+1*n,n,n);
    gfx_color(marker[0][0],marker[0][1],marker[0][2]);
    gfx_fill_rectangle(x+3*n,y+3*n,n,n);
    gfx_fill_rectangle(x+1*n,y-1*n,n,n);
    gfx_fill_rectangle(x+2*n,y-1*n,n,n);
    gfx_fill_rectangle(x+1*n,y-7*n,n,n);
    gfx_fill_rectangle(x+2*n,y-7*n,n,n);
    gfx_fill_rectangle(x+1*n,y-8*n,n,n);
    gfx_fill_rectangle(x+2*n,y-8*n,n,n);
    gfx_fill_rectangle(x+1*n,y-9*n,n,n);
    gfx_fill_rectangle(x+2*n,y-9*n,n,n);
    gfx_fill_rectangle(x+1*n,y-10*n,n,n);
    gfx_fill_rectangle(x+2*n,y-10*n,n,n);
    gfx_fill_rectangle(x+1*n,y-11*n,n,n);
    gfx_fill_rectangle(x+2*n,y-11*n,n,n);
    gfx_fill_rectangle(x+1*n,y-12*n,n,n);
    gfx_fill_rectangle(x+2*n,y-12*n,n,n);
    gfx_fill_rectangle(x+1*n,y-13*n,n,n);
    gfx_fill_rectangle(x+2*n,y-13*n,n,n);
    gfx_fill_rectangle(x+1*n,y-14*n,n,n);
    gfx_fill_rectangle(x+2*n,y-14*n,n,n);
    gfx_fill_rectangle(x+1*n,y-15*n,n,n);
    gfx_fill_rectangle(x+2*n,y-15*n,n,n);
    gfx_fill_rectangle(x+1*n,y-21*n,n,n);
    gfx_fill_rectangle(x+2*n,y-21*n,n,n);

    gfx_color(marker[1][0],marker[1][1],marker[1][2]);
    gfx_fill_rectangle(x+4*n,y+3*n,n,n);
    gfx_fill_rectangle(x+4*n,y+4*n,n,n);
    gfx_fill_rectangle(x+3*n,y-1*n,n,n);
    gfx_fill_rectangle(x+4*n,y-1*n,n,n);
    gfx_fill_rectangle(x+3*n,y-7*n,n,n);
    gfx_fill_rectangle(x+4*n,y-7*n,n,n);
    gfx_fill_rectangle(x+3*n,y-8*n,n,n);
    gfx_fill_rectangle(x+4*n,y-8*n,n,n);
    gfx_fill_rectangle(x+3*n,y-9*n,n,n);
    gfx_fill_rectangle(x+4*n,y-9*n,n,n);
    gfx_fill_rectangle(x+3*n,y-10*n,n,n);
    gfx_fill_rectangle(x+4*n,y-10*n,n,n);
    gfx_fill_rectangle(x+3*n,y-11*n,n,n);
    gfx_fill_rectangle(x+4*n,y-11*n,n,n);
    gfx_fill_rectangle(x+3*n,y-12*n,n,n);
    gfx_fill_rectangle(x+4*n,y-12*n,n,n);
    gfx_fill_rectangle(x+3*n,y-13*n,n,n);
    gfx_fill_rectangle(x+4*n,y-13*n,n,n);
    gfx_fill_rectangle(x+3*n,y-14*n,n,n);
    gfx_fill_rectangle(x+4*n,y-14*n,n,n);
    gfx_fill_rectangle(x+3*n,y-15*n,n,n);
    gfx_fill_rectangle(x+4*n,y-15*n,n,n);
    gfx_fill_rectangle(x+3*n,y-21*n,n,n);
    gfx_fill_rectangle(x+4*n,y-21*n,n,n);

    gfx_color(marker[2][0],marker[2][1],marker[2][2]);
    gfx_fill_rectangle(x+5*n,y-1*n,n,n);
    gfx_fill_rectangle(x+6*n,y-1*n,n,n);
    gfx_fill_rectangle(x+5*n,y-7*n,n,n);
    gfx_fill_rectangle(x+6*n,y-7*n,n,n);
    gfx_fill_rectangle(x+5*n,y-8*n,n,n);
    gfx_fill_rectangle(x+6*n,y-8*n,n,n);
    gfx_fill_rectangle(x+5*n,y-9*n,n,n);
    gfx_fill_rectangle(x+6*n,y-9*n,n,n);
    gfx_fill_rectangle(x+5*n,y-10*n,n,n);
    gfx_fill_rectangle(x+6*n,y-10*n,n,n);
    gfx_fill_rectangle(x+5*n,y-11*n,n,n);
    gfx_fill_rectangle(x+6*n,y-11*n,n,n);
    gfx_fill_rectangle(x+5*n,y-12*n,n,n);
    gfx_fill_rectangle(x+6*n,y-12*n,n,n);
    gfx_fill_rectangle(x+5*n,y-13*n,n,n);
    gfx_fill_rectangle(x+6*n,y-13*n,n,n);
    gfx_fill_rectangle(x+5*n,y-14*n,n,n);
    gfx_fill_rectangle(x+6*n,y-14*n,n,n);
    gfx_fill_rectangle(x+5*n,y-15*n,n,n);
    gfx_fill_rectangle(x+6*n,y-15*n,n,n);
    gfx_fill_rectangle(x+5*n,y-21*n,n,n);
    gfx_fill_rectangle(x+6*n,y-21*n,n,n);
    
    gfx_color(marker[3][0],marker[3][1],marker[3][2]);

    gfx_fill_rectangle(x+1*n,y-3*n,n,n);
    gfx_fill_rectangle(x+2*n,y-3*n,n,n);
    gfx_fill_rectangle(x+1*n,y-4*n,n,n);
    gfx_fill_rectangle(x+2*n,y-4*n,n,n);
    gfx_fill_rectangle(x+1*n,y-5*n,n,n);
    gfx_fill_rectangle(x+2*n,y-5*n,n,n);
    gfx_fill_rectangle(x+1*n,y-17*n,n,n);
    gfx_fill_rectangle(x+2*n,y-17*n,n,n);
    gfx_fill_rectangle(x+1*n,y-18*n,n,n);
    gfx_fill_rectangle(x+2*n,y-18*n,n,n);
    gfx_fill_rectangle(x+1*n,y-19*n,n,n);
    gfx_fill_rectangle(x+2*n,y-19*n,n,n);
    gfx_fill_rectangle(x+5*n,y+1*n,n,n);
    gfx_fill_rectangle(x+2*n,y+1*n,n,n);
    
    gfx_color(marker[4][0],marker[4][1],marker[4][2]);

    gfx_fill_rectangle(x+3*n,y-3*n,n,n);
    gfx_fill_rectangle(x+4*n,y-3*n,n,n);
    gfx_fill_rectangle(x+3*n,y-4*n,n,n);
    gfx_fill_rectangle(x+4*n,y-4*n,n,n);
    gfx_fill_rectangle(x+3*n,y-5*n,n,n);
    gfx_fill_rectangle(x+4*n,y-5*n,n,n);
    gfx_fill_rectangle(x+3*n,y-17*n,n,n);
    gfx_fill_rectangle(x+4*n,y-17*n,n,n);
    gfx_fill_rectangle(x+3*n,y-18*n,n,n);
    gfx_fill_rectangle(x+4*n,y-18*n,n,n);
    gfx_fill_rectangle(x+3*n,y-19*n,n,n);
    gfx_fill_rectangle(x+4*n,y-19*n,n,n);



return;
}

// function that will draw the rectangle icon on the tool bar
void draw_rectangle(int x, int y){
    int n=3;
    gfx_color(0,0,0);
    gfx_fill_rectangle(x,y-1*n,n,2*n);
    gfx_fill_rectangle(x,y-4*n,n,2*n);
    gfx_fill_rectangle(x,y-7*n,n,2*n);
    gfx_fill_rectangle(x,y-10*n,n,2*n);
    gfx_fill_rectangle(x+11*n,y-1*n,n,2*n);
    gfx_fill_rectangle(x+11*n,y-4*n,n,2*n);
    gfx_fill_rectangle(x+11*n,y-7*n,n,2*n);
    gfx_fill_rectangle(x+11*n,y-10*n,n,2*n);
    gfx_fill_rectangle(x+2*n,y,2*n,n);
    gfx_fill_rectangle(x+5*n,y,2*n,n);
    gfx_fill_rectangle(x+8*n,y,2*n,n);
    gfx_fill_rectangle(x+2*n,y-10*n,2*n,n);
    gfx_fill_rectangle(x+5*n,y-10*n,2*n,n);
    gfx_fill_rectangle(x+8*n,y-10*n,2*n,n);
    
    

return;
}

// function that will draw the clear icon on the tool bar
void draw_clear(int x, int y){
    int n=3;
    gfx_color(0,0,0);
    gfx_fill_rectangle(x+2*n,y,3*n,n);
    gfx_fill_rectangle(x+n,y-1*n,n,n);
    gfx_fill_rectangle(x,y-5*n,n,4*n);
    gfx_fill_rectangle(x+n,y-n,n,n);
    gfx_fill_rectangle(x+2*n,y-7*n,3*n,n);
    gfx_fill_rectangle(x+6*n,y-6*n,n,6*n);
    gfx_fill_rectangle(x+6*n,y,3*n,n);
    gfx_fill_rectangle(x+n,y-6*n,n,n);
    gfx_fill_rectangle(x+10*n,y-6*n,n,7*n);
    gfx_fill_rectangle(x+10*n,y,4*n,n);
    gfx_fill_rectangle(x+11*n,y-3*n,2*n,n);
    gfx_fill_rectangle(x+11*n,y-6*n,3*n,n);
    gfx_fill_rectangle(x+15*n,y-3*n,n,4*n);
    gfx_fill_rectangle(x+19*n,y-3*n,n,4*n);
    gfx_fill_rectangle(x+16*n,y-5*n,n,2*n);
    gfx_fill_rectangle(x+18*n,y-5*n,n,2*n);
    gfx_fill_rectangle(x+17*n,y-6*n,n,n);
    gfx_fill_rectangle(x+16*n,y-3*n,3*n,n);
    gfx_fill_rectangle(x+21*n,y-5*n,n,6*n);
    gfx_fill_rectangle(x+25*n,y-1*n,n,2*n);
    gfx_fill_rectangle(x+24*n,y-2*n,n,n);
    gfx_fill_rectangle(x+24*n,y-5*n,n,2*n);
    gfx_fill_rectangle(x+22*n,y-3*n,2*n,n);
    gfx_fill_rectangle(x+22*n,y-6*n,2*n,n);
return;
}

// function that will draw the eraser icon on the tool bar
void draw_eraser(int x,int y,int eraser[][3]){
    int n=3;
    gfx_color(eraser[0][0],eraser[0][1],eraser[0][2]);
    gfx_fill_rectangle(x,y-1*n,n,2*n);
    gfx_fill_rectangle(x+1*n,y-3*n,n,2*n);
    gfx_fill_rectangle(x+1*n,y+1*n,2*n,n);
    gfx_fill_rectangle(x+3*n,y+2*n,2*n,n);
    gfx_fill_rectangle(x+5*n,y+3*n,2*n,n);
    gfx_fill_rectangle(x+6*n,y+2*n,2*n,n);
    gfx_fill_rectangle(x+7*n,y-1*n,n,3*n);
    gfx_fill_rectangle(x+5*n,y-2*n,2*n,n);
    gfx_fill_rectangle(x+3*n,y-3*n,2*n,n);
    
    gfx_color(eraser[1][0],eraser[1][1],eraser[1][2]);
    gfx_fill_rectangle(x+2*n,y-4*n,n,n);
    gfx_fill_rectangle(x+3*n,y-5*n,n,n);
    gfx_fill_rectangle(x+4*n,y-6*n,n,n);
    gfx_fill_rectangle(x+5*n,y-7*n,n,n);
    gfx_fill_rectangle(x+6*n,y-8*n,n,n);
    gfx_fill_rectangle(x+7*n,y-9*n,n,n);

    gfx_fill_rectangle(x+7*n,y-9*n,7*n,n);
    gfx_fill_rectangle(x+11*n,y-9*n,4*n,n);
    gfx_fill_rectangle(x+14*n,y-9*n,n,n);
    
    gfx_fill_rectangle(x+8*n,y-2*n,n,n);
    gfx_fill_rectangle(x+9*n,y-3*n,n,n);
    gfx_fill_rectangle(x+10*n,y-4*n,n,n);
    gfx_fill_rectangle(x+11*n,y-5*n,n,n);
    gfx_fill_rectangle(x+12*n,y-6*n,n,n);
    gfx_fill_rectangle(x+13*n,y-7*n,n,n);
    gfx_fill_rectangle(x+14*n,y-8*n,n,n);

    gfx_fill_rectangle(x+8*n,y+1*n,n,n);
    gfx_fill_rectangle(x+9*n,y,n,n);
    gfx_fill_rectangle(x+10*n,y-1*n,n,n);
    gfx_fill_rectangle(x+11*n,y-2*n,n,n);
    gfx_fill_rectangle(x+12*n,y-3*n,n,n);
    gfx_fill_rectangle(x+13*n,y-4*n,n,n);
    gfx_fill_rectangle(x+14*n,y-5*n,n,n);   
    
    gfx_color(eraser[2][0],eraser[2][1],eraser[2][2]);
    
    gfx_fill_rectangle(x+2*n,y-3*n,n,n);
    gfx_fill_rectangle(x+2*n,y-2*n,3*n,n);
    gfx_fill_rectangle(x+1*n,y-1*n,6*n,n);
    gfx_fill_rectangle(x+1*n,y,6*n,n);
    gfx_fill_rectangle(x+3*n,y+1*n,4*n,n);
    gfx_fill_rectangle(x+5*n,y+2*n,n,n);
    

    gfx_color(eraser[3][0],eraser[3][1],eraser[3][2]);

    gfx_fill_rectangle(x+7*n,y-8*n,7*n,n);
    gfx_fill_rectangle(x+6*n,y-7*n,7*n,n);
    gfx_fill_rectangle(x+5*n,y-6*n,7*n,n);
    gfx_fill_rectangle(x+4*n,y-5*n,7*n,n);
    gfx_fill_rectangle(x+3*n,y-4*n,7*n,n);
    gfx_fill_rectangle(x+5*n,y-3*n,4*n,n);
    gfx_fill_rectangle(x+7*n,y-2*n,n,n);

    
    gfx_color(eraser[4][0],eraser[4][1],eraser[4][4]);
    gfx_fill_rectangle(x+8*n,y-1*n,n,2*n);
    gfx_fill_rectangle(x+9*n,y-2*n,n,2*n);
    gfx_fill_rectangle(x+10*n,y-3*n,n,2*n);
    gfx_fill_rectangle(x+11*n,y-4*n,n,2*n);
    gfx_fill_rectangle(x+12*n,y-5*n,n,2*n);
    gfx_fill_rectangle(x+13*n,y-6*n,n,2*n);
    gfx_fill_rectangle(x+14*n,y-7*n,n,2*n);
return;
}

