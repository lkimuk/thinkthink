#pragma once
#include <boost/asio.hpp>

using namespace boost::asio;
using acceptor_type = ip::tcp::acceptor;
using endpoint_type = ip::tcp::endpoint;
using socket_type   = ip::tcp::socket;
using socket_ptr	= std::shared_ptr<socket_type>;


class VideoSession
	: public std::enable_shared_from_this<VideoSession>
{
	using this_type = VideoSession;
public:
	VideoSession(socket_ptr socket);

	void Start();

private:
	void AsyncReadMessage();

	void AsyncWriteMessage(const std::string& res);

	void DispatchMessage(const std::string& data);

private:


private:
	enum { max_length = 1024 };
	char m_data[max_length];
	socket_ptr m_socket;
};

struct ThinkThinkServer
{
	ThinkThinkServer(uint16_t port)
		: m_acceptor(m_io, endpoint_type(ip::tcp::v4(), port))
	{}

	void Accept();
	void Run();

private:
	io_context m_io;
	acceptor_type m_acceptor;
};

