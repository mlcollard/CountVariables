/*
    variableCount.cpp

    Implementation file for variableCount()
*/

#include "variableCount.hpp"

#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

// number of variables in the srcML file
int variableCount(const char* srcMLfile) {

    xmlInitParser();

    // open the srcML file with no encoding change and no options
    xmlDocPtr doc = xmlReadFile(srcMLfile, nullptr, 0);
    if (!doc)
        return -1;

    // Create xpath evaluation context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx)
        return -1;

    // register namespaces
    if (xmlXPathRegisterNs(xpathCtx, BAD_CAST "src", BAD_CAST "http://www.srcML.org/srcML/src"))
        return -1;

    if (xmlXPathRegisterNs(xpathCtx, BAD_CAST "cpp", BAD_CAST "http://www.srcML.org/srcML/cpp"))
        return -1;

    // Evaluate xpath expression
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression(BAD_CAST "//src:decl/src:name", xpathCtx);
    if (!xpathObj) {
        xmlXPathFreeContext(xpathCtx); 
        return-1;
    }

    int count = xpathObj->nodesetval->nodeNr;

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx); 

    return count;
}
