# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force C:/Users/Eduardo/Documents/UFBA/2023.1/ENGG57/25.06.23/ransac-ransac_v2_review/ransac-ransac_v2_review/hardware/Quartus/software/TesteRANSAC/mem_init/hdl_sim/RANSAC_NIOS_memoria.dat ./ 
file copy -force C:/Users/Eduardo/Documents/UFBA/2023.1/ENGG57/25.06.23/ransac-ransac_v2_review/ransac-ransac_v2_review/hardware/Quartus/software/TesteRANSAC/mem_init/hdl_sim/MemoriaDados.dat ./ 
file copy -force C:/Users/Eduardo/Documents/UFBA/2023.1/ENGG57/25.06.23/ransac-ransac_v2_review/ransac-ransac_v2_review/hardware/Quartus/software/TesteRANSAC/mem_init/RANSAC_NIOS_memoria.hex ./ 
file copy -force C:/Users/Eduardo/Documents/UFBA/2023.1/ENGG57/25.06.23/ransac-ransac_v2_review/ransac-ransac_v2_review/hardware/Quartus/software/TesteRANSAC/mem_init/MemoriaDados.hex ./ 
