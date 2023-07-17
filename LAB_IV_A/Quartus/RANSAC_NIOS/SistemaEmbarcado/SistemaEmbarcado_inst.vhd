	component SistemaEmbarcado is
		port (
			clk_clk                    : in  std_logic                     := 'X'; -- clk
			reset_reset_n              : in  std_logic                     := 'X'; -- reset_n
			medidordesempenho_readdata : out std_logic_vector(31 downto 0)         -- readdata
		);
	end component SistemaEmbarcado;

	u0 : component SistemaEmbarcado
		port map (
			clk_clk                    => CONNECTED_TO_clk_clk,                    --               clk.clk
			reset_reset_n              => CONNECTED_TO_reset_reset_n,              --             reset.reset_n
			medidordesempenho_readdata => CONNECTED_TO_medidordesempenho_readdata  -- medidordesempenho.readdata
		);

