	component SistemaEmbarcadoRansac is
		port (
			clk_clk                 : in  std_logic                     := 'X';             -- clk
			reset_reset_n           : in  std_logic                     := 'X';             -- reset_n
			sender_conduit_readdata : out std_logic_vector(31 downto 0);                    -- readdata
			parallel_data_in_export : in  std_logic_vector(31 downto 0) := (others => 'X')  -- export
		);
	end component SistemaEmbarcadoRansac;

	u0 : component SistemaEmbarcadoRansac
		port map (
			clk_clk                 => CONNECTED_TO_clk_clk,                 --              clk.clk
			reset_reset_n           => CONNECTED_TO_reset_reset_n,           --            reset.reset_n
			sender_conduit_readdata => CONNECTED_TO_sender_conduit_readdata, --   sender_conduit.readdata
			parallel_data_in_export => CONNECTED_TO_parallel_data_in_export  -- parallel_data_in.export
		);

