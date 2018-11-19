#include "htmlpage.h"


// TODO implement script for changed settings and manual control and include it in html code
htmlpage::htmlpage(fileaccess* sysdata)
{
    string sysmode = sysdata->getsysmode();
    cout << HTTPHTMLHeader() << endl;
    cout << "<html>"<<endl;
    htmlhead();
    cout << "<body>"<< endl;
    header();
    settings(sysmode, sysdata->getwatermode());
    if(sysmode == "manual"){
        manual();
    }
    cout << "<script src=\"selectmenu.js\"></script>" << endl;
    cout << "</body>" << endl;
    cout << "</html>" << endl;
}

void htmlpage::settings(string sysmode, bool watermode){
    cout << "<div class=\"clear content\">" << endl;
    cout << "<div class=\"settings clear\">" << endl;
    cout << "<h2 class=\"content-header\">Settings</h2>" << endl;
    cout << "<div class=\"section clear\">" << endl;
    cout << "<h3>Choose system mode</h3>" << endl;
    cout << "<div class=\"select-menu-container clear\">" << endl;
    cout << "<div class=\"select-menu-select clear\">" << endl;
    cout << "<select>" << endl;
    if(sysmode == "normal"){
        cout << "option value=\"normal\" selected>Normal</option>" << endl;
        cout << "<option value=\"manual\">Manual</option>" << endl;
        cout << "<option value=\"powersaving\">Powersaving</option>" << endl;
        cout << "<option value=\"standby\">Standby</option>" << endl;
    }
    else if(sysmode == "manual"){
        cout << "option value=\"normal\">Normal</option>" << endl;
        cout << "<option value=\"manual\" selected>Manual</option>" << endl;
        cout << "<option value=\"powersaving\">Powersaving</option>" << endl;
        cout << "<option value=\"standby\">Standby</option>" << endl;
    }
    else if(sysmode == "powersaving"){
        cout << "option value=\"normal\">Normal</option>" << endl;
        cout << "<option value=\"manual\">Manual</option>" << endl;
        cout << "<option value=\"powersaving\" selected>Powersaving</option>" << endl;
        cout << "<option value=\"standby\">Standby</option>" << endl;
    }
    else if(sysmode == "standby"){
        cout << "option value=\"normal\">Normal</option>" << endl;
        cout << "<option value=\"manual\" selected>Manual</option>" << endl;
        cout << "<option value=\"powersaving\">Powersaving</option>" << endl;
        cout << "<option value=\"standby\" selected>Standby</option>" << endl;
    }
    cout << "</select>" << endl;
    cout << "</div>" << endl;
    cout << "<button class=\"select-menu-save\">Save</button>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"section clear\">" << endl;
    cout << "<h3>Automatic watering</h3>" << endl;
    cout << "<div class=\"clear\" id=\"water-mode-button\">" << endl;
    if(watermode){
        cout << "<button class=\"btn active true\">Enable</button>" << endl;
        cout << "<button class=\"btn false\">Disable</button>" << endl;
    }
    else{
        cout << "<button class=\"btn true\">Enable</button>" << endl;
        cout << "<button class=\"btn active false\">Disable</button>" << endl;
    }
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
}

void htmlpage::manual(){
    cout << "<div class=\"clear content\">" << endl;
    cout << "<div class=\"manual-control clear\">" << endl;
    cout << "<h2 class=\"content-header\">Manual Control</h2>" << endl;
    cout << "<div class=\"button-container clear\">" << endl;
    cout << "<button class=\"control-btn arrow up\">" << endl;
    cout << "<i class=\"fas fa-angle-up\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"button-container clear\">" << endl;
    cout << "<button class=\"control-btn \">" << endl;
    cout << "<i class=\"fas fa-angle-left\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "<button class=\"control-btn shoot-btn\">" << endl;
    cout << "<i class=\"circle\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "<button class=\"control-btn\">" << endl;
    cout << "<i class=\"fas fa-angle-right\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"button-container clear\">" << endl;
    cout << "<button class=\"control-btn\">" << endl;
    cout << "<i class=\"fas fa-angle-down\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"instruct-text\">" << endl;
    cout << "Press the buttons to move the gun by 5°. Press the button in the middle to shoot water for 3 seconds." << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
}

void htmlpage::log(vector<string> logfile){
    cout << "<div class=\"clear content\">" << endl;
    cout << "<div class=\"log clear\">" << endl;
    cout << "<h2 class=\"content-header\">Log</h2>" << endl;
    cout << "<pre class=\"clear\" id=\"log-content\">" << endl;
    for(std::vector<string>::iterator it = logfile.begin(); it != logfile.end(); ++it){
        cout << *it << endl;
    }
    cout << "</pre>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
}

void htmlpage::htmlhead(){
    cout << "<head>"<<endl;
    cout << "<title>PES</title>"<< endl;
    cout << "<meta charset=\"UTF-8\">"<< endl;
    cout << "<link rel=\"stylesheet\" href=\"style.css\">" << endl;
    cout << "<link href=\"font-awesome/css/all.css\" rel=\"stylesheet\">" << endl;
    cout << "</head>"<< endl;
}

void htmlpage::header(){
    cout << "<header class=\"clear\">" << endl;
    cout << "<div id=\"header-text\">" << endl;
    cout << "<h1>PIGEON EXTORMINATION SYSTEM</h1>" << endl;
    cout << "<p>Configuration website</p>" << endl;
    cout << "</div>" << endl;
    cout << "</header>" << endl;
}
