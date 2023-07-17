module Receiver_Interface (clock, reset_n, read, readdata, writeEnable, data_in);

input clock, reset_n, read, writeEnable;
input [31:0] data_in;
output [31:0] readdata;

wire [31:0] data;

Protocol inst (.clock(clock), .reset_n(reset_n), .enable(writeEnable), .data_in(data_in), .data_out(data));

assign readdata = data;

endmodule
