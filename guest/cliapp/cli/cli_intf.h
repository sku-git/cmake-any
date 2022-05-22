#ifndef CLI_INTF_H
#define	CLI_INTF_H

#include <stdint.h>
#include <stdbool.h>

enum CLI_CMD_CODE_e {
    CLI_CMD_ACTIVE,
    CLI_CMD_ERROR,
    CLI_CMD_DONE,
};

typedef enum CLI_CMD_CODE_e CLI_CMD_CODE_t;

CLI_CMD_CODE_t Cli_Cmd_processCommand(uint8_t * cmdBuff);


#endif	/* CLI_INTF_H */

