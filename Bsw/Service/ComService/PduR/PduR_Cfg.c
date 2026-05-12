#include "PduR_Cfg.h"
#include "PduR.h"

static const PduR_RoutingPathType MyRobot_RxPaths[] = {
    {0, 10, 0},
    {1, 11, 0}};

const PduR_PBConfigType PduR_GlobalConfig = {
    MyRobot_RxPaths,
    NULL_PTR};