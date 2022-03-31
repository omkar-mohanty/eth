module;
#include<boost/beast/core.hpp>
#include<boost/beast/http.hpp>
#include<boost/beast/version.hpp>
#include<boost/asio/connect.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/json.hpp>
#include<iostream>
#include<memory>
#include<string>
export module ETH.RPC:ImplRPC;
import ETH.Types;


enum class RPCMethod
{

};

export namespace ETH::RPC {


	namespace net = boost::asio;
	namespace beast = boost::beast;
	namespace http = beast::http;
	namespace json = boost::json;

	using BlockInformation = ETH::Types::BlockInformation;
	using tcp = net::ip::tcp;


	class RPC{
	private:
	json::object prepareJsonBody();
	inline std::string to_string(beast::flat_buffer const&);
	public:
		RPC(std::string,std::string);
		BlockInformation GetBlockByHash(std::string);
		std::string ClientVersion();
		~RPC() {}
	private:
		std::string ip_address;
		std::string port;
		net::io_context io_context;
		std::unique_ptr<beast::tcp_stream> stream;
		std::unique_ptr<tcp::resolver> resolver;
		
	};
	

	json::object RPC::prepareJsonBody()
	{
		json::object jsonBody;
		jsonBody["jsonrpc"] = "2.0";
		jsonBody["method"] = "web3_clientVersion";
		jsonBody["params"] = json::array{};
		jsonBody["id"] = 1;
		return jsonBody;
	}

	inline std::string RPC::to_string(beast::flat_buffer const& buffer)
	{
		return std::string(boost::asio::buffer_cast<char const*>(
			beast::buffers_front(buffer.data())),
			boost::asio::buffer_size(buffer.data()));
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

	std::string RPC::ClientVersion()
	{
		auto const results = resolver->resolve(ip_address, port);

		//connect to the server
		stream->connect(results);

		//get json body
		json::object jsonBody = prepareJsonBody();
		std::string serealizedBody = json::serialize(jsonBody);

		//build request
		http::request<http::string_body> req{ http::verb::post,port,11};
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
		
		std::string result = res.body();
		
		return result;
	}
}