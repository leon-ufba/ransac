// Copyright (C) 2018  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details.

// PROGRAM		"Quartus Prime"
// VERSION		"Version 18.1.0 Build 625 09/12/2018 SJ Lite Edition"
// CREATED		"Wed Jun 28 01:26:03 2023"

module RANSAC_NIOS(
	CLOCK_50,
	data_in,
	KEY,
	data_out
);


input wire	CLOCK_50;
input wire	[31:0] data_in;
input wire	[0:0] KEY;
output wire	[31:0] data_out;






SistemaEmbarcadoRansac	b2v_inst(
	.clk_clk(CLOCK_50),
	.reset_reset_n(KEY),
	.parallel_data_in_export(data_in),
	.sender_conduit_readdata(data_out));


endmodule
