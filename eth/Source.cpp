#include<exception>
#include<iostream>
import ETH.RPC;
int main() {
	using RPC = ETH::RPC::RPC;
	try {
		RPC rpc("127.0.0.1", "8545");
		std::cout<<rpc.ClientVersion();
	}catch(std::exception &e){
		std::cout << e.what();
	}
}