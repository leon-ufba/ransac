`timescale 1ns/1ns

module RANSACNiosTB;

reg	CLOCK_50;
reg	[0:0] KEY;
wire	[31:0] medidordesempenho_conduit_readdata;

RANSACNios DUV(CLOCK_50, KEY,	medidordesempenho_conduit_readdata);

always #10 CLOCK_50 = ~CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY[0] = 0;
	//medidordesempenho_conduit_readdata = 0;
	#102 KEY[0] = 1;
end

endmodule
