/*
 *
 *
 *  Created on: Mar 29, 2020
 *      Author: Andres Rogelio
 */
#include "labelEngine.h"

//int16_t retVal;
//uint16_t valueSize;
//void *valueBuff;
//Json_Handle labelTemplateHandle;
//Json_Handle labelObjectHandle;
LabelJSON resultLabel;
/*
 * This method will take the API and will create the
 * information necessary to drive the screen and
 * actually locate the received information in a proper
 * way taking into account the size of the data
 */
void printLabel(void);

int8_t createLabel(const char *object)
{
    const cJSON *ProductID = NULL;
    int status = 0;
    void *valueBuff = NULL;


    cJSON *jobj = cJSON_Parse(object);
    if(jobj == NULL)
    {
        status = 0;
        goto end;
    }
    ProductID = cJSON_GetObjectItemCaseSensitive(jobj, "ProductID");
    if(cJSON_IsString(ProductID) && (ProductID->valuestring != NULL))
    {
        strcpy(resultLabel.ProductID, ProductID->valuestring);
    }


    end:
    cJSON_Delete(jobj);
    return status;
}

//int8_t createLabel(const char *object)
//{
//    retVal = Json_createTemplate(&labelTemplateHandle, labelTemplate, strlen(labelTemplate));
//    if(retVal != 0)
//    {
//        //Error
//        return -1;
//    }
//
//    retVal = Json_createObject(&labelObjectHandle, labelTemplateHandle,0);
//    if(retVal != 0)
//    {
//        //Error
//        return -1;
//    }
//
//    //Start parsing the information
//    retVal = Json_parse(labelObjectHandle, object, strlen(object));
//    if(retVal != 0)
//    {
//        //error
//        return -1;
//    }
//
//    //This section of code needs to be done over all the attributes of the JSON
//    retVal = Json_getValue(labelObjectHandle, "\"ProductID\"", NULL, valueSize);
//    if(retVal != 0)
//    {
//        //error
//        return -1;
//    }
//
//    valueBuff = calloc(1,valueSize+1);
//
//    retVal = Json_getValue(labelObjectHandle, "\"ProductID\"", valueBuff, valueSize);
//    if(retVal != 0)
//    {
//        //error
//        return -1;
//    }
//
//    //Make sure the values are located in place
//    strcpy(resultLabel.ProductID, valueBuff);
//
//    return 0;
//}

void printLabel(void)
{
    gfxInit();

    gfxWriteText(&FONT_ubuntu_bold_16, 115, 0, resultLabel.ProductID);

//    gfxWriteText(&FONT_ubuntu_bold_16, 115, 0, "Scientific calculator for large");
//    gfxWriteText(&FONT_ubuntu_bold_16, 100, 0, "and digital part");
//    gfxWriteText(&FONT_ubuntu_medium_48, 24, 0, "545");
//    gfxWriteText(&FONT_ubuntu_bold_24, 58, 100, "98");
//    gfxWriteText(&FONT_ubuntu_bold_16, 20, 0, "SKU: 4568, 12/13/2020");
//    gfxWriteText(&FONT_ubuntu_bold_16, 0, 0, "Model: MFX4587");

    updateEPD();
}
