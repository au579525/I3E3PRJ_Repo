#ifndef HTMLPAGE_H
#define HTMLPAGE_H
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/CgiEnvironment.h"
#include "cgicc/FormEntry.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include <fileaccess.h>

using namespace cgicc;

class htmlpage
{
public:
    htmlpage(fileaccess *sysdata);
private:
    void htmlhead();
    void header();
    void settings(string, bool);
    void manual(bool show);
    void log(vector<string>);
};

#endif // HTMLPAGE_H
