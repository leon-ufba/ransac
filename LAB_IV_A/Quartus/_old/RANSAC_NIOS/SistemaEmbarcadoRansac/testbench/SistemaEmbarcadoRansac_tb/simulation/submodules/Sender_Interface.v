module Sender_Interface (clock, reset_n, write, writedata, read, readdata, data_export);

input clock, reset_n, write, read;
input [31:0] writedata;
output [31:0] readdata, data_export;

wire [31:0] data;

Sender sender (.clock(clock), .reset_n(reset_n), .enable(write), .data_in(writedata), .data_out(data));

assign readdata = data;
assign data_export = data;

endmodule
