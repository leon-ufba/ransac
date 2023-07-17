
module SistemaEmbarcadoRansac (
	clk_clk,
	reset_reset_n,
	sender_conduit_readdata,
	parallel_data_in_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[31:0]	sender_conduit_readdata;
	input	[31:0]	parallel_data_in_export;
endmodule
