module Inliers_Check(scale_factor, line_a, line_b, x, y, threshold, inlier_out);


input [31:0] scale_factor, line_a, line_b, x, y, threshold;

wire [31:0] term1, term2;

output inlier_out;

assign term1 = line_a * x - y * scale_factor + line_b * scale_factor;

assign term2 = line_a * line_a + scale_factor * scale_factor;

assign inlier_out = term1 * term1 / term2 <= threshold ? 1'b1 : 1'b0;


endmodule