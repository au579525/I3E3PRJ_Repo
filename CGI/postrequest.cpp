#include "postrequest.h"

postrequest::postrequest(Cgicc *data, fileaccess *_file)
{
    file = _file;
    string datastring = data->getEnvironment().getPostData();
    std::size_t found=datastring.find("sysmode");
    if (found!=std::string::npos){
        sysmode(datastring);
        return;
    }
    file->setsysmode(data->getEnvironment().getPostData());
    found=datastring.find("watermode");
    if (found!=std::string::npos){
        watermode(datastring);
        return;
    }

    found=datastring.find("manualctl");
    if (found!=std::string::npos){
        manualctl(datastring);
        return;
    }
}

void postrequest::sysmode(string mode)
{
    cout << HTTPXHTMLHeader() << endl;
    std::regex rgx("[=](.*)");
    std::smatch matches;
    std::regex_search(mode, matches, rgx);
    file->setsysmode(matches[1].str());
    int i = 0;
    while(file->getsysmode()!=matches[1].str()){
        usleep(10000);
        i++;
        if(i>300){
            break;
        }
    }
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
    std::regex rgx("[=](.*)");
    std::smatch matches;
    std::regex_search(mode, matches, rgx);
    bool boolmode = false;

    if(matches[1].str()=="enable"){
        boolmode = true;
    }
    int i = 0;
    while(boolmode != file->getwatermode()){
        usleep(10000);
        i++;
        if(i>300){
            break;
        }
    }

    if(file->getwatermode()==boolmode){
        cout << "Automatic watering " << matches[1].str() << "d";
    }
    else{
        cout << "Error watermode didnt change";
    }

}

void postrequest::manualctl(string control)
{
    std::regex rgx("[=](.*)");
    std::smatch matches;
    std::regex_search(control, matches, rgx);
    file->manualcontrol(matches[1].str());
}
