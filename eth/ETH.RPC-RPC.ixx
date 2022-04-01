module;
#include<boost/beast/core.hpp>
#include<boost/beast/http.hpp>
#include<boost/beast/version.hpp>
#include<boost/asio/connect.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/json.hpp>
#include<iostream>
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

template<typename ...T>
json::array prepareParams(T... args) {
	return json::array{args...};
}

enum class RPCMethod
{
	web3_clientVersion,
	web3_sha3,
	net_version,
	net_listening,
	net_peerCount
};

export namespace ETH::RPC {


	class RPC{


	private:
	json::object prepareJsonBody(RPCMethod,json::array);
	constexpr std::string methodToString(RPCMethod);
	std::string makeRequest(std::string);
	void connectToServer();
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


		BlockInformation GetBlockByHash(std::string);

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
		case RPCMethod::net_listening:
			stringMethod = "net_listening";
			break;
		case RPCMethod::net_peerCount:
			stringMethod = "net_peerCount";
			break;
		default:
			stringMethod = "web3_clientVersion";
			break;
		}
		return stringMethod;
	}

	std::string RPC::makeRequest(std::string serealizedBody)
	{
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

		return res.body();
	}

	void RPC::connectToServer()
	{
		auto const results = resolver->resolve(ip_address, port);

		//connect to the server
		stream->connect(results);

	}

	std::string RPC::prepareBody(RPCMethod method, json::array params=json::array{})
	{
		//get json body
		json::object jsonBody = prepareJsonBody(method, params);
		return json::serialize(jsonBody);
	}

	constexpr int RPC::methodId(RPCMethod method)
	{
		int id;
		switch (method)
		{
		case RPCMethod::web3_clientVersion:
			id = 1;
			break;
		case RPCMethod::web3_sha3:
			id = 64;
			break;
		case RPCMethod::net_version:
		case RPCMethod::net_listening:
			id = 67;
			break;
		case RPCMethod::net_peerCount:
			id = 74;
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

	BlockInformation RPC::GetBlockByHash(std::string hash)
	{
		return BlockInformation();
	}

	std::string RPC::Web3ClientVersion()
	{
		//Establish connection to server
		connectToServer();

		//prepare params

		std::string serealizedBody = prepareBody(RPCMethod::web3_clientVersion);

		return makeRequest(serealizedBody);
	}
	std::string RPC::Web3Sha3(std::string data)
	{
		connectToServer();

		json::array params = prepareParams(data);

		std::string serealizedBody = prepareBody(RPCMethod::web3_sha3,params);

		return makeRequest(serealizedBody);
	}
	std::string RPC::NetListening()
	{
		connectToServer();

		std::string serealizedBody = prepareBody(RPCMethod::net_listening);

		return makeRequest(serealizedBody);
	}
	std::string RPC::NetVersion()
	{
		connectToServer();

		std::string serealizedBody = prepareBody(RPCMethod::net_version);

		return makeRequest(serealizedBody);
	}
	std::string RPC::NetPeerCount()
	{
		connectToServer();

		std::string serealizedBody = prepareBody(RPCMethod::net_peerCount);

		return makeRequest(serealizedBody);
	}
}

