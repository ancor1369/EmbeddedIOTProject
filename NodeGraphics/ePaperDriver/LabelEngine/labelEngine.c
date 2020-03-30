/*
 *
 *
 *  Created on: Mar 29, 2020
 *      Author: Andres Rogelio
 */
#include "labelEngine.h"

int16_t retVal;
uint16_t valueSize;
void *valueBuff;
Json_Handle labelTemplateHandle;
Json_Handle labelObjectHandle;
//LabelJSON resultLabel;
/*
 * This method will take the API and will create the
 * information necessary to drive the screen and
 * actually locate the received information in a proper
 * way taking into account the size of the data
 */
void buildLabel(void);


int8_t createLabel(const char *object)
{
    retVal = Json_createTemplate(&labelTemplateHandle, labelTemplate, strlen(labelTemplate));
    if(retVal != 0)
    {
        //Error
        return -1;
    }

    retVal = Json_createObject(&labelObjectHandle, labelTemplateHandle,0);
    if(retVal != 0)
    {
        //Error
        return -1;
    }

    //Start parsing the information
    retVal = Json_parse(labelObjectHandle, object, strlen(object));
    if(retVal != 0)
    {
        //error
        return -1;
    }

    //This section of code needs to be done over all the attributes of the JSON
    retVal = Json_getValue(labelObjectHandle, "\"ProductID\"", NULL, valueSize);
    if(retVal != 0)
    {
        //error
        return -1;
    }

    valueBuff = calloc(1,valueSize+1);

    retVal = Json_getValue(labelObjectHandle, "\"ProductID\"", valueBuff, valueSize);
    if(retVal != 0)
    {
        //error
        return -1;
    }

    //Cast the result and assign
    //it to my data structure
    //resultLabel.ProductID = valueBuff;



}
