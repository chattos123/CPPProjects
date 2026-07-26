# 🔑 VS Code Keybinding Help Guide

This guide documents the custom keybindings configured for this project.  
Place these entries in your `keybindings.json` file (`File → Preferences → Keyboard Shortcuts → Open Keyboard Shortcuts (JSON)`).

---

## 📋 Current Keybindings

```json
[
  {
    "key": "ctrl+alt+d",
    "command": "workbench.action.debug.start"
  },
  {
    "key": "ctrl+alt+r",
    "command": "workbench.action.reloadWindow"
  },
  {
    "key": "ctrl+alt+b",
    "command": "workbench.action.tasks.runTask",
    "args": "Build: All (GCC + MSVC)"
  },
  {
    "key": "ctrl+alt+m",
    "command": "workbench.action.tasks.runTask",
    "args": "Build: MSVC Release"
  },
  {
    "key": "ctrl+alt+g",
    "command": "workbench.action.tasks.runTask",
    "args": "Build: GCC Release"
  },
  {
    "key": "ctrl+alt+c",
    "command": "workbench.action.tasks.runTask",
    "args": "Clean Workspace"
  }
]
