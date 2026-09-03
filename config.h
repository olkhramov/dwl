/*
 * bread's dwl configuration
 *
 * Applied patches:
 *   - rotate clients
 *   - vanity-gaps 0.7
 *   - client opacity focus
 *   - custom float
 *   - autostart
 *   - smart borders
 *   - hide cursor
 */

/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }

/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if its surface isn't visible */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const int monoclegaps               = 0;  /* 1 means outer gaps in monocle layout */
static const int smartborders              = 1;  /* 1 means no borders when there is only one visible window */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const unsigned int gappih           = 8;  /* horiz inner gap between windows */
static const unsigned int gappiv           = 8;  /* vert inner gap between windows */
static const unsigned int gappoh           = 16; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 16; /* vert outer gap between windows and screen edge */

/* Catppuccin Mocha palette (matches owlbar). Mutable (not const): SIGUSR1
 * overwrites these in place from ~/.config/xresources/theme (see
 * readthemecolor() in dwl.c) - color0/8/4/1, same colorN convention dwm's
 * own Xresources-based reload uses, so `set-theme <name>` retheme both
 * dwm and dwl (and owlbar/owlbar-wl) in step. */
static float rootcolor[4]             = COLOR(0x1e1e2eff);
static float bordercolor[4]           = COLOR(0x313244ff);
static float focuscolor[4]            = COLOR(0x89b4faff);
static float urgentcolor[4]           = COLOR(0xf38ba8ff);

/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static const int respect_monitor_reserved_area = 0;  /* 1 to monitor center while respecting the monitor's reserved area, 0 to monitor center */
static const float default_opacity_unfocus = 0.9f;
static const float default_opacity_focus   = 1.0f;
static const int focusonactivate           = 1;  /* 1 means focus the client on activate requests */

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {
	/* app_id  title  tags mask  isfloating  alpha unfocus  monitor x y w h */
	/* examples: */
	{ "EXAMPLE",  NULL,       0,       1,      default_opacity_unfocus, -1 },
	{ "ghostty",  NULL,       0,       0,      0.75,    -1 },
	{ "ghostty", "fzf",       0,       1,      1,       -1, 310, 200, 1300, 0.4},
	{ "ghostty", "menu",      0,       1,      1,       -1, 710, 300, 500, 0.35},
	{ "scratchpad", NULL,     0,       1,      0.9,     -1, 200, 100, 0.8f, 0.7f},
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=" , tile },
	{ "><>", NULL },    /* no layout function means floating behavior */
	{ "[M]" , monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
 */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor: */
	{ "eDP-1_example",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	{ NULL,                 0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* .layout/.variant here are only the compiled-in fallback if
	 * ~/.config/kblayouts is missing/unreadable - loadkblayouts()
	 * (dwl.c) reads that file at startup and overrides them when
	 * present, giving printstatus() (dwl.c) whatever layouts are
	 * configured there to report on the bar. Switching between them is
	 * grp:win_space_toggle (Super+Space) below - a real XKB action
	 * compiled into the keymap, processed by the same key-event path as
	 * every other keystroke. An earlier hand-rolled version drove the
	 * switch imperatively from C (wlr_keyboard_notify_modifiers, bound
	 * to Super+Shift+S) instead of through the keymap: that forced state
	 * silently got clobbered by the very next real key event (e.g.
	 * releasing Super), because xkb_state_update_key() - what every
	 * physical keypress goes through - recomputes the whole state from
	 * the currently-held keys and the keymap's own compiled actions, not
	 * from whatever an external xkb_state_update_mask() call last poked
	 * in. A grp: option doesn't have this problem: it changes the group
	 * *through* xkb_state_update_key() in the first place. */
	.layout = "us,fr",
	.options = "ctrl:nocaps,grp:win_space_toggle",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

/* You can choose between:
 * LIBINPUT_CONFIG_SCROLL_NO_SCROLL
 * LIBINPUT_CONFIG_SCROLL_2FG
 * LIBINPUT_CONFIG_SCROLL_EDGE
 * LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
 */
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
 * LIBINPUT_CONFIG_CLICK_METHOD_NONE
 * LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
 * LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
 */
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
 * LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
 * LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
 * LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
 */
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
 * LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
 * LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
 */
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
 * LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
 * LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
 */
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

static const int cursor_timeout = 5; /* seconds before hiding the cursor on inactivity */

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *term[] = { "ghostty", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *scratchpad_id = "scratchpad";
static const char *scratchpadcmd[] = { "ghostty", "--app-id=scratchpad", NULL };
static const char *launcher[] = { "wmenu-drun", NULL };
static const char *runner[] = { "wmenu-run-styled", NULL };
static const char *filecmd[] = { "ghostty", "-e", "lfub", NULL };
static const char *renewcmd[] = { "dwl-renew", NULL };
static const char *restartbarcmd[] = { "dwl-restart-bar", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */

	/* core programs */
	{ MODKEY,                    XKB_KEY_w,          spawn,          {.v = browser} },
	{ MODKEY,                    XKB_KEY_e,          spawn,          {.v = (const char*[]){ "emacs-open", NULL } } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_E,          spawn,          {.v = (const char*[]){ "org", NULL } } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_e,          spawn,          {.v = (const char*[]){ "org", "agenda", NULL } } },
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_E, spawn, {.v = (const char*[]){ "org", "capture", NULL } } },
	{ MODKEY,                    XKB_KEY_Escape,      spawn,          {.v = (const char*[]){ "noticenter", NULL } } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Escape,      spawn,          {.v = (const char*[]){ "notif-dnd", NULL } } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_X,          spawn,          SHCMD("lockscreen") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          spawn,          SHCMD("clipboard-menu") },
	{ 0,                         XKB_KEY_Print,      spawn,          {.v = (const char*[]){ "screenshot", NULL } } },
	{ WLR_MODIFIER_SHIFT,        XKB_KEY_Print,      spawn,          {.v = (const char*[]){ "screenshot", "full", NULL } } },
	{ MODKEY,                    XKB_KEY_r,          spawn,          {.v = filecmd} },
	{ MODKEY,                    XKB_KEY_Return,     spawn,          {.v = term} },
	{ MODKEY,                    XKB_KEY_d,          spawn,          {.v = launcher} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_D,          spawn,          {.v = runner} },
	{ MODKEY,                    XKB_KEY_BackSpace,  spawn,          {.v = (const char*[]){ "wmenu-sysact", NULL } } },
	{ MODKEY,                    XKB_KEY_n,          spawn,          {.v = (const char*[]){ "ghostty", "-e", "newsboat", NULL } } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_N,          spawn,          {.v = (const char*[]){ "quote-capture", NULL } } },
	{ MODKEY,                    XKB_KEY_F1,         spawn,          SHCMD("groff -mom /home/entekka/.local/share/shortcuts-dwl.mom -T pdf | zathura -") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F1,         spawn,          {.v = (const char*[]){ "lima-readme", NULL } } },
	{ MODKEY,                    XKB_KEY_F3,         spawn,          {.v = (const char*[]){ "wmenu-display", NULL } } },
	{ MODKEY,                    XKB_KEY_F9,         spawn,          {.v = (const char*[]){ "wmenu-mount", NULL } } },
	{ MODKEY,                    XKB_KEY_F10,        spawn,          {.v = (const char*[]){ "wmenu-unmount", NULL } } },

	/* media controls */
	{ MODKEY,                    XKB_KEY_Insert,     spawn,          SHCMD("mpc prev") },
	{ MODKEY,                    XKB_KEY_Prior,      spawn,          SHCMD("mpc next") },
	{ MODKEY,                    XKB_KEY_Scroll_Lock, spawn,         SHCMD("mpc toggle") },

	/* client and tag management */
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_J,          rotate_clients, {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_K,          rotate_clients, {.i = -1} },

	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },

	{ MODKEY,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Tab,        spawn,          SHCMD("palette") },
	{ MODKEY,                    XKB_KEY_q,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_g,          setlayout,      {0} },
	{ MODKEY,                    XKB_KEY_f,          togglefullscreen, {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,          togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_grave,      togglescratchpad, {.v = scratchpadcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_grave,      spawn,          SHCMD("emoji") },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_grave,      spawn,          SHCMD("emoji type") },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },

	/* monitors */
	{ MODKEY,                    XKB_KEY_backslash,  focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_bar,        tagmon,         {.i = WLR_DIRECTION_LEFT} },

	/* client opacity focus */
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_k,          setopacityunfocus, {.f = +0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_j,          setopacityunfocus, {.f = -0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_K, setopacityfocus, {.f = +0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_J, setopacityfocus, {.f = -0.1f} },

	/* vanity gaps */
	{ MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_h,          incgaps,        {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_l,          incgaps,        {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,   XKB_KEY_H,      incogaps,       {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,   XKB_KEY_L,      incogaps,       {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL,    XKB_KEY_h,      incigaps,       {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL,    XKB_KEY_l,      incigaps,       {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_0,          togglegaps,     {0} },
	{ MODKEY|WLR_MODIFIER_LOGO|WLR_MODIFIER_SHIFT,   XKB_KEY_parenright, defaultgaps, {0} },
	{ MODKEY,                    XKB_KEY_y,          incohgaps,      {.i = +1 } },
	{ MODKEY,                    XKB_KEY_o,          incohgaps,      {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_y,          incovgaps,      {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_o,          incovgaps,      {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_y,          incihgaps,      {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_LOGO,  XKB_KEY_o,          incihgaps,      {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Y,          incivgaps,      {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_O,          incivgaps,      {.i = -1 } },

	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),

	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_Q, spawn, {.v = renewcmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_B,          spawn,          {.v = restartbarcmd} },

	/* media/function keys */
	{ 0, XKB_KEY_XF86AudioMute,          spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
	{ 0, XKB_KEY_XF86AudioRaiseVolume,   spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+") },
	{ 0, XKB_KEY_XF86AudioLowerVolume,   spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-") },
	{ 0, XKB_KEY_XF86MonBrightnessUp,    spawn, SHCMD("brightnessctl set +5%") },
	{ 0, XKB_KEY_XF86MonBrightnessDown,  spawn, SHCMD("brightnessctl set 5%-") },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
