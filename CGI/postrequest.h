#ifndef POSTREQUEST_H
#define POSTREQUEST_H

#include <string>
#include <regex>
#include <unistd.h>

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/CgiEnvironment.h"
#include "cgicc/FormEntry.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "cgicc/HTTPXHTMLHeader.h"

#include "fileaccess.h"
#include "regex.h"

using namespace cgicc;

class postrequest
{
public:
    postrequest(Cgicc* data, fileaccess* _file);
private:
    void sysmode(string mode);
    void watermode(string mode);
    void manualctl(string control);
    fileaccess *file;
};

#endif // POSTREQUEST_H
