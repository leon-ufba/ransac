
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

# ACDS 18.1 625 win32 2023.06.26.13:59:12

# ----------------------------------------
# ncsim - auto-generated simulation script

# ----------------------------------------
# This script provides commands to simulate the following IP detected in
# your Quartus project:
#     RANSAC_NIOS_tb
# 
# Altera recommends that you source this Quartus-generated IP simulation
# script from your own customized top-level script, and avoid editing this
# generated script.
# 
# To write a top-level shell script that compiles Altera simulation libraries
# and the Quartus-generated IP in your project, along with your design and
# testbench files, copy the text from the TOP-LEVEL TEMPLATE section below
# into a new file, e.g. named "ncsim.sh", and modify text as directed.
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
# # the simulator. In this case, you must also copy the generated files
# # "cds.lib" and "hdl.var" - plus the directory "cds_libs" if generated - 
# # into the location from which you launch the simulator, or incorporate
# # into any existing library setup.
# #
# # Run Quartus-generated IP simulation script once to compile Quartus EDA
# # simulation libraries and Quartus-generated IP simulation files, and copy
# # any ROM/RAM initialization files to the simulation directory.
# # - If necessary, specify any compilation options:
# #   USER_DEFINED_COMPILE_OPTIONS
# #   USER_DEFINED_VHDL_COMPILE_OPTIONS applied to vhdl compiler
# #   USER_DEFINED_VERILOG_COMPILE_OPTIONS applied to verilog compiler
# #
# source <script generation output directory>/cadence/ncsim_setup.sh \
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
# ncvlog <compilation options> <design and testbench files>
# #
# # TOP_LEVEL_NAME is used in this script to set the top-level simulation or
# # testbench module/entity name.
# #
# # Run the IP script again to elaborate and simulate the top level:
# # - Specify TOP_LEVEL_NAME and USER_DEFINED_ELAB_OPTIONS.
# # - Override the default USER_DEFINED_SIM_OPTIONS. For example, to run
# #   until $finish(), set to an empty string: USER_DEFINED_SIM_OPTIONS="".
# #
# source <script generation output directory>/cadence/ncsim_setup.sh \
# SKIP_FILE_COPY=1 \
# SKIP_DEV_COM=1 \
# SKIP_COM=1 \
# TOP_LEVEL_NAME=<simulation top> \
# USER_DEFINED_ELAB_OPTIONS=<elaboration options for your design> \
# USER_DEFINED_SIM_OPTIONS=<simulation options for your design>
# #
# # TOP-LEVEL TEMPLATE - END
# ----------------------------------------
# 
# IP SIMULATION SCRIPT
# ----------------------------------------
# If RANSAC_NIOS_tb is one of several IP cores in your
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
# ACDS 18.1 625 win32 2023.06.26.13:59:12
# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="RANSAC_NIOS_tb"
QSYS_SIMDIR="./../"
QUARTUS_INSTALL_DIR="C:/intelfpga_lite/18.1/quartus/"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="-input \"@run 100; exit\""

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
if [[ `ncsim -version` != *"ncsim(64)"* ]]; then
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
mkdir -p ./libraries/cmd_mux_003/
mkdir -p ./libraries/cmd_mux/
mkdir -p ./libraries/cmd_demux_001/
mkdir -p ./libraries/cmd_demux/
mkdir -p ./libraries/router_005/
mkdir -p ./libraries/router_002/
mkdir -p ./libraries/router_001/
mkdir -p ./libraries/router/
mkdir -p ./libraries/MedidorDesempenho_Escrita_agent_rsp_fifo/
mkdir -p ./libraries/MedidorDesempenho_Escrita_agent/
mkdir -p ./libraries/Processador_data_master_agent/
mkdir -p ./libraries/MedidorDesempenho_Escrita_translator/
mkdir -p ./libraries/Processador_data_master_translator/
mkdir -p ./libraries/rst_controller/
mkdir -p ./libraries/irq_mapper/
mkdir -p ./libraries/mm_interconnect_0/
mkdir -p ./libraries/memoria_dados/
mkdir -p ./libraries/memoria/
mkdir -p ./libraries/jtag/
mkdir -p ./libraries/Processador/
mkdir -p ./libraries/MedidorDesempenho/
mkdir -p ./libraries/RANSAC_NIOS_inst_reset_bfm/
mkdir -p ./libraries/RANSAC_NIOS_inst_medidordesempenho_conduit_bfm/
mkdir -p ./libraries/RANSAC_NIOS_inst_clk_bfm/
mkdir -p ./libraries/RANSAC_NIOS_inst/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/altera_lnsim_ver/
mkdir -p ./libraries/cycloneive_ver/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_memoria.hex ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_ociram_default_contents.dat ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_ociram_default_contents.hex ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_ociram_default_contents.mif ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_rf_ram_a.dat ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_rf_ram_a.hex ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_rf_ram_a.mif ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_rf_ram_b.dat ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_rf_ram_b.hex ./
  cp -f $QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_rf_ram_b.mif ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.v" -work altera_ver      
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.v"          -work lpm_ver         
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.v"             -work sgate_ver       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.v"         -work altera_mf_ver   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"     -work altera_lnsim_ver
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cycloneive_atoms.v"  -work cycloneive_ver  
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/verbosity_pkg.sv"                                                   -work altera_common_sv_packages                      -cdslib ./cds_libs/altera_common_sv_packages.cds.lib                     
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_avalon_st_adapter_error_adapter_0.sv" -work error_adapter_0                                -cdslib ./cds_libs/error_adapter_0.cds.lib                               
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_avalon_st_adapter.v"                  -work avalon_st_adapter                              -cdslib ./cds_libs/avalon_st_adapter.cds.lib                             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_rsp_mux_001.sv"                       -work rsp_mux_001                                    -cdslib ./cds_libs/rsp_mux_001.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                        -work rsp_mux_001                                    -cdslib ./cds_libs/rsp_mux_001.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_rsp_mux.sv"                           -work rsp_mux                                        -cdslib ./cds_libs/rsp_mux.cds.lib                                       
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                        -work rsp_mux                                        -cdslib ./cds_libs/rsp_mux.cds.lib                                       
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_rsp_demux.sv"                         -work rsp_demux                                      -cdslib ./cds_libs/rsp_demux.cds.lib                                     
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_cmd_mux_003.sv"                       -work cmd_mux_003                                    -cdslib ./cds_libs/cmd_mux_003.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                        -work cmd_mux_003                                    -cdslib ./cds_libs/cmd_mux_003.cds.lib                                   
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_cmd_mux.sv"                           -work cmd_mux                                        -cdslib ./cds_libs/cmd_mux.cds.lib                                       
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_arbitrator.sv"                                        -work cmd_mux                                        -cdslib ./cds_libs/cmd_mux.cds.lib                                       
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_cmd_demux_001.sv"                     -work cmd_demux_001                                  -cdslib ./cds_libs/cmd_demux_001.cds.lib                                 
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_cmd_demux.sv"                         -work cmd_demux                                      -cdslib ./cds_libs/cmd_demux.cds.lib                                     
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_router_005.sv"                        -work router_005                                     -cdslib ./cds_libs/router_005.cds.lib                                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_router_002.sv"                        -work router_002                                     -cdslib ./cds_libs/router_002.cds.lib                                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_router_001.sv"                        -work router_001                                     -cdslib ./cds_libs/router_001.cds.lib                                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0_router.sv"                            -work router                                         -cdslib ./cds_libs/router.cds.lib                                        
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_avalon_sc_fifo.v"                                            -work MedidorDesempenho_Escrita_agent_rsp_fifo       -cdslib ./cds_libs/MedidorDesempenho_Escrita_agent_rsp_fifo.cds.lib      
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_slave_agent.sv"                                       -work MedidorDesempenho_Escrita_agent                -cdslib ./cds_libs/MedidorDesempenho_Escrita_agent.cds.lib               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_burst_uncompressor.sv"                                -work MedidorDesempenho_Escrita_agent                -cdslib ./cds_libs/MedidorDesempenho_Escrita_agent.cds.lib               
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_master_agent.sv"                                      -work Processador_data_master_agent                  -cdslib ./cds_libs/Processador_data_master_agent.cds.lib                 
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_slave_translator.sv"                                  -work MedidorDesempenho_Escrita_translator           -cdslib ./cds_libs/MedidorDesempenho_Escrita_translator.cds.lib          
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_merlin_master_translator.sv"                                 -work Processador_data_master_translator             -cdslib ./cds_libs/Processador_data_master_translator.cds.lib            
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_reset_controller.v"                                          -work rst_controller                                 -cdslib ./cds_libs/rst_controller.cds.lib                                
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_reset_synchronizer.v"                                        -work rst_controller                                 -cdslib ./cds_libs/rst_controller.cds.lib                                
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_irq_mapper.sv"                                          -work irq_mapper                                     -cdslib ./cds_libs/irq_mapper.cds.lib                                    
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_mm_interconnect_0.v"                                    -work mm_interconnect_0                              -cdslib ./cds_libs/mm_interconnect_0.cds.lib                             
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_memoria_dados.v"                                        -work memoria_dados                                  -cdslib ./cds_libs/memoria_dados.cds.lib                                 
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_memoria.v"                                              -work memoria                                        -cdslib ./cds_libs/memoria.cds.lib                                       
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_jtag.v"                                                 -work jtag                                           -cdslib ./cds_libs/jtag.cds.lib                                          
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador.v"                                          -work Processador                                    -cdslib ./cds_libs/Processador.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_jtag_debug_module_sysclk.v"                 -work Processador                                    -cdslib ./cds_libs/Processador.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_jtag_debug_module_tck.v"                    -work Processador                                    -cdslib ./cds_libs/Processador.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_jtag_debug_module_wrapper.v"                -work Processador                                    -cdslib ./cds_libs/Processador.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_oci_test_bench.v"                           -work Processador                                    -cdslib ./cds_libs/Processador.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS_Processador_test_bench.v"                               -work Processador                                    -cdslib ./cds_libs/Processador.cds.lib                                   
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/Clock_Counter_Interface.v"                                          -work MedidorDesempenho                              -cdslib ./cds_libs/MedidorDesempenho.cds.lib                             
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/Clock_Counter.v"                                                    -work MedidorDesempenho                              -cdslib ./cds_libs/MedidorDesempenho.cds.lib                             
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_avalon_reset_source.sv"                                      -work RANSAC_NIOS_inst_reset_bfm                     -cdslib ./cds_libs/RANSAC_NIOS_inst_reset_bfm.cds.lib                    
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_conduit_bfm.sv"                                              -work RANSAC_NIOS_inst_medidordesempenho_conduit_bfm -cdslib ./cds_libs/RANSAC_NIOS_inst_medidordesempenho_conduit_bfm.cds.lib
  ncvlog -sv $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/altera_avalon_clock_source.sv"                                      -work RANSAC_NIOS_inst_clk_bfm                       -cdslib ./cds_libs/RANSAC_NIOS_inst_clk_bfm.cds.lib                      
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/submodules/RANSAC_NIOS.v"                                                      -work RANSAC_NIOS_inst                               -cdslib ./cds_libs/RANSAC_NIOS_inst.cds.lib                              
  ncvlog $USER_DEFINED_VERILOG_COMPILE_OPTIONS $USER_DEFINED_COMPILE_OPTIONS     "$QSYS_SIMDIR/RANSAC_NIOS_tb/simulation/RANSAC_NIOS_tb.v"                                                                                                                                                                                            
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  export GENERIC_PARAM_COMPAT_CHECK=1
  ncelab -access +w+r+c -namemap_mixgen $ELAB_OPTIONS $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  eval ncsim -licqueue $SIM_OPTIONS $USER_DEFINED_SIM_OPTIONS $TOP_LEVEL_NAME
fi
