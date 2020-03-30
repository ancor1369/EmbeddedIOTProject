/*
 *
 *
 *  Created on: Mar 29, 2020
 *      Author: Andres Rogelio
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include <ti/utils/json/json.h>
#include "label_types.h"

#include "Driver/pinDefinintions.h"
#include "Driver/ePaper.h"
#include "grx/graphics.h"
#include "fonts/resources.h"

/*
 * This method is the only one I expose.
 * This method takes the JSON object and
 * then calculate the sections to call in
 * order to draw the label as it is required
 *
 * It returns a numeric response to know if the
 * function was successful or not.
 */
int8_t createLabel(const char *object);
