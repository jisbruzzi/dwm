/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10","FontAwesome:size=10"};
static const char dmenufont[]       = "FontAwesome:size=10";

static const char S_base03[]   = "#002b36";
static const char S_base02[]   = "#073642";
static const char S_base01[]   = "#586e75";
static const char S_base00[]   = "#657b83";
static const char S_base0[]    = "#839496";
static const char S_base1[]    = "#93a1a1";
static const char S_base2[]    = "#eee8d5";
static const char S_base3[]    = "#fdf6e3";
static const char S_yellow[]   = "#b58900";
static const char S_orange[]   = "#cb4b16";
static const char S_red[]      = "#dc322f";
static const char S_magenta[]  = "#d33682";
static const char S_violet[]   = "#6c71c4";
static const char S_blue[]     = "#268bd2";
static const char S_cyan[]     = "#2aa198";
static const char S_green[]    = "#859900";


static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { S_base1, S_base03, S_base03 },
	[SchemeSel]  = { S_base1, S_base02,  S_base02  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance        title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,           NULL,       0,            1,           -1 },
	{ "Spotify",  NULL,  	      NULL,       1 << 8,       1,           -1 },
	{ "Firefox",  NULL,  	      NULL,       1 << 8,       1,           -1 },
	{ NULL,       NULL,     "WhatsApp",       1 << 7,       1,           -1 },
	{ NULL,       NULL, "Telegram Web",       1 << 7,       1,           -1 },
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
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "HHH",      grid },
	{ NULL,      NULL },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[] = {
	"rofi",
	"-show", "run",
	"-show-icons",
	"-run-command","/bin/bash -i -c '{cmd}'"
};

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,		spawn,          {.v = roficmd } },
	{ MODKEY,             			XK_t, 		spawn,          SHCMD("alacritty") },
	{ MODKEY | ShiftMask,           XK_t, 		spawn,          SHCMD("dir_rofi 'alacritty --working-directory '") },
	{ MODKEY,             			XK_c, 		spawn,          SHCMD("xfe") },
	{ MODKEY | ShiftMask,           XK_c, 		spawn,          SHCMD("dir_rofi xfe") },
	{ MODKEY,             			XK_g, 		spawn,          SHCMD("google-chrome") },
	{ 0,		XF86XK_MonBrightnessUp, 		spawn,          SHCMD("xbacklight -inc 3") },
	{ 0,		XF86XK_MonBrightnessDown, 		spawn,          SHCMD("xbacklight -dec 3") },
	{ 0,		XF86XK_AudioLowerVolume, 		spawn,          SHCMD("pactl set-sink-volume 0 -5% ") },
	{ 0,		XF86XK_AudioRaiseVolume, 		spawn,          SHCMD("pactl set-sink-volume 0 +5% ") },
	{ 0,		XF86XK_AudioMute, 		    	spawn,          SHCMD("pactl set-sink-mute 0 toggle") },
	{ MODKEY,                       XK_b,       togglebar,      {0} },
	{ MODKEY,                       XK_Down,    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_plus,   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY|ControlMask,           XK_Right,           shiftview,  { .i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,           	shiftview,  { .i = -1 } },

	{ MODKEY|ControlMask,           XK_Up,           shiftlast,  { .i = +1 } },
	{ MODKEY|ControlMask,           XK_Down,           	shiftlast,  { .i = -1 } },

	{ MODKEY,           XK_Page_Down,           shiftview,  { .i = +1 } },
	{ MODKEY,           XK_Page_Up,           	shiftview,  { .i = -1 } },


	/*
	{ MODKEY,             			XK_F1, 		spawn,          SHCMD("xdotool key F1") },
	{ MODKEY,             			XK_F2, 		spawn,          SHCMD("xdotool key F2") },

	{ 0,             			XK_F2, 		shiftview,          { .i = +1 } },
	{ 0,             			XK_F1, 		shiftview,          { .i = -1 } },
	*/

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	TAGKEYS(                        XK_KP_1,                   0)
	TAGKEYS(                        XK_KP_2,                   1)
	TAGKEYS(                        XK_KP_3,                   2)
	TAGKEYS(                        XK_KP_4,                   3)
	TAGKEYS(                        XK_KP_5,                   4)
	TAGKEYS(                        XK_KP_6,                   5)
	TAGKEYS(                        XK_KP_7,                   6)
	TAGKEYS(                        XK_KP_8,                   7)
	TAGKEYS(                        XK_KP_9,                   8)

	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },

	{ MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },

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

