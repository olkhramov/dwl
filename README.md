My build of [dwl](https://codeberg.org/dwl/dwl) - patched with vanity gaps, custom floating windows, rotatable clients, and client opacity focus from [dwl's patches](https://codeberg.org/dwl/dwl-patches).

Development happens on the `personal-patches` branch.

## Patches / features added

- **scratchpad**: dropdown/scratchpad terminal toggled with `mod+grave` (spawns `foot --app-id=scratchpad`).
- **focusonactivate**: xdg activation requests focus the requesting client instead of only marking urgency.
- **smartborders**: borders are hidden when only one non-floating/non-fullscreen window is visible on a monitor.
- **autostart**: runs `~/.local/share/dwl/autostart.sh` once at startup if it exists and is executable.
- **hidecursor**: hides the cursor after a configurable period of inactivity and restores it on pointer/keyboard activity.

## Look & feel

- Nord-inspired color palette.
- 2px window borders, 8px inner gaps, 16px outer gaps.
- Keybindings include scratchpad toggle, `wofi` launcher/runner, media/brightness keys, and the existing vanity-gaps/opacity controls.
