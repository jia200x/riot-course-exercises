/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "xtimer.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include "board.h"

/* Declare globally the loramac descriptor */

/* Device and application informations required for OTAA activation */

/* The simple message to send */
const char *message = "This is RIOT!";

int main(void)
{
    /* initialize the loramac stack */

    /* use a fast datarate so we don't use the physical layer too much */

    /* set the LoRaWAN keys */

    /* start the OTAA join procedure */

    while (1) {
        printf("Sending message: %s\n", message);
    }

    return 0; /* should never be reached */
}
