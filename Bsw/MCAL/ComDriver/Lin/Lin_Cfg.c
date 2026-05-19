#include "Lin_Cfg.h"

Lin_HardwareConfig Lin_HardwareConfigs[NUMBER_OF_LIN_CHANNEL] = {[LIN_CHANNEL_1] = {.LinUartEn = LIN_UART_ENABLE,
                                                                                    .LinTx = LIN_TX_ENABLE,
                                                                                    .LinRx = LIN_RX_ENABLE,
                                                                                    .LinEn = LIN_MODE_ENABLE},

                                                                 [LIN_CHANNEL_2] = {.LinUartEn = LIN_UART_ENABLE,
                                                                                    .LinTx = LIN_TX_ENABLE,
                                                                                    .LinRx = LIN_RX_ENABLE,
                                                                                    .LinEn = LIN_MODE_ENABLE}};

Lin_ChannelConfig Lin_ChannelConfigs[NUMBER_OF_LIN_CHANNEL] = {[0] = {.LinChannel = LIN_CHANNEL_1,
                                                                      .LinBreakDetect = LIN_BREAK_DETECT_ENABLE,
                                                                      .LinBaud = 9600,
                                                                      .LinIsr = LIN_INTERRUPT_ENABLE,
                                                                      .LinMasterSlave = LIN_MASTER}};

Lin_ConfigType Lin_Config[NUMBER_OF_LIN_CHANNEL] = {[LIN_CHANNEL_1] = {.LinHardware = &Lin_HardwareConfigs[LIN_CHANNEL_1],
                                                                       .LinChannel = &Lin_ChannelConfigs[0]}};

uint8 Lin_FrameBuffer1[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8 Lin_FrameBuffer2[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8 Lin_FrameBuffer3[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

Lin_PduType LinTxPduInfo[SENSOR_USING_LIN] = {[SENSOR_4] = {.Pid = 0x12,
                                                            .Dl = 8,
                                                            .CsModel = LIN_ENHANCED_CS,
                                                            .Response = LIN_FRAMERESPONSE_TX,
                                                            .SduDataPtr = Lin_FrameBuffer1},
                                              [SENSOR_5] = {.Pid = 0x34,
                                                            .Dl = 8,
                                                            .CsModel = LIN_ENHANCED_CS,
                                                            .Response = LIN_FRAMERESPONSE_TX,
                                                            .SduDataPtr = Lin_FrameBuffer2},
                                              [SENSOR_6] = {.Pid = 0x56,
                                                            .Dl = 8,
                                                            .CsModel = LIN_ENHANCED_CS,
                                                            .Response = LIN_FRAMERESPONSE_TX,
                                                            .SduDataPtr = Lin_FrameBuffer3}};