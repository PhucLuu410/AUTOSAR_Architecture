#include "Port.h"
#include "Port_Cfg.h"

const Port_ConfigType Port_Configuration[] = {
    {PORT_A,
     0,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},

    {PORT_A,
     1,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     2,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},

    {PORT_A,
     3,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     8,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},
    {PORT_C,
     13,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_GP_OUTPUT_PP}};
     