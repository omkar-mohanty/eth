#include<exception>
#include<iostream>
import ETH.RPC;
int main() {
	using RPC = ETH::RPC::RPC;
	try {
		RPC rpc("127.0.0.1", "8545");
		std::cout<<"Client Version: " << rpc.Web3ClientVersion() << "\n";
		std::cout <<"Sha3: " << rpc.Web3Sha3("0x68656c6c6f20776f726c64")<<"\n";
		std::cout << "Net Version: " << rpc.NetVersion() << "\n";
		std::cout << "Net Listening: " << rpc.NetListening() << "\n";
		std::cout << "Net PeerCount: " << rpc.NetPeerCount() << "\n";
		std::cout << "ETH ProtocolVersion: " << rpc.EthProtocolVersion() << "\n";
		std::cout << "ETH Syncing: " << rpc.EthSyncing() << "\n";
		std::cout << "ETH Coinbase: " << rpc.EthCoinbase() << "\n";
		std::cout << "ETH Mining: " << rpc.EthMining() << "\n";
		std::cout << "ETH HashRate: " << rpc.EthHashRate() << "\n";
		std::cout << "ETH GasPrice: " << rpc.EthGasPrice() << "\n";
		std::cout << "ETH Accounts: " << rpc.EthAccounts() << "\n";
		std::cout << "ETH getBalance" << rpc.EthGetBalance("0x976ea74026e726554db657fa54763abd0c3a0aa9")<<"\n";
		std::cout << "ETH Transaction Count: " << rpc.EthGetTransactionCount("0x976ea74026e726554db657fa54763abd0c3a0aa9")<<"\n";
	}catch(std::exception &e){
		std::cout << e.what();
	}
}