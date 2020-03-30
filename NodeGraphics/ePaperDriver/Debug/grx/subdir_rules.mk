################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
grx/%.obj: ../grx/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/andres/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/utils" --include_path="/home/andres/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="/home/andres/Documents/EMBT/FinalProject/EmbeddedIOTProject/NodeGraphics/ePaperDriver" --include_path="/home/andres/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power="all" --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="grx/$(basename $(<F)).d_raw" --obj_directory="grx" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


