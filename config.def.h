/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]           = "monospace:size=10";
static const char normbgcolor[]         = "#222222";
static const char normbordercolor[]     = "#444444";
static const char normfgcolor[]         = "#bbbbbb";
static const char selfgcolor[]          = "#eeeeee";
static const char selbordercolor[]      = "#770000";
static const char selbgcolor[]          = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor   },
};

// Scratchpads
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = {"telegram-desktop", NULL };
const char *spcmd4[] = {"st", "-n", "spncmpcpp", "-g", "120x34", "-e", "ncmpcpp", NULL };
static Sp scratchpads[] = {
	/* name                  cmd  */
	{"spterm",              spcmd1},
	{"spcalc",              spcmd2},
	{"sptlgrm",             spcmd3},
	{"spncmpcpp",           spcmd4},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class            instance  title           tags mask  iscentered isfloating  isterminal  noswallow  monitor */
    { "Gimp",           NULL,     NULL,           0,         0,         1,          0,           0,        -1 },
    { "firefox",        NULL,     NULL,           1 << 8,    0,         0,          0,          -1,        -1 },
    { "Brave-browser",  NULL,     NULL,           1 << 8,    0,         0,          0,          -1,        -1 },
    { TERMCLASS,             NULL,     NULL,           0,    0,         0,          1,           0,        -1 },
    { NULL,             NULL,     "Event Tester", 0,         0,         0,          0,           1,        -1 }, /* xev */
    // Scratchpads
	{ NULL,		        "spterm",		NULL,	  SPTAG(0),	 1,         1,	        1,	         0,	       -1 },
	{ NULL,		        "spcalc",		NULL,	  SPTAG(1),	 1,         1,	        1,	         0,	       -1 },
	{ NULL,		        "telegram-desktop",	    NULL,     SPTAG(2),	 1,         1,	        0,	         0,	       -1 },
	{ NULL,		        "spncmpcpp",	NULL,     SPTAG(3),	 1,         1,	        1,	         0,	       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Hardware multimedia keys */
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *web[]  = { "brave", NULL };
static const char *mail[]  = { "thunderbird", NULL };
static const char *filemgr[]  = { "pcmanfm", NULL };

/* multimedia keys */
static const char *upvol[]     = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[]   = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *brupcmd[]   = { "/usr/bin/xbacklight", "-inc", "10", NULL };
static const char *brdowncmd[] = { "/usr/bin/xbacklight", "-dec", "10", NULL };

/* playerctl */
static const char *pctlpp[] = { "/usr/bin/playerctl", "--player=mpd", "play-pause", NULL };
static const char *pctln[]  = { "/usr/bin/playerctl", "--player=mpd", "next",       NULL };
static const char *pctlp[]  = { "/usr/bin/playerctl", "--player=mpd", "previous",   NULL };

/* protonvpn */
static const char *pvpn[]  = { "/home/ali/.local/scripts/Vpn", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ ALT,                          XK_Escape, spawn,          SHCMD("toglayout") },
	{ MODKEY,                       XK_r,      spawn,          SHCMD("alacritty -e lf") },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = filemgr } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = web    } },
	{ MODKEY,                       XK_e,      spawn,          {.v = mail   } },
    { MODKEY,                       XK_p,      spawn,          {.v = pctlpp } },
    { MODKEY,                       XK_s,      spawn,          {.v = pctln  } },
    { MODKEY,                       XK_a,      spawn,          {.v = pctlp  } },
    { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = pvpn   } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

    // Vanity-gaps
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY,                       XK_x,      incrgaps,       {.i = -3 } },
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	// { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	// { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	// { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	// { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },

	{ Mod1Mask,                     XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,            	XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_c,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,            	XK_t,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,            	XK_m,	   togglescratch,  {.ui = 3 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0,                            XF86XK_AudioLowerVolume,    spawn,  {.v = downvol  } },
    { 0,                            XF86XK_AudioMute,           spawn,  {.v = mutevol  } },
    { 0,                            XF86XK_AudioRaiseVolume,    spawn,  {.v = upvol    } },
    { 0,                            XF86XK_MonBrightnessUp,     spawn,  {.v = brupcmd  } },
    { 0,                            XF86XK_MonBrightnessDown,   spawn,  {.v = brdowncmd} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

