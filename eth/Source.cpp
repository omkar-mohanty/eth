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
	}catch(std::exception &e){
		std::cout << e.what();
	}
}