`timescale 1ns/1ns

module RansacNiosTB;

reg	CLOCK_50;
reg	KEY;
reg	[31:0] receiver_data;
wire	[31:0] sender_data;
integer i;


RansacNios DUV(
	CLOCK_50,
	KEY,
	receiver_data,
	sender_data
);


always #10 CLOCK_50 = !CLOCK_50;

initial
begin
	CLOCK_50 = 0;
	KEY = 0;
	receiver_data = 32'b0;
	i = 32'b1;
	#100 KEY = 1;
	@ (posedge CLOCK_50);
	begin
		receiver_data = i;
		i = i+1;
	end

end


endmodule
