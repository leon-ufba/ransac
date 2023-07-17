`timescale 1ns/1ns

module RANSAC_NIOS_TB;

reg	CLOCK_50;
reg	KEY;
reg	[31:0] data_in;
wire	[31:0] data_out;
integer i;


RANSAC_NIOS DUV(
	CLOCK_50,
	data_in,
	KEY,
	data_out
);



always #10 CLOCK_50 = !CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY = 0;
	//write = 0;
	#100 KEY = 1;
	for (i = 0; i < 10; i = i + 1)
	begin
		@ (posedge CLOCK_50);
		data_in = i;
		//write = 1;
		//@ (posedge CLOCK_50);
		//write = 0;
	end
	#100 $stop;

end


endmodule
