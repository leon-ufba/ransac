# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force C:/ti/projetos/LAB4/ransac/hardware/Quartus/software/RansacSoftware/mem_init/hdl_sim/RANSAC_NIOS_memoria.dat ./ 
file copy -force C:/ti/projetos/LAB4/ransac/hardware/Quartus/software/RansacSoftware/mem_init/hdl_sim/MemoriaDados.dat ./ 
file copy -force C:/ti/projetos/LAB4/ransac/hardware/Quartus/software/RansacSoftware/mem_init/RANSAC_NIOS_memoria.hex ./ 
file copy -force C:/ti/projetos/LAB4/ransac/hardware/Quartus/software/RansacSoftware/mem_init/MemoriaDados.hex ./ 
