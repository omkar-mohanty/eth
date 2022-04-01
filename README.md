# ETH
This is a ethereum RPC library written in c++20.

## Usage
### Creating an instance
```c++
//Assuming a client like geth or a test client like hardhat is running.
import ETH.RPC;
int main()
{
	using RPC = ETH::RPC::RPC;
	//creating an rpc instance connecting to localhost on port 8545
	RPC rpc("127.0.0.1", "8545");
}
```
### Web3 methods
```c++
//returns the client version
rpc.Web3ClientVersion();

//returns the sha3 of a given input
rpc.Web3Sha3();
```
