#!/bin/bash

# ==============================================================================
# miniRT Evaluation & Automated Test Runner with Memory Leak Detection
# ==============================================================================

# ANSI Color Codes
RESET="\033[0m"
BOLD="\033[1m"
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
CYAN="\033[36m"
MAGENTA="\033[35m"
BLUE="\033[34m"

LOG_FILE="/tmp/minirt_test_log.txt"
ERR_FILE="/tmp/minirt_err_log.txt"

# Ensure executables exist
check_build() {
    if [ ! -f "./miniRT" ] || [ ! -f "./miniRT_bonus" ]; then
        echo -e "${YELLOW}${BOLD}Building miniRT and miniRT_bonus...${RESET}"
        make && make bonus
        if [ $? -ne 0 ]; then
            echo -e "${RED}${BOLD}Build failed! Please fix compilation errors first.${RESET}"
            exit 1
        fi
        echo -e "${GREEN}Build complete.${RESET}\n"
    fi
}

# Run a single visual test (interactive window + leaks check)
run_visual_test() {
    local exec_bin="$1"
    local scene_file="$2"
    local test_num="$3"
    local total_num="$4"
    local title="$5"
    local desc="$6"

    clear
    echo -e "${CYAN}${BOLD}================================================================================${RESET}"
    echo -e "${CYAN}${BOLD} TEST [${test_num}/${total_num}]: ${title}${RESET}"
    echo -e "${CYAN}${BOLD}================================================================================${RESET}"
    echo -e "${YELLOW}File:${RESET} ${scene_file}"
    echo -e "${YELLOW}Evaluator Note:${RESET} ${desc}"
    echo -e "${BLUE}-------------------------------- Scene Contents --------------------------------${RESET}"
    cat "$scene_file"
    echo -e "${BLUE}--------------------------------------------------------------------------------${RESET}"
    echo -e "${MAGENTA}>> Launching ${exec_bin} with leaks check...${RESET}"
    echo -e "${MAGENTA}>> [Inspect the rendered window, then press ESC or close window to proceed]${RESET}\n"

    # Run executable with leaks checking
    leaks -atExit -- "$exec_bin" "$scene_file" > "$LOG_FILE" 2>&1
    local leak_run_code=$?

    echo -e "${BOLD}--- Test Result ---${RESET}"
    # Check leaks output
    if grep -q "0 leaks for 0 total leaked bytes" "$LOG_FILE"; then
        echo -e "Window Execution:      ${GREEN}PASS (Clean exit)${RESET}"
        echo -e "Memory Leak Check:     ${GREEN}✅ 0 leaks for 0 total leaked bytes [PASS]${RESET}"
    else
        echo -e "Window Execution:      ${YELLOW}Notice (Check leak details below)${RESET}"
        echo -e "Memory Leak Check:     ${RED}❌ LEAKS DETECTED!${RESET}"
        grep -E "leaks for|total leaked bytes" "$LOG_FILE"
    fi

    echo ""
    read -p "👉 Press [ENTER] for next test (or 'q' to return to menu): " choice
    if [ "$choice" = "q" ] || [ "$choice" = "Q" ]; then
        return 1
    fi
    return 0
}

# Run automated error tests with leaks check
run_error_tests() {
    echo -e "\n${CYAN}${BOLD}================================================================================${RESET}"
    echo -e "${CYAN}${BOLD}                    RUNNING ERROR & PARSING TESTS (WITH LEAKS)                  ${RESET}"
    echo -e "${CYAN}${BOLD}================================================================================${RESET}\n"

    local pass_count=0
    local total_count=0

    # 1. Missing arguments test
    total_count=$((total_count + 1))
    ./miniRT > "$ERR_FILE" 2>&1
    local code=$?
    leaks -atExit -- ./miniRT > "$LOG_FILE" 2>&1
    local has_err=$(grep -q "Error" "$ERR_FILE" && echo 1 || echo 0)
    local has_0_leaks=$(grep -q "0 leaks for 0 total leaked bytes" "$LOG_FILE" && echo 1 || echo 0)
    if [ $code -ne 0 ] && [ $has_err -eq 1 ] && [ $has_0_leaks -eq 1 ]; then
        printf "${GREEN}[PASS]${RESET} %-35s (Exit: %d | Msg: OK | Leaks: 0)\n" "missing_argument" "$code"
        pass_count=$((pass_count + 1))
    else
        printf "${RED}[FAIL]${RESET} %-35s (Exit: %d | Msg: %d | Leaks: %d)\n" "missing_argument" "$code" "$has_err" "$has_0_leaks"
    fi

    # 2. Non-existent file
    total_count=$((total_count + 1))
    ./miniRT "does_not_exist.rt" > "$ERR_FILE" 2>&1
    code=$?
    leaks -atExit -- ./miniRT "does_not_exist.rt" > "$LOG_FILE" 2>&1
    has_err=$(grep -q "Error" "$ERR_FILE" && echo 1 || echo 0)
    has_0_leaks=$(grep -q "0 leaks for 0 total leaked bytes" "$LOG_FILE" && echo 1 || echo 0)
    if [ $code -ne 0 ] && [ $has_err -eq 1 ] && [ $has_0_leaks -eq 1 ]; then
        printf "${GREEN}[PASS]${RESET} %-35s (Exit: %d | Msg: OK | Leaks: 0)\n" "non_existent_file" "$code"
        pass_count=$((pass_count + 1))
    else
        printf "${RED}[FAIL]${RESET} %-35s (Exit: %d | Msg: %d | Leaks: %d)\n" "non_existent_file" "$code" "$has_err" "$has_0_leaks"
    fi

    # 3. Test all invalid files in scenes/invalid
    for scene in scenes/invalid/*; do
        total_count=$((total_count + 1))
        local base_name=$(basename "$scene")
        ./miniRT "$scene" > "$ERR_FILE" 2>&1
        code=$?
        leaks -atExit -- ./miniRT "$scene" > "$LOG_FILE" 2>&1
        has_err=$(grep -q "Error" "$ERR_FILE" && echo 1 || echo 0)
        has_0_leaks=$(grep -q "0 leaks for 0 total leaked bytes" "$LOG_FILE" && echo 1 || echo 0)

        if [ $code -ne 0 ] && [ $has_err -eq 1 ] && [ $has_0_leaks -eq 1 ]; then
            printf "${GREEN}[PASS]${RESET} %-35s (Exit: %d | Msg: OK | Leaks: 0)\n" "$base_name" "$code"
            pass_count=$((pass_count + 1))
        else
            printf "${RED}[FAIL]${RESET} %-35s (Exit: %d | Msg: %d | Leaks: %d)\n" "$base_name" "$code" "$has_err" "$has_0_leaks"
            cat "$ERR_FILE"
        fi
    done

    echo -e "\n${BOLD}Error Testing Summary: ${GREEN}${pass_count}/${total_count} Passed.${RESET}\n"
    read -p "Press [ENTER] to continue..."
}

# Run all mandatory visual tests
run_mandatory_tests() {
    local scenes=(
        "scenes/mandatory/01_centered_sphere.rt|Centered Sphere|Sphere at {0,0,0} facing camera. Must be visible without glitching."
        "scenes/mandatory/02_centered_plane.rt|Centered Plane (Z=0)|Plane at {0,0,0} normal {0,0,1}. Must be visible without glitching."
        "scenes/mandatory/03_centered_cylinder.rt|Centered Cylinder (Y-axis)|Cylinder extending along Y-axis. Centered at origin, check rounded caps."
        "scenes/mandatory/04_sphere_translation.rt|Sphere Translation|Two spheres, one translated along camera view axis. Both visible."
        "scenes/mandatory/05_cylinder_rotation_90.rt|Cylinder 90° Rotation|Cylinder rotated 90 degrees along Z-axis (oriented along X-axis)."
        "scenes/mandatory/06_camera_x_axis.rt|Camera +X Axis|Camera on +X axis looking towards origin {0,0,0}."
        "scenes/mandatory/07_camera_y_axis.rt|Camera +Y Axis (Gimbal Lock Check)|Camera looking straight down Y-axis towards {0,0,0}."
        "scenes/mandatory/08_camera_z_axis.rt|Camera +Z Axis|Camera on +Z axis looking towards origin {0,0,0}."
        "scenes/mandatory/09_camera_random_diagonal.rt|Camera Random Diagonal|Camera placed at non-axis diagonal point looking at {0,0,0}."
        "scenes/mandatory/10_sphere_lit_sideways.rt|Sphere Lit Sideways|Light spot placed sideways to sphere. Shading must show smooth transition."
        "scenes/mandatory/11_sphere_trans_lit_sideways.rt|Translated Sphere Lit Sideways|Halo of light must be computed after translation."
        "scenes/mandatory/12_vertical_spot_plane_shadow.rt|Vertical Spot & Plane Shadow|Vertical light over sphere casting shadow onto plane."
        "scenes/mandatory/13_shadows_onto_other_objects.rt|Shadows on Multiple Objects|Complex scene with shadows falling on plane and cylinder."
        "scenes/mandatory/14_intersecting_objects.rt|Intersecting Objects|Sphere and cylinder intersecting cleanly without glitching."
        "scenes/mandatory/15_multiple_of_each_shape.rt|Multi-Objects of Each Shape|Two spheres, two cylinders, and plane in one scene."
    )

    local total=${#scenes[@]}
    local idx=1

    for item in "${scenes[@]}"; do
        IFS="|" read -r file title desc <<< "$item"
        run_visual_test "./miniRT" "$file" "$idx" "$total" "$title" "$desc"
        if [ $? -ne 0 ]; then
            break
        fi
        idx=$((idx + 1))
    done
}

# Run all bonus visual tests
run_bonus_tests() {
    local scenes=(
        "scenes/bonus/01_specular_sphere.rt|Bonus 1: Specular Reflection|Phong specular highlight on shiny sphere with power 32."
        "scenes/bonus/02_checkerboard_plane.rt|Bonus 2: Checkerboard Pattern|Alternating black & white checkered plane (stabilized, no acne)."
        "scenes/bonus/03_multi_colored_lights.rt|Bonus 3: Multi-Spot Colored Lights|Red and blue light sources producing colored highlights & mixed shadows."
        "scenes/bonus/04_final_bonus_combined.rt|Bonus 4: Combined Feature Scene|Specular sphere, multi-colored lights, and checkerboard floor."
    )

    local total=${#scenes[@]}
    local idx=1

    for item in "${scenes[@]}"; do
        IFS="|" read -r file title desc <<< "$item"
        run_visual_test "./miniRT_bonus" "$file" "$idx" "$total" "$title" "$desc"
        if [ $? -ne 0 ]; then
            break
        fi
        idx=$((idx + 1))
    done
}

# Run single file directly
run_custom_file() {
    local file="$1"
    if [ ! -f "$file" ]; then
        echo -e "${RED}File '$file' not found!${RESET}"
        exit 1
    fi
    local exec_bin="./miniRT"
    if [[ "$file" == *"bonus"* ]]; then
        exec_bin="./miniRT_bonus"
    fi
    run_visual_test "$exec_bin" "$file" 1 1 "Custom Scene" "User provided scene: $file"
}

# Main Execution Flow
check_build

if [ "$1" = "mandatory" ]; then
    run_mandatory_tests
    exit 0
elif [ "$1" = "bonus" ]; then
    run_bonus_tests
    exit 0
elif [ "$1" = "error" ]; then
    run_error_tests
    exit 0
elif [ "$1" = "all" ]; then
    run_error_tests
    run_mandatory_tests
    run_bonus_tests
    exit 0
elif [ -n "$1" ]; then
    run_custom_file "$1"
    exit 0
fi

# Interactive Menu
while true; do
    clear
    echo -e "${CYAN}${BOLD}================================================================================${RESET}"
    echo -e "${CYAN}${BOLD}                    miniRT Interactive Evaluation Tester                        ${RESET}"
    echo -e "${CYAN}${BOLD}================================================================================${RESET}"
    echo -e " ${BOLD}1)${RESET} Run Mandatory Visual Tests     (15 scenes, interactive window + leaks)"
    echo -e " ${BOLD}2)${RESET} Run Bonus Visual Tests         (4 scenes: specular, checkerboard, lights)"
    echo -e " ${BOLD}3)${RESET} Run Error & Parsing Tests       (23 automated edge-cases + leaks check)"
    echo -e " ${BOLD}4)${RESET} Run All Tests Sequentially     (Full Evaluation Protocol)"
    echo -e " ${BOLD}5)${RESET} Run Norminette Check           (All source & header files)"
    echo -e " ${BOLD}q)${RESET} Quit"
    echo -e "${CYAN}================================================================================${RESET}"
    read -p "Select an option [1-5, q]: " opt

    case "$opt" in
        1) run_mandatory_tests ;;
        2) run_bonus_tests ;;
        3) run_error_tests ;;
        4)
            run_error_tests
            run_mandatory_tests
            run_bonus_tests
            ;;
        5)
            clear
            echo -e "${CYAN}${BOLD}Running Norminette...${RESET}\n"
            /Users/celeste/.local/bin/norminette srcs includes bonus libft
            echo ""
            read -p "Press [ENTER] to return to menu..."
            ;;
        q|Q)
            echo -e "${GREEN}Goodbye!${RESET}"
            rm -f "$LOG_FILE" "$ERR_FILE"
            exit 0
            ;;
        *)
            echo -e "${RED}Invalid option!${RESET}"
            sleep 1
            ;;
    esac
done
