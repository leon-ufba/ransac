onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix unsigned /SistemaEmbarcadoRansac_tb/sistemaembarcadoransac_inst/clk_clk
add wave -noupdate -radix unsigned /SistemaEmbarcadoRansac_tb/sistemaembarcadoransac_inst/receiver_conduit_writeenable
add wave -noupdate -radix unsigned /SistemaEmbarcadoRansac_tb/sistemaembarcadoransac_inst/receiver_conduit_data_in
add wave -noupdate -radix unsigned /SistemaEmbarcadoRansac_tb/sistemaembarcadoransac_inst/reset_reset_n
add wave -noupdate -radix unsigned /SistemaEmbarcadoRansac_tb/sistemaembarcadoransac_inst/sender_conduit_readdata
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
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {1 ns}
