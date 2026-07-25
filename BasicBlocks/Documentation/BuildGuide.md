# Build Guide (`buildV.ps1`)

`buildV.ps1` is the automated build, configuration, and distribution script for this repository. It provides cross-toolchain support for both **GCC / MinGW (Ninja)** and **MSVC (Visual Studio 2022)** across **Debug** and **Release** configurations on Windows.

---

## 🛠 Script Parameters

| Parameter | Type | Default | Allowed Values | Description |
| :--- | :--- | :--- | :--- | :--- |
| `-Config` | `string` | `"All"` | `Debug`, `Release`, `All` | Target CMake build configuration. |
| `-Toolchain` | `string` | `"Both"` | `Ninja`, `MSVC`, `GCC`, `Both`, `Auto` | Selects compiler generator / toolchain. |
| `-CleanOnly` | `switch` | `false` | *N/A* | Cleans all build/dist folders and exits. |

---


## 🚀 Quick Commands

### 🧹 Cleaning

* **Standalone Clean (removes all `build-*` and `dist` folders):**
  ```powershell
  .\buildV.ps1 -CleanOnly