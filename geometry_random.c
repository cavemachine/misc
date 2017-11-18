#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define OFFSET_Y 400
     
SDL_Surface *screen;
double x_1;
double y_1;
double x_2;
double y_2;

void put_pixel(int x, int y);
void free_fall(int acc, int period);
double radians(double deg);
void draw_line(double x1, double y1, double x2, double y2);
int draw_parabolic(int x, int a, int b, int c, bool normal_direction, int offset_x);
void draw_triangle(double x1, double y1, double x2, double y2, double x3, double y3);
void draw_circle_point(double x1, double y1, double x2, double y2,
		       double length, double deg, int times);
void draw_polygon (double x_poly, double y_poly, double length_poly,
		   double rotation_deg, int sizes);
void test_polygon();
void test_circle();
void test_parabolic();
void test_triangle();
void initialize_win();


//--------------------------------

void put_pixel(int x, int y) {
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
    *(Uint32 *)p = SDL_MapRGB(screen->format, 120, 120, 150);
}

void free_fall(int acc, int period) {
    int S = 1;
    
    for (int per = 0; per < period; per++) {
	S = S + (acc * per);	
	if (S < 400) {
	    put_pixel(100 , 400 + S);
	}
	SDL_Delay(40);
	SDL_Flip(screen);
    }
}

double radians(double deg) {
    double rad_return = (deg * 3.14)/180;
    return (rad_return);
}

void draw_line(double x1, double y1, double x2, double y2) {

    put_pixel(x1,y1);
    put_pixel(x2,y2);
    
    double m;
    double x;
    double y;

    m = (y2-y1)/(x2-x1);

    if (abs (x1-x2) > abs(y1-y2)) {
	if (x1 < x2) {
	    for (x = x1; x <= x2; x++) {
		y = m*(x-x1) + y1;
		put_pixel(x,y);
	    }
	}

	if (x1 > x2) {
	    for (x = x2; x <= x1; x++) {
		y = m*(x-x1) + y1;
		put_pixel(x,y);
	    }
	}
    }
    else {
	if (y1 < y2) {
	    for (y = y1; y <= y2; y++) {
		x = (y - y1)/m + x1;
		put_pixel(x,y);
	    }
	}

	if (y1 > y2) {
	    for (y = y2; y <= y1; y++) {
		x = (y - y1)/m + x1;
		put_pixel(x,y);
	    }
	}
	
    }
}    

int draw_parabolic(int x, int a, int b, int c, bool normal_direction, int offset_x) {
    int y;
    int y_prev;
    int x_prev;
    int x_expand = 10;
    int offset = 400;
    
    x_prev = x - 1;
    
    y = a*(x*x) + b*x + c;
    y_prev = a*(x_prev*x_prev) + b*x_prev + c;

    SDL_FillRect(screen,NULL,0);
    draw_polygon(x*x_expand+offset+offset_x, y+offset, 20, 0, 6);

    /*
    if (normal_direction) {
	draw_line(offset + x_prev*x_expand + offset_x,
		  offset + y_prev,
		  offset + x*x_expand + offset_x,
		  offset + y);
    } else {
	draw_line(offset - x_prev*x_expand + offset_x + x_expand,
		  offset + y_prev,
		  offset - x*x_expand + offset_x + x_expand,
		  offset + y);
    }
    */
    
    SDL_Delay(50);
    SDL_Flip(screen);

    return(x*x_expand);  
}

void draw_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    draw_line(x1,y1, x2,y2);
    draw_line(x1,y1, x3,y3);
    draw_line(x3,y3, x2,y2);
}

void draw_circle_point(double x1, double y1, double x2,
		       double y2, double length, double deg, int times) {
    int new_x;
    int new_y;
    double actual_deg = 0;
    
    while (times >= -357) {
	new_x = x1 + (length * cos(radians(actual_deg)));
	new_y = y1 + (length * sin(radians(actual_deg)));
	put_pixel(new_x,new_y);
	actual_deg = actual_deg - deg;
	times--;
	SDL_Delay(1);
	SDL_Flip(screen);
    }
}

void draw_polygon (double x_poly, double y_poly, double length_poly,
		   double rotation_deg, int sizes) {
    
    double deg_poly = (360/sizes) + rotation_deg;
    double new_x;                                                                          
    double new_y;                                                                          
    double old_x;                                                                          
    double old_y;


    old_x = x_poly + (length_poly * cos( radians(deg_poly)));
    old_y = y_poly + (length_poly * sin( radians(deg_poly)));

    for (int faces = sizes; faces > 0; faces--) {

	deg_poly = deg_poly + (360/sizes);
	
	new_x = x_poly + (length_poly * cos( radians(deg_poly)));
	new_y = y_poly + (length_poly * sin( radians(deg_poly)));
	
	draw_line(old_x, old_y, new_x, new_y);
	old_x = new_x;
	old_y = new_y;
    }
    SDL_Flip(screen);
}

void test_polygon() {
    for (int j = 0; j < 100; j++) {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	draw_polygon(x_1, y_1, 80+j, j, 5);
	draw_polygon(x_1, y_1, 200-j, -j, 6);	
	SDL_Delay(1);
    }
}

void test_circle() {
    double length_line;
    double deg = 1;
    int times = 3;
    length_line = sqrt( pow((x_2 - x_1),2) + pow((y_2 - y_1),2) ); //hipotenusa
    draw_circle_point(x_1, y_1, x_2, y_2, length_line, deg, times);
}

void test_parabolic() {
    int a = 1;                                                                            
    int b = -30;                                                                           
    int c = 0;
    int last_x;
    
    for (int pb = 2; pb < 30; pb++) {                                                      
        last_x = draw_parabolic(pb,a,b,c,true,0);     
    }
    for (int pb = 2; pb < 20; pb++) {                                                      
        draw_parabolic(pb,a,b+10,c,true,last_x);     
    }
    
    
    /* 
       printf("\n");
       int xv = - (b/(2*a));
       int yv = - (((b*b) - 4*a*c)/4*a);
       printf("Xv: %i\n", xv);
       printf("Yv: %i\n", yv);
    */
}

void test_triangle() {
    double x_3 = 490;
    double y_3 = 320;
    for (int i = 0; i < 80; i++) {
	draw_triangle(x_1+400, y_1, x_2+400, y_2, x_3+400, y_3);
	x_1 += 1;
	y_1 += 5;
	x_2 -= 5;
	y_2 -= 5;
	SDL_Delay(50);
	SDL_Flip(screen);
    }
}

void initialize_win() {   
    x_1 = 300;
    y_1 = 300;
    x_2 = 420;
    y_2 = 430;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode( 1024, 768, 16, SDL_SWSURFACE|SDL_ANYFORMAT);
}

int main () {
    initialize_win();

    //-------------------
    
    //test_polygon();
    //test_circle();
    test_parabolic();
    //test_triangle();

    //-------------------

    SDL_Flip(screen);
    SDL_Delay(4000);
    SDL_Quit();
    exit(0);
    
}
