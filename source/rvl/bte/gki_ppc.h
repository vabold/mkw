#pragma once

#include <rk_types.h>

#include <decomp.h>

#ifdef __cplusplus
extern "C" {
#endif

// PAL: 0x80130070..0x80130100
UNKNOWN_FUNCTION(GKI_init);
// PAL: 0x80130100..0x801301a8
UNKNOWN_FUNCTION(GKI_shutdown);
// PAL: 0x801301a8..0x801301ac
UNKNOWN_FUNCTION(GKI_run);
// PAL: 0x801301ac..0x801301b0
UNKNOWN_FUNCTION(GKI_sched_lock);
// PAL: 0x801301b0..0x801301b4
UNKNOWN_FUNCTION(GKI_sched_unlock);
// PAL: 0x801301b4..0x801301b8
UNKNOWN_FUNCTION(GKI_delay);
// PAL: 0x801301b8..0x8013025c
UNKNOWN_FUNCTION(GKI_send_event);
// PAL: 0x8013025c..0x80130264
UNKNOWN_FUNCTION(GKI_get_taskid);
// PAL: 0x80130264..0x80130288
UNKNOWN_FUNCTION(GKI_enable);
// PAL: 0x80130288..0x801302cc
UNKNOWN_FUNCTION(GKI_disable);
// PAL: 0x801302cc..0x801302d0
UNKNOWN_FUNCTION(GKI_exception);
// PAL: 0x801302d0..0x801302fc
UNKNOWN_FUNCTION(GKI_os_malloc);
// PAL: 0x801302fc..0x80130300
UNKNOWN_FUNCTION(GKI_os_free);

#ifdef __cplusplus
}
#endif