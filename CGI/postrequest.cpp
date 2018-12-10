#include "postrequest.h"

postrequest::postrequest(Cgicc *data, fileaccess *_file)
{
    file = _file;
    string datastring = data->getEnvironment().getPostData();
    //check type of POST request
    //check if request is systemmode
    std::size_t found=datastring.find("sysmode");
    if (found!=std::string::npos){
        sysmode(datastring);
        return;
    }
    //check if request is watermode
    found=datastring.find("watermode");
    if (found!=std::string::npos){
        watermode(datastring);
        return;
    }
    //check if request is manual control
    found=datastring.find("manualctl");
    if (found!=std::string::npos){
        manualctl(datastring);
        return;
    }

    //check if waterlvl is requested
    found=datastring.find("waterlvl");
    if (found!=std::string::npos){
        waterlvl();
        return;
    }

}

void postrequest::sysmode(string mode)
{
    cout << HTTPXHTMLHeader() << endl;
    //use regular expressions to find first matchgroup(value of postrequest)
    std::regex rgx("[=](.*)");
    std::smatch matches;
    std::regex_search(mode, matches, rgx);
    file->setsysmode(matches[1].str());
    //check for around 3 seconds if settings change
    int i = 0;
    while(file->getsysmode()!=matches[1].str()){
        usleep(10000);
        i++;
        if(i>300){
            break;
        }
    }
    //send data to server
    if(file->getsysmode()==matches[1].str()){
        cout << "Changed systemmode to " << file->getsysmode();
    }
    else{
        cout << "Error systemmode didnt change";
    }

}

void postrequest::watermode(string mode)
{
    cout << HTTPXHTMLHeader() << endl;
    //use regular expressions to find first matchgroup(value of postrequest)
    std::regex rgx("[=](.*)");
    std::smatch matches;
    std::regex_search(mode, matches, rgx);
    bool boolmode = false;

    if(matches[1].str()=="enable"){
        boolmode = true;
    }
    file->setwatermode(boolmode);
    int i = 0;

    //check for around 3 seconds if settings change
    while(boolmode != file->getwatermode()){
        usleep(10000);
        i++;
        if(i>300){
            break;
        }
    }
    //send data to server
    if(file->getwatermode()==boolmode){
        cout << "Automatic watering " << matches[1].str() << "d";
    }
    else{
        cout << "Error watermode didnt change";
    }

}

void postrequest::manualctl(string control)
{
     //use regular expressions to find first matchgroup(value of postrequest)
    std::regex rgx("[=](.*)");
    std::smatch matches;
    std::regex_search(control, matches, rgx);
    file->manualcontrol(matches[1].str());
}

void postrequest::waterlvl(){
    cout << HTTPXHTMLHeader() << endl;
    string s = file->getwaterlvl();
    cout << "waterlvl=" << s << endl;
}
