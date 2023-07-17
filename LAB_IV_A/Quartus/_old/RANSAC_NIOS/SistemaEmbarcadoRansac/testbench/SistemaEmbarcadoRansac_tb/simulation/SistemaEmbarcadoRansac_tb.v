// SistemaEmbarcadoRansac_tb.v

// Generated using ACDS version 18.1 625

`timescale 1 ps / 1 ps
module SistemaEmbarcadoRansac_tb (
	);

	wire         sistemaembarcadoransac_inst_clk_bfm_clk_clk;                     // SistemaEmbarcadoRansac_inst_clk_bfm:clk -> [SistemaEmbarcadoRansac_inst:clk_clk, SistemaEmbarcadoRansac_inst_reset_bfm:clk, SistemaEmbarcadoRansac_inst_sender_conduit_bfm:clk]
	wire  [31:0] sistemaembarcadoransac_inst_parallel_data_in_bfm_conduit_export; // SistemaEmbarcadoRansac_inst_parallel_data_in_bfm:sig_export -> SistemaEmbarcadoRansac_inst:parallel_data_in_export
	wire  [31:0] sistemaembarcadoransac_inst_sender_conduit_readdata;             // SistemaEmbarcadoRansac_inst:sender_conduit_readdata -> SistemaEmbarcadoRansac_inst_sender_conduit_bfm:sig_readdata
	wire         sistemaembarcadoransac_inst_reset_bfm_reset_reset;               // SistemaEmbarcadoRansac_inst_reset_bfm:reset -> [SistemaEmbarcadoRansac_inst:reset_reset_n, SistemaEmbarcadoRansac_inst_sender_conduit_bfm:reset]

	SistemaEmbarcadoRansac sistemaembarcadoransac_inst (
		.clk_clk                 (sistemaembarcadoransac_inst_clk_bfm_clk_clk),                     //              clk.clk
		.parallel_data_in_export (sistemaembarcadoransac_inst_parallel_data_in_bfm_conduit_export), // parallel_data_in.export
		.reset_reset_n           (sistemaembarcadoransac_inst_reset_bfm_reset_reset),               //            reset.reset_n
		.sender_conduit_readdata (sistemaembarcadoransac_inst_sender_conduit_readdata)              //   sender_conduit.readdata
	);

	altera_avalon_clock_source #(
		.CLOCK_RATE (50000000),
		.CLOCK_UNIT (1)
	) sistemaembarcadoransac_inst_clk_bfm (
		.clk (sistemaembarcadoransac_inst_clk_bfm_clk_clk)  // clk.clk
	);

	altera_conduit_bfm sistemaembarcadoransac_inst_parallel_data_in_bfm (
		.sig_export (sistemaembarcadoransac_inst_parallel_data_in_bfm_conduit_export)  // conduit.export
	);

	altera_avalon_reset_source #(
		.ASSERT_HIGH_RESET    (0),
		.INITIAL_RESET_CYCLES (50)
	) sistemaembarcadoransac_inst_reset_bfm (
		.reset (sistemaembarcadoransac_inst_reset_bfm_reset_reset), // reset.reset_n
		.clk   (sistemaembarcadoransac_inst_clk_bfm_clk_clk)        //   clk.clk
	);

	altera_conduit_bfm_0002 sistemaembarcadoransac_inst_sender_conduit_bfm (
		.clk          (sistemaembarcadoransac_inst_clk_bfm_clk_clk),         //     clk.clk
		.reset        (~sistemaembarcadoransac_inst_reset_bfm_reset_reset),  //   reset.reset
		.sig_readdata (sistemaembarcadoransac_inst_sender_conduit_readdata)  // conduit.readdata
	);

endmodule
