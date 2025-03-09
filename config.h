/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = { "Comic Code:size=15", "SF Arabic:size=14","Symbols Nerd Font:size=14"};
static const char dmenufont[]  = "Comic Code:size=15";

/*themes/
/* Color definitions */
static const char col_black[]       = "#141423"; // Darkest background
static const char col_white[]       = "#E9E9F4"; // Light foreground
static const char col_gray[]        = "#373760"; // Dark gray accent
static const char col_purple[]      = "#C197FD"; // Purple accent
static const char col_yellow[]      = "#E5C697"; // Yellow accent
static const char col_cyan[]        = "#62D6E8"; // Cyan accent
static const char col_turquoise[]   = "#141423"; // Turquoise accent
static const char col_pink[]        = "#FF6BCB"; // Pink accent
static const char col_lightcyan[]   = "#8BE9FD"; // Light cyan accent
/* Urgent state colors */
static const char urg_fg[]    = "#141423"; // Urgent text color
static const char urg_bg[]    = "#FF6BCB"; // Urgent background color
static const char urg_border[] = "#FF6BCB"; // Urgent border color
/* Status bar colors */
static const char norm_fg[] = "#C197FD"; // Normal text color
static const char norm_bg[] = "#141423"; // Normal background color
static const char sel_fg[]  = "#E5C697"; // Selected text color
static const char sel_bg[]  = "#141423"; // Selected background color
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_purple, col_black, col_gray },       // Normal state (unfocused windows)
    [SchemeSel]  = { col_white, col_turquoise, col_turquoise }, // Selected state (focused window)
    [SchemeUrg]  = { col_pink, col_black, col_pink },        // Urgent state
};



/*sound*/
 static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
 static const char *upvol2[]   = { "/usr/bin/pactl", "set-sink-volume", "alsa_output.usb-TTGK_Technology_Co._Ltd_CX31993_384Khz_HIFI_AUDIO-00.analog-stereo", "+5%",     NULL };
 static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
 static const char *downvol2[] = { "/usr/bin/pactl", "set-sink-volume", "alsa_output.usb-TTGK_Technology_Co._Ltd_CX31993_384Khz_HIFI_AUDIO-00.analog-stereo", "-5%",     NULL };
 static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };


//slock
 static const char *slockcmd[] = { "slock", NULL };
//brightness
 static const char *brightnessup[] = {"sudo", "brillo","-q","-A","5", NULL };
 static const char *brightnessdown[] = { "sudo","brillo","-q", "-U", "5", NULL };
///tagging */
 static const char *tags[] = { " I ", " II ", " III ", " IV ", " V " };
/* Tag colors */
static const char *tagsel[][2] = {

    { "#C197FD", "#141423" }, // Selected tag 1
    { "#E5C697", "#141423" }, // Selected tag 2
    { "#f1f2f8", "#141423" }, // Selected tag 3
    { "#E9E9F4", "#141423" }, // Selected tag 4
    { "#ffffff", "#141423" }, // Selected tag 5

};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title */
{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
 };
/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[@]",      spiral },
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* commands */
static const char *filebrowsercmd[]  = { " ", NULL};
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run" };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[]       = { "librewolf", NULL, "librewolf" };
static const Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_b,      spawn,          SHCMD("xdotool type $(grep -v '^#' ~/.local/share/bookmarks/bookmarks | dmenu -i -l 50 | cut -d' ' -f1)") },
        { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0] } },
        { MODKEY,                       XK_f,      spawn,       {.v = filebrowsercmd } },
        { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd} },
        { MODKEY,                       XK_c,      spawn,       {.v = browser } },
        { MODKEY,                       XK_a,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_h,      setcfact,       {.f = +0.25} },
        { MODKEY,                       XK_l,      setcfact,       {.f = -0.25} },
        { MODKEY,                       XK_o,      setcfact,       {.f =  0.00} },
        { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
        { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,                       XK_x,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_q,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY|ShiftMask,             XK_w,      togglefloating, {0} },
        { 0,                            XK_Print,                   spawn,SHCMD("maim -o -s -d 1 | xclip -selection clipboard -t image/png -i") },
        { MODKEY,                       XK_s,                       spawn,SHCMD("telegram-desktop") },
        { MODKEY,                       XK_z,                       spawn,SHCMD("thorium-browser") },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
        { MODKEY,                       XK_n,      spawn,               {.v = slockcmd } },
        { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
        { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol2 } },
        { 0,                            XF86XK_AudioMute, spawn, {.v = mutevol } },
        { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
        { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol2   } },
        { 0,                            XF86XK_AudioNext, spawn, SHCMD("mpc next") },
        { 0,                            XF86XK_AudioPrev, spawn, SHCMD("mpc prev") },
        { 0,                            XF86XK_AudioPlay, spawn, SHCMD("mpc play") },
        { 0|ShiftMask,                            XF86XK_AudioPlay, spawn, SHCMD("mpc stop") },

        { 0,                            XF86XK_MonBrightnessUp,   spawn,                           {.v = brightnessup} },
        { 0,                            XF86XK_MonBrightnessDown, spawn,                           {.v = brightnessdown} },
        { MODKEY,                       XK_n,      spawn,               {.v = slockcmd } },
	      { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
      	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	      { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
