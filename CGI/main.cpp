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
        //check if file is open
        if(pathsettings.is_open()){
            string line;
            getline(pathsettings,line);
            file = new fileaccess(line);
        }
        //if file doesnt open use standard path
        else{
            ofstream pathsettings;
            pathsettings.open("path.txt", ios::trunc);
            pathsettings << "/opt/pigeon/";
            file = new fileaccess("/opt/pigeon/");
        }
        //check if webrequest is a POST request
        if(cgiccreq.getEnvironment().getRequestMethod() == "POST"){
            postrequest request(&cgiccreq, file);
        }
        //if not load website
        else{
            htmlpage page(file);
        }
    }
    catch(exception &e) {
        cout << HTTPHTMLHeader() << endl;
        cout <<"error exception thrown: " << e.what() <<endl;
    }
    delete file;
    return 0; //ellers giver apache vidst errors (ved ikke hvorfor... Endnu)

}
