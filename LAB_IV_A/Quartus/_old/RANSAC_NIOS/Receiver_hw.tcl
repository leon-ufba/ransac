# TCL File Generated by Component Editor 18.1
# Tue Jun 27 21:23:14 BRT 2023
# DO NOT MODIFY


# 
# Receiver "Receiver" v1.0
#  2023.06.27.21:23:14
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module Receiver
# 
set_module_property DESCRIPTION ""
set_module_property NAME Receiver
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP Meus_Componentes
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME Receiver
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL Receiver_Interface
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file Receiver_Function.v VERILOG PATH Backup/Receiver_Function.v
add_fileset_file Receiver_Interface.v VERILOG PATH Backup/Receiver_Interface.v TOP_LEVEL_FILE

add_fileset SIM_VERILOG SIM_VERILOG "" ""
set_fileset_property SIM_VERILOG TOP_LEVEL Receiver_Interface
set_fileset_property SIM_VERILOG ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property SIM_VERILOG ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file Receiver_Function.v VERILOG PATH Backup/Receiver_Function.v
add_fileset_file Receiver_Interface.v VERILOG PATH Backup/Receiver_Interface.v


# 
# parameters
# 


# 
# display items
# 


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_n reset_n Input 1


# 
# connection point avalon_slave_read
# 
add_interface avalon_slave_read avalon end
set_interface_property avalon_slave_read addressUnits WORDS
set_interface_property avalon_slave_read associatedClock clock
set_interface_property avalon_slave_read associatedReset reset
set_interface_property avalon_slave_read bitsPerSymbol 8
set_interface_property avalon_slave_read burstOnBurstBoundariesOnly false
set_interface_property avalon_slave_read burstcountUnits WORDS
set_interface_property avalon_slave_read explicitAddressSpan 0
set_interface_property avalon_slave_read holdTime 0
set_interface_property avalon_slave_read linewrapBursts false
set_interface_property avalon_slave_read maximumPendingReadTransactions 0
set_interface_property avalon_slave_read maximumPendingWriteTransactions 0
set_interface_property avalon_slave_read readLatency 0
set_interface_property avalon_slave_read readWaitStates 0
set_interface_property avalon_slave_read readWaitTime 0
set_interface_property avalon_slave_read setupTime 0
set_interface_property avalon_slave_read timingUnits Cycles
set_interface_property avalon_slave_read writeWaitTime 0
set_interface_property avalon_slave_read ENABLED true
set_interface_property avalon_slave_read EXPORT_OF ""
set_interface_property avalon_slave_read PORT_NAME_MAP ""
set_interface_property avalon_slave_read CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave_read SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave_read read read Input 1
add_interface_port avalon_slave_read readdata readdata Output 32
set_interface_assignment avalon_slave_read embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave_read embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave_read embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave_read embeddedsw.configuration.isPrintableDevice 0


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clock clk Input 1


# 
# connection point conduit_receiver
# 
add_interface conduit_receiver conduit end
set_interface_property conduit_receiver associatedClock clock
set_interface_property conduit_receiver associatedReset reset
set_interface_property conduit_receiver ENABLED true
set_interface_property conduit_receiver EXPORT_OF ""
set_interface_property conduit_receiver PORT_NAME_MAP ""
set_interface_property conduit_receiver CMSIS_SVD_VARIABLES ""
set_interface_property conduit_receiver SVD_ADDRESS_GROUP ""

add_interface_port conduit_receiver writeEnable writeenable Input 1
add_interface_port conduit_receiver data_in data_in Input 32

