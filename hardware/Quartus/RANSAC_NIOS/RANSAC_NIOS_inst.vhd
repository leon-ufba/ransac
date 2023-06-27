	component RANSAC_NIOS is
		port (
			clk_clk                            : in  std_logic                     := 'X'; -- clk
			reset_reset_n                      : in  std_logic                     := 'X'; -- reset_n
			medidordesempenho_conduit_readdata : out std_logic_vector(31 downto 0)         -- readdata
		);
	end component RANSAC_NIOS;

	u0 : component RANSAC_NIOS
		port map (
			clk_clk                            => CONNECTED_TO_clk_clk,                            --                       clk.clk
			reset_reset_n                      => CONNECTED_TO_reset_reset_n,                      --                     reset.reset_n
			medidordesempenho_conduit_readdata => CONNECTED_TO_medidordesempenho_conduit_readdata  -- medidordesempenho_conduit.readdata
		);

