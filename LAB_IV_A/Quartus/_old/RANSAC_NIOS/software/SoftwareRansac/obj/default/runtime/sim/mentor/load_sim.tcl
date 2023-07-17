# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force C:/LAB_IV_A/Quartus/RANSAC_NIOS/software/SoftwareRansac/mem_init/hdl_sim/SistemaEmbarcadoRansac_MemoriaDados.dat ./ 
file copy -force C:/LAB_IV_A/Quartus/RANSAC_NIOS/software/SoftwareRansac/mem_init/hdl_sim/SistemaEmbarcadoRansac_MemoriaPrograma.dat ./ 
file copy -force C:/LAB_IV_A/Quartus/RANSAC_NIOS/software/SoftwareRansac/mem_init/SistemaEmbarcadoRansac_MemoriaDados.hex ./ 
file copy -force C:/LAB_IV_A/Quartus/RANSAC_NIOS/software/SoftwareRansac/mem_init/SistemaEmbarcadoRansac_MemoriaPrograma.hex ./ 
