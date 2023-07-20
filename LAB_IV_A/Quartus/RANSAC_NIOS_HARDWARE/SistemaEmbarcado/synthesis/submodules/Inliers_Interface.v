module Inliers_Interface(clk, reset_n, write, writedata, read, readdata, write_address);

input clk, reset_n, write, read;
input [31:0] writedata;
input [3:0] write_address;

output [31:0] readdata;

wire [31:0] inlier_out;

reg [31:0] scale_factor, line_a, line_b, x, y, threshold;

Inliers_Check inst (.scale_factor(scale_factor), .line_a(line_a), .line_b(line_b), .x(x), .y(y), .threshold(threshold), .inlier_out(inlier_out));

assign readdata = {31'h00000000, inlier_out};

always @(negedge clk) begin
        if (!reset_n) begin
            // Reset all variables to default values
            scale_factor <= 0;
            line_a <= 0;
            line_b <= 0;
            x <= 0;
            y <= 0;
            threshold <= 0;
        end 
		  else if (write) begin
            case (write_address)
                4'b0000: scale_factor <= writedata;
                4'b0001: line_a <= writedata;
                4'b0010: line_b <= writedata;
                4'b0011: x <= writedata;       
                4'b0100: y <= writedata;
                4'b0101: threshold <= writedata;
            endcase
        end
    end



endmodule