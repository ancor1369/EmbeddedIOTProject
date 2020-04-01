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
    const cJSON *value = NULL;

    int status = 0;
    void *valueBuff = NULL;


    cJSON *jobj = cJSON_Parse(object);
    if(jobj == NULL)
    {
        status = 0;
        goto end;
    }
    value = cJSON_GetObjectItemCaseSensitive(jobj, "ProductID");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.ProductID, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "PriceDollar");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.PriceDollar, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "PriceDollar");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.PriceDollar, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "PriceCents");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.PriceCents, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "Description");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.Description, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "URL");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.URL, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "SKU");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.SKU, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "Model");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.Model, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "DueDate");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.DueDate, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "LayoutName");
    if(cJSON_IsString(value) && (value->valuestring != NULL))
    {
        strcpy(resultLabel.LayoutName, value->valuestring);
    }

    value = cJSON_GetObjectItemCaseSensitive(jobj, "Update");
     if(cJSON_IsString(value) && (value->valuestring != NULL))
     {
         strcpy(resultLabel.Update, value->valuestring);
     }
     value = cJSON_GetObjectItemCaseSensitive(jobj, "Blink");
      if(cJSON_IsString(value) && (value->valuestring != NULL))
      {
          strcpy(resultLabel.Blink, value->valuestring);
      }

    end:
    cJSON_Delete(jobj);
    return status;
}


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
