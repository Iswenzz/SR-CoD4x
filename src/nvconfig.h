#ifndef __NVCONFIG_H__
#define __NVCONFIG_H__

#define NV_ProcessBegin NV_LoadConfig
#define NV_ProcessEnd NV_WriteConfig

void NV_LoadConfig();
void NV_WriteConfig();

#endif
