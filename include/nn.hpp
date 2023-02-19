#pragma once

/* nnSdk is only available when loaded as a module. */
#ifndef EXL_AS_MODULE
#error "Cannot use nnSdk when not as a module!"
#endif

#include "nn/result.h"
#include "nn/fs.h"
#include "nn/os.h"
#include "nn/hid.h"