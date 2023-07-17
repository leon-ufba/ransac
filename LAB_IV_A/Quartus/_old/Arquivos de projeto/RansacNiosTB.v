`timescale 1ns/1ns

module RansacNiosTB;

reg	CLOCK_50;
reg	KEY;
wire	[31:0] data_out;


RansacNios DUV(
	CLOCK_50,
	KEY,
	data_out
);


always #10 CLOCK_50 = !CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY = 0;
	#100 KEY = 1;
end


endmodule
