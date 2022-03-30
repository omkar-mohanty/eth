export module ETH.RPC:IRPC;
import ETH.Types;
export namespace ETH::RPC {
	using IBlockInformation = ETH::Types::IBlockInformation;
	class IRPC
	{
	public:
		virtual ~IRPC();
		virtual IBlockInformation GetBlockByHash()=0;
	private:

	};

}