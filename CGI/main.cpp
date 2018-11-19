#include "htmlpage.h"
#include "fileaccess.h"

using namespace std;
using namespace cgicc;



int main()
{
    fileaccess* file;
    try{

        Cgicc formData;

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

        if(formData.getEnvironment().getRequestMethod() == "POST"){
            //SETTINGS ELLER MANUAL CONTROL CHANGE
        }
        else{
            new htmlpage(file);
        }
        //Static setup af hjemmesiden


        //Der skal her anvendes en double pointer(**) fordi at vi anvender formData pointeren til at gemme adressen
        //af den element/variabel som blevet valgt og derefter lagre chooseMode adressen på formData pointeren. Når vi
        //anvender en dereference når der skal printes, fåes værdien af den variabel som formData pointeren peger på.
        //Dette gentages i de fleste metoder.
        /*
        form_iterator chooseMode = formData.getElement("manualDropDown");
        if(!chooseMode->isEmpty() && chooseMode != (*formData).end()){
            cout<< "mode chosen: "<< **chooseMode <<endl;
            cout<< "Save your mode by pushing the 'save' button"<<endl;
            return **chooseMode;
        }

        //save move - mangler at angive en form name i HTML koden (skal være saveMode)...
        form_iterator saveMode = formData.getElement("saveMode");
        if(!saveMode->isEmpty() && saveMode != (*formData).end()){
            cout<< "mode saved"<<endl;
            return **saveMode;
        }

        //autowater
        form_iterator autoWater = formData.getElement("autoWater");
        if(!autoWater->isEmpty() && autoWater != (*formData).end()){
            cout<< "automatic water mode changed to: "<<**autoWater<<endl;
            return **autoWater;
        }

        //Mangler nok en anden implementation af logger

       cout<<"<log>"<<endl;
       cout<<"</log>"<<endl;

        */
    }
    catch(exception &e) {
        cout <<"error exception thrown: " << e.what() <<endl;
    }

return 0; //ellers giver apache vidst errors (ved ikke hvorfor... Endnu)

}
