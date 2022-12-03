#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <cstdlib>
#include <iostream>

#define PI 3.14159

class Bullet;
class Ship;
class Win;
Ship* mainShip;
Bullet* mainBullet;
Win* mainWindow;

class Ship : Fl_Widget {
public:
  int posX, posY, sizeW, sizeH;
  Ship(int X, int Y, int W, int H)
      : Fl_Widget(X, Y, W, H) {
    posX = X;
    posY = Y;
    sizeW = W;
    sizeH = H;
  }
  void draw() {
    fl_color(FL_RED);
    fl_rectf(posX, posY, sizeW, sizeH);
  }
};

class Bullet : Fl_Widget {
public:
  int b_color;
  int b_speed;
  int posX, posY, sizeW, sizeH;
  float fposX, fposY;

  Bullet(int X, int Y, int W, int H)
      : Fl_Widget(X, Y, W, H) {
    posX = X;
    posY = Y;
    sizeW = W;
    sizeH = H;
    fposX = posX;
    fposY = posY;
    b_speed = 1 + rand() % 7;
    b_color = 1 + rand() % 17;
  }

  void findSinCos(int mouseX, int mouseY) {
    if ((abs(mouseX - posX) <= 2) && (abs(mouseY - posY) <= 2)) {
      // Fl::delete_widget(this);
      return;
    }
    int difX, difY;
    int directionX, directionY;
    float tang, rad, degree;
    difX = abs(mouseX - posX);
    difY = abs(mouseY - posY);
    // std::cout << "difX: " << difX << std::endl;
    // std::cout << "difY: " << difY << std::endl;
    tang = (float)difY / difX;
    // std::cout << "tang: " << tang << std::endl;
    rad = atan(tang);
    // std::cout << "tang radian: " << rad << std::endl;
    degree = rad * 180 / PI;
    // std::cout << "degree: " << degree << std::endl;
    if (mouseX > posX)
      directionX = 1;
    if (mouseX < posX)
      directionX = -1;
    if (mouseY > posY)
      directionY = 1;
    if (mouseY < posY)
      directionY = -1;

    fposX = fposX + b_speed * cos(rad) * directionX;
    fposY = fposY + b_speed * sin(rad) * directionY;
    posX = int(fposX);
    posY = int(fposY);
  }

  void draw() {
    this->position(posX, posY);
    fl_color(b_color);
    fl_rectf(posX, posY, sizeW, sizeH);
    if (Fl::event_inside(this)) {
      Fl::delete_widget(this);
    }
  }

  int handle(int ev) {
    switch (ev) {
      case FL_ENTER:
        std::cout << "ENTER" << std::endl;
        Fl::delete_widget(this);
        return (1);
    }
    return (Fl_Widget::handle(ev));
  }
};

class Win : Fl_Double_Window {
public:
  Bullet* tmpBullet;

  Win(int W, int H)
      : Fl_Double_Window(W, H) {
    this->show();
  }
  void addChild(Fl_Widget* c) {
    this->add(c);
  }
  int getChildren() {
    return this->children();
  }
  void doRedraw() {
    this->redraw();
  }
  void processChild(int c, int mouseX, int mouseY) {
    tmpBullet = (Bullet*)this->child(c);
    tmpBullet->findSinCos(mouseX, mouseY);
  }

  int handle(int ev) {
    switch (ev) {
      case FL_FOCUS:
        // case FL_UNFOCUS:
        std::cout << "sdio" << std::endl;
        return (1);
        break;
      case FL_KEYDOWN:
        if (Fl::event_key() == 97) {
          mainShip->posX = mainShip->posX - 5;
          this->redraw();
          return (1);
          break;
        }
        if (Fl::event_key() == 98) {
          mainShip->posX = mainShip->posX + 5;
          this->redraw();
          return (1);
          break;
        }
        if (Fl::event_key() == 99) {
          tmpBullet = new Bullet(mainShip->posX, mainShip->posY - 20, 5 + rand() % 25, 5 + rand() % 25);
          this->addChild((Fl_Widget*)tmpBullet);
          return (1);
          break;
        }
    }
    return (Fl_Double_Window::handle(ev));
  }
};

void timer_CB(void*) {
  static int child_inc;
  int mouseX, mouseY;
  mouseX = Fl::event_x();
  mouseY = Fl::event_y();
  for (int i = 1; i < mainWindow->getChildren(); i++) {
    mainWindow->processChild(i, mouseX, mouseY);
  }
  child_inc++;
  if (child_inc == 10) {
    std::cout << "children:" << mainWindow->getChildren() << std::endl;
    child_inc = 0;
  }
  mainWindow->doRedraw();
  Fl::repeat_timeout(0.1, timer_CB);
}

int main() {
  srand((unsigned)time(NULL));
  mainWindow = new Win(500, 500);
  mainShip = new Ship(250, 400, 30, 30);
  mainWindow->addChild((Fl_Widget*)mainShip);

  Fl::add_timeout(2, timer_CB);
  std::cout << "hello" << std::endl;
  return Fl::run();
}
