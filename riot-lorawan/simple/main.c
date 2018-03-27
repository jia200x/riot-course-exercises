#include <string.h>

#include "xtimer.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include "board.h"

/* Declare globally the loramac descriptor */
semtech_loramac_t loramac;

/* Device and application informations required for OTAA activation */
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0x00, 0xBD, 0x35, 0xDE, 0xE5, 0x8F, 0xF9, 0xCB };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x00, 0xB0, 0x2F };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0xC9, 0x18, 0x70, 0x83, 0x5C, 0x73, 0xF5, 0xE3, 0x6E, 0xDF, 0x6E, 0x5D, 0xBD, 0x14, 0x45, 0xD0 };

/* The simple message to send */
const char *message = "This is RIOT!";

int main(void)
{
    /* initialize the loramac stack */
    semtech_loramac_init(&loramac);

    /* use a fast datarate so we don't use the physical layer too much */
    semtech_loramac_set_dr(&loramac, 5);

    /* set the LoRaWAN keys */
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    /* start the OTAA join procedure */
    puts("Starting join procedure");
    if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
        puts("Join procedure failed");
        return 1;
    }

    puts("Join procedure succeeded");

    while (1) {
        printf("Sending message: %s\n", message);
        /* send the message every 20 seconds */
        semtech_loramac_send(&loramac, (uint8_t *)message, strlen(message));
        /* Wait until the send cycle has completed */
        semtech_loramac_recv(&loramac);

        xtimer_sleep(20);
    }

    return 0; /* should never be reached */
}
