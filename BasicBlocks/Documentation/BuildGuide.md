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
  ```

### ⚙️ Build Configurations

* **Build Debug with Ninja (MSYS2 GCC):**
  ```powershell
  .\buildV.ps1 -Config Debug -Toolchain Ninja
  ```

* **Build Release with MSVC (Visual Studio 2022):**
  ```powershell
  .\buildV.ps1 -Config Release -Toolchain MSVC
  ```

* **Build All Configurations with Both Toolchains:**
  ```powershell
  .\buildV.ps1 -Config All -Toolchain Both
  ```

### 🔄 Auto Toolchain Detection

* **Let script auto-detect available toolchain (prefers GCC if found, else MSVC):**
  ```powershell
  .\buildV.ps1 -Config Debug -Toolchain Auto
  ```

### 📦 Full Clean + Rebuild

* **Clean everything and rebuild Release with GCC:**
  ```powershell
  .\buildV.ps1 -CleanOnly
  .\buildV.ps1 -Config Release -Toolchain GCC
  ```

---

## ✅ Notes

- All build logs are written to `build.log`.  
- Output binaries are staged into `dist/msvc` and `dist/gcc`.  
- Use `-CleanOnly` before switching toolchains to avoid stale artifacts.  
- The `Auto` mode is useful when you want the script to pick the best available compiler automatically.  
```