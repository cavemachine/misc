#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

int main() {
  
  std::cout << "basic Fltk + CMake" << std::endl;
  
  Fl_Double_Window* window = new Fl_Double_Window(400,600, "main window");
  window->end();
  window->show();
  
  return Fl::run();
  
  
}
