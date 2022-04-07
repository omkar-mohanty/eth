module;
#include<boost/beast/core.hpp>
#include<boost/beast/http.hpp>
#include<boost/beast/version.hpp>
#include<boost/asio/connect.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/json.hpp>
#include<utility>
#include<memory>
#include<string>



export module ETH.RPC:ImplRPC;
import ETH.Types;

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace json = boost::json;


using tcp = net::ip::tcp;
using BlockInformation = ETH::Types::BlockInformation;



enum class TAG {
	latest,
	earliest,
	pending
};

template<typename ...T>
json::array prepareParams(T... args) {
	return json::array{args...};
}


 constexpr std::string TagToString(TAG tag) {
	std::string result;
	switch (tag)
	{
	case TAG::latest:
		result = "latest";
		break;
	case TAG::earliest:
		result = "earliest";
		break;
	case TAG::pending:
		result = "pending";
		break;
	default:
		break;
	}
	return result;
}
enum class RPCMethod
{	
	//web3 methods
	web3_clientVersion,
	web3_sha3,

	//net methods
	net_version,
	net_listening,
	net_peerCount,

	//eth methods
	eth_protocolVersion,
	eth_syncing,
	eth_coinbase,
	eth_mining,
	eth_hashrate,
	eth_gasPrice,
	eth_accounts,
	eth_blockNumber,
	eth_getBalance,
	eth_getStorageAt,
	eth_getTransactionCount
};

export namespace ETH::RPC {


	class RPC{


	private:
	json::object prepareJsonBody(RPCMethod,json::array);
	constexpr std::string methodToString(RPCMethod);
	std::string makeRequest(std::string);
	inline void connectToServer();
	std::string prepareBody(RPCMethod, json::array);
	constexpr int methodId(RPCMethod);

	public:
		RPC(std::string,std::string);

		//Web3 RPC methods
		std::string Web3ClientVersion();
		std::string Web3Sha3(std::string);

		//Net RPC methods
		std::string NetListening();
		std::string NetVersion();
		std::string NetPeerCount();

		//Eth RPC methods
		std::string EthProtocolVersion();
		std::string EthSyncing();
		std::string EthCoinbase();
		std::string EthMining();
		std::string EthHashRate();
		std::string EthGasPrice();
		std::string EthAccounts();
		std::string EthBlockNumber();
		std::string EthGetBalance(std::string,TAG);
		std::string EthGetStorageAt(std::string, int, TAG);
		std::string EthGetTransactionCount(std::string,TAG);
		int EthGetBlockTransactionCountByHash(std::string);
		int EthGetBlockTransactionCountByNumber(unsigned long long);
		BlockInformation EthGetBlockByHash(std::string);


		~RPC() {}
	private:
		std::string ip_address;
		std::string port;
		net::io_context io_context;
		std::unique_ptr<beast::tcp_stream> stream;
		std::unique_ptr<tcp::resolver> resolver;
		
	};
	

	json::object RPC::prepareJsonBody(RPCMethod method,json::array params)
	{
		json::object jsonBody;
		jsonBody["jsonrpc"] = "2.0";
		jsonBody["method"] = methodToString(method);
		jsonBody["params"] = params;
		jsonBody["id"] = methodId(method);
		return jsonBody;
	}
	
	constexpr std::string RPC::methodToString(RPCMethod method)
	{
		std::string stringMethod;
		switch (method)
		{
		case RPCMethod::web3_clientVersion:
			stringMethod = "web3_clientVersion";
			break;
		case RPCMethod::web3_sha3:
			stringMethod = "web3_sha3";
			break;
		case RPCMethod::net_version:
			stringMethod = "net_version";
			break;
		case RPCMethod::net_listening:
			stringMethod = "net_listening";
			break;
		case RPCMethod::net_peerCount:
			stringMethod = "net_peerCount";
			break;
		case RPCMethod::eth_protocolVersion:
			stringMethod = "eth_protocolVersion";
			break;
		case RPCMethod::eth_syncing:
			stringMethod = "eth_syncing";
			break;
		case RPCMethod::eth_coinbase:
			stringMethod = "eth_coinbase";
			break;
		case RPCMethod::eth_mining:
			stringMethod = "eth_mining";
			break;
		case RPCMethod::eth_hashrate:
			stringMethod = "eth_hashrate";
			break;
		case RPCMethod::eth_gasPrice:
			stringMethod = "eth_gasPrice";
			break;
		case RPCMethod::eth_accounts:
			stringMethod = "eth_accounts";
			break;
		case RPCMethod::eth_blockNumber:
			stringMethod = "eth_blockNumber";
			break;
		case RPCMethod::eth_getBalance:
			stringMethod = "eth_getBalance";
			break;
		case RPCMethod::eth_getStorageAt:
			stringMethod = "eth_getStorageAt";
			break;
		case RPCMethod::eth_getTransactionCount:
			stringMethod = "eth_getTransactionCount";
			break;
		default:
			break;

		}
		return stringMethod;
	}

	std::string RPC::makeRequest(std::string serealizedBody)
	{
		connectToServer();
		http::request<http::string_body> req{ http::verb::post,port,11 };
		req.target("/");
		req.set(beast::http::field::content_type, "application/json");
		req.body() = serealizedBody;
		req.prepare_payload();

		//making request
		http::write(*stream.get(), req);

		//declaring buffers
		beast::flat_buffer buffer;

		//container to hold response
		http::response<http::string_body> res;

		// Receive the HTTP response
		http::read(*stream.get(), buffer, res);

		return std::move(res.body());
	}

	inline void RPC::connectToServer()
	{
		auto const results = resolver->resolve(ip_address, port);

		//connect to the server
		stream->connect(results);

	}

	std::string RPC::prepareBody(RPCMethod method, json::array params=json::array{})
	{
		//get json body
		json::object jsonBody = prepareJsonBody(method, params);
		return std::move(json::serialize(jsonBody));
	}

	constexpr int RPC::methodId(RPCMethod method)
	{
		int id=1;
		switch (method)
		{
		case RPCMethod::web3_clientVersion:
		case RPCMethod::eth_syncing:
		case RPCMethod::eth_accounts:
		case RPCMethod::eth_getBalance:
		case RPCMethod::eth_getStorageAt:
		case RPCMethod::eth_getTransactionCount:
			id = 1;
			break;
		case RPCMethod::web3_sha3:
		case RPCMethod::eth_coinbase:
			id = 64;
			break;
		case RPCMethod::net_version:
		case RPCMethod::net_listening:
		case RPCMethod::eth_protocolVersion:
			id = 67;
			break;
		case RPCMethod::eth_mining:
		case RPCMethod::eth_hashrate:
			id = 71;
			break;
		case RPCMethod::eth_gasPrice:
			id = 73;
			break;
		case RPCMethod::net_peerCount:
			id = 74;
			break;
		case RPCMethod::eth_blockNumber:
			id = 83;
			break;
		default:
			break;
		}
		return id;
	}

	

	RPC::RPC(std::string ip, std::string port):ip_address{ip},port{port}
	{
		stream = std::make_unique<beast::tcp_stream>(io_context);
		resolver = std::make_unique<tcp::resolver>(io_context);
	}


	std::string RPC::Web3ClientVersion()
	{
		
		//prepare params
		std::string serealizedBody = prepareBody(RPCMethod::web3_clientVersion);

		return makeRequest(serealizedBody);
	}
	std::string RPC::Web3Sha3(std::string data)
	{

		json::array params = prepareParams(data);

		std::string serealizedBody = prepareBody(RPCMethod::web3_sha3,params);

		return makeRequest(serealizedBody);
	}
	std::string RPC::NetListening()
	{

		std::string serealizedBody = prepareBody(RPCMethod::net_listening);

		return makeRequest(serealizedBody);
	}
	std::string RPC::NetVersion()
	{

		std::string serealizedBody = prepareBody(RPCMethod::net_version);

		return makeRequest(serealizedBody);
	}
	std::string RPC::NetPeerCount()
	{

		std::string serealizedBody = prepareBody(RPCMethod::net_peerCount);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthProtocolVersion()
	{

		std::string serealizedBody = prepareBody(RPCMethod::eth_protocolVersion);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthSyncing()
	{

		std::string serealizedBody = prepareBody(RPCMethod::eth_syncing);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthCoinbase()
	{

		std::string serealizedBody = prepareBody(RPCMethod::eth_coinbase);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthMining()
	{

		std::string serealizedBody = prepareBody(RPCMethod::eth_mining);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthHashRate()
	{

		std::string serealizedBody = prepareBody(RPCMethod::eth_hashrate);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthGasPrice()
	{
		std::string serealizedBody = prepareBody(RPCMethod::eth_gasPrice);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthAccounts()
	{
		std::string serealizedBody = prepareBody(RPCMethod::eth_accounts);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthBlockNumber()
	{
		std::string serealizedBody = prepareBody(RPCMethod::eth_blockNumber);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthGetBalance(std::string address,TAG tag=TAG::latest)
	{
		auto params = prepareParams(address, TagToString(tag));

		std::string serealizedBody = prepareBody(RPCMethod::eth_getBalance, params);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthGetStorageAt(std::string data, int quantity, TAG tag=TAG::latest)
	{
		auto params = prepareParams(data, quantity, TagToString(tag));

		auto serealizedBody = prepareBody(RPCMethod::eth_getStorageAt, params);

		return makeRequest(serealizedBody);
	}
	std::string RPC::EthGetTransactionCount(std::string data, TAG tag = TAG::latest)
	{
		auto params = prepareParams(data, TagToString(tag));

		auto serealizedBody = prepareBody(RPCMethod::eth_getTransactionCount,params);

		return makeRequest(serealizedBody);
	}
	
}

