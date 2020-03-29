################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/andres/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/json_MSP_EXP432P401R_tirtos_ccs" --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/json_MSP_EXP432P401R_tirtos_ccs/Debug" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="/home/andres/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/json_MSP_EXP432P401R_tirtos_ccs/Debug/syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-876835153:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-876835153-inproc

build-876835153-inproc: ../json.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: System Configuration Tool'
	"/home/andres/ti/ccsv8/tools/node/node" "/home/andres/ti/ccsv8/utils/sysconfig/cli.js" -s "/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/Board.c: build-876835153 ../json.syscfg
syscfg/Board.h: build-876835153
syscfg/: build-876835153

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/andres/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/json_MSP_EXP432P401R_tirtos_ccs" --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/json_MSP_EXP432P401R_tirtos_ccs/Debug" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="/home/andres/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/json_MSP_EXP432P401R_tirtos_ccs/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


