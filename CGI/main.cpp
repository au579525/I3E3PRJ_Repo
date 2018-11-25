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

        file = new fileaccess;
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
