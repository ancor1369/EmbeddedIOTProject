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

#include <stdint.h>

/*
 * This is the layout of the object
 * I will receive from the serial interface
 * as a message containing the information I need
 * to show the information on the final label
 */
//
#define labelTemplate       \
 "{"                        \
  "\"ProductID\": string,"  \
  "\"PriceDollar\": int32," \
  "\"PriceCents\": int16,"  \
  "\"Description\": string,"\
  "\"URL\": string,"        \
  "\"SKU\": string,"        \
  "\"Model\": string,"      \
  "\"DueDate\": string,"    \
  "\"LayoutName\": string," \
  "\"Update\": boolean,"    \
  "\"Blink\": boolean"      \
"}"


typedef struct {
    char ProductID[8];
    char PriceDollar[8];
    char PriceCents[8];
    char Description[64];
    char URL[32];
    char SKU[16];
    char Model[24];
    char DueDate[18];
    char LayoutName[16];
    char Update[4];
    char Blink[4];
} LabelJSON;

//typedef labelTemplate_t LabelJSON;


