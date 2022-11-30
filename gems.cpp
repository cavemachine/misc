#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <cstdlib>
#include <iostream>

#define BORDER 20
#define WIDTH 500
#define HEIGHT 500

class Canvas;
Canvas* mainCanvas;
Fl_Double_Window* mainWindow;

// ****************************************************************************

class Bouncing : Fl_Widget {
public:
  int tmpInc;
  int step;
  int bColor;
  int posX, posY, sizeW, sizeH;
  bool goingUp, goingLeft;
  Bouncing(int X, int Y, int W, int H, bool g_Up, bool g_Left)
      : Fl_Widget(X, Y, W, H) {
    posX = X;
    posY = Y;
    sizeW = W;
    sizeH = H;
    goingUp = g_Up;
    goingLeft = g_Left;
    bColor = rand() % 12;
    step = 1 + (rand() % 5);
    tmpInc = 0;
  }
  void changePos() {
    if (goingUp == true) {
      posY = posY - step;
      if (posY <= BORDER) {
        goingUp = false;
      }
    } else {
      posY = posY + step;
      if (posY >= HEIGHT - BORDER - sizeH) {
        goingUp = true;
      }
    }

    if (goingLeft == true) {
      posX = posX - step;
      if (posX <= BORDER) {
        goingLeft = false;
      }
    } else {
      posX = posX + step;
      if (posX >= WIDTH - BORDER - sizeW) {
        goingLeft = true;
      }
    }
  }

  void draw() {
    fl_color(bColor);
    // fl_circle(posX, posY, sizeW);
    fl_rectf(posX, posY, sizeW, sizeH);
    this->x(posX);
    this->y(posY);
  }

  int handle(int ev) {
    switch (ev) {
      case FL_ENTER:
        std::cout << "ENTER:" << tmpInc << std::endl;
        return (1);
        break;
      case FL_MOVE:
        tmpInc++;
        std::cout << "MOVING:" << tmpInc << std::endl;
        Fl::delete_widget(this);
        return (1);
        break;
    }
    return (Fl_Widget::handle(ev));
  }
};

//********************** -- CANVAS -- ***********************

class Canvas : Fl_Group {
public:
  bool first_bounce;
  Bouncing* tmpBounce;
  Canvas()
      : Fl_Group(BORDER, BORDER, WIDTH - (2 * BORDER), HEIGHT - (2 * BORDER)) {
    this->box(FL_UP_BOX);
    this->color(FL_DARK_GREEN);
    first_bounce = true;
  }

  void createBounce() {
    int tmpX, tmpY;
    int tmpW, tmpH;
    tmpW = 20 + (rand() % 20);
    tmpH = 20 + (rand() % 20);
    tmpX = rand() % (WIDTH - BORDER - tmpW);
    if (tmpX < 20) {
      tmpX = tmpX + 20;
    }
    tmpY = rand() % (HEIGHT - BORDER - tmpH);
    if (tmpY < 20) {
      tmpY = tmpY + 20;
    }
    Bouncing* myBounce = new Bouncing(tmpX, tmpY, tmpW, tmpH, rand() % 2, rand() % 2);
    this->add((Fl_Widget*)myBounce);
    this->redraw();
  }

  void moveBounce() {
    if (first_bounce) {
      createBounce();
      createBounce();
      first_bounce = false;
    }
    for (int i = 0; i < this->children(); i++) {
      tmpBounce = (Bouncing*)this->child(i);
      if (Fl::event_inside((Fl_Widget*)tmpBounce)) {
        Fl::delete_widget((Fl_Widget*)tmpBounce);
      } else {
        tmpBounce->changePos();
      }
    }
    this->redraw();
  }

  int handle(int ev) {
    switch (ev) {
      case FL_FOCUS:
      case FL_UNFOCUS:
        return (1);
        break;
      case FL_KEYDOWN:
        if (Fl::event_key() == 97) {
          createBounce();
          std::cout << "Letter A" << std::endl;
        }
        if (Fl::event_key() == 98) {
          moveBounce();
        }
        break;
    }

    return (Fl_Group::handle(ev));
  }
};

//******************** -- MAIN -- ***********************

void timer_CB(void*) {
  mainCanvas->moveBounce();
  Fl::repeat_timeout(0.5, timer_CB);
}

int main() {
  srand((unsigned)time(NULL));

  mainWindow = new Fl_Double_Window(500, 500, "main window");
  mainCanvas = new Canvas();

  mainWindow->add((Fl_Widget*)mainCanvas);
  mainWindow->show();

  Fl::add_timeout(0.5, timer_CB);
  return Fl::run();
}
