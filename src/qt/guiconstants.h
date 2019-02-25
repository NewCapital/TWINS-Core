// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The TWINS developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_GUICONSTANTS_H
#define BITCOIN_QT_GUICONSTANTS_H

/* Milliseconds between model updates */
static const int MODEL_UPDATE_DELAY = 1000;

/* AskPassphraseDialog -- Maximum passphrase length */
static const int MAX_PASSPHRASE_SIZE = 1024;

/* TWINS GUI -- Size of icons in status bar */
static const int STATUSBAR_ICONSIZE = 16;

static const bool DEFAULT_SPLASHSCREEN = true;

/* Invalid field background style */
#define STYLE_INVALID "background:#FF8080"

/* Transaction list -- unconfirmed transaction */
// Note: old value - #define COLOR_UNCONFIRMED QColor(91, 76, 134)
// Note: old value (default style) - #define COLOR_UNCONFIRMED QColor(140, 140, 140)
#define COLOR_UNCONFIRMED QColor(255, 255, 255)
/* Transaction list -- negative amount */
//Note: old value - #define COLOR_NEGATIVE QColor(206, 0, 188)
#define COLOR_NEGATIVE QColor(255, 255, 255)
/* Transaction list -- bare address (without label) */
//Note: old value - #define COLOR_BAREADDRESS QColor(140, 140, 140)
#define COLOR_BAREADDRESS QColor(255, 255, 255)
/* Transaction list -- TX status decoration - open until date */
//Note: old value - #define COLOR_TX_STATUS_OPENUNTILDATE QColor(64, 64, 255)
#define COLOR_TX_STATUS_OPENUNTILDATE QColor(255, 255, 255)
/* Transaction list -- TX status decoration - offline */
//Note: old value - #define COLOR_TX_STATUS_OFFLINE QColor(192, 192, 192)
#define COLOR_TX_STATUS_OFFLINE QColor(255, 255, 255)
/* Transaction list -- TX status decoration - default color */
//Note: old value - #define COLOR_BLACK QColor(51, 51, 51)
#define COLOR_BLACK QColor(255, 255, 255)
/* Transaction list -- TX status decoration - conflicted */
//Note: old value - #define COLOR_CONFLICTED QColor(255, 0, 0)
#define COLOR_CONFLICTED QColor(255, 255, 255)
/* Transaction list -- TX status decoration - orphan (Light Gray #D3D3D3) */
//Note: old value - #define COLOR_ORPHAN QColor(211, 211, 211)
#define COLOR_ORPHAN QColor(255, 255, 255)
/* Transaction list -- TX status decoration - stake (BlueViolet #8A2BE2) */
//Note: old value - #define COLOR_STAKE QColor(138,43,226)
#define COLOR_STAKE QColor(255, 255, 255)
/* Tooltips longer than this (in characters) are converted into rich text,
   so that they can be word-wrapped.
 */
static const int TOOLTIP_WRAP_THRESHOLD = 80;

/* Maximum allowed URI length */
static const int MAX_URI_LENGTH = 255;

/* QRCodeDialog -- size of exported QR Code image */
#define EXPORT_IMAGE_SIZE 256

/* Number of frames in spinner animation */
#define SPINNER_FRAMES 35

#define QAPP_ORG_NAME "TWINS"
#define QAPP_ORG_DOMAIN "win.win"
#define QAPP_APP_NAME_DEFAULT "TWINS-Qt"
#define QAPP_APP_NAME_TESTNET "TWINS-Qt-testnet"

#endif // BITCOIN_QT_GUICONSTANTS_H
