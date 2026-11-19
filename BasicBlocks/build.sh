#!/usr/bin/env bash
set -euo pipefail

# -------------------------------------------------------------------
# Automated build, configuration, and packaging script for Linux.
# Mirrors build.ps1 for GCC / Clang toolchains in Debug and/or Release.
# -------------------------------------------------------------------

CONFIG="All"
TOOLCHAIN="GCC"
CLEAN_ONLY=false
CONFIGURE_ONLY=false

# ANSI colors
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
MAGENTA='\033[0;35m'
GRAY='\033[0;90m'
RED='\033[0;31m'
NC='\033[0m'

show_help() {
    cat <<EOF
Usage: ./build.sh [OPTIONS]

Automated build, configuration, and packaging script for C++ projects on Linux.

Options:
  -c, --config <Debug|Release|All>
      Specifies the build configuration. Default: All

  -t, --toolchain <GCC|Clang|Both|Ninja|Auto>
      Specifies the compiler/generator toolchain. Default: GCC
      (Uses Ninja if installed, otherwise falls back to Unix Makefiles.)

  --clean-only
      Cleans all build output directories ('build-*', 'dist', 'build.log') and exits.

  --configure-only
      Runs the CMake configure step only (skips build and install).

  -h, --help
      Displays this help message and exits.

Examples:
  ./build.sh -c Debug -t GCC
  ./build.sh -c Release -t Clang
  ./build.sh -c All -t Both
  ./build.sh --clean-only
EOF
}

# -------------------------------------------------------------------
# 1. Parse Command-Line Arguments
# -------------------------------------------------------------------
while [[ $# -gt 0 ]]; do
    case "$1" in
        -c|--config)
            [[ $# -lt 2 ]] && { echo -e "${RED}Error: Missing value for $1${NC}"; exit 1; }
            CONFIG="$2"
            shift 2
            ;;
        -t|--toolchain)
            [[ $# -lt 2 ]] && { echo -e "${RED}Error: Missing value for $1${NC}"; exit 1; }
            TOOLCHAIN="$2"
            shift 2
            ;;
        --clean-only)
            CLEAN_ONLY=true
            shift
            ;;
        --configure-only)
            CONFIGURE_ONLY=true
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            show_help
            exit 1
            ;;
    esac
done

case "$CONFIG" in
    Debug|Release|All) ;;
    *)
        echo -e "${RED}Invalid --config '$CONFIG'. Expected: Debug, Release, or All.${NC}"
        exit 1
        ;;
esac

case "$TOOLCHAIN" in
    GCC|Clang|Both|Ninja|Auto) ;;
    *)
        echo -e "${RED}Invalid --toolchain '$TOOLCHAIN'. Expected: GCC, Clang, Both, Ninja, or Auto.${NC}"
        exit 1
        ;;
esac

# -------------------------------------------------------------------
# 2. Standalone Clean Routine
# -------------------------------------------------------------------
FOLDERS_TO_CLEAN=(
    "build-debug"
    "build-release"
    "build-clang-debug"
    "build-clang-release"
    "dist"
)

perform_clean() {
    echo -e "${CYAN}=== Cleaning build directories ===${NC}"
    for folder in "${FOLDERS_TO_CLEAN[@]}"; do
        if [[ -d "$folder" ]]; then
            echo -e "${GRAY}Removing: $folder${NC}"
            rm -rf "$folder"
        fi
    done
    if [[ -f "build.log" ]]; then
        rm -f "build.log"
    fi
}

if [[ "$CLEAN_ONLY" == true ]]; then
    perform_clean
    echo -e "${GREEN}=== Clean complete! No build performed. ===${NC}"
    exit 0
fi

# -------------------------------------------------------------------
# 3. Standard Build Execution
# -------------------------------------------------------------------
perform_clean

VERSION="$(date +"%Y.%m.%d.%H%M")"
echo -e "\n${CYAN}=== Using version stamp: $VERSION ===${NC}"

# Pick Ninja if available, else fall back to Unix Makefiles
pick_generator() {
    if command -v ninja >/dev/null 2>&1; then
        echo "Ninja"
    else
        echo "Unix Makefiles"
    fi
}

run_build() {
    local build_type="$1"
    local folder="$2"
    local target_toolchain="$3"

    local gen_args=()
    local dist_subdir="gcc"

    case "$target_toolchain" in
        GCC)
            gen_args+=(-G "$(pick_generator)" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++)
            dist_subdir="gcc"
            ;;
        Clang)
            gen_args+=(-G "$(pick_generator)" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++)
            dist_subdir="clang"
            ;;
        Ninja)
            gen_args+=(-G "Ninja")
            dist_subdir="gcc"
            ;;
        Auto)
            dist_subdir="gcc"
            ;;
    esac

    local dist_bin_abs_path="$(pwd)/dist/${dist_subdir}/bin"

    echo -e "\n${YELLOW}=== Configuring ${build_type} [${target_toolchain}] -> ${folder} ===${NC}"
    local config_cmd=(cmake "${gen_args[@]}" -B "$folder" -DCMAKE_BUILD_TYPE="$build_type" -DPROJECT_VERSION="$VERSION")
    echo -e "${GRAY}>> ${config_cmd[*]}${NC}"
    "${config_cmd[@]}" 2>&1 | tee -a build.log

    if [[ "$CONFIGURE_ONLY" == true ]]; then
        echo -e "${MAGENTA}=== ConfigureOnly mode: skipping build/install ===${NC}"
        return
    fi

    echo -e "\n${YELLOW}=== Building ${build_type} [${target_toolchain}] ===${NC}"
    local build_cmd=(cmake --build "$folder" --config "$build_type" --parallel)
    echo -e "${GRAY}>> ${build_cmd[*]}${NC}"
    "${build_cmd[@]}" 2>&1 | tee -a build.log

    echo -e "\n${YELLOW}=== Installing ${build_type} [${target_toolchain}] -> ${dist_bin_abs_path} ===${NC}"
    local install_cmd=(cmake --install "$folder" --config "$build_type" --prefix "$dist_bin_abs_path")
    echo -e "${GRAY}>> ${install_cmd[*]}${NC}"
    "${install_cmd[@]}" 2>&1 | tee -a build.log
}

dispatch_builds() {
    local toolchain_type="$1"
    local prefix="$2"

    if [[ "$CONFIG" == "Debug" || "$CONFIG" == "All" ]]; then
        run_build "Debug" "${prefix}-debug" "$toolchain_type"
    fi
    if [[ "$CONFIG" == "Release" || "$CONFIG" == "All" ]]; then
        run_build "Release" "${prefix}-release" "$toolchain_type"
    fi
}

# -------------------------------------------------------------------
# 4. Execute Configurations
# -------------------------------------------------------------------
if [[ "$TOOLCHAIN" == "Both" ]]; then
    dispatch_builds "GCC" "build"
    dispatch_builds "Clang" "build-clang"
elif [[ "$TOOLCHAIN" == "Clang" ]]; then
    dispatch_builds "Clang" "build-clang"
else
    dispatch_builds "$TOOLCHAIN" "build"
fi

echo -e "\n${GREEN}=======================================================${NC}"
echo -e "${GREEN}=== Build + Install complete! ===${NC}"
echo -e "${GREEN}GCC binaries staged at:   $(pwd)/dist/gcc/bin${NC}"
echo -e "${GREEN}Clang binaries staged at: $(pwd)/dist/clang/bin${NC}"
echo -e "${GREEN}Log file written to:      $(pwd)/build.log${NC}"
echo -e "${GREEN}=======================================================${NC}"