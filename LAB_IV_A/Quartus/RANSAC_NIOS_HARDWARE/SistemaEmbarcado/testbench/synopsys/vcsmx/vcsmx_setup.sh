
# (C) 2001-2023 Altera Corporation. All rights reserved.
# Your use of Altera Corporation's design tools, logic functions and 
# other software and tools, and its AMPP partner logic functions, and 
# any output files any of the foregoing (including device programming 
# or simulation files), and any associated documentation or information 
# are expressly subject to the terms and conditions of the Altera 
# Program License Subscription Agreement, Altera MegaCore Function 
# License Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by Altera 
# or its authorized distributors. Please refer to the applicable 
# agreement for further details.

# ACDS 18.1 625 win32 2023.07.18.18:22:15

# ----------------------------------------
# vcsmx - auto-generated simulation script

# ----------------------------------------
# This script provides commands to simulate the following IP detected in
# your Quartus project:
#     SistemaEmbarcado_tb
# 
# Altera recommends that you source this Quartus-generated IP simulation
# script from your own customized top-level script, and avoid editing this
# generated script.
# 
# To write a top-level shell script that compiles Altera simulation libraries 
# and the Quartus-generated IP in your project, along with your design and
# testbench files, copy the text from the TOP-LEVEL TEMPLATE section below
# into a new file, e.g. named "vcsmx_sim.sh", and modify text as directed.
# 
# You can also modify the simulation flow to suit your needs. Set the
# following variables to 1 to disable their corresponding processes:
# - SKIP_FILE_COPY: skip copying ROM/RAM initialization files
# - SKIP_DEV_COM: skip compiling the Quartus EDA simulation library
# - SKIP_COM: skip compiling Quartus-generated IP simulation files
# - SKIP_ELAB and SKIP_SIM: skip elaboration and simulation
# 
# ----------------------------------------
# # TOP-LEVEL TEMPLATE - BEGIN
# #
# # QSYS_SIMDIR is used in the Quartus-generated IP simulation script to
# # construct paths to the files required to simulate the IP in your Quartus
# # project. By default, the IP script assumes that you are launching the
# # simulator from the IP script location. If launching from another
# # location, set QSYS_SIMDIR to the output directory you specified when you
# # generated the IP script, relative to the directory from which you launch
# # the simulator. In this case, you must also copy the generated library
# # setup "synopsys_sim.setup" into the location from which you launch the
# # simulator, or incorporate into any existing library setup.
# #
# # Run Quartus-generated IP simulation script once to compile Quartus EDA
# # simulation libraries and Quartus-generated IP simulation files, and copy
# # any ROM/RAM initialization files to the simulation directory.
# #
# # - If necessary, specify any compilation options:
# #   USER_DEFINED_COMPILE_OPTIONS
# #   USER_DEFINED_VHDL_COMPILE_OPTIONS applied to vhdl compiler
# #   USER_DEFINED_VERILOG_COMPILE_OPTIONS applied to verilog compiler
# #
# source <script generation output directory>/synopsys/vcsmx/vcsmx_setup.sh \
# SKIP_ELAB=1 \
# SKIP_SIM=1 \
# USER_DEFINED_COMPILE_OPTIONS=<compilation options for your design> \
# USER_DEFINED_VHDL_COMPILE_OPTIONS=<VHDL compilation options for your design> \
# USER_DEFINED_VERILOG_COMPILE_OPTIONS=<Verilog compilation options for your design> \
# QSYS_SIMDIR=<script generation output directory>
# #
# # Compile all design files and testbench files, including the top level.
# # (These are all the files required for simulation other than the files
# # compiled by the IP script)
# #
# vlogan <compilation options> <design and testbench files>
# #
# # TOP_LEVEL_NAME is used in this script to set the top-level simulation or
# # testbench module/entity name.
# #
# # Run the IP script again to elaborate and simulate the top level:
# # - Specify TOP_LEVEL_NAME and USER_DEFINED_ELAB_OPTIONS.
# # - Override the default USER_DEFINED_SIM_OPTIONS. For example, to run
# #   until $finish(), set to an empty string: USER_DEFINED_SIM_OPTIONS="".
# #
# source <script generation output directory>/synopsys/vcsmx/vcsmx_setup.sh \
# SKIP_FILE_COPY=1 \
# SKIP_DEV_COM=1 \
# SKIP_COM=1 \
# TOP_LEVEL_NAME="'-top <simulation top>'" \
# QSYS_SIMDIR=<script generation output directory> \
# USER_DEFINED_ELAB_OPTIONS=<elaboration options for your design> \
# USER_DEFINED_SIM_OPTIONS=<simulation options for your design>
# #
# # TOP-LEVEL TEMPLATE - END
# ----------------------------------------
# 
# IP SIMULATION SCRIPT
# ----------------------------------------
# If SistemaEmbarcado_tb is one of several IP cores in your
# Quartus project, you can generate a simulation script
# suitable for inclusion in your top-level simulation
# script by running the following command line:
# 
# ip-setup-simulation --quartus-project=<quartus project>
# 
# ip-setup-simulation will discover the Altera IP
# within the Quartus project, and generate a unified
# script which supports all the Altera IP within the design.
# ----------------------------------------
# ACDS 18.1 625 win32 2023.07.18.18:22:15
# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="SistemaEmbarcado_tb"
QSYS_SIMDIR="./../../"
QUARTUS_INSTALL_DIR="C:/intelfpga_lite/18.1/quartus/"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="+vcs+finish+100"

# ----------------------------------------
# overwrite variables - DO NOT MODIFY!
# This block evaluates each command line argument, typically used for 
# overwriting variables. An example usage:
#   sh <simulator>_setup.sh SKIP_SIM=1
for expression in "$@"; do
  eval $expression
  if [ $? -ne 0 ]; then
    echo "Error: This command line argument, \"$expression\", is/has an invalid expression." >&2
    exit $?
  fi
done

# ----------------------------------------
# initialize simulation properties - DO NOT MODIFY!
ELAB_OPTIONS=""
SIM_OPTIONS=""
if [[ `vcs -platform` != *"amd64"* ]]; then
  :
else
  :
fi

# ----------------------------------------
# create compilation libraries
mkdir -p ./libraries/work/
mkdir -p ./libraries/altera_common_sv_packages/
mkdir -p ./libraries/error_adapter_0/
mkdir -p ./libraries/avalon_st_adapter/
mkdir -p ./libraries/rsp_mux_001/
mkdir -p ./libraries/rsp_mux/
mkdir -p ./libraries/rsp_demux/
mkdir -p ./libraries/cmd_mux_005/
mkdir -p ./libraries/cmd_mux/
mkdir -p ./libraries/cmd_demux_001/
mkdir -p ./libraries/cmd_demux/
mkdir -p ./libraries/router_007/
mkdir -p ./libraries/router_002/
mkdir -p ./libraries/router_001/
mkdir -p ./libraries/router/
mkdir -p ./libraries/MedidorDesempenho_Escrita_agent_rsp_fifo/
mkdir -p ./libraries/MedidorDesempenho_Escrita_agent/
mkdir -p ./libraries/Processador_data_master_agent/
mkdir -p ./libraries/MedidorDesempenho_Escrita_translator/
mkdir -p ./libraries/Processador_data_master_translator/
mkdir -p ./libraries/fpci_multi/
mkdir -p ./libraries/fpci_combi/
mkdir -p ./libraries/cpu/
mkdir -p ./libraries/rst_controller/
mkdir -p ./libraries/irq_mapper/
mkdir -p ./libraries/mm_interconnect_0/
mkdir -p ./libraries/Processador_custom_instruction_master_multi_xconnect/
mkdir -p ./libraries/Processador_custom_instruction_master_comb_slave_translator0/
mkdir -p ./libraries/Processador_custom_instruction_master_comb_xconnect/
mkdir -p ./libraries/Processador_custom_instruction_master_translator/
mkdir -p ./libraries/nios_custom_instr_floating_point_2_0/
mkdir -p ./libraries/jtag_uart/
mkdir -p ./libraries/Processador/
mkdir -p ./libraries/MemoriaPrograma/
mkdir -p ./libraries/MemoriaDados/
mkdir -p ./libraries/MedidorDesempenho/
mkdir -p ./libraries/InliersOutliers/
mkdir -p ./libraries/SistemaEmbarcado_inst_reset_bfm/
mkdir -p ./libraries/SistemaEmbarcado_inst_medidordesempenho_bfm/
mkdir -p ./libraries/SistemaEmbarcado_inst_clk_bfm/
mkdir -p ./libraries/SistemaEmbarcado_inst/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/altera_lnsim_ver/
mkdir -p ./libraries/cycloneive_ver/
mkdir -p ./libraries/altera/
mkdir -p ./libraries/lpm/
mkdir -p ./libraries/sgate/
mkdir -p ./libraries/altera_mf/
mkdir -p ./libraries/altera_lnsim/
mkdir -p ./libraries/cycloneive/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPSqrt/FPSqrt_memoryC0_uid59_sqrtTableGenerator_lutmem.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPSqrt/FPSqrt_memoryC1_uid60_sqrtTableGenerator_lutmem.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPSqrt/FPSqrt_memoryC2_uid61_sqrtTableGenerator_lutmem.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_ociram_default_contents.dat ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_ociram_default_contents.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_ociram_default_contents.mif ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_rf_ram_a.dat ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_rf_ram_a.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_rf_ram_a.mif ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_rf_ram_b.dat ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_rf_ram_b.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_rf_ram_b.mif ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_MemoriaPrograma.hex ./
  cp -f $QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_MemoriaDados.hex ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.v"              -work altera_ver      
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.v"                       -work lpm_ver         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.v"                          -work sgate_ver       
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.v"                      -work altera_mf_ver   
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"                  -work altera_lnsim_ver
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.v"               -work cycloneive_ver  
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_syn_attributes.vhd"        -work altera          
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_standard_functions.vhd"    -work altera          
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/alt_dspbuilder_package.vhd"       -work altera          
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_europa_support_lib.vhd"    -work altera          
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives_components.vhd" -work altera          
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.vhd"            -work altera          
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/220pack.vhd"                      -work lpm             
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.vhd"                     -work lpm             
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate_pack.vhd"                   -work sgate           
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.vhd"                        -work sgate           
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf_components.vhd"         -work altera_mf       
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.vhd"                    -work altera_mf       
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"                  -work altera_lnsim    
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim_components.vhd"      -work altera_lnsim    
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.vhd"             -work cycloneive      
  vhdlan $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS                   "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_components.vhd"        -work cycloneive      
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/verbosity_pkg.sv"                                                         -work altera_common_sv_packages                                   
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_avalon_st_adapter_error_adapter_0.sv"  -work error_adapter_0                                             
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_avalon_st_adapter.v"                   -work avalon_st_adapter                                           
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_rsp_mux_001.sv"                        -work rsp_mux_001                                                 
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                              -work rsp_mux_001                                                 
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_rsp_mux.sv"                            -work rsp_mux                                                     
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                              -work rsp_mux                                                     
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_rsp_demux.sv"                          -work rsp_demux                                                   
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_cmd_mux_005.sv"                        -work cmd_mux_005                                                 
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                              -work cmd_mux_005                                                 
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_cmd_mux.sv"                            -work cmd_mux                                                     
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                              -work cmd_mux                                                     
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_cmd_demux_001.sv"                      -work cmd_demux_001                                               
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_cmd_demux.sv"                          -work cmd_demux                                                   
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_router_007.sv"                         -work router_007                                                  
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_router_002.sv"                         -work router_002                                                  
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_router_001.sv"                         -work router_001                                                  
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0_router.sv"                             -work router                                                      
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_avalon_sc_fifo.v"                                                  -work MedidorDesempenho_Escrita_agent_rsp_fifo                    
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_slave_agent.sv"                                             -work MedidorDesempenho_Escrita_agent                             
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_burst_uncompressor.sv"                                      -work MedidorDesempenho_Escrita_agent                             
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_master_agent.sv"                                            -work Processador_data_master_agent                               
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_slave_translator.sv"                                        -work MedidorDesempenho_Escrita_translator                        
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_merlin_master_translator.sv"                                       -work Processador_data_master_translator                          
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/fpoint2_multi.vhd"                                                        -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/fpoint2_multi_datapath.vhd"                                               -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/fpoint2_multi_dspba_library_package.vhd"                                  -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/fpoint2_multi_dspba_library.vhd"                                          -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPAddSub/FPAddSub.vhd"                                                    -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPDiv/FPDiv.vhd"                                                          -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPMult/FPMult.vhd"                                                        -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/IntToFloat/IntToFloat.vhd"                                                -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FloatToInt/FloatToInt.vhd"                                                -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPSqrt/FPSqrt_safe_path.vhd"                                              -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPSqrt/FPSqrt.vhd"                                                        -work fpci_multi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/fpoint2_combi.vhd"                                                        -work fpci_combi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPMinMaxFused/FPMinMaxFused.vhd"                                          -work fpci_combi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPCompareFused/FPCompareFused.vhd"                                        -work fpci_combi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPNeg_Abs/FPNeg.vhd"                                                      -work fpci_combi                                                  
  vhdlan -xlrm $USER_DEFINED_VHDL_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS             "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/FPNeg_Abs/FPAbs.vhd"                                                      -work fpci_combi                                                  
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu.v"                                       -work cpu                                                         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_debug_slave_sysclk.v"                    -work cpu                                                         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_debug_slave_tck.v"                       -work cpu                                                         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_debug_slave_wrapper.v"                   -work cpu                                                         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_cpu_test_bench.v"                            -work cpu                                                         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_reset_controller.v"                                                -work rst_controller                                              
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_reset_synchronizer.v"                                              -work rst_controller                                              
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_irq_mapper.sv"                                           -work irq_mapper                                                  
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_mm_interconnect_0.v"                                     -work mm_interconnect_0                                           
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_custom_instruction_master_multi_xconnect.sv" -work Processador_custom_instruction_master_multi_xconnect        
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_customins_slave_translator.sv"                                     -work Processador_custom_instruction_master_comb_slave_translator0
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador_custom_instruction_master_comb_xconnect.sv"  -work Processador_custom_instruction_master_comb_xconnect         
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_customins_master_translator.v"                                     -work Processador_custom_instruction_master_translator            
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_nios_custom_instr_floating_point_2_0.v"                  -work nios_custom_instr_floating_point_2_0                        
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_jtag_uart.v"                                             -work jtag_uart                                                   
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_Processador.v"                                           -work Processador                                                 
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_MemoriaPrograma.v"                                       -work MemoriaPrograma                                             
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado_MemoriaDados.v"                                          -work MemoriaDados                                                
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/Clock_Counter.v"                                                          -work MedidorDesempenho                                           
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/Clock_Counter_Interface.v"                                                -work MedidorDesempenho                                           
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/Inliers_Check.v"                                                          -work InliersOutliers                                             
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/Inliers_Interface.v"                                                      -work InliersOutliers                                             
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_avalon_reset_source.sv"                                            -work SistemaEmbarcado_inst_reset_bfm                             
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_conduit_bfm.sv"                                                    -work SistemaEmbarcado_inst_medidordesempenho_bfm                 
  vlogan +v2k -sverilog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/altera_avalon_clock_source.sv"                                            -work SistemaEmbarcado_inst_clk_bfm                               
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/submodules/SistemaEmbarcado.v"                                                       -work SistemaEmbarcado_inst                                       
  vlogan +v2k $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS           "$QSYS_SIMDIR/SistemaEmbarcado_tb/simulation/SistemaEmbarcado_tb.v"                                                                                                                                 
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  vcs -lca -t ps $ELAB_OPTIONS $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  ./simv $SIM_OPTIONS $USER_DEFINED_SIM_OPTIONS
fi