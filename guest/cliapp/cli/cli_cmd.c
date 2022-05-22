
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#include "cli_intf.h"
#include "util/log.h"
#include "cli_cmd_config.h"
#include "util/util_mem.h"


#define CLI_CMD_TOKEN_SIZE  16
#define CLI_CMD_DELIMS  " ,"

const CLI_CMD_CONFIG_t * const CLI_CMD_CONFIG_ENTRIES_DATA[] = {
    CLI_CMD_CONFIG_ENTRIES
    NULL
};

struct CLI_CMD_DATA_s {
    char * cmdTokens[CLI_CMD_TOKEN_SIZE];
    uint8_t cmdTokenLen;
    const CLI_CMD_CONFIG_t *cmdEntry;
};

typedef struct CLI_CMD_DATA_s CLI_CMD_DATA_t;

static CLI_CMD_DATA_t selfCmdData;

static void Cli_Cmd_processBuffer(uint8_t * buffer)
{
    char *pch = NULL;
    selfCmdData.cmdEntry = NULL;
    selfCmdData.cmdTokenLen = 0U;
    UTIL_memclr(selfCmdData.cmdTokens, sizeof (selfCmdData.cmdTokens));

    pch = (char *) strtok((char *) buffer, CLI_CMD_DELIMS);
    while (pch != NULL) {
        selfCmdData.cmdTokens[selfCmdData.cmdTokenLen] = pch;
        selfCmdData.cmdTokenLen++;
        pch = strtok(NULL, CLI_CMD_DELIMS);
    }
    //    li("Processing : %s (params = %d)...", selfCmdData.cmdTokens[0], selfCmdData.cmdTokenLen);

}

static void Cli_Cmd_searchCommand(void)
{
    const CLI_CMD_CONFIG_t * const *cmdEntry = CLI_CMD_CONFIG_ENTRIES_DATA;
    uint16_t i = 0;

    while (cmdEntry[i] != NULL) {
        if (strcmp(
                (const char *) selfCmdData.cmdTokens[0],
                (const char *) cmdEntry[i]->cmd) == 0) {
            break;
        }
        i++;
    }
    selfCmdData.cmdEntry = cmdEntry[i];
}

CLI_CMD_CODE_t Cli_Cmd_processCommand(uint8_t * cmdBuff)
{
    CLI_CMD_CODE_t retcode = CLI_CMD_ERROR;
    Cli_Cmd_processBuffer(cmdBuff);
    Cli_Cmd_searchCommand();
    if (selfCmdData.cmdEntry != NULL) {
        //        li("Found Command : %s", selfCmdData.cmdEntry->cmd);
        if (selfCmdData.cmdEntry->handler != NULL) {
            retcode = selfCmdData.cmdEntry->handler(selfCmdData.cmdTokens, selfCmdData.cmdTokenLen);
        } else {
            lw("%s", "Command handler is NULL");
        }
    } else if (selfCmdData.cmdTokens[0][0] == '\0') {
        retcode = CLI_CMD_DONE;
    } else {
        lw("Command Not found : %s (use h for help)", selfCmdData.cmdTokens[0]);
        retcode = CLI_CMD_DONE;
    }
    //    lis("...Done!");
    return retcode;
}


/////////////////////////////////////////////////////////////////////////////
// Command implementations
/////////////////////////////////////////////////////////////////////////////

static CLI_CMD_CODE_t CLI_CMD_hShowMenu(char* cmds[], uint16_t cmdLen)
{
    CLI_CMD_CODE_t retCode = CLI_CMD_DONE;
    const CLI_CMD_CONFIG_t * const *cmdEntry = CLI_CMD_CONFIG_ENTRIES_DATA;
    uint16_t i = 0;
    while (cmdEntry[i] != NULL) {
        lp("%-5.5s : %s", cmdEntry[i]->title, cmdEntry[i]->description);
        i++;
    }

    return retCode;
}

const CLI_CMD_CONFIG_t CLI_CMD_cShowMenu = {
    .cmd = "h",
    .title = "h",
    .description = "Help Menu",
    .handler = CLI_CMD_hShowMenu
};
