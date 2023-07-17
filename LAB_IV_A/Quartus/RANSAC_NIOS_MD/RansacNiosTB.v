`timescale 1ns/1ns

module RansacNiosTB;

reg	CLOCK_50;
reg	[0:0] KEY;
wire	[31:0] medidordesempenho_conduit_readdata;


RansacNios DUV (CLOCK_50, KEY, medidordesempenho_conduit_readdata);

always #10 CLOCK_50 = ~CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY[0] = 0;
	#102 KEY[0] = 1;
end

endmodule
