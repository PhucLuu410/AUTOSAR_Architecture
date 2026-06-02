#include "Lin_Cfg.h"

Lin_HardwareConfig Lin_HardwareConfigs[] = {[LIN_CHANNEL_1] = {.LinUartEn = LIN_UART_ENABLE,
                                                               .LinTx = LIN_TX_ENABLE,
                                                               .LinRx = LIN_RX_ENABLE,
                                                               .LinEn = LIN_MODE_ENABLE}};

Lin_ChannelConfig Lin_ChannelConfigs[] = {[0] = {.LinChannel = LIN_CHANNEL_1,
                                                 .LinBreakDetect = LIN_BREAK_DETECT_ENABLE,
                                                 .LinBaud = 115200,
                                                 .LinIsr = LIN_INTERRUPT_ENABLE,
                                                 .LinMasterSlave = LIN_SLAVE}};

Lin_ConfigType Lin_Config[NUMBER_OF_LIN_CHANNEL] = {[LIN_CHANNEL_1] = {.LinHardware = &Lin_HardwareConfigs[LIN_CHANNEL_1],
                                                                       .LinChannel = &Lin_ChannelConfigs[0]}};

uint8 Lin_ElectronicWindowBuffer[13] = {0};
uint8 Lin_ElectricWipersBuffer[13] = {0};

uint8 *Lin_RxData[] = {[Lin_ElectronicWindow] = Lin_ElectronicWindowBuffer,
                       [Lin_ElectricWipers] = Lin_ElectricWipersBuffer};
// Lin_RxPduType Lin_RxPdu[] = {[Lin_ElectronicWindow] = {.Pid = 0x12,
//                                                        .Dl = 0,
//                                                        .CsModel = LIN_ENHANCED_CS,
//                                                        .Response = LIN_FRAMERESPONSE_RX,
//                                                        .SduDataPtr = Lin_ElectronicWindowBuffer,
//                                                        .Crc = 0}};