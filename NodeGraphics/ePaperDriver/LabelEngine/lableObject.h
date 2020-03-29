/*
 *
 *
 *  Created on: Mar 29, 2020
 *      Author: Andres Rogelio
 */

/*
 *  This structure represent the JSON object that will
 *  arrive to this device so that the information is
 *  extracted and sent to the screen.
 */

#include <stdio.h>
#include <string.h>

typedef struct LabelJSON{
    char ProductID[10];
    char PriceDollar[10];
    char Description[100];
    char URL[50];
    char SKU[10];
    char Model[20];
    char DueDate[10];
    char LayoutName[10];
    char Update[4];
    char Blink[4];
}LabelJSON;


