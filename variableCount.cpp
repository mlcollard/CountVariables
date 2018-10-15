/*
    variableCount.cpp

    Implementation file for variableCount()
*/

#include "variableCount.hpp"

#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

namespace {

    // XPath for count of all declared variables
    const char* VARIABLE_COUNT_XPATH = "count(//src:decl/src:name)";
}

// number of variables in the srcML file
int variableCount(const char* srcMLfile) {

    xmlInitParser();

    // open the srcML file with no encoding change and no options
    xmlDocPtr srcMLdoc = xmlReadFile(srcMLfile, nullptr, 0);
    if (!srcMLdoc)
        return -1;

    // Create xpath evaluation context
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(srcMLdoc);
    if (!xpathCtx) {
        xmlFreeDoc(srcMLdoc);
        return -1;
    }

    // register namespaces
    if (xmlXPathRegisterNs(xpathCtx, BAD_CAST "src", BAD_CAST "http://www.srcML.org/srcML/src")) {
        xmlFreeDoc(srcMLdoc);
        return -1;
    }

    if (xmlXPathRegisterNs(xpathCtx, BAD_CAST "cpp", BAD_CAST "http://www.srcML.org/srcML/cpp")) {
        xmlFreeDoc(srcMLdoc);
        return -1;
    }

    // Evaluate xpath expression
    xmlXPathObjectPtr xpathResults = xmlXPathEvalExpression(BAD_CAST VARIABLE_COUNT_XPATH, xpathCtx);
    if (!xpathResults) {
        xmlXPathFreeContext(xpathCtx); 
        xmlFreeDoc(srcMLdoc);
        return-1;
    }

    // Extract the count
    int count = xmlXPathCastToNumber(xpathResults);

    xmlXPathFreeObject(xpathResults);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(srcMLdoc);

    return count;
}
