// Copyright 2022 vuchvu (@vuchvu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 6
#define MATRIX_COLS 3

#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7, E6 }
#define MATRIX_COL_PINS { B3, B2, B6 }
#define UNUSED_PINS { D3, D2, B4, B5, B1, F7, F6, F5, F4 }

#define DIODE_DIRECTION COL2ROW

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
