onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -divider Medidor
add wave -noupdate -radix binary /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/clk
add wave -noupdate -radix binary /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/reset_n
add wave -noupdate -radix binary /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/write
add wave -noupdate -radix binary /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/read
add wave -noupdate -radix unsigned /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/writedata
add wave -noupdate -radix unsigned /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/clk_count
add wave -noupdate -radix unsigned /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/readdata
add wave -noupdate -radix unsigned /SistemaEmbarcado_tb/sistemaembarcado_inst/medidordesempenho/data
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
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
WaveRestoreZoom {0 ps} {1 ns}
