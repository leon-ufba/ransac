`timescale 1ns/1ns

module RansacNiosTB;

reg	CLOCK_50;
reg	KEY;



RansacNios DUV(
	CLOCK_50,
	KEY
);


always #10 CLOCK_50 = !CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY = 0;
end


endmodule
