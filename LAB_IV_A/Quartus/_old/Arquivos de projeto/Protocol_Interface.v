module Protocol_Interface (clock, reset_n, write, writedata, read, readdata, writeEnable, data_import, data_export);

input clock, reset_n, write, read, writeEnable;
input [31:0] writedata, data_import;
output [31:0] readdata, data_export;

wire [31:0] data;

Protocol sender (.clock(clock), .reset_n(reset_n), .enable(write), .data_in(writedata), .data_out(data));

Protocol receiver (.clock(clock), .reset_n(reset_n), .enable(writeEnable), .data_in(data_import), .data_out(data));

assign readdata = data;
assign data_export = data;

endmodule
