import ETH.RPC;
int main() {
	using RPC = ETH::RPC::RPC;
	RPC rpc("127.0.0.1", 8545);
	rpc.ClientVersion();
}