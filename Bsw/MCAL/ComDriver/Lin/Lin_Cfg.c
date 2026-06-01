#include "Lin_Cfg.h"

Lin_HardwareConfig Lin_HardwareConfigs[] = {[LIN_CHANNEL_1] = {.LinUartEn = LIN_UART_ENABLE,
                                                               .LinTx = LIN_TX_ENABLE,
                                                               .LinRx = LIN_RX_ENABLE,
                                                               .LinEn = LIN_MODE_ENABLE}};

Lin_ChannelConfig Lin_ChannelConfigs[] = {[0] = {.LinChannel = LIN_CHANNEL_1,
                                                 .LinBreakDetect = LIN_BREAK_DETECT_ENABLE,
                                                 .LinBaud = 115200,
                                                 .LinIsr = LIN_INTERRUPT_ENABLE,
                                                 .LinMasterSlave = LIN_MASTER}};

Lin_ConfigType Lin_Config[NUMBER_OF_LIN_CHANNEL] = {[LIN_CHANNEL_1] = {.LinHardware = &Lin_HardwareConfigs[LIN_CHANNEL_1],
                                                                       .LinChannel = &Lin_ChannelConfigs[0]}};