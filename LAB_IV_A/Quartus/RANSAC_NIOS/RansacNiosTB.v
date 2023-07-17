`timescale 1ns/1ns

module RansacNiosTB;

reg	CLOCK_50;
reg	[3:3] KEY;
wire	[31:0] medidordesempenho;


RansacNios DUV(
	CLOCK_50,
	KEY,
	medidordesempenho
);


always #10 CLOCK_50 = !CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY = 0;
end


endmodule
