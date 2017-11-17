#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>

#define OFFSET_Y 400

SDL_Surface *screen;

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

void func_parabolic(int x, int a, int b, int c) {
    int y;
    y = a*(x*x) + b*x + c;
    put_pixel(300 + x, 300 + y);
    printf(" [%i,%i] ", x, y); 
    SDL_Delay(50);
    SDL_Flip(screen);
}

void draw_parabolic() {
    int a = 1;                                                                             
    int b = -30;                                                                           
    int c = 0;                                                                          
    for (int pb = 1; pb < 30; pb++) {                                                      
        func_parabolic(pb,a,b,c);                                                          
    }          
    printf("\n");
    int xv = - (b/(2*a));
    int yv = - (((b*b) - 4*a*c)/4*a);
    printf("Xv: %i\n", xv);
    printf("Yv: %i\n", yv);
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

void draw_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    draw_line(x1,y1, x2,y2);
    draw_line(x1,y1, x3,y3);
    draw_line(x3,y3, x2,y2);
}

double rad(double deg) {
    double rad_return = (deg * 3.14)/180;
    return (rad_return);
}

void draw_circle_point(double x1, double y1, double x2,
		       double y2, double length, double deg, int times) {
    int new_x;
    int new_y;
    double actual_deg = 0;
    
    while (times >= -357) {
	new_x = x1 + (length * cos(rad(actual_deg)));
	new_y = y1 + (length * sin(rad(actual_deg)));
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


    old_x = x_poly + (length_poly * cos( rad(deg_poly)));
    old_y = y_poly + (length_poly * sin( rad(deg_poly)));

    for (int faces = sizes; faces > 0; faces--) {

	deg_poly = deg_poly + (360/sizes);
	
	new_x = x_poly + (length_poly * cos( rad(deg_poly)));
	new_y = y_poly + (length_poly * sin( rad(deg_poly)));
	
	draw_line(old_x, old_y, new_x, new_y);
	old_x = new_x;
	old_y = new_y;
    }
    SDL_Flip(screen);
}

int main () {

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode( 1024, 768, 16, SDL_SWSURFACE|SDL_ANYFORMAT);

     
    double x1 = 300;
    double y1 = 300;
    double x2 = 420;
    double y2 = 430;
   
    /*printf("[cateto1: %f ] ", x2-x1);
    printf("[cateto2: %f ] ", y2-y1);
    printf("[hipotenusa: %f ]\n",length_line);
    */
 
    for (int j = 0; j < 80; j++) {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	draw_polygon(x1, y1, 80, j, 5);
	draw_polygon(x1, y1, 70, -j, 5);	
	SDL_Delay(10);
    }

    double length_line;
    double deg = 1;
    int times = 3;
    length_line = sqrt( pow((x2 - x1),2) + pow((y2 - y1),2) ); //hipotenusa
    draw_circle_point(x1, y1, x2, y2, length_line, deg, times);

    draw_parabolic();

    double x3 = 490;
    double y3 = 320;
    for (int i = 0; i < 80; i++) {
	draw_triangle(x1+400, y1, x2+400, y2, x3+400, y3);
	x1 += 2;
	y1 += 5;
	x2 -= 5;
	y2 -= 5;
	SDL_Delay(50);
	SDL_Flip(screen);
    }
    
    SDL_Flip(screen);
    SDL_Delay(4000);
    SDL_Quit();
    exit(0);
    
}
