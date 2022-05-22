
#include <stdint.h>
#include <stdbool.h>

#include "util/util_mem.h"
#include "util/log.h"
#include "util/util.h"

#include "cli_intf.h"

#define CLI_CMD_LEN 32

enum CLI_STATES_e {
    CLI_OFF,
    CLI_START,
    CLI_PRINT_WELCOME,
    CLI_START_GET_CMD,
    CLI_GET_COMMAND,
    CLI_PROCESS_COMMAND,
    CLI_PROCESS_CONTINUE
};

typedef enum CLI_STATES_e CLI_STATES_t;

enum CLI_GET_CMD_e {
    CLI_SHOW_PROMPT,
    CLI_READ_LINE,
    CLI_READ_LINE_DONE
};

typedef enum CLI_GET_CMD_e CLI_GET_CMD_t;

struct CLI_DATA_s {
    uint8_t cmdBuffer[CLI_CMD_LEN];
    uint16_t cmdIndex;
    CLI_STATES_t state;
    CLI_GET_CMD_t stateGetCmd;
};

typedef struct CLI_DATA_s CLI_DATA_t;

static CLI_DATA_t selfCli;

void CLI_init(void)
{
    UTIL_memclr(&selfCli, sizeof (selfCli));
    selfCli.state = CLI_OFF;
}

void CLI_start(void)
{
    selfCli.state = CLI_START;
}

static void Cli_welcome(void)
{
    lhr();
    lp("%-40.40s", "Welcome to dsPIC33CH512MP508!");
    lp("%-40.40s", "h : help");
    lhr();
}

static CLI_GET_CMD_t Cli_processInput(CLI_GET_CMD_t cmdState)
{
    char ch;
    if (UTIL_getChar(&ch) == true) {
        switch (ch) {
        case '\r':
        case '\n':
            cmdState = CLI_READ_LINE_DONE;
            selfCli.cmdBuffer[selfCli.cmdIndex] = '\0';
            selfCli.cmdIndex++;
            break;
        default:
            selfCli.cmdBuffer[selfCli.cmdIndex] = ch;
            selfCli.cmdIndex++;
            break;
        }
        UTIL_putChar(ch);
        if (ch == '\r') {
            UTIL_putChar('\n');
        }
    }
    return cmdState;
}

static CLI_STATES_t Cli_getCmd(CLI_STATES_t state)
{
    switch (selfCli.stateGetCmd) {
    case CLI_SHOW_PROMPT:
        lc('>');
        UTIL_memclr(selfCli.cmdBuffer, CLI_CMD_LEN);
        selfCli.cmdIndex = 0x00U;
        selfCli.stateGetCmd = CLI_READ_LINE;
        break;
    case CLI_READ_LINE:
        selfCli.stateGetCmd = Cli_processInput(selfCli.stateGetCmd);
        break;
    case CLI_READ_LINE_DONE:
        state = CLI_PROCESS_COMMAND;
    default:
        break;
    }
    return state;
}

static CLI_STATES_t Cli_processCmd(CLI_STATES_t state)
{
    CLI_CMD_CODE_t cmdRet = Cli_Cmd_processCommand(selfCli.cmdBuffer);
    if (cmdRet == CLI_CMD_DONE) {
        state = CLI_START_GET_CMD;
    } else if (cmdRet == CLI_CMD_ERROR) {
        le("%s", "Error processing command!");
        state = CLI_START_GET_CMD;
    }
    return state;
}

void CLI_stateMachine(void)
{
    switch (selfCli.state) {
    case CLI_OFF:
        // Wait for starting...
        break;
    case CLI_START:
        selfCli.state = CLI_PRINT_WELCOME;
        break;
    case CLI_PRINT_WELCOME:
        Cli_welcome();
        selfCli.state = CLI_GET_COMMAND;
        selfCli.stateGetCmd = CLI_SHOW_PROMPT;
        break;
    case CLI_START_GET_CMD:
        selfCli.state = CLI_GET_COMMAND;
        selfCli.stateGetCmd = CLI_SHOW_PROMPT;
        break;
    case CLI_GET_COMMAND:
        selfCli.state = Cli_getCmd(selfCli.state);
        break;
    case CLI_PROCESS_COMMAND:
        selfCli.state = Cli_processCmd(selfCli.state);
    default:
        break;
    }
}
