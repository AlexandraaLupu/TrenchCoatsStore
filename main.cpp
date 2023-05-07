#include "QtWidgetsApplication.h"
#include <QtWidgets/QApplication>
#include "Validator/Validator.h"
#include "Repository/Repository.h"
#include "Service/Service.h"
#include "Service/UserService.h"
#include "GUI/GUI.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //QtWidgetsApplication w;
    //w.show();
    string filename = "trenchcoats.txt";
    TrenchCoatValidator tValidator;
    Repository repo{ filename };
    UserRepository userRepo;
    Service service{ repo, tValidator };
    UserService userService{ repo, userRepo };
    GUI gui(service, userService);
    gui.resize(800, 600);
    gui.show();
    return a.exec();
}
