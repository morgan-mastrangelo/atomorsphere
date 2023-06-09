/**
 * @file sm_ams.h
 * @brief Service manager (sm) IPC wrapper for Atmosphere extensions.
 * @author SciresM
 * @copyright libnx Authors
 */
#pragma once

#if defined(ATMOSPHERE_OS_HORIZON)

#include <switch.h>

#ifdef __cplusplus
extern "C" {
#endif

Result smAtmosphereHasService(bool *out, SmServiceName name);
Result smAtmosphereWaitService(SmServiceName name);
Result smAtmosphereHasMitm(bool *out, SmServiceName name);
Result smAtmosphereWaitMitm(SmServiceName name);

Result smAtmosphereMitmInitialize(void);
void smAtmosphereMitmExit(void);
TipcService *smAtmosphereMitmGetServiceSession();

Result smAtmosphereOpenSession(TipcService *out);
void smAtmosphereCloseSession(TipcService *srv);

Result smAtmosphereMitmInstall(TipcService *fwd_srv, Handle *handle_out, Handle *query_out, SmServiceName name);
Result smAtmosphereMitmUninstall(SmServiceName name);
Result smAtmosphereMitmDeclareFuture(SmServiceName name);
Result smAtmosphereMitmClearFuture(SmServiceName name);
Result smAtmosphereMitmAcknowledgeSession(Service *srv_out, void *info_out, SmServiceName name);

#ifdef __cplusplus
}
#endif

#endif