#include "htmlpage.h"
#include "fileaccess.h"
#include "postrequest.h"

using namespace std;
using namespace cgicc;



int main()
{
    fileaccess* file;
    try{

        Cgicc cgiccreq;

        //get path of folder with queue and setting files
        ifstream pathsettings;
        pathsettings.open("path.txt");
        if(pathsettings.is_open()){
            string line;
            getline(pathsettings,line);
            file = new fileaccess(line);
        }
        else{
            file = new fileaccess("/opt/pigeon/");
        }

        if(cgiccreq.getEnvironment().getRequestMethod() == "POST"){
            //SETTINGS ELLER MANUAL CONTROL CHANGE
            new postrequest(&cgiccreq, file);
        }
        else{
            new htmlpage(file);
        }
    }
    catch(exception &e) {
        cout <<"error exception thrown: " << e.what() <<endl;
    }

return 0; //ellers giver apache vidst errors (ved ikke hvorfor... Endnu)

}
