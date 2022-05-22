
#include "util/util.h"

#include "util/log.h"
#include "cli/cli.h"
#include "evt/event.h"
#include "tmr/tmr.h"


static void Main_drvInit(void)
{
}

static void Main_drvStart(void)
{
    lis("Welcome");
    Log_clearScreen();
}

static void Main_devInit(void)
{
}

static void Main_devStart(void)
{
}

static void Main_modInit(void)
{
    Log_init();
    Event_init();
    CLI_init();
}

static void Main_modStart(void)
{
    CLI_start();
}

static void Main_appInit(void)
{
}

static void Main_appStart(void)
{

}

/*
                         Main application
 */

#define WELCOME_MESSAGE "Hello World"

int main1(void)
{
    // initialize the device
    Main_drvInit();
    Main_devInit();
    Main_modInit();
    Main_appInit();


    Main_drvStart();
    Main_devStart();
    Main_modStart();
    Main_appStart();



    while (1) {
        Event_process();
    }
    return 1;
}

/**
 End of File
 */

