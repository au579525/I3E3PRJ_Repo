#include "htmlpage.h"


// TODO implement script for changed settings and manual control and include it in html code
htmlpage::htmlpage(fileaccess *sysdata)
{
    string sysmode = sysdata->getsysmode();
    cout << HTTPHTMLHeader() << endl;
    cout << "<html>"<<endl;
    htmlhead();
    cout << "<body>"<< endl;
    header();
    waterlvl(sysdata->getwaterlvl());
    //check if system is in manual code
    settings(sysmode, sysdata->getwatermode());
    if(sysmode == "manual"){
        manual(true);
    }
    else{
        manual(false);
    }
    log(sysdata->getlog());
    cout << "<script src=\"postrequests.js\"></script>" << endl;
    cout << "<script src=\"selectmenu.js\"></script>" << endl;
    cout << "</body>" << endl;
    cout << "</html>" << endl;
}

void htmlpage::waterlvl(string lvl){
    cout << "<div class=\"clear content\">" << endl;
    cout << "<div class=\"waterlvl clear \">" << endl;
    cout << "<h2 class=\"content-header\">Water level</h2>" << endl;
    cout << "<h3 id=\"waterlvl\">" << endl;
    if(lvl == "0"){
        cout << "There is not enough water in the tank!" << endl;
    }
    else{
        cout << "There are approximately " << lvl << "mL water in the tank";
    }
    cout << "</h3>" << endl;
    cout << "<div class=\"waterlvltxt\">" << endl;
    cout << "If the water level gets below 200 ml the system automatically goes into standby mode" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
}

void htmlpage::settings(string sysmode, bool watermode){
    cout << "<div class=\"clear content\">" << endl;
    cout << "<div class=\"settings clear\">" << endl;
    cout << "<h2 class=\"content-header\">Settings</h2>" << endl;
    cout << "<div class=\"section clear\">" << endl;
    cout << "<h3>Choose system mode</h3>" << endl;
    cout << "<div class=\"select-menu-container clear\">" << endl;
    cout << "<div class=\"select-menu-select clear\">" << endl;
    cout << "<select id=\"sysmode\">" << endl;
    //different menu outputs depending on systemmode
    if(sysmode == "normal"){
        cout << "<option value=\"normal\" selected>Normal</option>" << endl;
        cout << "<option value=\"manual\">Manual</option>" << endl;
        cout << "<option value=\"powersaving\">Powersaving</option>" << endl;
        cout << "<option value=\"standby\">Standby</option>" << endl;
    }
    else if(sysmode == "manual"){
        cout << "<option value=\"normal\">Normal</option>" << endl;
        cout << "<option value=\"manual\" selected>Manual</option>" << endl;
        cout << "<option value=\"powersaving\">Powersaving</option>" << endl;
        cout << "<option value=\"standby\">Standby</option>" << endl;
    }
    else if(sysmode == "powersaving"){
        cout << "<option value=\"normal\">Normal</option>" << endl;
        cout << "<option value=\"manual\">Manual</option>" << endl;
        cout << "<option value=\"powersaving\" selected>Powersaving</option>" << endl;
        cout << "<option value=\"standby\">Standby</option>" << endl;
    }
    else if(sysmode == "standby"){
        cout << "<option value=\"normal\">Normal</option>" << endl;
        cout << "<option value=\"manual\" selected>Manual</option>" << endl;
        cout << "<option value=\"powersaving\">Powersaving</option>" << endl;
        cout << "<option value=\"standby\" selected>Standby</option>" << endl;
    }
    cout << "</select>" << endl;
    cout << "</div>" << endl;
    cout << "<button class=\"select-menu-save\" onclick=\"changesysmode()\">Save</button>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"section clear\">" << endl;
    cout << "<h3>Automatic watering</h3>" << endl;
    cout << "<div class=\"clear\" id=\"water-mode-button\">" << endl;
    //check watermode
    if(watermode){
        cout << "<button class=\"btn active true\" onclick=\"changewatermode('enable')\">Enable</button>" << endl;
        cout << "<button class=\"btn false\" onclick=\"changewatermode('disable')\">Disable</button>" << endl;
    }
    else{
        cout << "<button class=\"btn true\" onclick=\"changewatermode('enable')\">Enable</button>" << endl;
        cout << "<button class=\"btn active false\" onclick=\"changewatermode('disable')\">Disable</button>" << endl;
    }
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
}

void htmlpage::manual(bool show){
    //show or hide manualcontrol container
    if(show){
       cout << "<div class=\"clear content\" id=\"manualctn\">" << endl;
    }
    else{
        cout << "<div class=\"clear hide content\" id=\"manualctn\">" << endl;
    }
    cout << "<div class=\"manual-control clear\">" << endl;
    cout << "<h2 class=\"content-header\">Manual Control</h2>" << endl;
    cout << "<div class=\"button-container clear\">" << endl;
    cout << "<button class=\"control-btn arrow up\" onclick=\"manualcontrol('up')\">" << endl;
    cout << "<i class=\"fas fa-angle-up\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"button-container clear\">" << endl;
    cout << "<button class=\"control-btn \" onclick=\"manualcontrol('left')\">" << endl;
    cout << "<i class=\"fas fa-angle-left\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "<button class=\"control-btn shoot-btn\" onclick=\"manualcontrol('shoot')\">" << endl;
    cout << "<i class=\"circle\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "<button class=\"control-btn\" onclick=\"manualcontrol('right')\">" << endl;
    cout << "<i class=\"fas fa-angle-right\"></i>" << endl;
    cout << "</button>" << endl;
    cout << "</div>" << endl;
    cout << "<div class=\"button-container clear\">" << endl;
    cout << "<button class=\"control-btn\" onclick=\"manualcontrol('down')\">" << endl;
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

    //interate over lines in logfile and print out
    int i = 0;
    for(std::vector<string>::reverse_iterator it = logfile.rbegin(); it != logfile.rend() && i<50 ; ++it){
        i++;
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
    cout << "<link href=\"/font-awesome/css/all.css\" rel=\"stylesheet\">" << endl;
    cout << "</head>"<< endl;
}

void htmlpage::header(){
    cout << "<header class=\"clear\">" << endl;
    cout << "<div id=\"header-text\">" << endl;
    cout << "<h1>PIGEON EXTERMINATION SYSTEM</h1>" << endl;
    cout << "<p>Configuration website</p>" << endl;
    cout << "</div>" << endl;
    cout << "</header>" << endl;
}
