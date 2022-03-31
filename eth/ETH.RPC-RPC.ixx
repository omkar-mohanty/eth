module;
#include<boost/beast/core.hpp>
#include<boost/beast/http.hpp>
#include<boost/beast/version.hpp>
#include<boost/asio/connect.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<iostream>
#include<memory>
#include<string>
export module ETH.RPC:ImplRPC;
import ETH.Types;


export namespace ETH::RPC {


	namespace net = boost::asio;
	namespace beast = boost::beast;
	namespace http = beast::http;


	using BlockInformation = ETH::Types::BlockInformation;
	using tcp = net::ip::tcp;


	class RPC{
	public:
		RPC(std::string,size_t);
		BlockInformation GetBlockByHash(std::string);
		std::string ClientVersion();
		~RPC() {}
	private:
		std::string ip_address;
		std::unique_ptr<beast::tcp_stream> stream;
		net::io_context io_context;
	};
	

	RPC::RPC(std::string ip, size_t port):ip_address{ip}
	{
		stream = std::make_unique<beast::tcp_stream>(io_context);
	}

	BlockInformation RPC::GetBlockByHash(std::string hash)
	{
		return BlockInformation();
	}

	std::string RPC::ClientVersion()
	{
		try
		{
			tcp::resolver resolver(io_context);
			auto const results = resolver.resolve(ip_address,"8545");
			
			stream->connect(results);
			
			http::request<http::string_body> req{ http::verb::post,"8545",1};
			req.set(http::field::host, ip_address);
			req.set("Content-Type", "application/json");
			req.prepare_payload();
			std::cout << req;
		}
		catch (const std::exception&)
		{

		}
		return std::string();
	}


}