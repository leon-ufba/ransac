onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix decimal /SistemaEmbarcado_tb/sistemaembarcado_inst/clk_clk
add wave -noupdate -radix decimal /SistemaEmbarcado_tb/sistemaembarcado_inst/reset_reset_n
add wave -noupdate -radix decimal /SistemaEmbarcado_tb/sistemaembarcado_inst/memoriadados/writedata
add wave -noupdate -radix decimal /SistemaEmbarcado_tb/sistemaembarcado_inst/memoriadados/readdata
add wave -noupdate -radix decimal /SistemaEmbarcado_tb/sistemaembarcado_inst/memoriadados/address
add wave -noupdate -radix decimal /SistemaEmbarcado_tb/sistemaembarcado_inst/memoriadados/wren
add wave -noupdate -radix float32 /SistemaEmbarcado_tb/sistemaembarcado_inst/nios_custom_instr_floating_point_2_0/s2_result
add wave -noupdate -radix float32 /SistemaEmbarcado_tb/sistemaembarcado_inst/nios_custom_instr_floating_point_2_0/s1_result
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {17695823069 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 1
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {17695602981 ps} {17696562690 ps}
