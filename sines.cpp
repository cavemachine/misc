#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <iostream>
#include <FL/names.h>

class Canvas;
class Balls;
Canvas* canvas_1;
Fl_Double_Window* window;


#define WEIGHT 500
#define HEIGHT 500
#define BORDER 20

//************************* -- BALLS -- **************************
static int j = 0;

class Balls : Fl_Widget {
public:
  int ball_inc;
  int posX, posY, sizeW, sizeH;
  Balls(int X, int Y, int W, int H)
      : Fl_Widget(X, Y, W, H) {
    posX = X;
    posY = Y;
    sizeW = W;
    sizeH = H;
    ball_inc = 0;
  }
  void doDraw() {
    this->redraw();
  }
  
  int handle(int ev) {
    if (ev == FL_ENTER) {
      std::cout << "ENTROU" << std::endl;
      return(1);
    }
    if (ev == FL_MOVE) {
      std::cout << "MOVE" << std::endl;
      return(1);
    }

    fprintf(stderr, "EVENT canvas: %s(%d)\n", fl_eventnames[ev], ev);
    return(0);
  }
  
private:
  void draw() {
    posX = this->x();
    posY = this->y();
    fl_color(FL_RED);
    fl_rectf(posX, posY, sizeW, sizeH);
  }
};

//************************* - CANVAS - ***************************

class Canvas : Fl_Group {
public:
  int draw_inc;
  int enter_inc;
  void PaintShapes();
  Canvas()
      : Fl_Group(BORDER, BORDER, WEIGHT - (2 * BORDER), HEIGHT - (2 * BORDER)) {
    this->box(FL_UP_BOX);
    posY = HEIGHT / 2;
    posX = 0;
    draw_inc = 0;
    enter_inc = 0;
    Balls* myball = new Balls(40, 60 + j, 60, 30);
    j += 40;
    this->add((Fl_Widget*)myball);

    // this->add((Fl_Widget*)mybutton);
    // this->redraw();
  }
  bool first_t = true;
  float posX;
  int posY, Ysine;

  int handle(int e) ;

private:
  int j = 0;
  void draw();
};

//****** CANVAS ----> HANDLE() ******

int Canvas::handle(int ev) {
  static int posX;
  switch (ev) {
    case FL_FOCUS:
    case FL_UNFOCUS:
      return (1);
      break;
  }

  // fprintf(stderr, "EVENT canvas: %s(%d)\n", fl_eventnames[ev], ev);

  if (ev == FL_ENTER) {
    enter_inc++;
    std::cout << "enter: " << enter_inc << std::endl;
    return (1);
  }
  // if (ev == FL_MOVE) {
  //   enter_inc++;
  //   std::cout << "MOVE: " << enter_inc << std::endl;
  //   return (1);
  // }

  // if (ev == FL_PUSH) {
  //   enter_inc++;
  //   std::cout << "CLICK: " << enter_inc << Fl::belowmouse() << std::endl;
  //   return(1);
  // }

  if (ev == FL_KEYDOWN) {
    if (Fl::event_key() == 97) {
      Balls* myball = new Balls(40, 60 + j, 60, 30);
      // Fl_Button* mybutton = new Fl_Button(40, 60 + j, 60, 30, "OI");
      j += 40;
      this->add((Fl_Widget*)myball);

      //this->add((Fl_Widget*)mybutton);
      this->redraw();
      // Balls* myball = new Balls(70,40+j,20,20);
      // myball->doDraw();
    }
    if (Fl::event_key() == 98) {
      this->posX += 0.1;
      this->PaintShapes();
    }
    if (Fl::event_key() == 99) {
      delete this->child(this->children() - 1);
      this->redraw();
    }
    if (Fl::event_key() == 100) {
      //Fl_Widget* tmpBall = this->child(1);
      //Balls* newBall = (Balls*)this->child(1);
      this->child(1)->position(this->child(1)->x() + 20, this->child(1)->y());
      //newBall->posX = newBall->posX + 20;
      // this->child(1)->position( this->child(1)->x() + 20 , 130);
      this->redraw();
    }
  }
  return (Fl_Group::handle(ev));
}

//****** CANVAS ----> DRAW() ******

void Canvas::PaintShapes() {
  // Ysine = 200 + sin(posX) * 100;
  // fl_color(FL_BLACK);
  // fl_circle(posX * 7, Ysine, 10);

  // fl_push_clip(100, 100, 20, 20);
  fl_color(FL_RED);
  fl_rectf(100, 100, 70, 70);
  // fl_pop_clip();
}

void Canvas::draw() {
  if (first_t == true) {
    first_t = false;
  }
  this->draw_box(FL_UP_BOX, FL_DARK_GREEN);

  // fl_color(FL_BLACK);
  // Ysine = 200 + sin(posX) * 100;
  // fl_circle(posX * 7, Ysine, 10);
  this->draw_children();
  // this->redraw();
  // this->parent()->redraw();
  // window()->redraw();
  draw_inc++;
  std::cout << "draw: " << draw_inc << std::endl;
}

//**************************** -- MAIN -- *******************************

int main() {
  std::cout << "running" << std::endl;

  window = new Fl_Double_Window(WEIGHT, HEIGHT, "Window");
  canvas_1 = new Canvas();

  window->add((Fl_Widget*)canvas_1);
  window->show();

  return Fl::run();
}
