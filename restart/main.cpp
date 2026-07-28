#include "qt.h" //im gonna cry my includepath is right my cmake config is right please work

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  qtWindow window;
  window.show();

  return app.exec();
}
//67
//the 67 wards away my past compilation errors
//it is not working bruh


//old code
  //while (1) {
 //imshow("Camera", frame); //lets see the final product //lets NOT actually
  //if (waitKey(30) == 27) //esc key to exit
  //  break;
  //}